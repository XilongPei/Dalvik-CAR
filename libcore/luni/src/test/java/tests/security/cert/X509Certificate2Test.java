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

package tests.security.cert;

import dalvik.annotation.TestLevel;
import dalvik.annotation.TestTargetClass;
import dalvik.annotation.TestTargetNew;
import dalvik.annotation.TestTargets;

import org.apache.harmony.security.tests.support.cert.TestUtils;

import java.io.ByteArrayInputStream;
import java.math.BigInteger;
import java.security.Principal;
import java.security.PublicKey;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.CertificateParsingException;
import java.security.cert.X509Certificate;
import java.security.cert.X509Extension;
import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.List;
import java.util.Set;

import javax.security.auth.x500.X500Principal;

@TestTargetClass(X509Certificate.class)
public class X509Certificate2Test extends junit.framework.TestCase {

    /**
     * Test for X.509 Certificate provider
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "toString",
        args = {}
    )
    public void test_toString() throws Exception {

        // Regression for HARMONY-3384
        CertificateFactory certFact = CertificateFactory.getInstance("X509");
        X509Certificate pemCert = (X509Certificate) certFact
                .generateCertificate(new ByteArrayInputStream(TestUtils
                        .getX509Certificate_v3()));

        // extension value is empty sequence
        byte[] extnValue = pemCert.getExtensionValue("2.5.29.35");
        assertTrue(Arrays
                .equals(new byte[] {0x04, 0x02, 0x30, 0x00}, extnValue));
        assertNotNull(pemCert.toString());
        // End regression for HARMONY-3384
    }

    /**
     * @tests java.security.cert.X509Certificate#X509Certificate()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "X509Certificate",
        args = {}
    )
    public void test_X509Certificate() {
        MyX509Certificate s = null;
        try {
            s = new MyX509Certificate();
        } catch (Exception e) {
            fail("Unexpected exception " + e.getMessage());
        }
        assertEquals("X.509", s.getType());
    }

    @TestTargets({
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "checkValidity",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "checkValidity",
            args = {java.util.Date.class}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getBasicConstraints",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getIssuerDN",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getIssuerUniqueID",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getKeyUsage",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getNotAfter",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getNotBefore",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSerialNumber",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSigAlgName",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSigAlgOID",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSigAlgParams",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSignature",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSubjectDN",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getSubjectUniqueID",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getTBSCertificate",
            args = {}
        ),
        @TestTargetNew(
            level = TestLevel.COMPLETE,
            notes = "",
            method = "getVersion",
            args = {}
        )
    })
    public void testAbstractMethods() {
        MyX509Certificate s = new MyX509Certificate();
        try {
            s.checkValidity();
            s.checkValidity(new Date());
            s.getBasicConstraints();
            s.getIssuerDN();
            s.getIssuerUniqueID();
            s.getKeyUsage();
            s.getNotAfter();
            s.getNotBefore();
            s.getSerialNumber();
            s.getSigAlgName();
            s.getSigAlgOID();
            s.getSigAlgParams();
            s.getSignature();
            s.getSubjectDN();
            s.getSubjectUniqueID();
            s.getTBSCertificate();
            s.getVersion();
        } catch (Exception e) {
            fail("Unexpected exception " + e.getMessage());
        }
    }

    // Base64 encoded form of ASN.1 DER encoded X.509 Certificate
    // (see RFC 3280 at http://www.ietf.org/rfc/rfc3280.txt)
    // (generated by using of classes from
    // org.apache.harmony.security.x509 package)
    static String base64cert =
        "MIIByzCCATagAwIBAgICAiswCwYJKoZIhvcNAQEFMB0xGzAZBgNVBAoT"
            + "EkNlcnRpZmljYXRlIElzc3VlcjAeFw0wNjA0MjYwNjI4MjJaFw0zMzAz"
            + "MDExNjQ0MDlaMB0xGzAZBgNVBAoTEkNlcnRpZmljYXRlIElzc3VlcjCB"
            + "nzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkLGLsPdSPDMyP1OUOKu"
            + "U3cvbNK5RGaQ3bXc5aDjvApx43BcaoXgt6YD/5yXz0OsIooj5yA37bY"
            + "JGcVrvFD5FMPdDd3vjNPQOep0MzG4CdbkaZde5SigPabOMQYS4oUyLBx"
            + "W3LGG0mUODe5AGGqtqXU0GlKg4K2je6cCtookCUCAwEAAaMeMBwwGgYD"
            + "VR0RAQH/BBAwDoEMcmZjQDgyMi5OYW1lMAsGCSqGSIb3DQEBBQOBgQBZ"
            + "pVXj01dOpqnZErUQb50j8lJD1dIaz1eJTvJCSadj7ziV1VtnnapI07c"
            + "XEa7ONzcHQTYTG10poHfOK/a0BaULF3GlctDESilwQYbW5BdfpAlZpbH"
            + "AFLcUDh6Eq50kc0A/anh/j3mgBNuvbIMo7hHNnZB6k/prswm2BszyLD"
            + "yw==";
    static String base64certCorrect =
        "-----BEGIN CERTIFICATE-----\n"
        + "MIIC+jCCAragAwIBAgICAiswDAYHKoZIzjgEAwEBADAdMRswGQYDVQQKExJDZXJ0a"
        + "WZpY2F0ZSBJc3N1ZXIwIhgPMTk3MDAxMTIxMzQ2NDBaGA8xOTcwMDEyNDAzMzMyMF"
        + "owHzEdMBsGA1UEChMUU3ViamVjdCBPcmdhbml6YXRpb24wGTAMBgcqhkjOOAQDAQE"
        + "AAwkAAQIDBAUGBwiBAgCqggIAVaOCAhQwggIQMA8GA1UdDwEB/wQFAwMBqoAwEgYD"
        + "VR0TAQH/BAgwBgEB/wIBBTAUBgNVHSABAf8ECjAIMAYGBFUdIAAwZwYDVR0RAQH/B"
        + "F0wW4EMcmZjQDgyMi5OYW1lggdkTlNOYW1lpBcxFTATBgNVBAoTDE9yZ2FuaXphdG"
        + "lvboYaaHR0cDovL3VuaWZvcm0uUmVzb3VyY2UuSWSHBP///wCIByoDolyDsgMwDAY"
        + "DVR0eAQH/BAIwADAMBgNVHSQBAf8EAjAAMIGZBgNVHSUBAf8EgY4wgYsGBFUdJQAG"
        + "CCsGAQUFBwMBBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUFBwMDBggrBgEFBQcDB"
        + "AYIKwYBBQUHAwUGCCsGAQUFBwMGBggrBgEFBQcDBwYIKwYBBQUHAwgGCCsGAQUFBw"
        + "MJBggrBgEFBQgCAgYKKwYBBAGCNwoDAwYJYIZIAYb4QgQBMA0GA1UdNgEB/wQDAgE"
        + "BMA4GBCpNhgkBAf8EAwEBATBkBgNVHRIEXTBbgQxyZmNAODIyLk5hbWWCB2ROU05h"
        + "bWWkFzEVMBMGA1UEChMMT3JnYW5pemF0aW9uhhpodHRwOi8vdW5pZm9ybS5SZXNvd"
        + "XJjZS5JZIcE////AIgHKgOiXIOyAzAJBgNVHR8EAjAAMAoGA1UdIwQDAQEBMAoGA1"
        + "UdDgQDAQEBMAoGA1UdIQQDAQEBMAwGByqGSM44BAMBAQADMAAwLQIUAL4QvoazNWP"
        + "7jrj84/GZlhm09DsCFQCBKGKCGbrP64VtUt4JPmLjW1VxQA==\n"
        + "-----END CERTIFICATE-----";

    private X509Certificate cert;

    static String base64certTampered = "-----BEGIN CERTIFICATE-----\n"
        + "MIIC+jCCAragAwIBAgICAiswDAYHKoZIzjgEAwEBADAdMRswGQYDVQQKExJDZXJ0a"
        + "WZpY2F0ZSBJc3N1ZXIwIhgPMTk3MDAxMTIxMzQ2NDBaGA8xOTcwMDEyNDAzMzMyMF"
        + "owHzEdMBsGA1UEChMUU3ViamVjdCBPcmdhbml6YXRpb24wGTAMBgcqhkjOOAQDAQE"
        + "AAwkAAQIDBAUGBwiBAgCqggIAVaOCAhQwggIQMA8GA1UdDwEB/wQFAwMBqoAwEgYD"
        + "VR0TAQH/BAgwBgEB/wIBBTAUBgNVHSABAf8ECjAIMAyGBFUdIAAwZwYDVR0RAQH/B"
        + "F0wW4EMcmZjQDgyMi5OYW1lggdkTlNOYW1lpBcxFTATBgNVBAoTDE9yZ2FuaXphdG"
        + "lvboYaaHR0cDovL3VuaWZvcm0uUmVzb3VyY2UuSWSHBP///wCIByoDolyDsgMwDAY"
        + "DVR0eAQH/BAIwADAMBgNVHSQBAf8EAjAAMIGZBgNVHSUBAf8EgY4wgYsGBFUdJQAG"
        + "CCsGAQUFBwMBBggrBgEFBQcDAQYIKxYBBQUHAwIGCCsGAQUFBwMDBggrBgEFBQcDB"
        + "AYIKwYBBQUHAwUGCCsGAQUFBwMGBggrBgEFBQcDBwYIKwYBBQUHAwgGCCsGAQUFBw"
        + "MJBggrBgEFBQgCAgYKKwYBBAGCNwoDAwYJYIZIAYb4QgQBMA0GA1UdNgEB/wQDAgE"
        + "BMA4GBCpNhgkBAf8EAwEBATBkBgNVHRIEXTBbgQxyZmNAODIyLk5hbWWCB2ROU05h"
        + "bWWkFzEVMBMGA1UEChMMT3JnYW5pemF0aW9uhhpodHRwOi8vdW5pZm9ybS5SZXNvd"
        + "XJjZS5JZIcE////AIgHKgOiXIOyAzAJBgNVHR8EAjAAMAoGA1UdIwQDAQEBMAoGA1"
        + "UdDgQDAQEBMAoGA1UdIQQDAQEBMAwHByqGSM44BAMBAQADMAAwLQIUAL4QvoazNWP"
        + "7jrj84/GZlhm09DsCFQCBKGKCGbrP64VtUt4JPmLjW1VxQA==\n"
        + "-----END CERTIFICATE-----";

    // Base64 encoded form of ASN.1 DER encoded X.509 CRL
    // (see RFC 3280 at http://www.ietf.org/rfc/rfc3280.txt)
    // (generated by using of classes from
    // org.apache.harmony.security.x509 package)
    static String base64crl =
        "MIHXMIGXAgEBMAkGByqGSM44BAMwFTETMBEGA1UEChMKQ1JMIElzc3Vl"
            + "chcNMDYwNDI3MDYxMzQ1WhcNMDYwNDI3MDYxNTI1WjBBMD8CAgIrFw0w"
            + "NjA0MjcwNjEzNDZaMCowCgYDVR0VBAMKAQEwHAYDVR0YBBUYEzIwMDYw"
            + "NDI3MDYxMzQ1LjQ2OFqgDzANMAsGA1UdFAQEBAQEBDAJBgcqhkjOOAQD"
            + "AzAAMC0CFQCk0t0DTyu82QpajbBlxX9uXvUDSgIUSBN4g+xTEeexs/0k"
            + "9AkjBhjF0Es=";

    // has stub implementation for abstract methods
    private static class MyX509Certificate extends X509Certificate implements
            X509Extension {

        private static final long serialVersionUID = -7196694072296607007L;

        public void checkValidity() {
        }

        public void checkValidity(Date date) {
        }

        public int getVersion() {
            return 3;
        }

        public BigInteger getSerialNumber() {
            return null;
        }

        public Principal getIssuerDN() {
            return null;
        }

        public Principal getSubjectDN() {
            return null;
        }

        public Date getNotBefore() {
            return null;
        }

        public Date getNotAfter() {
            return null;
        }

        public byte[] getTBSCertificate() {
            return null;
        }

        public byte[] getSignature() {
            return null;
        }

        public String getSigAlgName() {
            return null;
        }

        public String getSigAlgOID() {
            return null;
        }

        public byte[] getSigAlgParams() {
            return null;
        }

        public boolean[] getIssuerUniqueID() {
            return null;
        }

        public boolean[] getSubjectUniqueID() {
            return null;
        }

        public boolean[] getKeyUsage() {
            return null;
        }

        public int getBasicConstraints() {
            return 0;
        }

        public void verify(PublicKey key) {
        }

        public void verify(PublicKey key, String sigProvider) {
        }

        public String toString() {
            return "";
        }

        public PublicKey getPublicKey() {
            return null;
        }

        public byte[] getEncoded() {
            return null;
        }

        public Set<String> getNonCriticalExtensionOIDs() {
            return null;
        }

        public Set<String> getCriticalExtensionOIDs() {
            return null;
        }

        public byte[] getExtensionValue(String oid) {
            return null;
        }

        public boolean hasUnsupportedCriticalExtension() {
            return false;
        }
    }

    /**
     * @tests java.security.cert.X509Certificate#getType()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "getType",
        args = {}
    )
    public void testGetType() {
        assertEquals("X.509", new MyX509Certificate().getType());
    }

    /**
     * @tests java.security.cert.X509Certificate#getIssuerX500Principal()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "getIssuerX500Principal",
        args = {}
    )
    public void testGetIssuerX500Principal() {
        // return valid encoding
        MyX509Certificate cert = new MyX509Certificate() {
            private static final long serialVersionUID = 638659908323741165L;

            public byte[] getEncoded() {
                return TestUtils.getX509Certificate_v1();
            }
        };

        assertEquals(new X500Principal("CN=Z"), cert.getIssuerX500Principal());
    }

    /**
     * @tests java.security.cert.X509Certificate#getSubjectX500Principal()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "getSubjectX500Principal",
        args = {}
    )
    public void testGetSubjectX500Principal() {
        // return valid encoding
        MyX509Certificate cert = new MyX509Certificate() {
            private static final long serialVersionUID = -3625913637413840694L;

            public byte[] getEncoded() {
                return TestUtils.getX509Certificate_v1();
            }
        };

        assertEquals(new X500Principal("CN=Y"), cert.getSubjectX500Principal());
    }

    /**
     * @throws CertificateException
     * @tests java.security.cert.X509Certificate#getExtendedKeyUsage()
     */
    @TestTargetNew(
        level = TestLevel.SUFFICIENT,
        notes = "Doesn't verify CertificateParsingException.",
        method = "getExtendedKeyUsage",
        args = {}
    )
    public void testGetExtendedKeyUsage() throws CertificateException {
        assertNull(new MyX509Certificate().getExtendedKeyUsage());

        List<String> l = cert.getExtendedKeyUsage();
        assertNotNull(l);

        try {
            l.clear();
        } catch (Exception e) {
            // ok
        }

        try {
            l.add("Test");
        } catch (Exception e) {
            // ok
        }

        try {
            if (l.size() > 0) {
                l.remove(0);
            }
        } catch (Exception e) {
            // ok
        }

    }

