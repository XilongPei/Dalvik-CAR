/*
 * a part of Elastos
 */

package java.lang;

import dalvik.CAR.CARCallbackFunc;

/**
 * Elastos Callbacks
 *
 * class Foo {
 *    Callbacks  callback;
 * }
 *
 * obj = new Foo();
 *
 * //JavaClassname looks like it in JNI FindClass(), packageName/className, "java/lang/String"
 * obj.callback = new Callbacks("JavaClassname", "methodname");
 *
 * //should this be supported?
 * obj.callback = null;
 */
public class Callbacks {

    //minimize pointer value of Method
    private static final int MIN_METHOD_ID = 0x800;

    int[] CallbackMethods;
    Object[] ThisObjs;
    int   count;


    /**
     * Constructs a Callbacks with className and callbackName, suit for java static method
     *
     * @param className
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Callbacks(String className, String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
        ThisObjs = new Object[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodNoSignature(className, callbackName);
        ThisObjs[0] = null;
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }

    /**
     * Constructs a Callbacks with callbackName
     * use the newer object as 'this' of running the callback method
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Callbacks(String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
        ThisObjs = new Object[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodInSameClass(callbackName);
        ThisObjs[0] = null;
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }


    /**
     * Constructs an Callbacks with object and callbackName
     * random object to be run
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Callbacks(Object obj, String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
		ThisObjs = new Object[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodNoSignature(obj, callbackName);
        ThisObjs[0] = obj;
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }

    /**
     * Constructs a Callbacks with object and callbackName
     * random object to be run
     *
     * @param obj
     *
     */
    public Callbacks(Object obj)
    {
        CallbackMethods = new int[1];
		ThisObjs = new Object[1];
        count = 1;

        CallbackMethods[0] = 0;
        ThisObjs[0] = obj;
    }

    /**
     * Constructs a Callbacks
     *
     */
    public Callbacks()
    {
        CallbackMethods = new int[1];
		ThisObjs = new Object[1];
        count = 1;

        CallbackMethods[0] = 0;
        ThisObjs[0] = null;
    }


    /**
     * Append methods and objects information in a Callbacks into another
     *
     * @param cb
     *
     */
    public void Append(Callbacks cb)
    {
        int[] iary;
        Object[] iary2;
        int   i;

        iary = CallbackMethods;
        iary2 = ThisObjs;
        CallbackMethods = new int[count+cb.count];
        ThisObjs = new Object[count+cb.count];
        for (i = 0;  i < count;  i++) {
            CallbackMethods[i] = iary[i];
            ThisObjs[i] =  iary2[i];
        }

        for (i = 0;  i < cb.count;  i++) {
            CallbackMethods[count+i] = cb.CallbackMethods[i];
            ThisObjs[count+i] =  iary2[i];
        }
    }

    public void Remove(Callbacks cb)
    {
        //TODO, how to remove?
        ;
    }


}

