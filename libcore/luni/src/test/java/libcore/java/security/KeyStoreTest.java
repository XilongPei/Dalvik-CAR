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

package libcore.java.security;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.security.Key;
import java.security.KeyStore;
import java.security.KeyStore.Builder;
import java.security.KeyStore.Entry;
import java.security.KeyStore.LoadStoreParameter;
import java.security.KeyStore.PasswordProtection;
import java.security.KeyStore.PrivateKeyEntry;
import java.security.KeyStore.ProtectionParameter;
import java.security.KeyStore.SecretKeyEntry;
import java.security.KeyStore.TrustedCertificateEntry;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.Provider;
import java.security.Security;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import junit.framework.TestCase;

public class KeyStoreTest extends TestCase {

    private static final PrivateKeyEntry PRIVATE_KEY
            = TestKeyStore.privateKey(TestKeyStore.getServer().keyStore,
                                      TestKeyStore.getServer().keyPassword,
                                      "RSA");
    private static final PrivateKeyEntry PRIVATE_KEY_2
            = TestKeyStore.privateKey(TestKeyStore.getClientCertificate().keyStore,
                                      TestKeyStore.getClientCertificate().keyPassword,
                                      "RSA");
    private static final SecretKey SECRET_KEY = generateSecretKey();
    private static final SecretKey SECRET_KEY_2 = generateSecretKey();

