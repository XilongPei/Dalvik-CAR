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

package java.io;

import java.nio.channels.FileChannel;
import libcore.io.IoUtils;
import org.apache.harmony.luni.platform.IFileSystem;
import org.apache.harmony.luni.platform.Platform;
import org.apache.harmony.nio.FileChannelFactory;

/**
 * A specialized {@link InputStream} that reads from a file in the file system.
 * All read requests made by calling methods in this class are directly
 * forwarded to the equivalent function of the underlying operating system.
 * Since this may induce some performance penalty, in particular if many small
 * read requests are made, a FileInputStream is often wrapped by a
 * BufferedInputStream.
 *
 * @see BufferedInputStream
 * @see FileOutputStream
 */
public class FileInputStream extends InputStream implements Closeable {
    /**
     * The {@link FileDescriptor} representing this {@code FileInputStream}.
     */
    FileDescriptor fd;

    // The unique file channel associated with this FileInputStream (lazily
    // initialized).
    private FileChannel channel;

    boolean innerFD;

    private IFileSystem fileSystem = Platform.getFileSystem();

    private static class RepositioningLock {
    }

    private Object repositioningLock = new RepositioningLock();

    /**
     * Constructs a new {@code FileInputStream} based on {@code file}.
     *
     * @param file
     *            the file from which this stream reads.
     * @throws FileNotFoundException
     *             if {@code file} does not exist.
     * @throws SecurityException
     *             if a {@code SecurityManager} is installed and it denies the
     *             read request.
     */
    public FileInputStream(File file) throws FileNotFoundException {
        super();
        SecurityManager security = System.getSecurityManager();
        if (security != null) {
            // For compatibility, nulls are passed to the manager.
            String filePath = (null == file ? null : file.getPath());
            security.checkRead(filePath);
        }
        if (file == null) {
            throw new NullPointerException("file == null");
        }
        fd = new FileDescriptor();
        fd.readOnly = true;
        fd.descriptor = fileSystem.open(file.getAbsolutePath(), IFileSystem.O_RDONLY);
        innerFD = true;
        // BEGIN android-removed
        // channel = FileChannelFactory.getFileChannel(this, fd.descriptor,
        //         IFileSystem.O_RDONLY);
        // END android-removed
    }

    /**
     * Constructs a new {@code FileInputStream} on the {@link FileDescriptor}
     * {@code fd}. The file must already be open, therefore no
     * {@code FileNotFoundException} will be thrown.
     *
     * @param fd
     *            the FileDescriptor from which this stream reads.
     * @throws NullPointerException
     *             if {@code fd} is {@code null}.
     * @throws SecurityException
     *             if a {@code SecurityManager} is installed and it denies the
     *             read request.
     */
    public FileInputStream(FileDescriptor fd) {
        super();
        if (fd == null) {
            throw new NullPointerException("fd == null");
        }
        SecurityManager security = System.getSecurityManager();
        if (security != null) {
            security.checkRead(fd);
        }
        this.fd = fd;
        innerFD = false;
        // BEGIN android-removed
        // channel = FileChannelFactory.getFileChannel(this, fd.descriptor,
        //         IFileSystem.O_RDONLY);
        // END android-removed
    }

    /**
     * Constructs a new {@code FileInputStream} on the file named
     * {@code fileName}. The path of {@code fileName} may be absolute or
     * relative to the system property {@code "user.dir"}.
     *
     * @param fileName
     *            the path and name of the file from which this stream reads.
     * @throws FileNotFoundException
     *             if there is no file named {@code fileName}.
     * @throws SecurityException
     *             if a {@code SecurityManager} is installed and it denies the
     *             read request.
     */
    public FileInputStream(String fileName) throws FileNotFoundException {
        this(null == fileName ? (File) null : new File(fileName));
    }

    @Override
    public int available() throws IOException {
        openCheck();
        return fileSystem.ioctlAvailable(fd);
    }

    /**
     * Closes this stream.
     *
     * @throws IOException
     *             if an error occurs attempting to close this stream.
     */
    @Override
    public void close() throws IOException {
        // BEGIN android-changed
        synchronized (this) {
            if (channel != null && channel.isOpen()) {
                channel.close();
                channel = null;
            }
            if (fd != null && fd.valid() && innerFD) {
                IoUtils.close(fd);
            }
        }
        // END android-changed
    }

    /**
     * Ensures that all resources for this stream are released when it is about
     * to be garbage collected.
     *
     * @throws IOException
     *             if an error occurs attempting to finalize this stream.
     */
    @Override protected void finalize() throws IOException {
        try {
            close();
        } finally {
            try {
                super.finalize();
            } catch (Throwable t) {
                throw new AssertionError(t);
            }
        }
    }

