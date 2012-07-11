/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

package org.apache.harmony.luni.internal.net.www.protocol.http;

import java.io.BufferedInputStream;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.URI;
import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;
import libcore.base.Objects;
import org.apache.harmony.xnet.provider.jsse.OpenSSLSocketImpl;

/**
 * Holds the sockets and streams of an HTTP or HTTPS connection, which may be
 * used for multiple HTTP request/response exchanges. Connections may be direct
 * to the origin server or via a proxy. Create an instance using the {@link
 * Address} inner class.
 *
 * <p>Do not confuse this class with the misnamed {@code HttpURLConnection},
 * which isn't so much a connection as a single request/response pair.
 */
public final class HttpConnection {
    private final Address address;

    private final Socket socket;
    private InputStream inputStream;
    private OutputStream outputStream;

    private SSLSocket sslSocket;
    private InputStream sslInputStream;
    private OutputStream sslOutputStream;

    private HttpConnection(Address config, int connectTimeout) throws IOException {
        this.address = config;

        /*
         * Try each of the host's addresses for best behaviour in mixed IPv4/IPv6
         * environments. See http://b/2876927
         * TODO: add a hidden method so that Socket.tryAllAddresses can does this for us
         */
        Socket socketCandidate = null;
        InetAddress[] addresses = InetAddress.getAllByName(config.hostName);
        for (int i = 0; i < addresses.length; i++) {
            socketCandidate = (config.proxy != null && config.proxy.type() != Proxy.Type.HTTP)
                    ? new Socket(config.proxy)
                    : new Socket();
            try {
                socketCandidate.connect(
                        new InetSocketAddress(addresses[i], config.hostPort), connectTimeout);
                break;
            } catch (IOException e) {
                if (i == addresses.length - 1) {
                    throw e;
                }
            }
        }

        this.socket = socketCandidate;
    }

    public void closeSocketAndStreams() {
        closeQuietly(sslOutputStream);
        closeQuietly(sslInputStream);
        closeQuietly(sslSocket);
        closeQuietly(outputStream);
        closeQuietly(inputStream);
        closeQuietly(socket);
    }

    private void closeQuietly(Socket socket) {
        if (socket != null) {
            try {
                socket.close();
            } catch (Exception ignored) {
            }
        }
    }

    private void closeQuietly(Closeable closeable) {
        if (closeable != null) {
            try {
                closeable.close();
            } catch (Exception ignored) {
            }
        }
    }

    public void setSoTimeout(int readTimeout) throws SocketException {
        socket.setSoTimeout(readTimeout);
    }

    public OutputStream getOutputStream() throws IOException {
        if (sslSocket != null) {
            if (sslOutputStream == null) {
                sslOutputStream = sslSocket.getOutputStream();
            }
            return sslOutputStream;
        } else if(outputStream == null) {
            outputStream = socket.getOutputStream();
        }
        return outputStream;
    }

    public InputStream getInputStream() throws IOException {
        if (sslSocket != null) {
            if (sslInputStream == null) {
                sslInputStream = sslSocket.getInputStream();
            }
            return sslInputStream;
        } else if (inputStream == null) {
            /*
             * Buffer the socket stream to permit efficient parsing of HTTP
             * headers and chunk sizes. Benchmarks suggest 128 is sufficient.
             * We cannot buffer when setting up a tunnel because we may consume
             * bytes intended for the SSL socket.
             */
            int bufferSize = 128;
            inputStream = address.requiresTunnel
                    ? socket.getInputStream()
                    : new BufferedInputStream(socket.getInputStream(), bufferSize);
        }
        return inputStream;
    }

    private Socket getSocket() {
        return sslSocket != null ? sslSocket : socket;
    }

    public Address getAddress() {
        return address;
    }

