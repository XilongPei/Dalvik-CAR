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
import java.util.concurrent.*;
import static java.util.concurrent.TimeUnit.MILLISECONDS;
import java.io.*;

public class PriorityBlockingQueueTest extends JSR166TestCase {
    public static Test suite() {
        return new TestSuite(PriorityBlockingQueueTest.class);
    }

    private static final int NOCAP = Integer.MAX_VALUE;

    /** Sample Comparator */
    static class MyReverseComparator implements Comparator {
        public int compare(Object x, Object y) {
            return ((Comparable)y).compareTo(x);
        }
    }

    /**
     * Create a queue of given size containing consecutive
     * Integers 0 ... n.
     */
    private PriorityBlockingQueue populatedQueue(int n) {
        PriorityBlockingQueue q = new PriorityBlockingQueue(n);
        assertTrue(q.isEmpty());
        for (int i = n-1; i >= 0; i-=2)
            assertTrue(q.offer(new Integer(i)));
        for (int i = (n & 1); i < n; i+=2)
            assertTrue(q.offer(new Integer(i)));
        assertFalse(q.isEmpty());
        assertEquals(NOCAP, q.remainingCapacity());
        assertEquals(n, q.size());
        return q;
    }

    /**
     * A new queue has unbounded capacity
     */
    public void testConstructor1() {
        assertEquals(NOCAP, new PriorityBlockingQueue(SIZE).remainingCapacity());
    }

    /**
     * Constructor throws IAE if capacity argument nonpositive
     */
    public void testConstructor2() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(0);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * Initializing from null Collection throws NPE
     */
    public void testConstructor3() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Initializing from Collection of null elements throws NPE
     */
    public void testConstructor4() {
        try {
            Integer[] ints = new Integer[SIZE];
            PriorityBlockingQueue q = new PriorityBlockingQueue(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Initializing from Collection with some null elements throws NPE
     */
    public void testConstructor5() {
        try {
            Integer[] ints = new Integer[SIZE];
            for (int i = 0; i < SIZE-1; ++i)
                ints[i] = new Integer(i);
            PriorityBlockingQueue q = new PriorityBlockingQueue(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Queue contains all elements of collection used to initialize
     */
    public void testConstructor6() {
        Integer[] ints = new Integer[SIZE];
        for (int i = 0; i < SIZE; ++i)
            ints[i] = new Integer(i);
        PriorityBlockingQueue q = new PriorityBlockingQueue(Arrays.asList(ints));
        for (int i = 0; i < SIZE; ++i)
            assertEquals(ints[i], q.poll());
    }

    /**
     * The comparator used in constructor is used
     */
    public void testConstructor7() {
        MyReverseComparator cmp = new MyReverseComparator();
        PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE, cmp);
        assertEquals(cmp, q.comparator());
        Integer[] ints = new Integer[SIZE];
        for (int i = 0; i < SIZE; ++i)
            ints[i] = new Integer(i);
        q.addAll(Arrays.asList(ints));
        for (int i = SIZE-1; i >= 0; --i)
            assertEquals(ints[i], q.poll());
    }

    /**
     * isEmpty is true before add, false after
     */
    public void testEmpty() {
        PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        assertTrue(q.isEmpty());
        assertEquals(NOCAP, q.remainingCapacity());
        q.add(one);
        assertFalse(q.isEmpty());
        q.add(two);
        q.remove();
        q.remove();
        assertTrue(q.isEmpty());
    }

    /**
     * remainingCapacity does not change when elements added or removed,
     * but size does
     */
    public void testRemainingCapacity() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(NOCAP, q.remainingCapacity());
            assertEquals(SIZE-i, q.size());
            q.remove();
        }
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(NOCAP, q.remainingCapacity());
            assertEquals(i, q.size());
            q.add(new Integer(i));
        }
    }

    /**
     * offer(null) throws NPE
     */
    public void testOfferNull() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(1);
            q.offer(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * add(null) throws NPE
     */
    public void testAddNull() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(1);
            q.add(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Offer of comparable element succeeds
     */
    public void testOffer() {
        PriorityBlockingQueue q = new PriorityBlockingQueue(1);
        assertTrue(q.offer(zero));
        assertTrue(q.offer(one));
    }

    /**
     * Offer of non-Comparable throws CCE
     */
    public void testOfferNonComparable() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(1);
            q.offer(new Object());
            q.offer(new Object());
            q.offer(new Object());
            shouldThrow();
        } catch (ClassCastException success) {}
    }

    /**
     * add of comparable succeeds
     */
    public void testAdd() {
        PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.size());
            assertTrue(q.add(new Integer(i)));
        }
    }