    /**
     * Returns the {@link FileChannel} equivalent to this input stream.
     * <p>
     * The file channel is read-only and has an initial position within the file
     * that is the same as the current position of this stream within the file.
     * All changes made to the underlying file descriptor state via the channel
     * are visible by the input stream and vice versa.
     *
     * @return the file channel for this stream.
     */
    public FileChannel getChannel() {
        // BEGIN android-changed
        synchronized(this) {
            if (channel == null) {
                channel = FileChannelFactory.getFileChannel(this, fd.descriptor,
                        IFileSystem.O_RDONLY);
            }
            return channel;
        }
        // END android-changed
    }

    /**
     * Returns the {@link FileDescriptor} representing the operating system
     * resource for this stream.
     *
     * @return the {@code FileDescriptor} for this stream.
     * @throws IOException
     *             if an error occurs while getting this stream's
     *             {@code FileDescriptor}.
     */
    public final FileDescriptor getFD() throws IOException {
        return fd;
    }

    /**
     * Reads a single byte from this stream and returns it as an integer in the
     * range from 0 to 255. Returns -1 if the end of this stream has been
     * reached.
     *
     * @return the byte read or -1 if the end of this stream has been reached.
     * @throws IOException
     *             if this stream is closed or another I/O error occurs.
     */
    @Override
    public int read() throws IOException {
        byte[] readed = new byte[1];
        int result = read(readed, 0, 1);
        return result == -1 ? -1 : readed[0] & 0xff;
    }

    /**
     * Reads bytes from this stream and stores them in the byte array
     * {@code buffer}.
     *
     * @param buffer
     *            the byte array in which to store the bytes read.
     * @return the number of bytes actually read or -1 if the end of the stream
     *         has been reached.
     * @throws IOException
     *             if this stream is closed or another I/O error occurs.
     */
    @Override
    public int read(byte[] buffer) throws IOException {
        return read(buffer, 0, buffer.length);
    }

    /**
     * Reads at most {@code count} bytes from this stream and stores them in the
     * byte array {@code buffer} starting at {@code offset}.
     *
     * @param buffer
     *            the byte array in which to store the bytes read.
     * @param offset
     *            the initial position in {@code buffer} to store the bytes read
     *            from this stream.
     * @param count
     *            the maximum number of bytes to store in {@code buffer}.
     * @return the number of bytes actually read or -1 if the end of the stream
     *         has been reached.
     * @throws IndexOutOfBoundsException
     *             if {@code offset < 0} or {@code count < 0}, or if
     *             {@code offset + count} is greater than the size of
     *             {@code buffer}.
     * @throws IOException
     *             if the stream is closed or another IOException occurs.
     */
    @Override
    public int read(byte[] buffer, int offset, int count) throws IOException {
        // BEGIN android-changed
        // Exception priorities (in case of multiple errors) differ from
        // RI, but are spec-compliant.
        // made implicit null check explicit,
        // used (offset | count) < 0 instead of (offset < 0) || (count < 0)
        // to safe one operation
        if (buffer == null) {
            throw new NullPointerException("buffer == null");
        }
        if ((count | offset) < 0 || count > buffer.length - offset) {
            throw new IndexOutOfBoundsException();
        }
        // END android-changed
        if (0 == count) {
            return 0;
        }
        openCheck();
        synchronized (repositioningLock) {
            // BEGIN android-changed
            // If you only support Linux, there's nothing special about stdin.
            return (int) fileSystem.read(fd.descriptor, buffer, offset, count);
            // END android-changed
        }
    }

    /**
     * Skips {@code count} number of bytes in this stream. Subsequent
     * {@code read()}s will not return these bytes unless {@code reset()} is
     * used. If the underlying stream is unseekable, an IOException is thrown.
     *
     * @param count
     *            the number of bytes to skip.
     * @return the number of bytes actually skipped.
     * @throws IOException
     *             if {@code count < 0}, this stream is closed or unseekable,
     *             or another IOException occurs.
     */
    @Override
    public long skip(long count) throws IOException {
        openCheck();

        if (count == 0) {
            return 0;
        }
        if (count < 0) {
            throw new IOException("count < 0");
        }

        // The RI doesn't treat stdin as special. It throws IOException for
        // all non-seekable streams, so we do too. If you did want to support
        // non-seekable streams, the best way to do it would be to recognize
        // when lseek(2) fails with ESPIPE and call super.skip(count).
        synchronized (repositioningLock) {
            // Our seek returns the new offset, but we know it will throw an
            // exception if it couldn't perform exactly the seek we asked for.
            fileSystem.seek(fd.descriptor, count, IFileSystem.SEEK_CUR);
            return count;
        }
    }

    private synchronized void openCheck() throws IOException {
        if (fd.descriptor < 0) {
            throw new IOException();
        }
    }
}