    /**
     * Return an {@code SSLSocket} that is connected and passed hostname verification.
     *
     * @param sslSocketFactory Source of new {@code SSLSocket} instances.
     * @param hostnameVerifier Used to verify the hostname we
     * connected to is an acceptable match for the peer certificate
     * chain of the SSLSession.
     * @param tlsTolerant If true, assume server can handle common
     * TLS extensions and SSL deflate compression. If false, use
     * an SSL3 only fallback mode without compression.
     */
    public SSLSocket getSecureSocket(SSLSocketFactory sslSocketFactory,
            HostnameVerifier hostnameVerifier,
            boolean tlsTolerant) throws IOException {
        if (sslSocket == null) {
            // create the wrapper over connected socket
            SSLSocket unverifiedSocket = (SSLSocket) sslSocketFactory.createSocket(socket,
                    address.uri.getHost(), address.uri.getEffectivePort(), true /* autoClose */);
            // tlsTolerant mimics Chrome's behavior
            if (tlsTolerant && unverifiedSocket instanceof OpenSSLSocketImpl) {
                OpenSSLSocketImpl openSslSocket = (OpenSSLSocketImpl) unverifiedSocket;
                openSslSocket.setEnabledCompressionMethods(new String[] { "ZLIB"});
                openSslSocket.setUseSessionTickets(true);
                openSslSocket.setHostname(address.hostName);
                // use SSLSocketFactory default enabled protocols
            } else {
                unverifiedSocket.setEnabledProtocols(new String [] { "SSLv3" });
            }
            if (!hostnameVerifier.verify(address.uri.getHost(), unverifiedSocket.getSession())) {
                throw new IOException("Hostname '" + address.uri.getHost() + "' was not verified");
            }
            sslSocket = unverifiedSocket;
        }

        return sslSocket;
    }

    /**
     * Returns true if the connection is functional. This uses a shameful hack
     * to peek a byte from the socket.
     */
    boolean isStale() throws IOException {
        if (!isEligibleForRecycling()) {
            return true;
        }

        InputStream in = getInputStream();
        if (in.available() > 0) {
            return false;
        }

        Socket socket = getSocket();
        int soTimeout = socket.getSoTimeout();
        try {
            socket.setSoTimeout(1);
            in.mark(1);
            int byteRead = in.read();
            if (byteRead != -1) {
                in.reset();
                return false;
            }
            return true; // the socket is reporting all data read; it's stale
        } catch (SocketTimeoutException e) {
            return false; // the connection is not stale; hooray
        } catch (IOException e) {
            return true; // the connection is stale, the read or soTimeout failed.
        } finally {
            socket.setSoTimeout(soTimeout);
        }
    }

    /**
     * Returns true if this connection is eligible to be recycled. This
     * is like {@link #isStale} except that it doesn't try to actually
     * perform any I/O.
     */
    protected boolean isEligibleForRecycling() {
        return !socket.isClosed()
                && !socket.isInputShutdown()
                && !socket.isOutputShutdown();
    }

    public static final class Address {
        private final URI uri;
        private final Proxy proxy;
        private final boolean requiresTunnel;
        private final String hostName;
        private final int hostPort;

        public Address(URI uri) {
            this.uri = uri;
            this.proxy = null;
            this.requiresTunnel = false;
            this.hostName = uri.getHost();
            this.hostPort = uri.getEffectivePort();
        }

        /**
         * @param requiresTunnel true if the HTTP connection needs to tunnel one
         *     protocol over another, such as when using HTTPS through an HTTP
         *     proxy. When doing so, we must avoid buffering bytes intended for
         *     the higher-level protocol.
         */
        public Address(URI uri, Proxy proxy, boolean requiresTunnel) {
            this.uri = uri;
            this.proxy = proxy;
            this.requiresTunnel = requiresTunnel;

            SocketAddress proxyAddress = proxy.address();
            if (!(proxyAddress instanceof InetSocketAddress)) {
                throw new IllegalArgumentException("Proxy.address() is not an InetSocketAddress: " +
                        proxyAddress.getClass());
            }
            InetSocketAddress proxySocketAddress = (InetSocketAddress) proxyAddress;
            this.hostName = proxySocketAddress.getHostName();
            this.hostPort = proxySocketAddress.getPort();
        }

        @Override public boolean equals(Object other) {
           if (other instanceof Address) {
               Address that = (Address) other;
               return Objects.equal(this.proxy, that.proxy)
                       && this.uri.getHost().equals(that.uri.getHost())
                       && this.uri.getEffectivePort() == that.uri.getEffectivePort()
                       && this.requiresTunnel == that.requiresTunnel;
           }
           return false;
       }

       @Override public int hashCode() {
           int result = 17;
           result = 31 * result + uri.getHost().hashCode();
           result = 31 * result + uri.getEffectivePort();
           result = 31 * result + (proxy != null ? proxy.hashCode() : 0);
           result = 31 * result + (requiresTunnel ? 1 : 0);
           return result;
       }

        public HttpConnection connect(int connectTimeout) throws IOException {
            return new HttpConnection(this, connectTimeout);
        }
    }
}
