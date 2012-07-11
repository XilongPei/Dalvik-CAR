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

/**
* @author Alexey V. Varlamov
* @version $Revision$
*/

package org.apache.harmony.security.tests.java.security;

import java.security.Permission;
import java.security.SecurityPermission;

import junit.framework.TestCase;
import dalvik.annotation.KnownFailure;
import dalvik.annotation.TestLevel;
import dalvik.annotation.TestTargetClass;
import dalvik.annotation.TestTargetNew;
@TestTargetClass(Permission.class)
/**
 * Tests for <code>Permission</code>
 */

public class PermissionTest extends TestCase {
    // Bare extension to instantiate abstract Permission class
    static final class RealPermission extends Permission {

        public RealPermission(String name) {
            super(name);
        }

        public boolean equals(Object obj) {
            return false;
        }

        public String getActions() {
            return null;
        }

        public int hashCode() {
            return 0;
        }

        public boolean implies(Permission permission) {
            return false;
        }
    }

    /**
     * Test that a permission object is created with the specified name and is
     * properly converted to String
     */
    @TestTargetNew(
        level = TestLevel.PARTIAL,
        notes = "Non null string parameter verified",
        method = "Permission",
        args = {java.lang.String.class}
    )
    public void testCtor() {
        String name = "testCtor123^%$#&^ &^$";
        Permission test = new RealPermission(name);
        assertEquals(name, test.getName());
        assertEquals("(" + test.getClass().getName() + " " + name + ")", test
            .toString());
    }

    /** newPermissionCollection() should return null */
    @TestTargetNew(
        level = TestLevel.PARTIAL,
        notes = "Returned parameter was tested.",
        method = "newPermissionCollection",
        args = {}
    )
    public void testCollection() {
        assertNull(new RealPermission("123").newPermissionCollection());
    }
}
