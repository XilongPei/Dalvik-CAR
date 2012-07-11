/*
 * a part of Elastos
 */

package java.lang;

import dalvik.CAR.CARCallbackFunc;

/**
 * Elastos Delegates
 *
 * class Foo {
 *    Delegate  callback;
 * }
 *
 * obj = new Foo();
 *
 * //JavaClassname looks like it in JNI FindClass(), packageName/className, "java/lang/String"
 * obj.callback = new Delegates("JavaClassname", "methodname");
 *
 * //should this be supported?
 * obj.callback = null;
 */
public final class Delegates {

    //minimize pointer value of Method
    private static final int MIN_METHOD_ID = 0x800;

    int[] CallbackMethods;
    int[] ThisObjs;
    int   count;

    //final String  className;
    //final String  callbackName;

    /**
     * Constructs a Delegate with className and callbackName, suit for java static method
     *
     * @param className
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Delegates(String className, String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
        ThisObjs = new int[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodNoSignature(className, callbackName);
        ThisObjs[0] = 0;
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }

    /**
     * Constructs a Delegate with callbackName
     * use the newer object as 'this' of running the callback method
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Delegates(String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
        ThisObjs = new int[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodInSameClass(callbackName);
        ThisObjs[0] = 0;
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }


    /**
     * Constructs an Delegate with object and callbackName
     * random object to be run
     *
     * @param callbackName
     *            the CAR callback name.
     */
    public Delegates(Object obj, String callbackName) throws InstantiationException
    {
        CallbackMethods = new int[1];
        count = 1;

        CallbackMethods[0] = CARCallbackFunc.GetJavaMethodNoSignature(obj, callbackName);
        ThisObjs[0] = CARCallbackFunc.Object2Int(obj);
        String  info;

        info = String.valueOf(CallbackMethods);
        if (CallbackMethods[0] < MIN_METHOD_ID) {
            throw new InstantiationException(info);
        }
    }

    /**
     * Constructs a Delegate with object and callbackName
     * random object to be run
     *
     * @param obj
     *
     */
    public Delegates(Object obj) throws InstantiationException
    {
        CallbackMethods = new int[1];
        count = 1;

        CallbackMethods[0] = 0;
        ThisObjs[0] = CARCallbackFunc.Object2Int(obj);
    }

    /**
     * Constructs a Delegate
     *
     */
    public Delegates() throws InstantiationException
    {
        CallbackMethods = new int[1];
        count = 1;

        CallbackMethods[0] = 0;
        ThisObjs[0] = 0;
    }


    /**
     * Append methods and objects information in a Delegate into another
     *
     * @param dgt
     *
     */
    public void Append(Delegates dgt)
    {
        int[] iary;
        int[] iary2;
        int   i;

        iary = CallbackMethods;
        iary2 = ThisObjs;
        CallbackMethods = new int[count+dgt.count];
        ThisObjs = new int[count+dgt.count];
        for (i = 0;  i < count;  i++) {
            CallbackMethods[i] = iary[i];
            ThisObjs[i] =  iary2[i];
        }

        for (i = 0;  i < dgt.count;  i++) {
            CallbackMethods[count+i] = dgt.CallbackMethods[i];
            ThisObjs[count+i] =  dgt.ThisObjs[i];
        }
    }

    public void Remove(Delegates dgt)
    {
        //TODO, how to remove?
        ;
    }

}

