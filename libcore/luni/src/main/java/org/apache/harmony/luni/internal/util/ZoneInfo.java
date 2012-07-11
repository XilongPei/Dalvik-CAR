/*
 * Copyright (C) 2007 The Android Open Source Project
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

package org.apache.harmony.luni.internal.util;

import java.nio.charset.Charsets;
import java.util.Arrays;
import java.util.Date;
import java.util.TimeZone;
import libcore.base.Objects;

final class ZoneInfo extends TimeZone {

    private static final long MILLISECONDS_PER_DAY = 24 * 60 * 60 * 1000;
    private static final long MILLISECONDS_PER_400_YEARS =
            MILLISECONDS_PER_DAY * (400 * 365 + 100 - 3);

    private static final long UNIX_OFFSET = 62167219200000L;

    private static final int[] NORMAL = new int[] {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
    };

    private static final int[] LEAP = new int[] {
        0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
    };

    private static String nullName(byte[] bytes, int begin) {
        if (begin < 0) {
            return null;
        }
        int end = begin;
        while (end < bytes.length && bytes[end] != 0) {
            ++end;
        }
        return new String(bytes, begin, end - begin, Charsets.US_ASCII);
    }

    private int mRawOffset;

    private final int[] mTransitions;
    private final int[] mGmtOffs;
    private final byte[] mTypes;
    private final byte[] mIsDsts;
    private final boolean mUseDst;
    private final String mDaylightName;
    private final String mStandardName;

    ZoneInfo(String name, int[] transitions, byte[] type, int[] gmtoff, byte[] isdst,
            byte[] abbreviationIndexes, byte[] abbreviationList) {
        mTransitions = transitions;
        mTypes = type;
        mGmtOffs = gmtoff;
        mIsDsts = isdst;
        setID(name);

        // Find the latest GMT and non-GMT offsets for their abbreviations

        int lastdst;
        for (lastdst = mTransitions.length - 1; lastdst >= 0; lastdst--) {
            if (mIsDsts[mTypes[lastdst] & 0xFF] != 0) {
                break;
            }
        }

        int laststd;
        for (laststd = mTransitions.length - 1; laststd >= 0; laststd--) {
            if (mIsDsts[mTypes[laststd] & 0xFF] == 0) {
                break;
            }
        }

        if (lastdst >= 0) {
            mDaylightName = nullName(abbreviationList, abbreviationIndexes[mTypes[lastdst] & 0xFF]);
        } else {
            mDaylightName = null;
        }
        if (laststd >= 0) {
            mStandardName = nullName(abbreviationList, abbreviationIndexes[mTypes[laststd] & 0xFF]);
        } else {
            mStandardName = null;
        }

        // Use the latest non-DST offset if any as the raw offset

        if (laststd < 0) {
            laststd = 0;
        }

        if (laststd >= mTypes.length) {
            mRawOffset = mGmtOffs[0];
        } else {
            mRawOffset = mGmtOffs[mTypes[laststd] & 0xFF];
        }

        // Subtract the raw offset from all offsets so it can be changed
        // and affect them too.
        for (int i = 0; i < mGmtOffs.length; i++) {
            mGmtOffs[i] -= mRawOffset;
        }

        // Is this zone still observing DST?
        // We don't care if they've historically used it: most places have at least once.
        // We want to know whether the last "schedule info" (the unix times in the mTransitions
        // array) is in the future. If it is, DST is still relevant.
        // See http://code.google.com/p/android/issues/detail?id=877.
        // This test means that for somewhere like Morocco, which tried DST in 2009 but has
        // no future plans (and thus no future schedule info) will report "true" from
        // useDaylightTime at the start of 2009 but "false" at the end. This seems appropriate.
        boolean usesDst = false;
        long currentUnixTime = System.currentTimeMillis() / 1000;
        if (mTransitions.length > 0) {
            // (We're really dealing with uint32_t values, so long is most convenient in Java.)
            long latestScheduleTime = mTransitions[mTransitions.length - 1] & 0xffffffff;
            if (currentUnixTime < latestScheduleTime) {
                usesDst = true;
            }
        }
        mUseDst = usesDst;

        mRawOffset *= 1000;
    }

    @Override
    public int getOffset(int era, int year, int month, int day, int dayOfWeek, int millis) {
        // XXX This assumes Gregorian always; Calendar switches from
        // Julian to Gregorian in 1582.  What calendar system are the
        // arguments supposed to come from?

        long calc = (year / 400) * MILLISECONDS_PER_400_YEARS;
        year %= 400;

        calc += year * (365 * MILLISECONDS_PER_DAY);
        calc += ((year + 3) / 4) * MILLISECONDS_PER_DAY;

        if (year > 0)
            calc -= ((year - 1) / 100) * MILLISECONDS_PER_DAY;

        boolean isLeap = (year == 0 || (year % 4 == 0 && year % 100 != 0));
        int[] mlen = isLeap ? LEAP : NORMAL;

        calc += mlen[month] * MILLISECONDS_PER_DAY;
        calc += (day - 1) * MILLISECONDS_PER_DAY;
        calc += millis;

        calc -= mRawOffset;
        calc -= UNIX_OFFSET;

        return getOffset(calc);
    }

    @Override
    public int getOffset(long when) {
        int unix = (int) (when / 1000);
        int trans = Arrays.binarySearch(mTransitions, unix);

        if (trans == ~0) {
            return mGmtOffs[0] * 1000 + mRawOffset;
        }
        if (trans < 0) {
            trans = ~trans - 1;
        }

        return mGmtOffs[mTypes[trans] & 0xFF] * 1000 + mRawOffset;
    }

    @Override
    public int getRawOffset() {
        return mRawOffset;
    }

    @Override
    public void setRawOffset(int off) {
        mRawOffset = off;
    }

    @Override
    public boolean inDaylightTime(Date when) {
        int unix = (int) (when.getTime() / 1000);
        int trans = Arrays.binarySearch(mTransitions, unix);

        if (trans == ~0) {
            return mIsDsts[0] != 0;
        }
        if (trans < 0) {
            trans = ~trans - 1;
        }

        return mIsDsts[mTypes[trans] & 0xFF] != 0;
    }

    @Override
    public boolean useDaylightTime() {
        return mUseDst;
    }

    @Override public boolean hasSameRules(TimeZone timeZone) {
        if (!(timeZone instanceof ZoneInfo)) {
            return false;
        }
        ZoneInfo other = (ZoneInfo) timeZone;
        if (mUseDst != other.mUseDst) {
            return false;
        }
        if (!mUseDst) {
            return mRawOffset == other.mRawOffset;
        }
        return mRawOffset == other.mRawOffset
                // Arrays.equals returns true if both arrays are null
                && Arrays.equals(mGmtOffs, other.mGmtOffs)
                && Arrays.equals(mIsDsts, other.mIsDsts)
                && Arrays.equals(mTypes, other.mTypes)
                && Arrays.equals(mTransitions, other.mTransitions);
    }

    @Override public boolean equals(Object obj) {
        if (!(obj instanceof ZoneInfo)) {
            return false;
        }
        ZoneInfo other = (ZoneInfo) obj;
        return Objects.equal(mDaylightName, other.mDaylightName)
                && Objects.equal(mStandardName, other.mStandardName)
                && hasSameRules(other);
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((mDaylightName == null) ? 0 : mDaylightName.hashCode());
        result = prime * result + Arrays.hashCode(mGmtOffs);
        result = prime * result + Arrays.hashCode(mIsDsts);
        result = prime * result + mRawOffset;
        result = prime * result + ((mStandardName == null) ? 0 : mStandardName.hashCode());
        result = prime * result + Arrays.hashCode(mTransitions);
        result = prime * result + Arrays.hashCode(mTypes);
        result = prime * result + (mUseDst ? 1231 : 1237);
        return result;
    }

    @Override
    public String toString() {
        return getClass().getName() +
                "[\"" + mStandardName + "\",mRawOffset=" + mRawOffset + ",mUseDst=" + mUseDst + "]";
    }
}
