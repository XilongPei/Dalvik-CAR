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
/*
 * Copyright (C) 2008 The Android Open Source Project
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

package java.lang.ref;

/**
 * Provides an abstract class which describes behavior common to all reference
 * objects. It is not possible to create immediate subclasses of
 * {@code Reference} in addition to the ones provided by this package. It is
 * also not desirable to do so, since references require very close cooperation
 * with the system's garbage collector. The existing, specialized reference
 * classes should be used instead.
 */
public abstract class Reference<T> {

    /**
     * The object to which this reference refers.
     * VM requirement: this field <em>must</em> be called "referent"
     * and be an object.
     */
    volatile T referent;

    /**
     * If non-null, the queue on which this reference will be enqueued
     * when the referent is appropriately reachable.
     * VM requirement: this field <em>must</em> be called "queue"
     * and be a java.lang.ref.ReferenceQueue.
     */
    @SuppressWarnings("unchecked")
    volatile ReferenceQueue queue;

    /**
     * Used internally by java.lang.ref.ReferenceQueue.
     * VM requirement: this field <em>must</em> be called "queueNext"
     * and be a java.lang.ref.Reference.
     */
    @SuppressWarnings("unchecked")
    volatile Reference queueNext;

    /**
     * Used internally by the VM.  This field forms a singly-linked
     * list of reference objects awaiting processing by the garbage
     * collector.
     */
    @SuppressWarnings("unchecked")
    volatile Reference pendingNext;

    /**
     * Constructs a new instance of this class.
     */
    Reference() {
        super();
    }

    /**
     * Makes the referent {@code null}. This does not force the reference
     * object to be enqueued.
     */
    public void clear() {
        referent = null;
    }

    /**
     * An implementation of .enqueue() that is safe for the VM to call.
     * If a Reference object is a subclass of any of the
     * java.lang.ref.*Reference classes and that subclass overrides enqueue(),
     * the VM may not call the overridden method.
     * VM requirement: this method <em>must</em> be called "enqueueInternal",
     * have the signature "()Z", and be private.
     *
     * @return {@code true} if this call has caused the {@code Reference} to
     * become enqueued, or {@code false} otherwise
     */
    @SuppressWarnings("unchecked")
    private synchronized boolean enqueueInternal() {
        /* VM requirement:
         * The VM assumes that this function only does work
         * if "(queue != null && queueNext == null)".
         * If that changes, Dalvik needs to change, too.
         * (see MarkSweep.c:enqueueReference())
         */
        if (queue != null && queueNext == null) {
            queue.enqueue(this);
            queue = null;
            return true;
        }
        return false;
    }

    /**
     * Forces the reference object to be enqueued if it has been associated with
     * a queue.
     *
     * @return {@code true} if this call has caused the {@code Reference} to
     * become enqueued, or {@code false} otherwise
     */
    public boolean enqueue() {
        return enqueueInternal();
    }

    /**
     * Returns the referent of the reference object.
     *
     * @return the referent to which reference refers, or {@code null} if the
     *         object has been cleared.
     */
    public T get() {
        return referent;
    }

    /**
     * Checks whether the reference object has been enqueued.
     *
     * @return {@code true} if the {@code Reference} has been enqueued, {@code
     *         false} otherwise
     */
    public boolean isEnqueued() {
        return queueNext != null;
    }

}
