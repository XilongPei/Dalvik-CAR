/*
 * Written by Doug Lea with assistance from members of JCP JSR-166
 * Expert Group and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 * Other contributors include Andrew Wright, Jeffrey Hayes,
 * Pat Fisher, Mike Judd.
 */

package tests.api.java.util.concurrent; // android-added

import junit.framework.*;
import java.util.*;
import static java.util.concurrent.TimeUnit.MILLISECONDS;
import java.util.concurrent.*;

public class DelayQueueTest extends JSR166TestCase {
    public static Test suite() {
        return new TestSuite(DelayQueueTest.class);
    }

    private static final int NOCAP = Integer.MAX_VALUE;

    /**
     * A delayed implementation for testing.
     * Most tests use Pseudodelays, where delays are all elapsed
     * (so, no blocking solely for delays) but are still ordered
     */
    static class PDelay implements Delayed {
        int pseudodelay;
        PDelay(int i) { pseudodelay = Integer.MIN_VALUE + i; }
        public int compareTo(PDelay y) {
            int i = pseudodelay;
            int j = y.pseudodelay;
            if (i < j) return -1;
            if (i > j) return 1;
            return 0;
        }

        public int compareTo(Delayed y) {
            return compareTo((PDelay)y);
        }

        public boolean equals(Object other) {
            return equals((PDelay)other);
        }
        public boolean equals(PDelay other) {
            return other.pseudodelay == pseudodelay;
        }


        public long getDelay(TimeUnit ignore) {
            return pseudodelay;
        }
        public int intValue() {
            return pseudodelay;
        }

        public String toString() {
            return String.valueOf(pseudodelay);
        }
    }


    /**
     * Delayed implementation that actually delays
     */
    static class NanoDelay implements Delayed {
        long trigger;
        NanoDelay(long i) {
            trigger = System.nanoTime() + i;
        }
        public int compareTo(NanoDelay y) {
            long i = trigger;
            long j = y.trigger;
            if (i < j) return -1;
            if (i > j) return 1;
            return 0;
        }

        public int compareTo(Delayed y) {
            return compareTo((NanoDelay)y);
        }

        public boolean equals(Object other) {
            return equals((NanoDelay)other);
        }
        public boolean equals(NanoDelay other) {
            return other.trigger == trigger;
        }

        public long getDelay(TimeUnit unit) {
            long n = trigger - System.nanoTime();
            return unit.convert(n, TimeUnit.NANOSECONDS);
        }

        public long getTriggerTime() {
            return trigger;
        }

        public String toString() {
            return String.valueOf(trigger);
        }
    }


    /**
     * Create a queue of given size containing consecutive
     * PDelays 0 ... n.
     */
    private DelayQueue populatedQueue(int n) {
        DelayQueue q = new DelayQueue();
        assertTrue(q.isEmpty());
        for (int i = n-1; i >= 0; i-=2)
            assertTrue(q.offer(new PDelay(i)));
        for (int i = (n & 1); i < n; i+=2)
            assertTrue(q.offer(new PDelay(i)));
        assertFalse(q.isEmpty());
        assertEquals(NOCAP, q.remainingCapacity());
        assertEquals(n, q.size());
        return q;
    }

    /**
     * A new queue has unbounded capacity
     */
    public void testConstructor1() {
        assertEquals(NOCAP, new DelayQueue().remainingCapacity());
    }

