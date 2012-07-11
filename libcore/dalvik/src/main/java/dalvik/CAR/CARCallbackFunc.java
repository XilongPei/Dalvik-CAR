package dalvik.CAR;

public class CARCallbackFunc{
	native public static void addCallbackHandler(Object obj, String callbackMethodName, String className, String methodName, String signature);
	native public static void addCallbackHandlerNoSignatire(Object obj, String callbackMethodName, String className, String methodName);
	native public static void removeCallbackHandler(Object obj, String callbackMethodName, String className, String methodName, String signature);
	native public static void removeAllCallbackHandler(Object obj);
	native public static int GetJavaMethodNoSignature(String className, String methodName);
	native public static int GetJavaMethodNoSignature(Object obj, String methodName);
	native public static int GetJavaMethodInSameClass(String methodName);
	native public static int Object2Int(Object obj);
}