    /**
     * addAll(null) throws NPE
     */
    public void testAddAll1() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(1);
            q.addAll(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * addAll(this) throws IAE
     */
    public void testAddAllSelf() {
        try {
            PriorityBlockingQueue q = populatedQueue(SIZE);
            q.addAll(q);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * addAll of a collection with null elements throws NPE
     */
    public void testAddAll2() {
        try {
            PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
            Integer[] ints = new Integer[SIZE];
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
            PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
            Integer[] ints = new Integer[SIZE];
            for (int i = 0; i < SIZE-1; ++i)
                ints[i] = new Integer(i);
            q.addAll(Arrays.asList(ints));
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * Queue contains all elements of successful addAll
     */
    public void testAddAll5() {
        Integer[] empty = new Integer[0];
        Integer[] ints = new Integer[SIZE];
        for (int i = SIZE-1; i >= 0; --i)
            ints[i] = new Integer(i);
        PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
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
            PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
            q.put(null);
            shouldThrow();
        } catch (NullPointerException success) {}
     }

    /**
     * all elements successfully put are contained
     */
     public void testPut() {
         PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE);
         for (int i = 0; i < SIZE; ++i) {
             Integer I = new Integer(i);
             q.put(I);
             assertTrue(q.contains(I));
         }
         assertEquals(SIZE, q.size());
    }

    /**
     * put doesn't block waiting for take
     */
    public void testPutWithTake() throws InterruptedException {
        final PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        final int size = 4;
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() {
                for (int i = 0; i < size; i++)
                    q.put(new Integer(0));
            }});

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        assertEquals(q.size(), size);
        q.take();
        t.interrupt();
        t.join();
    }

    /**
     * timed offer does not time out
     */
    public void testTimedOffer() throws InterruptedException {
        final PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() {
                q.put(new Integer(0));
                q.put(new Integer(0));
                assertTrue(q.offer(new Integer(0), SHORT_DELAY_MS, MILLISECONDS));
                assertTrue(q.offer(new Integer(0), LONG_DELAY_MS, MILLISECONDS));
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
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.take());
        }
    }

    /**
     * take blocks interruptibly when empty
     */
    public void testTakeFromEmpty() throws InterruptedException {
        final PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        Thread t = new Thread(new CheckedInterruptedRunnable() {
            public void realRun() throws InterruptedException {
                q.take();
            }});

        t.start();
        Thread.sleep(SHORT_DELAY_MS);
        t.interrupt();
        t.join();
    }

