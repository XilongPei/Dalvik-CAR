/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.harmony.xnet.provider.jsse;

import java.io.FileDescriptor;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.security.KeyStore.PrivateKeyEntry;
import java.security.KeyStore;
import java.security.KeyStoreException;
import libcore.java.security.StandardNames;
import libcore.java.security.TestKeyStore;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import javax.net.ssl.SSLException;
import javax.net.ssl.SSLProtocolException;
import javax.security.auth.x500.X500Principal;
import junit.framework.TestCase;
import org.apache.harmony.xnet.provider.jsse.NativeCrypto.SSLHandshakeCallbacks;

public class NativeCryptoTest extends TestCase {

    private static final int NULL = 0;
    private static final FileDescriptor INVALID_FD = new FileDescriptor();
    private static final SSLHandshakeCallbacks DUMMY_CB = new TestSSLHandshakeCallbacks(-1, null);

    private static final long TIMEOUT_SECONDS = 5;

    public static void assertEqualSessions(int expected, int actual) {
        assertEqualByteArrays(NativeCrypto.SSL_SESSION_session_id(expected),
                              NativeCrypto.SSL_SESSION_session_id(actual));
    }
    public static void assertEqualByteArrays(byte[] expected, byte[] actual) {
        assertEquals(Arrays.toString(expected), Arrays.toString(actual));
    }

    public static void assertEqualPrincipals(byte[][] expected, byte[][] actual) {
        assertEqualByteArrays(expected, actual);
    }
    public static void assertEqualCertificateChains(byte[][] expected, byte[][] actual) {
        assertEqualByteArrays(expected, actual);
    }
    public static void assertEqualByteArrays(byte[][] expected, byte[][] actual) {
        assertEquals(Arrays.deepToString(expected), Arrays.deepToString(actual));
    }

