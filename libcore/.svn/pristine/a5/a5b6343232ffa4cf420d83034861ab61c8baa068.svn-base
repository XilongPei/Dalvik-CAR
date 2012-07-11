/*
 * Elastos Applet main thread, create or shutdown
 */

package java.lang;

public class MsgLoopThread {

    /* some of these are accessed directly by the VM; do not rename them */
    VMThread vmThread;
    int      id;

    /**
     * Constructs a new AppletThread
     */
    public MsgLoopThread() {
        id = vmThread.CreateMsgLoopThread();
    }

    protected void finalize() throws Throwable {
        if (id != 0)
            vmThread.ShutdownMsgLoopThread(id);
    }

    /**
     * Destroy an AppletThread
     */
    public boolean DestroyMsgLoopThread() {
        if (id != 0) {
            vmThread.ShutdownMsgLoopThread(id);
            id = 0;
            return  true;
        }

        return  false;
    }

}


