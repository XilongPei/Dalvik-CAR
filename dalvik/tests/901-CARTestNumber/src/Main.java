

public class Main{
	public static void main(String[] args)
	{
		System.out.println("test start here\n");
		CTestNumber test = new CTestNumber();

		System.out.println("test byte:");
	    byte b1 = 0;
		byte b2 = 9;
		byte b3 = -8;
		byte b4 = 5;
		byte b5 = Byte.MIN_VALUE;
		byte b6 = Byte.MAX_VALUE;	
		int bres = b2 + b4;
		
		StringBuffer sb = new StringBuffer();
		int b = test.addByte(b2,b4);
	System.out.println(""+ b);
	
		String s = "ss" + test.addByte(b2,b4);
	    System.out.printf("ss%s\n" , s);
		System.out.println(b2 + " + " + b4 + " = " + test.addByte(b2,b4) + " (" + bres + ")");
		bres = b1 + b2;
		System.out.println(b1 + " + " + b2 + " = " + test.addByte(b1,b2) + " (" + bres + ")");
		bres = b3 + b4;
		System.out.println(b3 + " + " + b4 + " = " + test.addByte(b3,b4) + " (" + bres + ")");
		bres = b5 + b6;
		System.out.println(b5 + " + " + b6 + " = " + test.addByte(b5,b6) + " (" + bres + ")");
		bres = b2 + b6;
		System.out.println(b2 + " + " + b6 + " = " + test.addByte(b2,b6) + " (" + bres + ")");
		System.out.println();

		System.out.println("test short:");
	        short s1 = 0;
		short s2 = 9;
		short s3 = -8;
		short s4 = 5;
		short s5 = Short.MIN_VALUE;
		short s6 = Short.MAX_VALUE;	
		int sres = s2 + s4;
		System.out.println(s2 + " + " + s4 + " = " + test.addShort(s2,s4) + " (" + sres + ")");
		sres = s1 + s2;
		System.out.println(s1 + " + " + s2 + " = " + test.addShort(s1,s2) + " (" + sres + ")");
		sres = s3 + s4;
		System.out.println(s3 + " + " + s4 + " = " + test.addShort(s3,s4) + " (" + sres + ")");
		sres = s5 + s6;
		System.out.println(s5 + " + " + s6 + " = " + test.addShort(s5,s6) + " (" + sres + ")");
		sres = s2 + s6;
		System.out.println(s2 + " + " + s6 + " = " + test.addShort(s2,s6) + " (" + sres + ")");
		System.out.println();

		System.out.println("test int:");
	        int i1 = 0;
		int i2 = 309;
		int i3 = -80;
		int i4 = 50;
		int i5 = Integer.MIN_VALUE;
		int i6 = Integer.MAX_VALUE;	
		int ires = i2 + i4;
		System.out.println(i2 + " + " + i4 + " = " + test.addInt(i2,i4) + " (" + ires + ")");
		ires = i1 + i2;
		System.out.println(i1 + " + " + i2 + " = " + test.addInt(i1,i2) + " (" + ires + ")");
		ires = i3 + i4;
		System.out.println(i3 + " + " + i4 + " = " + test.addInt(i3,i4) + " (" + ires + ")");
		ires = i5 + i6;
		System.out.println(i5 + " + " + i6 + " = " + test.addInt(i5,i6) + " (" + ires + ")");
		ires = i2 + i6;
		System.out.println(i2 + " + " + i6 + " = " + test.addInt(i2,i6) + " (" + ires + ")");
		System.out.println();

		System.out.println("test long:");
	        long l1 = 0;
		long l2 = 309392394;
		long l3 = -8034823;
		long l4 = 5234230;
		long l5 = Long.MIN_VALUE;
		long l6 = Long.MAX_VALUE;	
		long lres = l2 + l4;
		System.out.println(l2 + " + " + l4 + " = " + test.addLong(l2,l4) + " (" + lres + ")");
		lres = l1 + l2;
		System.out.println(l1 + " + " + l2 + " = " + test.addLong(l1,l2) + " (" + lres + ")");
		lres = l3 + l4;
		System.out.println(l3 + " + " + l4 + " = " + test.addLong(l3,l4) + " (" + lres + ")");
		lres = l5 + l6;
		System.out.println(l5 + " + " + l6 + " = " + test.addLong(l5,l6) + " (" + lres + ")");
		lres = l2 + l6;
		System.out.println(l2 + " + " + l6 + " = " + test.addLong(l2,l6) + " (" + lres + ")");
		System.out.println();

		System.out.println("test float:");
	        float f1 = 0f;
		float f2 = 3093.294f;
		float f3 = -80.823f;
		float f4 = 5.234230f;
		float f5 = Float.MIN_VALUE;
		float f6 = Float.MAX_VALUE;	
		float fres = f2 + f4;
		System.out.println(f2 + " + " + f4 + " = " + test.addFloat(f2,f4) + " (" + fres + ")");
		fres = f1 + f2;
		System.out.println(f1 + " + " + f2 + " = " + test.addFloat(f1,f2) + " (" + fres + ")");
		fres = f3 + f4;
		System.out.println(f3 + " + " + f4 + " = " + test.addFloat(f3,f4) + " (" + fres + ")");
		fres = f5 + f6;
		System.out.println(f5 + " + " + f6 + " = " + test.addFloat(f5,f6) + " (" + fres + ")");
		fres = f2 + f6;
		System.out.println(f2 + " + " + f6 + " = " + test.addFloat(f2,f6) + " (" + fres + ")");
		System.out.println();

		System.out.println("test double:");
	        double d1 = 0;
		double d2 = 309394023.94123123;
		double d3 = -8034821.231233;
		double d4 = 5234.230;
		double d5 = Double.MIN_VALUE;
		double d6 = Double.MAX_VALUE;	
		double dres = d2 + d4;
		System.out.println(d2 + " + " + d4 + " = " + test.addDouble(d2,d4) + " (" + dres + ")");
		dres = d1 + d2;
		System.out.println(d1 + " + " + d2 + " = " + test.addDouble(d1,d2) + " (" + dres + ")");
		dres = d3 + d4;
		System.out.println(d3 + " + " + d4 + " = " + test.addDouble(d3,d4) + " (" + dres + ")");
		dres = d5 + d6;
		System.out.println(d5 + " + " + d6 + " = " + test.addDouble(d5,d6) + " (" + dres + ")");
		dres = d2 + d6;
		System.out.println(d2 + " + " + d6 + " = " + test.addDouble(d2,d6) + " (" + dres + ")");
		System.out.println();

	}
}
