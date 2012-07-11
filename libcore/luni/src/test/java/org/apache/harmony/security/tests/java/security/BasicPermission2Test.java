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

package org.apache.harmony.security.tests.java.security;

import dalvik.annotation.TestTargetClass;
import dalvik.annotation.TestTargets;
import dalvik.annotation.TestLevel;
import dalvik.annotation.TestTargetNew;

import java.security.BasicPermission;
import java.security.PermissionCollection;

@TestTargetClass(BasicPermission.class)
public class BasicPermission2Test extends junit.framework.TestCase {

    public static class BasicPermissionSubclass extends BasicPermission {
        public BasicPermissionSubclass(String name) {
            super(name);
        }

        public BasicPermissionSubclass(String name, String actions) {
            super(name, actions);
        }
    }

    BasicPermission bp = new BasicPermissionSubclass("aName");

    BasicPermission bp2 = new BasicPermissionSubclass("aName", "anAction");

    BasicPermission bp3 = new BasicPermissionSubclass("*");

    BasicPermission bp4 = new BasicPermissionSubclass("this.that");

    BasicPermission bp5 = new BasicPermissionSubclass("this.*");

    /**
     * @tests java.security.BasicPermission#BasicPermission(java.lang.String)
     */
    @TestTargetNew(
        level = TestLevel.PARTIAL,
        notes = "Test cases, where parameter name is null (expect NullPointerException) and parameter name is empty (expect IllegalArgumentException) are absent",
        method = "BasicPermission",
        args = {java.lang.String.class}
    )
    public void test_ConstructorLjava_lang_String() {
        // Test for method java.security.BasicPermission(java.lang.String)
        assertEquals("Incorrect name returned", "aName", bp.getName());
    }

    /**
     * @tests java.security.BasicPermission#BasicPermission(java.lang.String,
     *        java.lang.String)
     */
    @TestTargetNew(
        level = TestLevel.PARTIAL,
        notes = "Test cases, where parameter name is null (expect NullPointerException) and parameter name is empty (expect IllegalArgumentException) are absent",
        method = "BasicPermission",
        args = {java.lang.String.class, java.lang.String.class}
    )
    public void test_ConstructorLjava_lang_StringLjava_lang_String() {
        // Test for method java.security.BasicPermission(java.lang.String,
        // java.lang.String)
        assertEquals("Incorrect name returned", "aName", bp2.getName());
    }

    /**
     * @tests java.security.BasicPermission#equals(java.lang.Object)
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "equals",
        args = {java.lang.Object.class}
    )
    public void test_equalsLjava_lang_Object() {
        // Test for method boolean
        // java.security.BasicPermission.equals(java.lang.Object)
        assertTrue("a) Equal objects returned non-equal", bp.equals(bp2));
        assertTrue("b) Equal objects returned non-equal", bp2.equals(bp));
        assertTrue("a) Unequal objects returned equal", !bp.equals(bp3));
        assertTrue("b) Unequal objects returned equal", !bp4.equals(bp5));
    }

    /**
     * @tests java.security.BasicPermission#getActions()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "getActions",
        args = {}
    )
    public void test_getActions() {
        // Test for method java.lang.String
        // java.security.BasicPermission.getActions()
        assertTrue("a) Incorrect actions returned, wanted the empty String", bp
                .getActions().equals(""));
        assertTrue("b) Incorrect actions returned, wanted the empty String",
                bp2.getActions().equals(""));
    }

    /**
     * @tests java.security.BasicPermission#hashCode()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "hashCode",
        args = {}
    )
    public void test_hashCode() {
        // Test for method int java.security.BasicPermission.hashCode()
        assertTrue("Equal objects should return same hash",
                bp.hashCode() == bp2.hashCode());
    }

    /**
     * @tests java.security.BasicPermission#implies(java.security.Permission)
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "implies",
        args = {java.security.Permission.class}
    )
    public void test_impliesLjava_security_Permission() {
        // Test for method boolean
        // java.security.BasicPermission.implies(java.security.Permission)
        assertTrue("Equal objects should imply each other", bp.implies(bp2));
        assertTrue("a) should not imply", !bp.implies(bp3));
        assertTrue("b) should not imply", !bp4.implies(bp5));
        assertTrue("a) should imply", bp3.implies(bp5));
        assertTrue("b) should imply", bp5.implies(bp4));

    }

    /**
     * @tests java.security.BasicPermission#newPermissionCollection()
     */
    @TestTargetNew(
        level = TestLevel.COMPLETE,
        notes = "",
        method = "newPermissionCollection",
        args = {}
    )
    public void test_newPermissionCollection() {
        // Test for method java.security.PermissionCollection
        // java.security.BasicPermission.newPermissionCollection()
        PermissionCollection bpc = bp.newPermissionCollection();
        bpc.add(bp5);
        bpc.add(bp);
        assertTrue("Should imply", bpc.implies(bp4));
        assertTrue("Should not imply", !bpc.implies(bp3));
    }
}