    public void test_SSL_CTX_new() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        assertTrue(c != NULL);
        int c2 = NativeCrypto.SSL_CTX_new();
        assertTrue(c != c2);
        NativeCrypto.SSL_CTX_free(c);
        NativeCrypto.SSL_CTX_free(c2);
    }

    public void test_SSL_CTX_free() throws Exception {
        try {
            NativeCrypto.SSL_CTX_free(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        NativeCrypto.SSL_CTX_free(NativeCrypto.SSL_CTX_new());
    }

    public void test_SSL_new() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        assertTrue(s != NULL);
        assertTrue((NativeCrypto.SSL_get_options(s) & 0x01000000L) != 0); // SSL_OP_NO_SSLv2
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) == 0);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_TLSv1) == 0);

        int s2 = NativeCrypto.SSL_new(c);
        assertTrue(s != s2);
        NativeCrypto.SSL_free(s2);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    private static final PrivateKeyEntry SERVER_PRIVATE_KEY_ENTRY
            = TestKeyStore.privateKey(TestKeyStore.getServer().keyStore,
                                      TestKeyStore.getServer().keyPassword,
                                      "RSA");
    private static final byte[] SERVER_PRIVATE_KEY
            = SERVER_PRIVATE_KEY_ENTRY.getPrivateKey().getEncoded();
    private static final byte[][] SERVER_CERTIFICATES;

    private static final PrivateKeyEntry CLIENT_PRIVATE_KEY_ENTRY
            = TestKeyStore.privateKey(TestKeyStore.getClientCertificate().keyStore,
                                      TestKeyStore.getClientCertificate().keyPassword,
                                      "RSA");
    private static final byte[] CLIENT_PRIVATE_KEY
            = CLIENT_PRIVATE_KEY_ENTRY.getPrivateKey().getEncoded();
    private static final byte[][] CLIENT_CERTIFICATES;

    static {
        try {
            CLIENT_CERTIFICATES = NativeCrypto.encodeCertificates(
                    CLIENT_PRIVATE_KEY_ENTRY.getCertificateChain());
            SERVER_CERTIFICATES = NativeCrypto.encodeCertificates(
                    SERVER_PRIVATE_KEY_ENTRY.getCertificateChain());
        } catch (CertificateEncodingException e) {
            throw new RuntimeException(e);
        }
    }

    private static final byte[][] CA_PRINCIPALS;
    static {
        try {
            KeyStore ks = TestKeyStore.getClient().keyStore;
            String caCertAlias = ks.aliases().nextElement();
            X509Certificate certificate = (X509Certificate) ks.getCertificate(caCertAlias);
            X500Principal principal = certificate.getIssuerX500Principal();
            CA_PRINCIPALS = new byte[][] { principal.getEncoded() };
        } catch (KeyStoreException e) {
            throw new RuntimeException(e);
        }
    }

    public void test_SSL_use_certificate() throws Exception {
        try {
            NativeCrypto.SSL_use_certificate(NULL, null);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        try {
            NativeCrypto.SSL_use_certificate(s, null);
            fail();
        } catch (NullPointerException expected) {
        }

        NativeCrypto.SSL_use_certificate(s, SERVER_CERTIFICATES);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_use_PrivateKey() throws Exception {
        try {
            NativeCrypto.SSL_use_PrivateKey(NULL, null);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        try {
            NativeCrypto.SSL_use_PrivateKey(s, null);
            fail();
        } catch (NullPointerException expected) {
        }

        NativeCrypto.SSL_use_PrivateKey(s, SERVER_PRIVATE_KEY);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_check_private_key_null() throws Exception {
        try {
            NativeCrypto.SSL_check_private_key(NULL);
            fail();
        } catch (NullPointerException expected) {
        }
    }

    public void test_SSL_check_private_key_no_key_no_cert() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        // neither private or certificate set
        try {
            NativeCrypto.SSL_check_private_key(s);
            fail();
        } catch (SSLException expected) {
        }

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_check_private_key_cert_then_key() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        // first certificate, then private
        NativeCrypto.SSL_use_certificate(s, SERVER_CERTIFICATES);

        try {
            NativeCrypto.SSL_check_private_key(s);
            fail();
        } catch (SSLException expected) {
        }

        NativeCrypto.SSL_use_PrivateKey(s, SERVER_PRIVATE_KEY);
        NativeCrypto.SSL_check_private_key(s);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }
    public void test_SSL_check_private_key_key_then_cert() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        // first private, then certificate
        NativeCrypto.SSL_use_PrivateKey(s, SERVER_PRIVATE_KEY);

        try {
            NativeCrypto.SSL_check_private_key(s);
            fail();
        } catch (SSLException expected) {
        }

        NativeCrypto.SSL_use_certificate(s, SERVER_CERTIFICATES);
        NativeCrypto.SSL_check_private_key(s);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_get_mode() throws Exception {
        try {
            NativeCrypto.SSL_get_mode(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        assertTrue(NativeCrypto.SSL_get_mode(s) != 0);
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_set_mode() throws Exception {
        try {
            NativeCrypto.SSL_set_mode(NULL, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        // check SSL_MODE_HANDSHAKE_CUTTHROUGH on
        assertTrue((NativeCrypto.SSL_get_mode(s)
                    & NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH) != 0);
        // clear SSL_MODE_HANDSHAKE_CUTTHROUGH off
        NativeCrypto.SSL_clear_mode(s, NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH);
        assertTrue((NativeCrypto.SSL_get_mode(s)
                    & NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH) == 0);
        // set SSL_MODE_HANDSHAKE_CUTTHROUGH on
        NativeCrypto.SSL_set_mode(s, NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH);
        assertTrue((NativeCrypto.SSL_get_mode(s)
                    & NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH) != 0);

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_clear_mode() throws Exception {
        try {
            NativeCrypto.SSL_clear_mode(NULL, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        // check SSL_MODE_HANDSHAKE_CUTTHROUGH on
        assertTrue((NativeCrypto.SSL_get_mode(s)
                    & NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH) != 0);
        // clear SSL_MODE_HANDSHAKE_CUTTHROUGH off
        NativeCrypto.SSL_clear_mode(s, NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH);
        assertTrue((NativeCrypto.SSL_get_mode(s)
                    & NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH) == 0);
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_get_options() throws Exception {
        try {
            NativeCrypto.SSL_get_options(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        assertTrue(NativeCrypto.SSL_get_options(s) != 0);
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_set_options() throws Exception {
        try {
            NativeCrypto.SSL_set_options(NULL, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) == 0);
        NativeCrypto.SSL_set_options(s, NativeCrypto.SSL_OP_NO_SSLv3);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) != 0);
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_clear_options() throws Exception {
        try {
            NativeCrypto.SSL_clear_options(NULL, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) == 0);
        NativeCrypto.SSL_set_options(s, NativeCrypto.SSL_OP_NO_SSLv3);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) != 0);
        NativeCrypto.SSL_clear_options(s, NativeCrypto.SSL_OP_NO_SSLv3);
        assertTrue((NativeCrypto.SSL_get_options(s) & NativeCrypto.SSL_OP_NO_SSLv3) == 0);
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_set_cipher_lists() throws Exception {
        try {
            NativeCrypto.SSL_set_cipher_lists(NULL, null);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        try {
            NativeCrypto.SSL_set_cipher_lists(s, null);
            fail();
        } catch (NullPointerException expected) {
        }

        NativeCrypto.SSL_set_cipher_lists(s, new String[] {});

        try {
            NativeCrypto.SSL_set_cipher_lists(s, new String[] { null });
            fail();
        } catch (NullPointerException expected) {
        }

        // see OpenSSL ciphers man page
        String[] illegals = new String[] {
            // empty
            "",
            // never standardized
            "EXP1024-DES-CBC-SHA", "EXP1024-RC4-SHA", "DHE-DSS-RC4-SHA",
            // IDEA
            "IDEA-CBC-SHA", "IDEA-CBC-MD5"
        };

        for (String illegal : illegals) {
            try {
                NativeCrypto.SSL_set_cipher_lists(s, new String[] { illegal });
                fail(illegal);
            } catch (IllegalArgumentException expected) {
            }
        }

        List<String> ciphers
                = new ArrayList<String>(NativeCrypto.OPENSSL_TO_STANDARD_CIPHER_SUITES.keySet());
        NativeCrypto.SSL_set_cipher_lists(s, ciphers.toArray(new String[ciphers.size()]));

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_set_verify() throws Exception {
        try {
            NativeCrypto.SSL_set_verify(NULL, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        NativeCrypto.SSL_set_verify(s, NativeCrypto.SSL_VERIFY_NONE);
        NativeCrypto.SSL_set_verify(s, NativeCrypto.SSL_VERIFY_PEER);
        NativeCrypto.SSL_set_verify(s, NativeCrypto.SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
        NativeCrypto.SSL_set_verify(s, (NativeCrypto.SSL_VERIFY_PEER
                                        | NativeCrypto.SSL_VERIFY_FAIL_IF_NO_PEER_CERT));
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    private static final boolean DEBUG = false;

    public static class Hooks {
        public int getContext() throws SSLException {
            return NativeCrypto.SSL_CTX_new();
        }
        public int beforeHandshake(int context) throws SSLException {
            int s = NativeCrypto.SSL_new(context);
            // without this SSL_set_cipher_lists call the tests were
            // negotiating DHE-RSA-AES256-SHA by default which had
            // very slow ephemeral RSA key generation
            NativeCrypto.SSL_set_cipher_lists(s, new String[] { "RC4-MD5" });
            return s;
        }
        public void clientCertificateRequested(int s) {}
        public void afterHandshake(int session, int ssl, int context,
                                   Socket socket, FileDescriptor fd,
                                   SSLHandshakeCallbacks callback)
                throws Exception {
            if (session != NULL) {
                NativeCrypto.SSL_SESSION_free(session);
            }
            if (ssl != NULL) {
                try {
                    NativeCrypto.SSL_shutdown(ssl, fd, callback);
                } catch (IOException e) {
                }
                NativeCrypto.SSL_free(ssl);
            }
            if (context != NULL) {
                NativeCrypto.SSL_CTX_free(context);
            }
            if (socket != null) {
                socket.close();
            }
        }
    }

    public static class TestSSLHandshakeCallbacks implements SSLHandshakeCallbacks {
        private final int sslNativePointer;
        private final Hooks hooks;

        public TestSSLHandshakeCallbacks(int sslNativePointer,
                                         Hooks hooks) {
            this.sslNativePointer = sslNativePointer;
            this.hooks = hooks;
        }

        public byte[][] asn1DerEncodedCertificateChain;
        public String authMethod;
        public boolean verifyCertificateChainCalled;

        public void verifyCertificateChain(byte[][] asn1DerEncodedCertificateChain,
                                           String authMethod)
                throws CertificateException {
            if (DEBUG) {
                System.out.println("ssl=0x" + Integer.toString(sslNativePointer, 16)
                                   + " verifyCertificateChain"
                                   + " asn1DerEncodedCertificateChain="
                                   + asn1DerEncodedCertificateChain
                                   + " authMethod=" + authMethod);
            }
            this.asn1DerEncodedCertificateChain = asn1DerEncodedCertificateChain;
            this.authMethod = authMethod;
            this.verifyCertificateChainCalled = true;
            return;
        }

        public byte[] keyTypes;
        public byte[][] asn1DerEncodedX500Principals;
        public boolean clientCertificateRequestedCalled;
        public void clientCertificateRequested(byte[] keyTypes,
                                               byte[][] asn1DerEncodedX500Principals) {
            if (DEBUG) {
                System.out.println("ssl=0x" + Integer.toString(sslNativePointer, 16)
                                   + " clientCertificateRequested"
                                   + " keyTypes=" + keyTypes
                                   + " asn1DerEncodedX500Principals="
                                   + asn1DerEncodedX500Principals);
            }
            this.keyTypes = keyTypes;
            this.asn1DerEncodedX500Principals = asn1DerEncodedX500Principals;
            this.clientCertificateRequestedCalled = true;
            if (hooks != null ) {
                hooks.clientCertificateRequested(sslNativePointer);
            }
        }

        public boolean handshakeCompletedCalled;
        public void handshakeCompleted() {
            if (DEBUG) {
                System.out.println("ssl=0x" + Integer.toString(sslNativePointer, 16)
                                   + " handshakeCompleted");
            }
            this.handshakeCompletedCalled = true;
            return;
        }
    }

    public static class ServerHooks extends Hooks {
        private final byte[] privateKey;
        private final byte[][] certificates;
        public ServerHooks(byte[] privateKey, byte[][] certificates) {
            this.privateKey = privateKey;
            this.certificates = certificates;
        }

        @Override
        public int beforeHandshake(int c) throws SSLException {
            int s = super.beforeHandshake(c);
            if (privateKey != null) {
                NativeCrypto.SSL_use_PrivateKey(s, privateKey);
            }
            if (certificates != null) {
                NativeCrypto.SSL_use_certificate(s, certificates);
            }
            return s;
        }
        public void clientCertificateRequested(int s) {
            fail("Server asked for client certificates");
        }
    }

    public static Future<TestSSLHandshakeCallbacks> handshake(final ServerSocket listener,
                                                              final int timeout,
                                                              final boolean client,
                                                              final Hooks hooks) {
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Future future = executor.submit(new Callable<TestSSLHandshakeCallbacks>() {
            public TestSSLHandshakeCallbacks call() throws Exception {
                Socket socket = (client
                                 ? new Socket(listener.getInetAddress(),
                                              listener.getLocalPort())
                                 : listener.accept());
                if (timeout == -1) {
                    return null;
                }
                FileDescriptor fd = NativeCrypto.getFileDescriptor(socket);
                int c = hooks.getContext();
                int s = hooks.beforeHandshake(c);
                TestSSLHandshakeCallbacks callback = new TestSSLHandshakeCallbacks(s, hooks);
                if (DEBUG) {
                    System.out.println("ssl=0x" + Integer.toString(s, 16)
                                       + " handshake"
                                       + " context=0x" + Integer.toString(c, 16)
                                       + " socket=" + socket
                                       + " fd=" + fd
                                       + " timeout=" + timeout
                                       + " client=" + client);
                }
                int session = NativeCrypto.SSL_do_handshake(s,
                                                            fd,
                                                            callback,
                                                            timeout,
                                                            client);
                if (DEBUG) {
                    System.out.println("ssl=0x" + Integer.toString(s, 16)
                                       + " handshake"
                                       + " session=0x" + Integer.toString(session, 16));
                }
                hooks.afterHandshake(session, s, c, socket, fd, callback);
                return callback;
            }
        });
        executor.shutdown();
        return future;
    }

    public void test_SSL_do_handshake_NULL_SSL() throws Exception {
        try {
            NativeCrypto.SSL_do_handshake(NULL, null, null, 0, false);
            fail();
        } catch (NullPointerException expected) {
        }
    }

    public void test_SSL_do_handshake_null_args() throws Exception {
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);

        try {
            NativeCrypto.SSL_do_handshake(s, null, null, 0, true);
            fail();
        } catch (NullPointerException e) {
        }

        try {
            NativeCrypto.SSL_do_handshake(s, INVALID_FD, null, 0, true);
            fail();
        } catch (NullPointerException e) {
        }

        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);
    }

    public void test_SSL_do_handshake_normal() throws Exception {
        // normal client and server case
        final ServerSocket listener = new ServerSocket(0);
        Hooks cHooks = new Hooks() {
            @Override
            public int beforeHandshake(int context) throws SSLException {
                int s = super.beforeHandshake(context);
                NativeCrypto.SSL_clear_mode(s, NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH);
                return s;
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        TestSSLHandshakeCallbacks clientCallback = client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        TestSSLHandshakeCallbacks serverCallback = server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        assertTrue(clientCallback.verifyCertificateChainCalled);
        assertEqualCertificateChains(SERVER_CERTIFICATES,
                                     clientCallback.asn1DerEncodedCertificateChain);
        assertEquals("RSA", clientCallback.authMethod);
        assertFalse(serverCallback.verifyCertificateChainCalled);
        assertFalse(clientCallback.clientCertificateRequestedCalled);
        assertFalse(serverCallback.clientCertificateRequestedCalled);
        assertTrue(clientCallback.handshakeCompletedCalled);
        assertTrue(serverCallback.handshakeCompletedCalled);
    }

    public void test_SSL_do_handshake_optional_client_certificate() throws Exception {
        // optional client certificate case
        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public int beforeHandshake(int context) throws SSLException {
                int s = super.beforeHandshake(context);
                NativeCrypto.SSL_clear_mode(s, NativeCrypto.SSL_MODE_HANDSHAKE_CUTTHROUGH);
                return s;
            }
            @Override
            public void clientCertificateRequested(int s) {
                super.clientCertificateRequested(s);
                NativeCrypto.SSL_use_PrivateKey(s, CLIENT_PRIVATE_KEY);
                NativeCrypto.SSL_use_certificate(s, CLIENT_CERTIFICATES);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public int beforeHandshake(int c) throws SSLException {
                int s = super.beforeHandshake(c);
                NativeCrypto.SSL_set_client_CA_list(s, CA_PRINCIPALS);
                NativeCrypto.SSL_set_verify(s, NativeCrypto.SSL_VERIFY_PEER);
                return s;
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        TestSSLHandshakeCallbacks clientCallback = client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        TestSSLHandshakeCallbacks serverCallback = server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        assertTrue(clientCallback.verifyCertificateChainCalled);
        assertEqualCertificateChains(SERVER_CERTIFICATES,
                                     clientCallback.asn1DerEncodedCertificateChain);
        assertEquals("RSA", clientCallback.authMethod);
        assertTrue(serverCallback.verifyCertificateChainCalled);
        assertEqualCertificateChains(CLIENT_CERTIFICATES,
                                     serverCallback.asn1DerEncodedCertificateChain);
        assertEquals("RSA", serverCallback.authMethod);

        assertTrue(clientCallback.clientCertificateRequestedCalled);
        assertNotNull(clientCallback.keyTypes);
        // this depends on the SSL_set_cipher_lists call in beforeHandshake
        // the three returned are the non-ephemeral cases.
        assertEquals(3, clientCallback.keyTypes.length);
        assertEquals("RSA", NativeCrypto.keyType(clientCallback.keyTypes[0]));
        assertEquals("DSA", NativeCrypto.keyType(clientCallback.keyTypes[1]));
        assertEquals("EC", NativeCrypto.keyType(clientCallback.keyTypes[2]));
        assertEqualPrincipals(CA_PRINCIPALS,
                              clientCallback.asn1DerEncodedX500Principals);
        assertFalse(serverCallback.clientCertificateRequestedCalled);

        assertTrue(clientCallback.handshakeCompletedCalled);
        assertTrue(serverCallback.handshakeCompletedCalled);
    }

    public void test_SSL_do_handshake_missing_required_certificate() throws Exception {
        // required client certificate negative case
        final ServerSocket listener = new ServerSocket(0);
        try {
            Hooks cHooks = new Hooks();
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public int beforeHandshake(int c) throws SSLException {
                    int s = super.beforeHandshake(c);
                    NativeCrypto.SSL_set_client_CA_list(s, CA_PRINCIPALS);
                    NativeCrypto.SSL_set_verify(s,
                                                NativeCrypto.SSL_VERIFY_PEER
                                                | NativeCrypto.SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
                    return s;
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SSLProtocolException.class, expected.getCause().getClass());
        }
    }

    public void test_SSL_do_handshake_client_timeout() throws Exception {
        // client timeout
        final ServerSocket listener = new ServerSocket(0);
        try {
            Hooks cHooks = new Hooks();
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 1, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, -1, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SocketTimeoutException.class, expected.getCause().getClass());
        }
    }

    public void test_SSL_do_handshake_server_timeout() throws Exception {
        // server timeout
        final ServerSocket listener = new ServerSocket(0);
        try {
            Hooks cHooks = new Hooks();
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, -1, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 1, false, sHooks);
            server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SocketTimeoutException.class, expected.getCause().getClass());
        }
    }

    public void test_SSL_set_session() throws Exception {
        try {
            NativeCrypto.SSL_set_session(NULL, NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            NativeCrypto.SSL_set_session(s, NULL);
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        {
            final int clientContext = NativeCrypto.SSL_CTX_new();
            final int serverContext = NativeCrypto.SSL_CTX_new();
            final ServerSocket listener = new ServerSocket(0);
            final int[] clientSession = new int[] { NULL };
            final int[] serverSession = new int[] { NULL };
            {
                Hooks cHooks = new Hooks() {
                    @Override
                    public int getContext() throws SSLException {
                        return clientContext;
                    }
                    @Override
                    public void afterHandshake(int session, int s, int c,
                                               Socket sock, FileDescriptor fd,
                                               SSLHandshakeCallbacks callback)
                            throws Exception {
                        super.afterHandshake(NULL, s, NULL, sock, fd, callback);
                        clientSession[0] = session;
                    }
                };
                Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                    @Override
                    public int getContext() throws SSLException {
                        return serverContext;
                    }
                    @Override
                    public void afterHandshake(int session, int s, int c,
                                               Socket sock, FileDescriptor fd,
                                               SSLHandshakeCallbacks callback)
                            throws Exception {
                        super.afterHandshake(NULL, s, NULL, sock, fd, callback);
                        serverSession[0] = session;
                    }
                };
                Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
                Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
                client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
                server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            }
            assertEqualSessions(clientSession[0], serverSession[0]);
            {
                Hooks cHooks = new Hooks() {
                    @Override
                    public int getContext() throws SSLException {
                        return clientContext;
                    }
                    @Override
                    public int beforeHandshake(int c) throws SSLException {
                        int s = NativeCrypto.SSL_new(clientContext);
                        NativeCrypto.SSL_set_session(s, clientSession[0]);
                        return s;
                    }
                    @Override
                    public void afterHandshake(int session, int s, int c,
                                               Socket sock, FileDescriptor fd,
                                               SSLHandshakeCallbacks callback)
                            throws Exception {
                        assertEqualSessions(clientSession[0], session);
                        super.afterHandshake(NULL, s, NULL, sock, fd, callback);
                    }
                };
                Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                    @Override
                    public int getContext() throws SSLException {
                        return serverContext;
                    }
                    @Override
                    public void afterHandshake(int session, int s, int c,
                                               Socket sock, FileDescriptor fd,
                                               SSLHandshakeCallbacks callback)
                            throws Exception {
                        assertEqualSessions(serverSession[0], session);
                        super.afterHandshake(NULL, s, NULL, sock, fd, callback);
                    }
                };
                Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
                Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
                client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
                server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            }
            NativeCrypto.SSL_SESSION_free(clientSession[0]);
            NativeCrypto.SSL_SESSION_free(serverSession[0]);
            NativeCrypto.SSL_CTX_free(serverContext);
            NativeCrypto.SSL_CTX_free(clientContext);
        }
    }

    public void test_SSL_set_session_creation_enabled() throws Exception {
        try {
            NativeCrypto.SSL_set_session_creation_enabled(NULL, false);
            fail();
        } catch (NullPointerException expected) {
        }

        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            NativeCrypto.SSL_set_session_creation_enabled(s, false);
            NativeCrypto.SSL_set_session_creation_enabled(s, true);
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        final ServerSocket listener = new ServerSocket(0);

        // negative test case for SSL_set_session_creation_enabled(false) on client
        try {
            Hooks cHooks = new Hooks() {
                @Override
                public int beforeHandshake(int c) throws SSLException {
                    int s = super.beforeHandshake(c);
                    NativeCrypto.SSL_set_session_creation_enabled(s, false);
                    return s;
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SSLProtocolException.class, expected.getCause().getClass());
        }

        // negative test case for SSL_set_session_creation_enabled(false) on server
        try {
            Hooks cHooks = new Hooks();
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public int beforeHandshake(int c) throws SSLException {
                    int s = super.beforeHandshake(c);
                    NativeCrypto.SSL_set_session_creation_enabled(s, false);
                    return s;
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SSLProtocolException.class, expected.getCause().getClass());
        }
    }

    public void test_SSL_set_tlsext_host_name() throws Exception {
        // NULL SSL
        try {
            NativeCrypto.SSL_set_tlsext_host_name(NULL, null);
            fail();
        } catch (NullPointerException expected) {
        }

        final String hostname = "www.android.com";

        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);

            // null hostname
            try {
                NativeCrypto.SSL_set_tlsext_host_name(s, null);
                fail();
            } catch (NullPointerException expected) {
            }

            // too long hostname
            try {
                char[] longHostname = new char[256];
                Arrays.fill(longHostname, 'w');
                NativeCrypto.SSL_set_tlsext_host_name(s, new String(longHostname));
                fail();
            } catch (SSLException expected) {
            }

            assertNull(NativeCrypto.SSL_get_servername(s));
            NativeCrypto.SSL_set_tlsext_host_name(s, new String(hostname));
            assertEquals(hostname, NativeCrypto.SSL_get_servername(s));

            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        final ServerSocket listener = new ServerSocket(0);

        // normal
        Hooks cHooks = new Hooks() {
            @Override
            public int beforeHandshake(int c) throws SSLException {
                int s = super.beforeHandshake(c);
                NativeCrypto.SSL_set_tlsext_host_name(s, hostname);
                return s;
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                assertEquals(hostname, NativeCrypto.SSL_get_servername(s));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_get_servername_null() throws Exception {
        // NULL SSL
        try {
            NativeCrypto.SSL_get_servername(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        assertNull(NativeCrypto.SSL_get_servername(s));
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);

        // additional positive testing by test_SSL_set_tlsext_host_name
    }

    public void test_SSL_renegotiate() throws Exception {
        try {
            NativeCrypto.SSL_renegotiate(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);
        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                assertEquals(42, NativeCrypto.SSL_read_byte(s, fd, callback, 0));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                throws Exception {
                NativeCrypto.SSL_renegotiate(s);
                NativeCrypto.SSL_write_byte(s, fd, callback, 42);
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_get_certificate() throws Exception {
        try {
            NativeCrypto.SSL_get_certificate(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);
        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                throws Exception {
                assertNull(NativeCrypto.SSL_get_certificate(s));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                assertEqualCertificateChains(
                                             SERVER_CERTIFICATES,
                                             NativeCrypto.SSL_get_certificate(s));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_get_peer_cert_chain() throws Exception {
        try {
            NativeCrypto.SSL_get_peer_cert_chain(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                byte[][] cc = NativeCrypto.SSL_get_peer_cert_chain(s);
                assertEqualCertificateChains(SERVER_CERTIFICATES, cc);
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_read_byte() throws Exception {
        try {
            NativeCrypto.SSL_read_byte(NULL, null, null, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        // null FileDescriptor
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read_byte(s, null, DUMMY_CB, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null SSLHandshakeCallbacks
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read_byte(s, INVALID_FD, null, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // handshaking not yet performed
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read_byte(s, INVALID_FD, DUMMY_CB, 0);
                fail();
            } catch (SSLException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        final ServerSocket listener = new ServerSocket(0);

        // normal case
        {
            Hooks cHooks = new Hooks() {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    assertEquals(37, NativeCrypto.SSL_read_byte(s, fd, callback, 0));
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_write_byte(s, fd, callback, 37);
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        }

        // timeout case
        try {
            Hooks cHooks = new Hooks() {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_read_byte(s, fd, callback, 1);
                    fail();
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_read_byte(s, fd, callback, 0);
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SocketTimeoutException.class, expected.getCause().getClass());
        }
    }

    final byte[] BYTES = new byte[] { 2, -3, 5, 127, 0, -128 };

    public void test_SSL_read() throws Exception {

        // NULL ssl
        try {
            NativeCrypto.SSL_read(NULL, null, null, null, 0, 0, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        // null FileDescriptor
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read(s, null, DUMMY_CB, null, 0, 0, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null SSLHandshakeCallbacks
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read(s, INVALID_FD, null, null, 0, 0, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null byte array
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read(s, INVALID_FD, DUMMY_CB, null, 0, 0, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // handshaking not yet performed
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_read(s, INVALID_FD, DUMMY_CB, new byte[1], 0, 1, 0);
                fail();
            } catch (SSLException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        final ServerSocket listener = new ServerSocket(0);

        // normal case
        {
            Hooks cHooks = new Hooks() {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    byte[] in = new byte[256];
                    assertEquals(BYTES.length,
                                 NativeCrypto.SSL_read(s,
                                                       fd,
                                                       callback,
                                                       in,
                                                       0,
                                                       BYTES.length,
                                                       0));
                    for (int i = 0; i < BYTES.length; i++) {
                        assertEquals(BYTES[i], in[i]);
                    }
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_write(s, fd, callback, BYTES, 0, BYTES.length);
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        }

        // timeout case
        try {
            Hooks cHooks = new Hooks() {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_read(s, fd, callback, new byte[1], 0, 1, 1);
                    fail();
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    NativeCrypto.SSL_read_byte(s, fd, callback, 0);
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            fail();
        } catch (ExecutionException expected) {
            assertEquals(SocketTimeoutException.class, expected.getCause().getClass());
        }
    }

    public void test_SSL_write_byte() throws Exception {
        try {
            NativeCrypto.SSL_write_byte(NULL, null, null, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        // null FileDescriptor
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write_byte(s, null, DUMMY_CB, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null SSLHandshakeCallbacks
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write_byte(s, INVALID_FD, null, 0);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // handshaking not yet performed
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write_byte(s, INVALID_FD, DUMMY_CB, 0);
                fail();
            } catch (SSLException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // tested by test_SSL_read_byte
    }

    public void test_SSL_write() throws Exception {
        try {
            NativeCrypto.SSL_write(NULL, null, null, null, 0, 0);
            fail();
        } catch (NullPointerException expected) {
        }

        // null FileDescriptor
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write(s, null, DUMMY_CB, null, 0, 1);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null SSLHandshakeCallbacks
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write(s, INVALID_FD, null, null, 0, 1);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // null byte array
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write(s, INVALID_FD, DUMMY_CB, null, 0, 1);
                fail();
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // handshaking not yet performed
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            try {
                NativeCrypto.SSL_write(s, INVALID_FD, DUMMY_CB, new byte[1], 0, 1);
                fail();
            } catch (SSLException expected) {
            }
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        // positively tested by test_SSL_read
    }

    public void test_SSL_interrupt() throws Exception {
        // SSL_interrupt is a rare case that tolerates a null SSL argument
        NativeCrypto.SSL_interrupt(NULL);

        // also works without handshaking
        {
            int c = NativeCrypto.SSL_CTX_new();
            int s = NativeCrypto.SSL_new(c);
            NativeCrypto.SSL_interrupt(s);
            NativeCrypto.SSL_free(s);
            NativeCrypto.SSL_CTX_free(c);
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                byte[] in = new byte[256];
                NativeCrypto.SSL_read_byte(s, fd, callback, 0);
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public void afterHandshake(int session, final int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                new Thread() {
                    public void run() {
                        try {
                            Thread.sleep(1*1000);
                            NativeCrypto.SSL_interrupt(s);
                        } catch (Exception e) {
                        }
                    }
                }.start();
                assertEquals(-1, NativeCrypto.SSL_read_byte(s, fd, callback, 0));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_shutdown() throws Exception {

        // null FileDescriptor
        try {
            NativeCrypto.SSL_shutdown(NULL, null, DUMMY_CB);
        } catch (NullPointerException expected) {
        }

        // null SSLHandshakeCallbacks
        try {
            NativeCrypto.SSL_shutdown(NULL, INVALID_FD, null);
        } catch (NullPointerException expected) {
        }

        // SSL_shutdown is a rare case that tolerates a null SSL argument
        NativeCrypto.SSL_shutdown(NULL, INVALID_FD, DUMMY_CB);

        // handshaking not yet performed
        int c = NativeCrypto.SSL_CTX_new();
        int s = NativeCrypto.SSL_new(c);
        try {
            NativeCrypto.SSL_shutdown(s, INVALID_FD, DUMMY_CB);
        } catch (SSLProtocolException expected) {
        }
        NativeCrypto.SSL_free(s);
        NativeCrypto.SSL_CTX_free(c);

        // positively tested elsewhere because handshake uses use
        // SSL_shutdown to ensure SSL_SESSIONs are reused.
    }

    public void test_SSL_free() throws Exception {
        try {
            NativeCrypto.SSL_free(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        int c = NativeCrypto.SSL_CTX_new();
        NativeCrypto.SSL_free(NativeCrypto.SSL_new(c));
        NativeCrypto.SSL_CTX_free(c);

        // additional positive testing elsewhere because handshake
        // uses use SSL_free to cleanup in afterHandshake.
    }

    public void test_SSL_SESSION_session_id() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_session_id(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                byte[] id = NativeCrypto.SSL_SESSION_session_id(session);
                assertNotNull(id);
                assertEquals(32, id.length);
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_SESSION_get_time() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_get_time(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        {
            Hooks cHooks = new Hooks() {
                @Override
                public void afterHandshake(int session, int s, int c,
                                           Socket sock, FileDescriptor fd,
                                           SSLHandshakeCallbacks callback)
                        throws Exception {
                    long time = NativeCrypto.SSL_SESSION_get_time(session);
                    assertTrue(time != 0);
                    assertTrue(time < System.currentTimeMillis());
                    super.afterHandshake(session, s, c, sock, fd, callback);
                }
            };
            Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
            Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
            Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
            client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        }
    }

    public void test_SSL_SESSION_get_version() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_get_version(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                String v = NativeCrypto.SSL_SESSION_get_version(session);
                assertTrue(StandardNames.SSL_SOCKET_PROTOCOLS.contains(v));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_SESSION_cipher() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_cipher(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                        throws Exception {
                String a = NativeCrypto.SSL_SESSION_cipher(session);
                assertTrue(NativeCrypto.OPENSSL_TO_STANDARD_CIPHER_SUITES.containsKey(a));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_SESSION_compress_meth_null() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_compress_meth(NULL, NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        {
            int c = NativeCrypto.SSL_CTX_new();
            try {
                NativeCrypto.SSL_SESSION_compress_meth(c, NULL);
            } catch (NullPointerException expected) {
            }
            NativeCrypto.SSL_CTX_free(c);
        }
    }

    public void test_SSL_SESSION_compress_meth_NULL() throws Exception {
        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                assertEquals("NULL", NativeCrypto.SSL_SESSION_compress_meth(c, session));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_SESSION_compress_meth_ZLIB() throws Exception {
        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public int beforeHandshake(int c) throws SSLException {
                int s = super.beforeHandshake(c);
                NativeCrypto.SSL_clear_options(s, NativeCrypto.SSL_OP_NO_COMPRESSION);
                return s;
            }
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                assertEquals("ZLIB", NativeCrypto.SSL_SESSION_compress_meth(c, session));
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES) {
            @Override
            public int beforeHandshake(int c) throws SSLException {
                int s = super.beforeHandshake(c);
                NativeCrypto.SSL_clear_options(s, NativeCrypto.SSL_OP_NO_COMPRESSION);
                return s;
            }
        };
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_SSL_SESSION_free() throws Exception {
        try {
            NativeCrypto.SSL_SESSION_free(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        // additional positive testing elsewhere because handshake
        // uses use SSL_SESSION_free to cleanup in afterHandshake.
    }

    public void test_i2d_SSL_SESSION() throws Exception {
        try {
            NativeCrypto.i2d_SSL_SESSION(NULL);
            fail();
        } catch (NullPointerException expected) {
        }

        final ServerSocket listener = new ServerSocket(0);

        Hooks cHooks = new Hooks() {
            @Override
            public void afterHandshake(int session, int s, int c,
                                       Socket sock, FileDescriptor fd,
                                       SSLHandshakeCallbacks callback)
                    throws Exception {
                byte[] b = NativeCrypto.i2d_SSL_SESSION(session);
                assertNotNull(b);
                int session2 = NativeCrypto.d2i_SSL_SESSION(b);
                assertTrue(session2 != NULL);
                NativeCrypto.SSL_SESSION_free(session2);
                super.afterHandshake(session, s, c, sock, fd, callback);
            }
        };
        Hooks sHooks = new ServerHooks(SERVER_PRIVATE_KEY, SERVER_CERTIFICATES);
        Future<TestSSLHandshakeCallbacks> client = handshake(listener, 0, true, cHooks);
        Future<TestSSLHandshakeCallbacks> server = handshake(listener, 0, false, sHooks);
        client.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
        server.get(TIMEOUT_SECONDS, TimeUnit.SECONDS);
    }

    public void test_d2i_SSL_SESSION() throws Exception {
        try {
            NativeCrypto.d2i_SSL_SESSION(null);
            fail();
        } catch (NullPointerException expected) {
        }

        assertEquals(NULL, NativeCrypto.d2i_SSL_SESSION(new byte[0]));
        assertEquals(NULL, NativeCrypto.d2i_SSL_SESSION(new byte[1]));

        // positively testing by test_i2d_SSL_SESSION
    }
}