    /**
     * Initializing from null Collection throws NPE
     */
    public void testConstructor3() {
        try {
            DelayQueue q = new DelayQueue(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Initializing from Collection of null elements throws NPE
     */
    public void testConstructor4() {
        try {
            PDelay[] ints = new PDelay[SIZE];
            DelayQueue q = new DelayQueue(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Initializing from Collection with some null elements throws NPE
     */
    public void testConstructor5() {
        try {
            PDelay[] ints = new PDelay[SIZE];
            for (int i = 0; i < SIZE-1; ++i)
                ints[i] = new PDelay(i);
            DelayQueue q = new DelayQueue(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Queue contains all elements of collection used to initialize
     */
    public void testConstructor6() {
        PDelay[] ints = new PDelay[SIZE];
        for (int i = 0; i < SIZE; ++i)
            ints[i] = new PDelay(i);
        DelayQueue q = new DelayQueue(Arrays.asList(ints));
        for (int i = 0; i < SIZE; ++i)
            assertEquals(ints[i], q.poll());
    }

    /**
     * isEmpty is true before add, false after
     */
    public void testEmpty() {
        DelayQueue q = new DelayQueue();
        assertTrue(q.isEmpty());
        assertEquals(NOCAP, q.remainingCapacity());
        q.add(new PDelay(1));
        assertFalse(q.isEmpty());
        q.add(new PDelay(2));
        q.remove();
        q.remove();
        assertTrue(q.isEmpty());
    }

    /**
     * remainingCapacity does not change when elements added or removed,
     * but size does
     */
    public void testRemainingCapacity() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(NOCAP, q.remainingCapacity());
            assertEquals(SIZE-i, q.size());
            q.remove();
        }
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(NOCAP, q.remainingCapacity());
            assertEquals(i, q.size());
            q.add(new PDelay(i));
        }
    }

    /**
     * offer(null) throws NPE
     */
    public void testOfferNull() {
        try {
            DelayQueue q = new DelayQueue();
            q.offer(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * add(null) throws NPE
     */
    public void testAddNull() {
        try {
            DelayQueue q = new DelayQueue();
            q.add(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * offer non-null succeeds
     */
    public void testOffer() {
        DelayQueue q = new DelayQueue();
        assertTrue(q.offer(new PDelay(0)));
        assertTrue(q.offer(new PDelay(1)));
    }

    /**
     * add succeeds
     */
    public void testAdd() {
        DelayQueue q = new DelayQueue();
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.size());
            assertTrue(q.add(new PDelay(i)));
        }
    }

    /**
     * addAll(null) throws NPE
     */
    public void testAddAll1() {
        try {
            DelayQueue q = new DelayQueue();
            q.addAll(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }


    /**
     * addAll(this) throws IAE
     */
    public void testAddAllSelf() {
        try {
            DelayQueue q = populatedQueue(SIZE);
            q.addAll(q);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * addAll of a collection with null elements throws NPE
     */
    public void testAddAll2() {
        try {
            DelayQueue q = new DelayQueue();
            PDelay[] ints = new PDelay[SIZE];
            q.addAll(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }
    /**
     * addAll of a collection with any null elements throws NPE after
     * possibly adding some elements
     */
    public void testAddAll3() {
        try {
            DelayQueue q = new DelayQueue();
            PDelay[] ints = new PDelay[SIZE];
            for (int i = 0; i < SIZE-1; ++i)
                ints[i] = new PDelay(i);
            q.addAll(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Queue contains all elements of successful addAll
     */
    public void testAddAll5() {
        PDelay[] empty = new PDelay[0];
        PDelay[] ints = new PDelay[SIZE];
        for (int i = SIZE-1; i >= 0; --i)
            ints[i] = new PDelay(i);
        DelayQueue q = new DelayQueue();
        assertFalse(q.addAll(Arrays.asList(empty)));
        assertTrue(q.addAll(Arrays.asList(ints)));
        for (int i = 0; i < SIZE; ++i)
            assertEquals(ints[i], q.poll());
    }

    /**
     * put(null) throws NPE
     */
     public void testPutNull() {
        try {
            DelayQueue q = new DelayQueue();
            q.put(null);
            shouldThrow();
        } catch (NullPointerException success) {}
     }

    /**
     * all elements successfully put are contained
     */
     public void testPut() {
         DelayQueue q = new DelayQueue();
         for (int i = 0; i < SIZE; ++i) {
             PDelay I = new PDelay(i);
             q.put(I);
             assertTrue(q.contains(I));
         }
         assertEquals(SIZE, q.size());
    }

    /**
     * put doesn't block waiting for take
     */
    public void testPutWithTake() throws InterruptedException {
        final DelayQueue q = new DelayQueue();
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() {
                q.put(new PDelay(0));
                q.put(new PDelay(0));
                q.put(new PDelay(0));
                q.put(new PDelay(0));
            }});

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        q.take();
        t.interrupt();
        t.join();
    }

    /**
     * timed offer does not time out
     */
    public void testTimedOffer() throws InterruptedException {
        final DelayQueue q = new DelayQueue();
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                q.put(new PDelay(0));
                q.put(new PDelay(0));
                assertTrue(q.offer(new PDelay(0), SHORT_DELAY_MS, MILLISECONDS));
                assertTrue(q.offer(new PDelay(0), LONG_DELAY_MS, MILLISECONDS));
            }});

        t.start();
        Thread.sleep(SMALL_DELAY_MS);
        t.interrupt();
        t.join();
    }

    /**
     * take retrieves elements in priority order
     */
    public void testTake() throws InterruptedException {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.take()));
        }
    }

    /**
     * take blocks interruptibly when empty
     */
    public void testTakeFromEmpty() throws InterruptedException {
        final DelayQueue q = new DelayQueue();
        Thread t = new ThreadShouldThrow(InterruptedException.class) {
            public void realRun() throws InterruptedException {
                q.take();
            }};

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        t.interrupt();
        t.join();
    }

    /**
     * Take removes existing elements until empty, then blocks interruptibly
     */
    public void testBlockingTake() throws InterruptedException {
        final DelayQueue q = populatedQueue(SIZE);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                for (int i = 0; i < SIZE; ++i) {
                    assertEquals(new PDelay(i), ((PDelay)q.take()));
                }
                try {
                    q.take();
                    shouldThrow();
                } catch (InterruptedException success) {}
            }});

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        t.interrupt();
        t.join();
    }


    /**
     * poll succeeds unless empty
     */
    public void testPoll() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.poll()));
        }
        assertNull(q.poll());
    }

    /**
     * timed pool with zero timeout succeeds when non-empty, else times out
     */
    public void testTimedPoll0() throws InterruptedException {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.poll(0, MILLISECONDS)));
        }
        assertNull(q.poll(0, MILLISECONDS));
    }

    /**
     * timed pool with nonzero timeout succeeds when non-empty, else times out
     */
    public void testTimedPoll() throws InterruptedException {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.poll(SHORT_DELAY_MS, MILLISECONDS)));
        }
        assertNull(q.poll(SHORT_DELAY_MS, MILLISECONDS));
    }

    /**
     * Interrupted timed poll throws InterruptedException instead of
     * returning timeout status
     */
    public void testInterruptedTimedPoll() throws InterruptedException {
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                DelayQueue q = populatedQueue(SIZE);
                for (int i = 0; i < SIZE; ++i) {
                    assertEquals(new PDelay(i), ((PDelay)q.poll(SHORT_DELAY_MS, MILLISECONDS)));
                }
                try {
                    q.poll(SMALL_DELAY_MS, MILLISECONDS);
                    shouldThrow();
                } catch (InterruptedException success) {}
            }});

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        t.interrupt();
        t.join();
    }

    /**
     *  timed poll before a delayed offer fails; after offer succeeds;
     *  on interruption throws
     */
    public void testTimedPollWithOffer() throws InterruptedException {
        final DelayQueue q = new DelayQueue();
        final PDelay pdelay = new PDelay(0);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                assertNull(q.poll(SHORT_DELAY_MS, MILLISECONDS));
                assertSame(pdelay, q.poll(LONG_DELAY_MS, MILLISECONDS));
                try {
                    q.poll(LONG_DELAY_MS, MILLISECONDS);
                    shouldThrow();
                } catch (InterruptedException success) {}
            }});

        t.start();
        Thread.sleep(SMALL_DELAY_MS);
        assertTrue(q.offer(pdelay, SHORT_DELAY_MS, MILLISECONDS));
        t.interrupt();
        t.join();
    }


    /**
     * peek returns next element, or null if empty
     */
    public void testPeek() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.peek()));
            assertEquals(new PDelay(i), ((PDelay)q.poll()));
            if (q.isEmpty())
                assertNull(q.peek());
            else
                assertFalse(new PDelay(i).equals(q.peek()));
        }
        assertNull(q.peek());
    }

    /**
     * element returns next element, or throws NSEE if empty
     */
    public void testElement() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.element()));
            q.poll();
        }
        try {
            q.element();
            shouldThrow();
        } catch (NoSuchElementException success) {}
    }

    /**
     * remove removes next element, or throws NSEE if empty
     */
    public void testRemove() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(new PDelay(i), ((PDelay)q.remove()));
        }
        try {
            q.remove();
            shouldThrow();
        } catch (NoSuchElementException success) {}
    }

    /**
     * remove(x) removes x and returns true if present
     */
    public void testRemoveElement() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 1; i < SIZE; i+=2) {
            assertTrue(q.remove(new PDelay(i)));
        }
        for (int i = 0; i < SIZE; i+=2) {
            assertTrue(q.remove(new PDelay(i)));
            assertFalse(q.remove(new PDelay(i+1)));
        }
        assertTrue(q.isEmpty());
    }

    /**
     * contains(x) reports true when elements added but not yet removed
     */
    public void testContains() {
        DelayQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(q.contains(new PDelay(i)));
            q.poll();
            assertFalse(q.contains(new PDelay(i)));
        }
    }

    /**
     * clear removes all elements
     */
    public void testClear() {
        DelayQueue q = populatedQueue(SIZE);
        q.clear();
        assertTrue(q.isEmpty());
        assertEquals(0, q.size());
        assertEquals(NOCAP, q.remainingCapacity());
        PDelay x = new PDelay(1);
        q.add(x);
        assertFalse(q.isEmpty());
        assertTrue(q.contains(x));
        q.clear();
        assertTrue(q.isEmpty());
    }

    /**
     * containsAll(c) is true when c contains a subset of elements
     */
    public void testContainsAll() {
        DelayQueue q = populatedQueue(SIZE);
        DelayQueue p = new DelayQueue();
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(q.containsAll(p));
            assertFalse(p.containsAll(q));
            p.add(new PDelay(i));
        }
        assertTrue(p.containsAll(q));
    }

    /**
     * retainAll(c) retains only those elements of c and reports true if changed
     */
    public void testRetainAll() {
        DelayQueue q = populatedQueue(SIZE);
        DelayQueue p = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            boolean changed = q.retainAll(p);
            if (i == 0)
                assertFalse(changed);
            else
                assertTrue(changed);

            assertTrue(q.containsAll(p));
            assertEquals(SIZE-i, q.size());
            p.remove();
        }
    }

    /**
     * removeAll(c) removes only those elements of c and reports true if changed
     */
    public void testRemoveAll() {
        for (int i = 1; i < SIZE; ++i) {
            DelayQueue q = populatedQueue(SIZE);
            DelayQueue p = populatedQueue(i);
            assertTrue(q.removeAll(p));
            assertEquals(SIZE-i, q.size());
            for (int j = 0; j < i; ++j) {
                PDelay I = (PDelay)(p.remove());
                assertFalse(q.contains(I));
            }
        }
    }

    /**
     * toArray contains all elements
     */
    public void testToArray() throws InterruptedException {
        DelayQueue q = populatedQueue(SIZE);
        Object[] o = q.toArray();
        Arrays.sort(o);
        for (int i = 0; i < o.length; i++)
            assertEquals(o[i], q.take());
    }

    /**
     * toArray(a) contains all elements
     */
    public void testToArray2() throws InterruptedException {
        DelayQueue q = populatedQueue(SIZE);
        PDelay[] ints = new PDelay[SIZE];
        ints = (PDelay[])q.toArray(ints);
        Arrays.sort(ints);
        for (int i = 0; i < ints.length; i++)
            assertEquals(ints[i], q.take());
    }


    /**
     * toArray(null) throws NPE
     */
    public void testToArray_BadArg() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            Object o[] = q.toArray(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * toArray with incompatible array type throws CCE
     */
    public void testToArray1_BadArg() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            Object o[] = q.toArray(new String[10]);
            shouldThrow();
        } catch (ArrayStoreException success) {}
    }

    /**
     * iterator iterates through all elements
     */
    public void testIterator() {
        DelayQueue q = populatedQueue(SIZE);
        int i = 0;
        Iterator it = q.iterator();
        while (it.hasNext()) {
            assertTrue(q.contains(it.next()));
            ++i;
        }
        assertEquals(i, SIZE);
    }

    /**
     * iterator.remove removes current element
     */
    public void testIteratorRemove () {
        final DelayQueue q = new DelayQueue();
        q.add(new PDelay(2));
        q.add(new PDelay(1));
        q.add(new PDelay(3));
        Iterator it = q.iterator();
        it.next();
        it.remove();
        it = q.iterator();
        assertEquals(it.next(), new PDelay(2));
        assertEquals(it.next(), new PDelay(3));
        assertFalse(it.hasNext());
    }


    /**
     * toString contains toStrings of elements
     */
    public void testToString() {
        DelayQueue q = populatedQueue(SIZE);
        String s = q.toString();
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(s.indexOf(String.valueOf(Integer.MIN_VALUE+i)) >= 0);
        }
    }

    /**
     * offer transfers elements across Executor tasks
     */
    public void testPollInExecutor() {
        final DelayQueue q = new DelayQueue();
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.execute(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                assertNull(q.poll());
                assertTrue(null != q.poll(MEDIUM_DELAY_MS, MILLISECONDS));
                assertTrue(q.isEmpty());
            }});

        executor.execute(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                Thread.sleep(SHORT_DELAY_MS);
                q.put(new PDelay(1));
            }});

        joinPool(executor);
    }


    /**
     * Delayed actions do not occur until their delay elapses
     */
    public void testDelay() throws InterruptedException {
        DelayQueue q = new DelayQueue();
        NanoDelay[] elements = new NanoDelay[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            elements[i] = new NanoDelay(1000000000L + 1000000L * (SIZE - i));
        }
        for (int i = 0; i < SIZE; ++i) {
            q.add(elements[i]);
        }

        long last = 0;
        for (int i = 0; i < SIZE; ++i) {
            NanoDelay e = (NanoDelay)(q.take());
            long tt = e.getTriggerTime();
            assertTrue(tt <= System.nanoTime());
            if (i != 0)
                assertTrue(tt >= last);
            last = tt;
        }
    }

    /**
     * peek of a non-empty queue returns non-null even if not expired
     */
    public void testPeekDelayed() {
        DelayQueue q = new DelayQueue();
        q.add(new NanoDelay(Long.MAX_VALUE));
        assert(q.peek() != null);
    }


    /**
     * poll of a non-empty queue returns null if no expired elements.
     */
    public void testPollDelayed() {
        DelayQueue q = new DelayQueue();
        q.add(new NanoDelay(Long.MAX_VALUE));
        assertNull(q.poll());
    }

    /**
     * timed poll of a non-empty queue returns null if no expired elements.
     */
    public void testTimedPollDelayed() throws InterruptedException {
        DelayQueue q = new DelayQueue();
        q.add(new NanoDelay(LONG_DELAY_MS * 1000000L));
        assertNull(q.poll(SHORT_DELAY_MS, MILLISECONDS));
    }

    /**
     * drainTo(null) throws NPE
     */
    public void testDrainToNull() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * drainTo(this) throws IAE
     */
    public void testDrainToSelf() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(q);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * drainTo(c) empties queue into another collection c
     */
    public void testDrainTo() {
        DelayQueue q = new DelayQueue();
        PDelay[] elems = new PDelay[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            elems[i] = new PDelay(i);
            q.add(elems[i]);
        }
        ArrayList l = new ArrayList();
        q.drainTo(l);
        assertEquals(q.size(), 0);
        for (int i = 0; i < SIZE; ++i)
            assertEquals(l.get(i), elems[i]);
        q.add(elems[0]);
        q.add(elems[1]);
        assertFalse(q.isEmpty());
        assertTrue(q.contains(elems[0]));
        assertTrue(q.contains(elems[1]));
        l.clear();
        q.drainTo(l);
        assertEquals(q.size(), 0);
        assertEquals(l.size(), 2);
        for (int i = 0; i < 2; ++i)
            assertEquals(l.get(i), elems[i]);
    }

    /**
     * drainTo empties queue
     */
    public void testDrainToWithActivePut() throws InterruptedException {
        final DelayQueue q = populatedQueue(SIZE);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() {
                q.put(new PDelay(SIZE+1));
            }});

        t.start();
        ArrayList l = new ArrayList();
        q.drainTo(l);
        assertTrue(l.size() >= SIZE);
        t.join();
        assertTrue(q.size() + l.size() >= SIZE);
    }

    /**
     * drainTo(null, n) throws NPE
     */
    public void testDrainToNullN() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(null, 0);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * drainTo(this, n) throws IAE
     */
    public void testDrainToSelfN() {
        DelayQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(q, 0);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * drainTo(c, n) empties first max {n, size} elements of queue into c
     */
    public void testDrainToN() {
        for (int i = 0; i < SIZE + 2; ++i) {
            DelayQueue q = populatedQueue(SIZE);
            ArrayList l = new ArrayList();
            q.drainTo(l, i);
            int k = (i < SIZE)? i : SIZE;
            assertEquals(q.size(), SIZE-k);
            assertEquals(l.size(), k);
        }
    }


}