    /**
     * @tests java.security.cert.X509Certificate#getSubjectAlternativeNames()
     */
    @TestTargetNew(
        level = TestLevel.SUFFICIENT,
        notes = "",
        method = "getSubjectAlternativeNames",
        args = {}
    )
    public void testGetSubjectAlternativeNames()
            throws CertificateParsingException {

        assertNull(new MyX509Certificate().getSubjectAlternativeNames());

        Collection<List<?>> coll = cert.getSubjectAlternativeNames();
        //getSubjectAlternativeNames method is not supported
        assertNotNull(coll);

        try {
            coll.clear();
        } catch (Exception e) {
            // ok
        }

        try {
            if (coll.size() > 0) {
                coll.remove(0);
            }
        } catch (Exception e) {
            // ok
        }

        assertTrue(coll.size() < 10);

    }

    /**
     * @tests java.security.cert.X509Certificate#getIssuerAlternativeNames()
     */
    @TestTargetNew(
        level = TestLevel.SUFFICIENT,
        notes = "Doesn't verify CertificateParsingException.",
        method = "getIssuerAlternativeNames",
        args = {}
    )
    public void testGetIssuerAlternativeNames()
            throws CertificateParsingException {

        assertNull(new MyX509Certificate().getIssuerAlternativeNames());

        Collection<List<?>> coll = cert.getIssuerAlternativeNames();
        // getIssuerAlternativeNames returns null.
        assertNotNull(coll);

        try {
            coll.clear();
        } catch (Exception e) {
            // ok
        }

        try {
            if (coll.size() > 0) {
                coll.remove(0);
            }
        } catch (Exception e) {
            // ok
        }

        assertTrue(coll.size() < 10);
    }

    @TestTargetNew(
            level = TestLevel.PARTIAL_COMPLETE,
            notes = "",
            clazz = CertificateException.class,
            method = "CertificateException",
            args = {}
        )
    public void testCerficateException() {
        try {
            CertificateFactory cf = CertificateFactory.getInstance("X.509");
            ByteArrayInputStream bais = new ByteArrayInputStream(
                    base64certTampered.getBytes());
            cert = (X509Certificate) cf.generateCertificate(bais);
        } catch (CertificateException e) {
            // ok
        }

        try {
            CertificateFactory cf = CertificateFactory.getInstance("X.509");
            ByteArrayInputStream bais = new ByteArrayInputStream(base64cert
                    .getBytes());
            cert = (X509Certificate) cf.generateCertificate(bais);
        } catch (CertificateException e) {
            // ok
        }
    }

    public void setUp() throws Exception {
        super.setUp();
        CertificateFactory cf = CertificateFactory.getInstance("X.509");
        ByteArrayInputStream bais = new ByteArrayInputStream(base64certCorrect
                .getBytes());
        cert = (X509Certificate) cf.generateCertificate(bais);
        assertNotNull(cert);
    }
}
