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

package org.apache.harmony.xnet.provider.jsse;

import java.io.IOException;
import java.io.OutputStream;

/**
 * This is a application data output stream used in SSLSocket
 * implementation.
 * The written bytes are encrypted, packed into the records,
 * and then sent to the peer host.
 */
public class SSLSocketOutputStream extends OutputStream {

    private final SSLSocketImpl owner;

    protected SSLSocketOutputStream(SSLSocketImpl owner) {
        this.owner = owner;
    }

    private final byte[] singleByte = new byte[1];

    @Override
    public void write(int b) throws IOException {
        singleByte[0] = (byte) (b & 0xFF);
        owner.writeAppData(singleByte, 0, 1);
    }

    @Override
    public void write(byte[] b) throws IOException {
        owner.writeAppData(b, 0, b.length);
    }

    @Override
    public void write(byte[] b, int off, int len) throws IOException {
        owner.writeAppData(b, off, len);
    }

}
