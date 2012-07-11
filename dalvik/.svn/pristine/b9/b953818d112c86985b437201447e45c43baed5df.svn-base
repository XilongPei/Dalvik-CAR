class Main{
	public static void main(String []args){
		System.out.println("tests begins here....");
		
		//this is for car 
		CServer cs = new CServer();
		long time = System.currentTimeMillis();
		long l = cs.compute(10,1000000);
		System.out.println("for car:the result is " + l);
		long t = System.currentTimeMillis() - time;
		System.out.println("The time car computes is :" + t+"ms");
		//this is for java
		long time2 = System.currentTimeMillis();
		long res = 0;
		for(int j = 0; j < 1000000; j++){
			res += 10;
		}
		System.out.println("for java: the result is " + res);
		long t2 = System.currentTimeMillis() - time2 ;
		System.out.println("The time java computes is :" + t2+"ms");
	}
}