    private static SecretKey generateSecretKey() {
        try {
            KeyGenerator kg = KeyGenerator.getInstance("DES");
            return kg.generateKey();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static final String ALIAS_PRIVATE = "private";
    private static final String ALIAS_CERTIFICATE = "certificate";
    private static final String ALIAS_SECRET = "secret";

    private static final String ALIAS_ALT_CASE_PRIVATE = "pRiVaTe";
    private static final String ALIAS_ALT_CASE_CERTIFICATE = "cErTiFiCaTe";
    private static final String ALIAS_ALT_CASE_SECRET = "sEcRet";

    private static final String ALIAS_NO_PASSWORD_PRIVATE = "private-no-password";
    private static final String ALIAS_NO_PASSWORD_SECRET = "secret-no-password";

    private static final char[] PASSWORD_STORE = "store password".toCharArray();
    private static final char[] PASSWORD_KEY = "key password".toCharArray();
    private static final char[] PASSWORD_BAD = "dummy".toCharArray();

    private static final ProtectionParameter PARAM_STORE = new PasswordProtection(PASSWORD_STORE);
    private static final ProtectionParameter PARAM_KEY = new PasswordProtection(PASSWORD_KEY);
    private static final ProtectionParameter PARAM_BAD = new PasswordProtection(PASSWORD_BAD);

    public static List<KeyStore> keyStores () throws Exception {
        List<KeyStore> keyStores = new ArrayList<KeyStore>();
        Provider[] providers = Security.getProviders();
        for (Provider provider : providers) {
            Set<Provider.Service> services = provider.getServices();
            for (Provider.Service service : services) {
                String type = service.getType();
                if (!type.equals("KeyStore")) {
                    continue;
                }
                String algorithm = service.getAlgorithm();
                KeyStore ks = KeyStore.getInstance(algorithm, provider);
                assertEquals(provider, ks.getProvider());
                assertEquals(algorithm, ks.getType());
                if (!isUnsupported(ks)) {
                    keyStores.add(ks);
                }
            }
        }
        return keyStores;
    }

    private static boolean isSecretKeyEnabled(KeyStore ks) {
        // JKS key stores cannot store secret keys, neither can the RI's PKCS12
        return (!(ks.getType().equals("JKS")
                  || ks.getType().equals("CaseExactJKS")
                  || (ks.getType().equals("PKCS12"))));
    }

    private static boolean isCertificateEnabled(KeyStore ks) {
        // RI can't handle certificate in PKCS12, but BC can
        return (!(ks.getType().equals("PKCS12") && ks.getProvider().getName().equals("SunJSSE")));
    }

    private static boolean isCaseSensitive(KeyStore ks) {
        return (ks.getType().equals("CaseExactJKS")
                || ks.getType().equals("BKS")
                || ks.getType().equals("BouncyCastle"));

    }

    private static boolean isUnsupported(KeyStore ks) {
        // Don't bother testing BC on RI
        return (StandardNames.IS_RI && ks.getProvider().getName().equals("BC"));
    }

    private static boolean isNullPasswordAllowed(KeyStore ks) {
        return (!(ks.getType().equals("JKS")
                  || ks.getType().equals("CaseExactJKS")
                  || ks.getType().equals("JCEKS")
                  || ks.getType().equals("PKCS12")));
    }

    private static boolean isKeyPasswordIgnored(KeyStore ks) {
        // BouncyCastle's PKCS12 ignores the key password unlike the RI which requires it
        return (ks.getType().equals("PKCS12") && ks.getProvider().getName().equals("BC"));
    }

    private static boolean isSetKeyByteArrayUnimplemented(KeyStore ks) {
        // All of BouncyCastle's
        // KeyStore.setKeyEntry(String,byte[],char[]) implementations
        // throw RuntimeException
        return (ks.getProvider().getName().equals("BC"));
    }

    public static void populate(KeyStore ks) throws Exception {
        ks.load(null, null);
        setPrivateKey(ks);
        if (isNullPasswordAllowed(ks)) {
            ks.setKeyEntry(ALIAS_NO_PASSWORD_PRIVATE,
                           PRIVATE_KEY.getPrivateKey(),
                           null,
                           PRIVATE_KEY.getCertificateChain());
        }
        if (isCertificateEnabled(ks)) {
            ks.setCertificateEntry(ALIAS_CERTIFICATE,
                                   PRIVATE_KEY.getCertificate());
        }
        if (isSecretKeyEnabled(ks)) {
            setSecretKey(ks);
            if (isNullPasswordAllowed(ks)) {
                ks.setKeyEntry(ALIAS_NO_PASSWORD_SECRET,
                               SECRET_KEY,
                               null,
                               null);
            }
        }
    }

    public static void setPrivateKey(KeyStore ks) throws Exception {
        setPrivateKey(ks, ALIAS_PRIVATE);
    }
    public static void setPrivateKey(KeyStore ks, String alias) throws Exception {
        setPrivateKey(ks, alias, PRIVATE_KEY);
    }
    public static void setPrivateKey(KeyStore ks,
                                     String alias,
                                     PrivateKeyEntry privateKey)
            throws Exception {
        ks.setKeyEntry(alias,
                       privateKey.getPrivateKey(),
                       PASSWORD_KEY,
                       privateKey.getCertificateChain());
    }

    public static void setPrivateKeyBytes(KeyStore ks) throws Exception {
        setPrivateKeyBytes(ks, ALIAS_PRIVATE);
    }
    public static void setPrivateKeyBytes(KeyStore ks, String alias) throws Exception {
        setPrivateKeyBytes(ks, alias, PRIVATE_KEY);
    }
    public static void setPrivateKeyBytes(KeyStore ks,
                                     String alias,
                                     PrivateKeyEntry privateKey)
            throws Exception {
        ks.setKeyEntry(alias,
                       privateKey.getPrivateKey().getEncoded(),
                       privateKey.getCertificateChain());
    }

    public static void setSecretKey(KeyStore ks) throws Exception {
        setSecretKey(ks, ALIAS_SECRET);
    }
    public static void setSecretKey(KeyStore ks, String alias) throws Exception {
        setSecretKey(ks, alias, SECRET_KEY);
    }
    public static void setSecretKey(KeyStore ks, String alias, SecretKey key) throws Exception {
        ks.setKeyEntry(alias,
                       key,
                       PASSWORD_KEY,
                       null);
    }

    public static void setSecretKeyBytes(KeyStore ks) throws Exception {
        setSecretKeyBytes(ks, ALIAS_SECRET);
    }
    public static void setSecretKeyBytes(KeyStore ks, String alias) throws Exception {
        setSecretKeyBytes(ks, alias, SECRET_KEY);
    }
    public static void setSecretKeyBytes(KeyStore ks, String alias, SecretKey key)
            throws Exception {
        ks.setKeyEntry(alias,
                       key.getEncoded(),
                       null);
    }

    public static void setCertificate(KeyStore ks) throws Exception {
        setCertificate(ks, ALIAS_CERTIFICATE);
    }
    public static void setCertificate(KeyStore ks, String alias) throws Exception {
        setCertificate(ks, alias, PRIVATE_KEY.getCertificate());
    }
    public static void setCertificate(KeyStore ks, String alias, Certificate certificate)
            throws Exception {
        ks.setCertificateEntry(alias, certificate);
    }

    public static void assertPrivateKey(Key actual)
            throws Exception {
        assertEquals(PRIVATE_KEY.getPrivateKey(), actual);
    }
    public static void assertPrivateKey2(Key actual)
            throws Exception {
        assertEquals(PRIVATE_KEY_2.getPrivateKey(), actual);
    }
    public static void assertPrivateKey(Entry actual)
            throws Exception {
        assertSame(PrivateKeyEntry.class, actual.getClass());
        PrivateKeyEntry privateKey = (PrivateKeyEntry) actual;
        assertEquals(PRIVATE_KEY.getPrivateKey(), privateKey.getPrivateKey());
        assertEquals(PRIVATE_KEY.getCertificate(), privateKey.getCertificate());
        assertEquals(Arrays.asList(PRIVATE_KEY.getCertificateChain()),
                     Arrays.asList(privateKey.getCertificateChain()));
    }

    public static void assertSecretKey(Key actual)
            throws Exception {
        assertEquals(SECRET_KEY, actual);
    }
    public static void assertSecretKey2(Key actual)
            throws Exception {
        assertEquals(SECRET_KEY_2, actual);
    }
    public static void assertSecretKey(Entry actual)
            throws Exception {
        assertSame(SecretKeyEntry.class, actual.getClass());
        assertEquals(SECRET_KEY, ((SecretKeyEntry) actual).getSecretKey());
    }

    public static void assertCertificate(Certificate actual)
            throws Exception {
        assertEquals(PRIVATE_KEY.getCertificate(), actual);
    }
    public static void assertCertificate2(Certificate actual)
            throws Exception {
        assertEquals(PRIVATE_KEY_2.getCertificate(), actual);
    }
    public static void assertCertificate(Entry actual)
            throws Exception {
        assertSame(TrustedCertificateEntry.class, actual.getClass());
        assertEquals(PRIVATE_KEY.getCertificate(),
                     ((TrustedCertificateEntry) actual).getTrustedCertificate());
    }

    public static void assertCertificateChain(Certificate[] actual)
            throws Exception {
        assertEquals(Arrays.asList(PRIVATE_KEY.getCertificateChain()),
                     Arrays.asList(actual));
    }

    public void test_KeyStore_create() throws Exception {
        Provider[] providers = Security.getProviders();
        for (Provider provider : providers) {
            Set<Provider.Service> services = provider.getServices();
            for (Provider.Service service : services) {
                String type = service.getType();
                if (!type.equals("KeyStore")) {
                    continue;
                }
                String algorithm = service.getAlgorithm();
                KeyStore ks = KeyStore.getInstance(algorithm, provider);
                assertEquals(provider, ks.getProvider());
                assertEquals(algorithm, ks.getType());
            }
        }
    }

    public void test_KeyStore_getInstance() throws Exception {
        String type = KeyStore.getDefaultType();
        try {
            KeyStore.getInstance(null);
            fail();
        } catch (NullPointerException expected) {
        }

        assertNotNull(KeyStore.getInstance(type));

        String providerName = StandardNames.SECURITY_PROVIDER_NAME;
        try {
            KeyStore.getInstance(null, (String)null);
            fail();
        } catch (IllegalArgumentException expected) {
        }
        try {
            KeyStore.getInstance(null, providerName);
            fail();
        } catch (Exception e) {
            if (e.getClass() != NullPointerException.class
                && e.getClass() != KeyStoreException.class) {
                throw e;
            }
        }
        try {
            KeyStore.getInstance(type, (String)null);
            fail();
        } catch (IllegalArgumentException expected) {
        }
        assertNotNull(KeyStore.getInstance(type, providerName));

        Provider provider = Security.getProvider(providerName);
        try {
            KeyStore.getInstance(null, (Provider)null);
            fail();
        } catch (IllegalArgumentException expected) {
        }
        try {
            KeyStore.getInstance(null, provider);
            fail();
        } catch (NullPointerException expected) {
        }
        try {
            KeyStore.getInstance(type, (Provider)null);
            fail();
        } catch (IllegalArgumentException expected) {
        }
        assertNotNull(KeyStore.getInstance(type, provider));
    }

    public void test_KeyStore_getDefaultType() throws Exception {
        String type = KeyStore.getDefaultType();
        assertNotNull(type);
        KeyStore ks = KeyStore.getInstance(type);
        assertNotNull(ks);
        assertEquals(type, ks.getType());
    }

    public void test_KeyStore_getProvider() throws Exception {
        KeyStore ks = KeyStore.getInstance(KeyStore.getDefaultType());
        assertNotNull(ks.getProvider());
        assertNotNull(StandardNames.SECURITY_PROVIDER_NAME, ks.getProvider().getName());

        for (KeyStore keyStore : keyStores()) {
            assertNotNull(keyStore.getProvider());
        }
    }

    public void test_KeyStore_getType() throws Exception {
        String type = KeyStore.getDefaultType();
        KeyStore ks = KeyStore.getInstance(type);
        assertNotNull(ks.getType());
        assertNotNull(type, ks.getType());

        for (KeyStore keyStore : keyStores()) {
            assertNotNull(keyStore.getType());
        }
    }

    public void test_KeyStore_getKey() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.getKey(null, null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test odd inputs
            try {
                keyStore.getKey(null, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != IllegalArgumentException.class) {
                    throw e;
                }
            }
            try {
                keyStore.getKey(null, PASSWORD_KEY);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != IllegalArgumentException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            assertNull(keyStore.getKey("", null));
            assertNull(keyStore.getKey("", PASSWORD_KEY));

            // test case sensitive
            assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            if (isSecretKeyEnabled(keyStore)) {
                assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            } else {
                assertNull(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            }

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                assertNull(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
            } else {
                assertPrivateKey(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }
            }

            // test with null passwords
            if (isKeyPasswordIgnored(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, null));
            } else {
                try {
                    keyStore.getKey(ALIAS_PRIVATE, null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class) {
                        throw e;
                    }
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                try {
                    keyStore.getKey(ALIAS_SECRET, null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class) {
                        throw e;
                    }
                }
            }

            // test with bad passwords
            if (isKeyPasswordIgnored(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, null));
            } else {
                try {
                    keyStore.getKey(ALIAS_PRIVATE, PASSWORD_BAD);
                    fail();
                } catch (UnrecoverableKeyException expected) {
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                try {
                    keyStore.getKey(ALIAS_SECRET, PASSWORD_BAD);
                    fail();
                } catch (UnrecoverableKeyException expected) {
                }
            }
        }
    }

    public void test_KeyStore_getCertificateChain() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.getCertificateChain(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }
        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test odd inputs
            try {
                keyStore.getCertificateChain(null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != IllegalArgumentException.class) {
                    throw e;
                }
            }
            assertNull(keyStore.getCertificateChain(""));

            // test case sensitive
            assertCertificateChain(keyStore.getCertificateChain(ALIAS_PRIVATE));

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getCertificateChain(ALIAS_ALT_CASE_PRIVATE));
            } else {
                assertCertificateChain(keyStore.getCertificateChain(ALIAS_ALT_CASE_PRIVATE));
            }
        }
    }

    public void test_KeyStore_getCertificate() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.getCertificate(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }
        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test odd inputs
            try {
                keyStore.getCertificate(null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != IllegalArgumentException.class) {
                    throw e;
                }
            }
            assertNull(keyStore.getCertificate(""));

            // test case sensitive
            if (isCertificateEnabled(keyStore)) {
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
            } else {
                assertNull(keyStore.getCertificate(ALIAS_CERTIFICATE));
            }

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
            } else {
                if (isCertificateEnabled(keyStore)) {
                    assertCertificate(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                }
            }
        }
    }

    public void test_KeyStore_getCreationDate() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                assertNotNull(keyStore.getCreationDate(null));
            } catch (KeyStoreException expected) {
            }
        }
        long before = System.currentTimeMillis();
        for (KeyStore keyStore : keyStores()) {
            // add 1000 since some key stores round of time to nearest second
            long after = System.currentTimeMillis() + 1000;
            populate(keyStore);

            // test odd inputs
            try {
                keyStore.getCreationDate(null);
                fail();
            } catch (NullPointerException expected) {
            }
            assertNull(keyStore.getCreationDate(""));

            // test case sensitive
            if (isCertificateEnabled(keyStore)) {
                Date date = keyStore.getCreationDate(ALIAS_CERTIFICATE);
                assertNotNull(date);
                assertTrue(before <= date.getTime());
                assertTrue(date.getTime() <= after);
            } else {
                assertNull(keyStore.getCreationDate(ALIAS_CERTIFICATE));
            }

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getCreationDate(ALIAS_ALT_CASE_CERTIFICATE));
            } else {
                if (isCertificateEnabled(keyStore)) {
                    Date date = keyStore.getCreationDate(ALIAS_ALT_CASE_CERTIFICATE);
                    assertTrue(before <= date.getTime());
                    assertTrue(date.getTime() <= after);
                }
            }
        }
    }

    public void test_KeyStore_setKeyEntry_Key() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.setKeyEntry(null, null, null, null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test odd inputs
            try {
                keyStore.setKeyEntry(null, null, null, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            try {
                keyStore.setKeyEntry(null, null, PASSWORD_KEY, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            try {
                keyStore.setKeyEntry(ALIAS_PRIVATE,
                                     PRIVATE_KEY.getPrivateKey(),
                                     PASSWORD_KEY,
                                     null);
                fail();
            } catch (IllegalArgumentException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test case sensitive
            assertNull(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            setPrivateKey(keyStore);
            assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            assertCertificateChain(keyStore.getCertificateChain(ALIAS_PRIVATE));
            if (isSecretKeyEnabled(keyStore)) {
                assertNull(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                setSecretKey(keyStore);
                assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            } else {
                try {
                    keyStore.setKeyEntry(ALIAS_SECRET, SECRET_KEY, PASSWORD_KEY, null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != KeyStoreException.class
                        && e.getClass() != NullPointerException.class) {
                        throw e;
                    }
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            // test case insensitive

            if (isCaseSensitive(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertNull(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                setPrivateKey(keyStore, ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2);
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertNull(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    setSecretKey(keyStore, ALIAS_ALT_CASE_SECRET, SECRET_KEY_2);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey2(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }
            } else {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                setPrivateKey(keyStore, ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2);
                assertPrivateKey2(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    setSecretKey(keyStore, ALIAS_ALT_CASE_PRIVATE, SECRET_KEY_2);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test with null passwords
            if (isNullPasswordAllowed(keyStore) || isKeyPasswordIgnored(keyStore)) {
                keyStore.setKeyEntry(ALIAS_PRIVATE,
                                     PRIVATE_KEY.getPrivateKey(),
                                     null,
                                     PRIVATE_KEY.getCertificateChain());
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, null));
            } else {
                try {
                    keyStore.setKeyEntry(ALIAS_PRIVATE,
                                         PRIVATE_KEY.getPrivateKey(),
                                         null,
                                         PRIVATE_KEY.getCertificateChain());
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class
                        && e.getClass() != KeyStoreException.class) {
                        throw e;
                    }
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                if (isNullPasswordAllowed(keyStore) || isKeyPasswordIgnored(keyStore)) {
                    keyStore.setKeyEntry(ALIAS_SECRET, SECRET_KEY, null, null);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, null));
                } else {
                    try {
                        keyStore.setKeyEntry(ALIAS_SECRET, SECRET_KEY, null, null);
                        fail();
                    } catch (Exception e) {
                        if (e.getClass() != UnrecoverableKeyException.class
                            && e.getClass() != IllegalArgumentException.class
                            && e.getClass() != KeyStoreException.class) {
                            throw e;
                        }
                    }
                }
            }
        }
    }

    public void test_KeyStore_setKeyEntry_array() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.setKeyEntry(null, null, null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test odd inputs
            try {
                keyStore.setKeyEntry(null, null, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != IllegalArgumentException.class
                    && e.getClass() != KeyStoreException.class
                    && e.getClass() != RuntimeException.class) {
                    throw e;
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            if (!isNullPasswordAllowed(keyStore)) {
                // TODO Use EncryptedPrivateKeyInfo to protect keys if
                // password is required.
                continue;
            }
            if (isSetKeyByteArrayUnimplemented(keyStore)) {
                continue;
            }

            keyStore.load(null, null);

            // test case sensitive
            assertNull(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            setPrivateKeyBytes(keyStore);
            assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            assertCertificateChain(keyStore.getCertificateChain(ALIAS_PRIVATE));
            if (isSecretKeyEnabled(keyStore)) {
                assertNull(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                setSecretKeyBytes(keyStore);
                assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            } else {
                try {
                    keyStore.setKeyEntry(ALIAS_SECRET, SECRET_KEY.getEncoded(), null);
                    fail();
                } catch (KeyStoreException expected) {
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            if (!isNullPasswordAllowed(keyStore)) {
                // TODO Use EncryptedPrivateKeyInfo to protect keys if
                // password is required.
                continue;
            }
            if (isSetKeyByteArrayUnimplemented(keyStore)) {
                continue;
            }

            populate(keyStore);

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertNull(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                setPrivateKeyBytes(keyStore, ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2);
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertNull(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    setSecretKeyBytes(keyStore, ALIAS_ALT_CASE_PRIVATE, SECRET_KEY_2);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey2(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }
            } else {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                setPrivateKeyBytes(keyStore, ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2);
                assertPrivateKey2(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    setSecretKeyBytes(keyStore, ALIAS_ALT_CASE_PRIVATE, SECRET_KEY_2);
                    assertSecretKey2(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey2(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }
            }
        }
    }

    public void test_KeyStore_setCertificateEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.setCertificateEntry(null, null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            // test odd inputs
            try {
                keyStore.setCertificateEntry(null, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }

            // Sort of delete by setting null.  Note that even though
            // certificiate is null, size doesn't change,
            // isCertificateEntry returns true, and it is still listed in aliases.
            if (isCertificateEnabled(keyStore)) {
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                try {
                    int size = keyStore.size();
                    keyStore.setCertificateEntry(ALIAS_CERTIFICATE, null);
                    assertNull(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    assertEquals(size, keyStore.size());
                    assertTrue(keyStore.isCertificateEntry(ALIAS_CERTIFICATE));
                    assertTrue(Collections.list(keyStore.aliases()).contains(ALIAS_CERTIFICATE));
                } catch (NullPointerException expectedSometimes) {
                    assertEquals("PKCS12", keyStore.getType());
                    assertEquals("BC", keyStore.getProvider().getName());
                }
            } else {
                try {
                    keyStore.setCertificateEntry(ALIAS_CERTIFICATE, null);
                } catch (KeyStoreException expected) {
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            if (!isCertificateEnabled(keyStore)) {
                continue;
            }

            keyStore.load(null, null);

            // test case sensitive
            assertNull(keyStore.getCertificate(ALIAS_CERTIFICATE));
            setCertificate(keyStore);
            assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
        }

        for (KeyStore keyStore : keyStores()) {
            if (!isCertificateEnabled(keyStore)) {
                continue;
            }

            populate(keyStore);

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                assertNull(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                setCertificate(keyStore,
                               ALIAS_ALT_CASE_CERTIFICATE,
                               PRIVATE_KEY_2.getCertificate());
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                assertCertificate2(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
            } else {
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                assertCertificate(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                setCertificate(keyStore,
                               ALIAS_ALT_CASE_CERTIFICATE,
                               PRIVATE_KEY_2.getCertificate());
                assertCertificate2(keyStore.getCertificate(ALIAS_CERTIFICATE));
                assertCertificate2(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
            }
        }
    }
    public void test_KeyStore_deleteEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.deleteEntry(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test odd inputs
            try {
                keyStore.deleteEntry(null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            keyStore.deleteEntry("");
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test case sensitive
            assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            assertCertificateChain(keyStore.getCertificateChain(ALIAS_PRIVATE));
            keyStore.deleteEntry(ALIAS_PRIVATE);
            assertNull(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));

            if (isSecretKeyEnabled(keyStore)) {
                assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                keyStore.deleteEntry(ALIAS_SECRET);
                assertNull(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            } else {
                keyStore.deleteEntry(ALIAS_SECRET);
            }

            if (isCertificateEnabled(keyStore)) {
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                keyStore.deleteEntry(ALIAS_CERTIFICATE);
                assertNull(keyStore.getCertificate(ALIAS_CERTIFICATE));
            } else {
                keyStore.deleteEntry(ALIAS_CERTIFICATE);
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            // test case insensitive

            if (isCaseSensitive(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                keyStore.deleteEntry(ALIAS_ALT_CASE_PRIVATE);
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    keyStore.deleteEntry(ALIAS_ALT_CASE_SECRET);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                } else {
                    keyStore.deleteEntry(ALIAS_SECRET);
                }

                if (isCertificateEnabled(keyStore)) {
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    keyStore.deleteEntry(ALIAS_ALT_CASE_CERTIFICATE);
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                } else {
                    keyStore.deleteEntry(ALIAS_CERTIFICATE);
                }
            }
        }
    }

    public void test_KeyStore_aliases() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.aliases();
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            assertEquals(Collections.EMPTY_SET, new HashSet(Collections.list(keyStore.aliases())));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            Set<String> expected = new HashSet<String>();
            expected.add(ALIAS_PRIVATE);
            if (isNullPasswordAllowed(keyStore)) {
                expected.add(ALIAS_NO_PASSWORD_PRIVATE);
            }
            if (isSecretKeyEnabled(keyStore)) {
                expected.add(ALIAS_SECRET);
                if (isNullPasswordAllowed(keyStore)) {
                    expected.add(ALIAS_NO_PASSWORD_SECRET);
                }
            }
            if (isCertificateEnabled(keyStore)) {
                expected.add(ALIAS_CERTIFICATE);
            }
            assertEquals(expected, new HashSet<String>(Collections.list(keyStore.aliases())));
        }
    }

    public void test_KeyStore_containsAlias() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.containsAlias(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            try {
                keyStore.containsAlias(null);
                fail();
            } catch (NullPointerException expected) {
            }

            assertFalse(keyStore.containsAlias(""));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            assertFalse(keyStore.containsAlias(""));

            assertTrue(keyStore.containsAlias(ALIAS_PRIVATE));
            assertEquals(isSecretKeyEnabled(keyStore), keyStore.containsAlias(ALIAS_SECRET));
            assertEquals(isCertificateEnabled(keyStore), keyStore.containsAlias(ALIAS_CERTIFICATE));

            assertEquals(!isCaseSensitive(keyStore),
                         keyStore.containsAlias(ALIAS_ALT_CASE_PRIVATE));
            assertEquals(!isCaseSensitive(keyStore) && isSecretKeyEnabled(keyStore),
                         keyStore.containsAlias(ALIAS_ALT_CASE_SECRET));
            assertEquals(!isCaseSensitive(keyStore) && isCertificateEnabled(keyStore),
                         keyStore.containsAlias(ALIAS_ALT_CASE_CERTIFICATE));
        }
    }

    public void test_KeyStore_size() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.aliases();
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            assertEquals(0, keyStore.size());
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            int expected = 1;
            if (isNullPasswordAllowed(keyStore)) {
                expected++;
            }
            if (isSecretKeyEnabled(keyStore)) {
                expected++;
                if (isNullPasswordAllowed(keyStore)) {
                    expected++;
                }
            }
            if (isCertificateEnabled(keyStore)) {
                expected++;
            }
            assertEquals(expected, keyStore.size());
        }
    }

    public void test_KeyStore_isKeyEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.isKeyEntry(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            try {
                keyStore.isKeyEntry(null);
                fail();
            } catch (NullPointerException expected) {
            }

            assertFalse(keyStore.isKeyEntry(""));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            assertFalse(keyStore.isKeyEntry(""));

            assertTrue(keyStore.isKeyEntry(ALIAS_PRIVATE));
            assertEquals(isSecretKeyEnabled(keyStore), keyStore.isKeyEntry(ALIAS_SECRET));
            assertFalse(keyStore.isKeyEntry(ALIAS_CERTIFICATE));

            assertEquals(!isCaseSensitive(keyStore),
                         keyStore.isKeyEntry(ALIAS_ALT_CASE_PRIVATE));
            assertEquals(!isCaseSensitive(keyStore) && isSecretKeyEnabled(keyStore),
                         keyStore.isKeyEntry(ALIAS_ALT_CASE_SECRET));
            assertFalse(keyStore.isKeyEntry(ALIAS_ALT_CASE_CERTIFICATE));
        }
    }

    public void test_KeyStore_isCertificateEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.isCertificateEntry(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            if (isCertificateEnabled(keyStore)) {
                try {
                    keyStore.isCertificateEntry(null);
                    fail();
                } catch (NullPointerException expected) {
                }
            } else {
                assertFalse(keyStore.isCertificateEntry(null));
            }

            assertFalse(keyStore.isCertificateEntry(""));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            assertFalse(keyStore.isCertificateEntry(""));

            assertFalse(keyStore.isCertificateEntry(ALIAS_PRIVATE));
            assertFalse(keyStore.isCertificateEntry(ALIAS_SECRET));
            assertEquals(isCertificateEnabled(keyStore),
                         keyStore.isCertificateEntry(ALIAS_CERTIFICATE));

            assertFalse(keyStore.isCertificateEntry(ALIAS_ALT_CASE_PRIVATE));
            assertFalse(keyStore.isCertificateEntry(ALIAS_ALT_CASE_SECRET));
            assertEquals(!isCaseSensitive(keyStore) && isCertificateEnabled(keyStore),
                         keyStore.isCertificateEntry(ALIAS_ALT_CASE_CERTIFICATE));
        }
    }

    public void test_KeyStore_getCertificateAlias() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.getCertificateAlias(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            assertNull(keyStore.getCertificateAlias(null));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            Set<String> expected = new HashSet<String>();
            expected.add(ALIAS_PRIVATE);
            if (isNullPasswordAllowed(keyStore)) {
                expected.add(ALIAS_NO_PASSWORD_PRIVATE);
            }
            if (isCertificateEnabled(keyStore)) {
                expected.add(ALIAS_CERTIFICATE);
            }
            String actual = keyStore.getCertificateAlias(PRIVATE_KEY.getCertificate());
            assertTrue(expected.contains(actual));
            assertNull(keyStore.getCertificateAlias(PRIVATE_KEY_2.getCertificate()));
        }
    }

    public void assertEqualsKeyStores(File expected, char[] storePassword, KeyStore actual)
            throws Exception{
        KeyStore ks = KeyStore.getInstance(actual.getType(), actual.getProvider());
        ks.load(new FileInputStream(expected), storePassword);
        assertEqualsKeyStores(ks, actual);
    }

    public void assertEqualsKeyStores(KeyStore expected,
                                      ByteArrayOutputStream actual, char[] storePassword)
            throws Exception{
        KeyStore ks = KeyStore.getInstance(expected.getType(), expected.getProvider());
        ks.load(new ByteArrayInputStream(actual.toByteArray()), storePassword);
        assertEqualsKeyStores(expected, ks);
    }

    public void assertEqualsKeyStores(KeyStore expected, KeyStore actual)
            throws Exception{
        assertEquals(expected.size(), actual.size());
        for (String alias : Collections.list(actual.aliases())) {
            if (alias.equals(ALIAS_NO_PASSWORD_PRIVATE)
                    || alias.equals(ALIAS_NO_PASSWORD_SECRET)) {
                assertEquals(expected.getKey(alias, null),
                             actual.getKey(alias, null));
            } else {
                assertEquals(expected.getKey(alias, PASSWORD_KEY),
                             actual.getKey(alias, PASSWORD_KEY));
            }
            assertEquals(expected.getCertificate(alias), actual.getCertificate(alias));
        }
    }

    public void test_KeyStore_store_OutputStream() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.store(null, null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            if (isNullPasswordAllowed(keyStore)) {
                keyStore.store(out, null);
                assertEqualsKeyStores(keyStore, out, null);
            } else {
                try {
                    keyStore.store(out, null);
                } catch (Exception e) {
                    if (e.getClass() != IllegalArgumentException.class
                        && e.getClass() != NullPointerException.class) {
                        throw e;
                    }
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            if (isNullPasswordAllowed(keyStore)) {
                keyStore.store(out, null);
                assertEqualsKeyStores(keyStore, out, null);
            } else {
                try {
                    keyStore.store(out, null);
                } catch (Exception e) {
                    if (e.getClass() != IllegalArgumentException.class
                        && e.getClass() != NullPointerException.class) {
                        throw e;
                    }
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            keyStore.store(out, PASSWORD_STORE);
            assertEqualsKeyStores(keyStore, out, PASSWORD_STORE);
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            keyStore.store(out, PASSWORD_STORE);
            assertEqualsKeyStores(keyStore, out, PASSWORD_STORE);
        }
    }

    public void test_KeyStore_store_LoadStoreParameter() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.store(null);
                fail();
            } catch (KeyStoreException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            try {
                keyStore.store(null);
                fail();
            } catch (UnsupportedOperationException expected) {
            }
        }
    }

    public void test_KeyStore_load_InputStream() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            assertEquals(0, keyStore.size());
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, PASSWORD_STORE);
            assertEquals(0, keyStore.size());
        }

        // test_KeyStore_store_OutputStream effectively tests load as well as store
    }

    public void test_KeyStore_load_LoadStoreParameter() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null);
            assertEquals(0, keyStore.size());
        }

        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.load(new LoadStoreParameter() {
                        public ProtectionParameter getProtectionParameter() {
                            return null;
                        }
                    });
                assertEquals(0, keyStore.size());
            } catch (UnsupportedOperationException expected) {
            }
        }
    }

    public void test_KeyStore_getEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.getEntry(null, null);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test odd inputs
            try {
                keyStore.getEntry(null, null);
                fail();
            } catch (NullPointerException expected) {
            }
            try {
                keyStore.getEntry(null, PARAM_KEY);
                fail();
            } catch (NullPointerException expected) {
            }
            assertNull(keyStore.getEntry("", null));
            assertNull(keyStore.getEntry("", PARAM_KEY));

            // test case sensitive
            assertPrivateKey(keyStore.getEntry(ALIAS_PRIVATE, PARAM_KEY));
            if (isSecretKeyEnabled(keyStore)) {
                assertSecretKey(keyStore.getEntry(ALIAS_SECRET, PARAM_KEY));
            } else {
                assertNull(keyStore.getEntry(ALIAS_SECRET, PARAM_KEY));
            }
            if (isCertificateEnabled(keyStore)) {
                assertCertificate(keyStore.getEntry(ALIAS_CERTIFICATE, null));
            } else {
                assertNull(keyStore.getEntry(ALIAS_CERTIFICATE, null));
            }

            // test case insensitive
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getEntry(ALIAS_ALT_CASE_PRIVATE, PARAM_KEY));
                assertNull(keyStore.getEntry(ALIAS_ALT_CASE_SECRET, PARAM_KEY));
            } else {
                assertPrivateKey(keyStore.getEntry(ALIAS_ALT_CASE_PRIVATE, PARAM_KEY));
                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getEntry(ALIAS_ALT_CASE_SECRET, PARAM_KEY));
                }
            }
            if (isCaseSensitive(keyStore)) {
                assertNull(keyStore.getEntry(ALIAS_ALT_CASE_CERTIFICATE, null));
            } else {
                if (isCertificateEnabled(keyStore)) {
                    assertCertificate(keyStore.getEntry(ALIAS_ALT_CASE_CERTIFICATE, null));
                }
            }

            // test with null passwords
            if (isNullPasswordAllowed(keyStore)) {
                assertPrivateKey(keyStore.getEntry(ALIAS_NO_PASSWORD_PRIVATE, null));
            } else if (isKeyPasswordIgnored(keyStore)) {
                assertPrivateKey(keyStore.getEntry(ALIAS_PRIVATE, null));
            } else {
                try {
                    keyStore.getEntry(ALIAS_PRIVATE, null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class) {
                        throw e;
                    }
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                try {
                    keyStore.getEntry(ALIAS_SECRET, null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class) {
                        throw e;
                    }
                }
            }

            // test with bad passwords
            if (isKeyPasswordIgnored(keyStore)) {
                assertPrivateKey(keyStore.getEntry(ALIAS_PRIVATE, PARAM_BAD));
            } else {
                try {
                    keyStore.getEntry(ALIAS_PRIVATE, PARAM_BAD);
                    fail();
                } catch (UnrecoverableKeyException expected) {
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                try {
                    keyStore.getEntry(ALIAS_SECRET, PARAM_BAD);
                    fail();
                } catch (UnrecoverableKeyException expected) {
                }
            }
        }
    }

    public void test_KeyStore_setEntry() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            try {
                keyStore.setEntry(null, null, null);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test odd inputs
            try {
                keyStore.setEntry(null, null, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            try {
                keyStore.setEntry(null, null, PARAM_KEY);
                fail();
            } catch (Exception e) {
                if (e.getClass() != NullPointerException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            try {
                keyStore.setEntry("", null, PARAM_KEY);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test case sensitive
            assertNull(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            keyStore.setEntry(ALIAS_PRIVATE, PRIVATE_KEY, PARAM_KEY);
            assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
            assertCertificateChain(keyStore.getCertificateChain(ALIAS_PRIVATE));
            if (isSecretKeyEnabled(keyStore)) {
                assertNull(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                keyStore.setEntry(ALIAS_SECRET, new SecretKeyEntry(SECRET_KEY), PARAM_KEY);
                assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
            } else {
                try {
                    keyStore.setKeyEntry(ALIAS_SECRET, SECRET_KEY, PASSWORD_KEY, null);
                    fail();
                } catch (KeyStoreException expected) {
                }
            }
            if (isCertificateEnabled(keyStore)) {
                assertNull(keyStore.getCertificate(ALIAS_CERTIFICATE));
                keyStore.setEntry(ALIAS_CERTIFICATE,
                                  new TrustedCertificateEntry(PRIVATE_KEY.getCertificate()),
                                  null);
                assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
            } else {
                try {
                    keyStore.setEntry(ALIAS_CERTIFICATE,
                                      new TrustedCertificateEntry(PRIVATE_KEY.getCertificate()),
                                      null);
                    fail();
                } catch (KeyStoreException expected) {
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            // test case insensitive

            if (isCaseSensitive(keyStore)) {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertNull(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                keyStore.setEntry(ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2, PARAM_KEY);
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertNull(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    keyStore.setEntry(ALIAS_ALT_CASE_SECRET,
                                      new SecretKeyEntry(SECRET_KEY_2),
                                      PARAM_KEY);
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey2(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }

                if (isCertificateEnabled(keyStore)) {
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    assertNull(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                    keyStore.setEntry(ALIAS_ALT_CASE_CERTIFICATE,
                                      new TrustedCertificateEntry(PRIVATE_KEY_2.getCertificate()),
                                      null);
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    assertCertificate2(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                }
            } else {
                assertPrivateKey(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));
                keyStore.setEntry(ALIAS_ALT_CASE_PRIVATE, PRIVATE_KEY_2, PARAM_KEY);
                assertPrivateKey2(keyStore.getKey(ALIAS_PRIVATE, PASSWORD_KEY));
                assertPrivateKey2(keyStore.getKey(ALIAS_ALT_CASE_PRIVATE, PASSWORD_KEY));

                if (isSecretKeyEnabled(keyStore)) {
                    assertSecretKey(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                    keyStore.setEntry(ALIAS_ALT_CASE_SECRET,
                                      new SecretKeyEntry(SECRET_KEY_2),
                                      PARAM_KEY);
                    assertSecretKey2(keyStore.getKey(ALIAS_SECRET, PASSWORD_KEY));
                    assertSecretKey2(keyStore.getKey(ALIAS_ALT_CASE_SECRET, PASSWORD_KEY));
                }

                if (isCertificateEnabled(keyStore)) {
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    assertCertificate(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                    keyStore.setEntry(ALIAS_ALT_CASE_CERTIFICATE,
                                      new TrustedCertificateEntry(PRIVATE_KEY_2.getCertificate()),
                                      null);
                    assertCertificate2(keyStore.getCertificate(ALIAS_CERTIFICATE));
                    assertCertificate2(keyStore.getCertificate(ALIAS_ALT_CASE_CERTIFICATE));
                }
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            // test with null/non-null passwords
            try {
                keyStore.setEntry(ALIAS_PRIVATE, PRIVATE_KEY, null);
                fail();
            } catch (Exception e) {
                if (e.getClass() != UnrecoverableKeyException.class
                    && e.getClass() != IllegalArgumentException.class
                    && e.getClass() != KeyStoreException.class) {
                    throw e;
                }
            }
            if (isSecretKeyEnabled(keyStore)) {
                try {
                    keyStore.setEntry(ALIAS_SECRET, new SecretKeyEntry(SECRET_KEY), null);
                    fail();
                } catch (Exception e) {
                    if (e.getClass() != UnrecoverableKeyException.class
                        && e.getClass() != IllegalArgumentException.class
                        && e.getClass() != KeyStoreException.class) {
                        throw e;
                    }
                }
            }
            if (isCertificateEnabled(keyStore)) {
                if (isNullPasswordAllowed(keyStore) || isKeyPasswordIgnored(keyStore)) {
                    keyStore.setEntry(ALIAS_CERTIFICATE,
                                      new TrustedCertificateEntry(PRIVATE_KEY.getCertificate()),
                                      PARAM_KEY);
                    assertCertificate(keyStore.getCertificate(ALIAS_CERTIFICATE));
                } else {
                    try {
                        keyStore.setEntry(ALIAS_CERTIFICATE,
                                          new TrustedCertificateEntry(PRIVATE_KEY.getCertificate()),
                                          PARAM_KEY);
                        fail();
                    } catch (KeyStoreException expected) {
                    }
                }
            }
        }
    }

    public void test_KeyStore_entryInstanceOf() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            try {
                keyStore.entryInstanceOf(null, null);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);

            try {
                keyStore.entryInstanceOf(null, null);
                fail();
            } catch (NullPointerException expected) {
            }
            try {
                keyStore.entryInstanceOf(null, Entry.class);
                fail();
            } catch (NullPointerException expected) {
            }
            try {
                keyStore.entryInstanceOf("", null);
                fail();
            } catch (NullPointerException expected) {
            }

            assertFalse(keyStore.entryInstanceOf("", Entry.class));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);

            // test odd inputs
            assertFalse(keyStore.entryInstanceOf("", Entry.class));
            assertFalse(keyStore.entryInstanceOf("", PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf("", SecretKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf("", TrustedCertificateEntry.class));

            // test case sensitive
            assertTrue(keyStore.entryInstanceOf(ALIAS_PRIVATE, PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_PRIVATE, SecretKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_PRIVATE, TrustedCertificateEntry.class));

            assertEquals(isSecretKeyEnabled(keyStore),
                         keyStore.entryInstanceOf(ALIAS_SECRET, SecretKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_SECRET, PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_SECRET, TrustedCertificateEntry.class));

            assertEquals(isCertificateEnabled(keyStore),
                         keyStore.entryInstanceOf(ALIAS_CERTIFICATE,
                                                  TrustedCertificateEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_CERTIFICATE, PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_CERTIFICATE, SecretKeyEntry.class));

            // test case insensitive
            assertEquals(!isCaseSensitive(keyStore),
                         keyStore.entryInstanceOf(ALIAS_ALT_CASE_PRIVATE, PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_PRIVATE, SecretKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_PRIVATE,
                                                 TrustedCertificateEntry.class));

            assertEquals(!isCaseSensitive(keyStore) && isSecretKeyEnabled(keyStore),
                         keyStore.entryInstanceOf(ALIAS_ALT_CASE_SECRET, SecretKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_SECRET, PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_SECRET,
                                                 TrustedCertificateEntry.class));

            assertEquals(!isCaseSensitive(keyStore) && isCertificateEnabled(keyStore),
                         keyStore.entryInstanceOf(ALIAS_ALT_CASE_CERTIFICATE,
                                                  TrustedCertificateEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_CERTIFICATE,
                                                 PrivateKeyEntry.class));
            assertFalse(keyStore.entryInstanceOf(ALIAS_ALT_CASE_CERTIFICATE, SecretKeyEntry.class));
        }
    }

    public void test_KeyStore_Builder() throws Exception {
        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            try {
                Builder.newInstance(keyStore, null);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            try {
                Builder.newInstance(keyStore.getType(),
                                    keyStore.getProvider(),
                                    null);
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            try {
                Builder.newInstance(null,
                                    null,
                                    null,
                                    null);
                fail();
            } catch (NullPointerException expected) {
            }
            try {
                Builder.newInstance(keyStore.getType(),
                                    keyStore.getProvider(),
                                    null,
                                    null);
                fail();
            } catch (NullPointerException expected) {
            }
        }

        for (KeyStore keyStore : keyStores()) {
            keyStore.load(null, null);
            Builder builder = Builder.newInstance(keyStore, PARAM_STORE);
            try {
                builder.getProtectionParameter(null);
                fail();
            } catch (NullPointerException expected) {
            }
            assertEquals(keyStore, builder.getKeyStore());
            try {
                builder.getProtectionParameter(null);
                fail();
            } catch (NullPointerException expected) {
            }
            assertEquals(PARAM_STORE, builder.getProtectionParameter(""));
        }

        for (KeyStore keyStore : keyStores()) {
            populate(keyStore);
            File file = File.createTempFile("keystore", keyStore.getProvider().getName());
            try {
                keyStore.store(new FileOutputStream(file), PASSWORD_STORE);
                Builder builder = Builder.newInstance(keyStore.getType(),
                                                      keyStore.getProvider(),
                                                      file,
                                                      PARAM_STORE);
                assertEquals(keyStore.getType(), builder.getKeyStore().getType());
                assertEquals(keyStore.getProvider(), builder.getKeyStore().getProvider());
                assertEquals(PARAM_STORE, builder.getProtectionParameter(""));
                assertEqualsKeyStores(file, PASSWORD_STORE, keyStore);
            } finally {
                file.delete();
            }
        }

        for (KeyStore keyStore : keyStores()) {
            Builder builder = Builder.newInstance(keyStore.getType(),
                                                  keyStore.getProvider(),
                                                  PARAM_STORE);
            assertEquals(keyStore.getType(), builder.getKeyStore().getType());
            assertEquals(keyStore.getProvider(), builder.getKeyStore().getProvider());
            assertEquals(PARAM_STORE, builder.getProtectionParameter(""));
        }
    }

    public void test_KeyStore_cacerts_bks() throws Exception {
        if (StandardNames.IS_RI) {
            return;
        }
        KeyStore ks = KeyStore.getInstance("BKS");
        InputStream in = new FileInputStream(System.getProperty(
                "javax.net.ssl.trustStore", "/etc/security/cacerts.bks"));
        ks.load(in, null);
        for (String alias : Collections.list(ks.aliases())) {
            assert(ks.isCertificateEntry(alias));
            Certificate c = ks.getCertificate(alias);
            assertTrue(c instanceof X509Certificate);
            X509Certificate cert = (X509Certificate) c;
            assertEquals(cert.getSubjectUniqueID(), cert.getIssuerUniqueID());
        }
    }
}
