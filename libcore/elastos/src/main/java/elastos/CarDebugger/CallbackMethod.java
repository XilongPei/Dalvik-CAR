/*
 * Copyright (C) 2010 elastos
 *
 * package for CAR debugger with JDWP
 */

package elastos.CarDebugger;

public class CallbackMethod {
	String involvedClass;
	String methodName;

	CallbackMethod(){
		involvedClass = null;
		methodName = null;	
	}
	
	void setClazz(String clazzStr) {
		involvedClass = clazzStr;
	}

	void setName(String nameStr) {
		methodName = nameStr;
	}	
}
