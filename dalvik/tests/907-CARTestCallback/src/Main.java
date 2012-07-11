import dalvik.CAR.CARCallbackFunc;

class Main{
	
	public static void EmployeeEvent_callback()
	{
		System.out.println("callback EmployeeEvent!!!");
	}
	
	public static void FiremanEvent_callback()
	{
		System.out.println("callback FiremanEvent~~~");
	}
	
	public static void main(String []args){
		System.out.println("test start here");
		CTestCallback ctc = new CTestCallback();
		CARCallbackFunc.addCallbackHandler(ctc, "EmployeeEvent", "Main", "EmployeeEvent_callback", "()V");
		CARCallbackFunc.addCallbackHandler(ctc, "FiremanEvent", "Main", "FiremanEvent_callback", "()V");

        //ctc += OnEmployee;

		ctc.CatchFire();
		
		System.out.println("test end here");
	}
}
