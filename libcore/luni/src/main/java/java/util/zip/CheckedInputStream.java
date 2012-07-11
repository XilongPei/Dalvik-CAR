/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package java.util.zip;

import java.io.IOException;
import java.io.InputStream;

/**
 * The {@code CheckedInputStream} class is used to maintain a checksum at the
 * same time as the data, on which the checksum is computed, is read from a
 * stream. The purpose of this checksum is to establish data integrity,
 * comparing the computed checksum against a published checksum value.
 */
public class CheckedInputStream extends java.io.FilterInputStream {

    private final Checksum check;

    /**
     * Constructs a new {@code CheckedInputStream} on {@code InputStream}
     * {@code is}. The checksum will be calculated using the algorithm
     * implemented by {@code csum}.
     *
     * <p><strong>Warning:</strong> passing a null source creates an invalid
     * {@code CheckedInputStream}. All operations on such a stream will fail.
     *
     * @param is
     *            the input stream to calculate checksum from.
     * @param csum
     *            an entity implementing the checksum algorithm.
     */
    public CheckedInputStream(InputStream is, Checksum csum) {
        super(is);
        check = csum;
    }

    /**
     * Reads one byte of data from the underlying input stream and updates the
     * checksum with the byte data.
     *
     * @return {@code -1} at the end of the stream, a single byte value
     *         otherwise.
     * @throws IOException
     *             if an {@code IOException} occurs.
     */
    @Override
    public int read() throws IOException {
        int x = in.read();
        if (x != -1) {
            check.update(x);
        }
        return x;
    }

    /**
     * Reads up to n bytes of data from the underlying input stream, storing it
     * into {@code buf}, starting at offset {@code off}. The checksum is
     * updated with the bytes read.
     *
     * @param buf
     *            the byte array in which to store the bytes read.
     * @param off
     *            the initial position in {@code buf} to store the bytes read
     *            from this stream.
     * @param nbytes
     *            the maximum number of bytes to store in {@code buf}.
     * @return the number of bytes actually read or {@code -1} if arrived at the
     *         end of the filtered stream while reading the data.
     * @throws IOException
     *             if this stream is closed or some I/O error occurs.
     */
    @Override
    public int read(byte[] buf, int off, int nbytes) throws IOException {
        int x = in.read(buf, off, nbytes);
        if (x != -1) {
            check.update(buf, off, x);
        }
        return x;
    }

    /**
     * Returns the checksum calculated on the stream read so far.
     *
     * @return the updated checksum.
     */
    public Checksum getChecksum() {
        return check;
    }

    /**
     * Skip up to n bytes of data on the underlying input stream. Any skipped
     * bytes are added to the running checksum value.
     *
     * @param nbytes
     *            the number of bytes to skip.
     * @throws IOException
     *             if this stream is closed or another I/O error occurs.
     * @return the number of bytes skipped.
     */
    @Override
    public long skip(long nbytes) throws IOException {
        if (nbytes < 1) {
            return 0;
        }
        long skipped = 0;
        byte[] b = new byte[(int)Math.min(nbytes, 2048L)];
        int x, v;
        while (skipped != nbytes) {
            x = in.read(b, 0,
                    (v = (int) (nbytes - skipped)) > b.length ? b.length : v);
            if (x == -1) {
                return skipped;
            }
            check.update(b, 0, x);
            skipped += x;
        }
        return skipped;
    }
}