    /**
     * Take removes existing elements until empty, then blocks interruptibly
     */
    public void testBlockingTake() throws InterruptedException {
        final PriorityBlockingQueue q = populatedQueue(SIZE);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                for (int i = 0; i < SIZE; ++i) {
                    assertEquals(i, q.take());
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
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.poll());
        }
        assertNull(q.poll());
    }

    /**
     * timed pool with zero timeout succeeds when non-empty, else times out
     */
    public void testTimedPoll0() throws InterruptedException {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.poll(0, MILLISECONDS));
        }
        assertNull(q.poll(0, MILLISECONDS));
    }

    /**
     * timed pool with nonzero timeout succeeds when non-empty, else times out
     */
    public void testTimedPoll() throws InterruptedException {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.poll(SHORT_DELAY_MS, MILLISECONDS));
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
                PriorityBlockingQueue q = populatedQueue(SIZE);
                for (int i = 0; i < SIZE; ++i) {
                    assertEquals(i, q.poll(SHORT_DELAY_MS, MILLISECONDS));
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
        final PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                assertNull(q.poll(SHORT_DELAY_MS, MILLISECONDS));
                assertSame(zero, q.poll(MEDIUM_DELAY_MS, MILLISECONDS));
                try {
                    q.poll(LONG_DELAY_MS, MILLISECONDS);
                    shouldThrow();
                } catch (InterruptedException success) {}
            }});

        t.start();
        Thread.sleep(SMALL_DELAY_MS);
        assertTrue(q.offer(zero, SHORT_DELAY_MS, MILLISECONDS));
        t.interrupt();
        t.join();
    }


    /**
     * peek returns next element, or null if empty
     */
    public void testPeek() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.peek());
            assertEquals(i, q.poll());
            assertTrue(q.peek() == null ||
                       !q.peek().equals(i));
        }
        assertNull(q.peek());
    }

    /**
     * element returns next element, or throws NSEE if empty
     */
    public void testElement() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.element());
            assertEquals(i, q.poll());
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
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertEquals(i, q.remove());
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
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 1; i < SIZE; i+=2) {
            assertTrue(q.remove(new Integer(i)));
        }
        for (int i = 0; i < SIZE; i+=2) {
            assertTrue(q.remove(new Integer(i)));
            assertFalse(q.remove(new Integer(i+1)));
        }
        assertTrue(q.isEmpty());
    }

    /**
     * contains(x) reports true when elements added but not yet removed
     */
    public void testContains() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(q.contains(new Integer(i)));
            q.poll();
            assertFalse(q.contains(new Integer(i)));
        }
    }

    /**
     * clear removes all elements
     */
    public void testClear() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        q.clear();
        assertTrue(q.isEmpty());
        assertEquals(0, q.size());
        q.add(one);
        assertFalse(q.isEmpty());
        assertTrue(q.contains(one));
        q.clear();
        assertTrue(q.isEmpty());
    }

    /**
     * containsAll(c) is true when c contains a subset of elements
     */
    public void testContainsAll() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        PriorityBlockingQueue p = new PriorityBlockingQueue(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(q.containsAll(p));
            assertFalse(p.containsAll(q));
            p.add(new Integer(i));
        }
        assertTrue(p.containsAll(q));
    }

    /**
     * retainAll(c) retains only those elements of c and reports true if changed
     */
    public void testRetainAll() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        PriorityBlockingQueue p = populatedQueue(SIZE);
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
            PriorityBlockingQueue q = populatedQueue(SIZE);
            PriorityBlockingQueue p = populatedQueue(i);
            assertTrue(q.removeAll(p));
            assertEquals(SIZE-i, q.size());
            for (int j = 0; j < i; ++j) {
                Integer I = (Integer)(p.remove());
                assertFalse(q.contains(I));
            }
        }
    }

    /**
     *  toArray contains all elements
     */
    public void testToArray() throws InterruptedException {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        Object[] o = q.toArray();
        Arrays.sort(o);
        for (int i = 0; i < o.length; i++)
            assertEquals(o[i], q.take());
    }

    /**
     * toArray(a) contains all elements
     */
    public void testToArray2() throws InterruptedException {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        Integer[] ints = new Integer[SIZE];
        ints = (Integer[])q.toArray(ints);
        Arrays.sort(ints);
        for (int i = 0; i < ints.length; i++)
            assertEquals(ints[i], q.take());
    }

    /**
     * toArray(null) throws NPE
     */
    public void testToArray_BadArg() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            Object o[] = q.toArray(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * toArray with incompatible array type throws CCE
     */
    public void testToArray1_BadArg() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            Object o[] = q.toArray(new String[10]);
            shouldThrow();
        } catch (ArrayStoreException success) {}
    }

    /**
     * iterator iterates through all elements
     */
    public void testIterator() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
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
        final PriorityBlockingQueue q = new PriorityBlockingQueue(3);
        q.add(new Integer(2));
        q.add(new Integer(1));
        q.add(new Integer(3));

        Iterator it = q.iterator();
        it.next();
        it.remove();

        it = q.iterator();
        assertEquals(it.next(), new Integer(2));
        assertEquals(it.next(), new Integer(3));
        assertFalse(it.hasNext());
    }


    /**
     * toString contains toStrings of elements
     */
    public void testToString() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        String s = q.toString();
        for (int i = 0; i < SIZE; ++i) {
            assertTrue(s.indexOf(String.valueOf(i)) >= 0);
        }
    }

    /**
     * offer transfers elements across Executor tasks
     */
    public void testPollInExecutor() {
        final PriorityBlockingQueue q = new PriorityBlockingQueue(2);
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.execute(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                assertNull(q.poll());
                assertSame(one, q.poll(MEDIUM_DELAY_MS, MILLISECONDS));
                assertTrue(q.isEmpty());
            }});

        executor.execute(new CheckedRunnable() {
            public void realRun() throws InterruptedException {
                Thread.sleep(SMALL_DELAY_MS);
                q.put(one);
            }});

        joinPool(executor);
    }

    /**
     * A deserialized serialized queue has same elements
     */
    public void testSerialization() throws Exception {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        ByteArrayOutputStream bout = new ByteArrayOutputStream(10000);
        ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(bout));
        out.writeObject(q);
        out.close();

        ByteArrayInputStream bin = new ByteArrayInputStream(bout.toByteArray());
        ObjectInputStream in = new ObjectInputStream(new BufferedInputStream(bin));
        PriorityBlockingQueue r = (PriorityBlockingQueue)in.readObject();
        assertEquals(q.size(), r.size());
        while (!q.isEmpty())
            assertEquals(q.remove(), r.remove());
    }

    /**
     * drainTo(null) throws NPE
     */
    public void testDrainToNull() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(null);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * drainTo(this) throws IAE
     */
    public void testDrainToSelf() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(q);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * drainTo(c) empties queue into another collection c
     */
    public void testDrainTo() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        ArrayList l = new ArrayList();
        q.drainTo(l);
        assertEquals(q.size(), 0);
        assertEquals(l.size(), SIZE);
        for (int i = 0; i < SIZE; ++i)
            assertEquals(l.get(i), new Integer(i));
        q.add(zero);
        q.add(one);
        assertFalse(q.isEmpty());
        assertTrue(q.contains(zero));
        assertTrue(q.contains(one));
        l.clear();
        q.drainTo(l);
        assertEquals(q.size(), 0);
        assertEquals(l.size(), 2);
        for (int i = 0; i < 2; ++i)
            assertEquals(l.get(i), new Integer(i));
    }

    /**
     * drainTo empties queue
     */
    public void testDrainToWithActivePut() throws InterruptedException {
        final PriorityBlockingQueue q = populatedQueue(SIZE);
        Thread t = new Thread(new CheckedRunnable() {
            public void realRun() {
                q.put(new Integer(SIZE+1));
            }});

        t.start();
        ArrayList l = new ArrayList();
        q.drainTo(l);
        assertTrue(l.size() >= SIZE);
        for (int i = 0; i < SIZE; ++i)
            assertEquals(l.get(i), new Integer(i));
        t.join();
        assertTrue(q.size() + l.size() >= SIZE);
    }

    /**
     * drainTo(null, n) throws NPE
     */
    public void testDrainToNullN() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(null, 0);
            shouldThrow();
        } catch (NullPointerException success) {}
    }

    /**
     * drainTo(this, n) throws IAE
     */
    public void testDrainToSelfN() {
        PriorityBlockingQueue q = populatedQueue(SIZE);
        try {
            q.drainTo(q, 0);
            shouldThrow();
        } catch (IllegalArgumentException success) {}
    }

    /**
     * drainTo(c, n) empties first max {n, size} elements of queue into c
     */
    public void testDrainToN() {
        PriorityBlockingQueue q = new PriorityBlockingQueue(SIZE*2);
        for (int i = 0; i < SIZE + 2; ++i) {
            for (int j = 0; j < SIZE; j++)
                assertTrue(q.offer(new Integer(j)));
            ArrayList l = new ArrayList();
            q.drainTo(l, i);
            int k = (i < SIZE)? i : SIZE;
            assertEquals(l.size(), k);
            assertEquals(q.size(), SIZE-k);
            for (int j = 0; j < k; ++j)
                assertEquals(l.get(j), new Integer(j));
            while (q.poll() != null) ;
        }
    }

}
