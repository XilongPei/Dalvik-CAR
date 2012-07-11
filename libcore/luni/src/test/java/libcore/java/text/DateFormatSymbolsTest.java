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

package libcore.java.text;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.DateFormatSymbols;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

public class DateFormatSymbolsTest extends junit.framework.TestCase {
    private void assertLocaleIsEquivalentToRoot(Locale locale) {
        DateFormatSymbols dfs = DateFormatSymbols.getInstance(locale);
        assertEquals(DateFormatSymbols.getInstance(Locale.ROOT), dfs);
    }

    /** http://b/3056586 */
    public void test_getInstance_unknown_locale() throws Exception {
        // TODO: we fail this test. on Android, the root locale uses GMT offsets as names.
        // see the invalid locale test below. on the RI, the root locale uses English names.
        assertLocaleIsEquivalentToRoot(new Locale("xx", "XX"));
    }

    public void test_getInstance_invalid_locale() throws Exception {
        assertLocaleIsEquivalentToRoot(new Locale("not exist language", "not exist country"));
    }

    public void testSerialization() throws Exception {
        // The Polish language needs stand-alone month and weekday names.
        Locale pl = new Locale("pl");
        DateFormatSymbols originalDfs = new DateFormatSymbols(pl);

        // Serialize...
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        new ObjectOutputStream(out).writeObject(originalDfs);
        byte[] bytes = out.toByteArray();

        // Deserialize...
        ObjectInputStream in = new ObjectInputStream(new ByteArrayInputStream(bytes));
        DateFormatSymbols deserializedDfs = (DateFormatSymbols) in.readObject();
        assertEquals(-1, in.read());

        // The two objects should claim to be equal, even though they aren't really.
        assertEquals(originalDfs, deserializedDfs);

        // The original differentiates between regular month names and stand-alone month names...
        assertEquals("stycznia", formatDate(pl, "MMMM", originalDfs));
        assertEquals("stycze\u0144", formatDate(pl, "LLLL", originalDfs));

        // Whereas the deserialized object can't, because it lost the strings...
        assertEquals("stycznia", formatDate(pl, "MMMM", deserializedDfs));
        assertEquals("stycznia", formatDate(pl, "LLLL", deserializedDfs));
    }

    private String formatDate(Locale l, String fmt, DateFormatSymbols dfs) {
        SimpleDateFormat sdf = new SimpleDateFormat(fmt, l);
        sdf.setDateFormatSymbols(dfs);
        sdf.setTimeZone(TimeZone.getTimeZone("UTC"));
        return sdf.format(new Date(0));
    }
}
