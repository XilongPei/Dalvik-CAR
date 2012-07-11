/*
 * Copyright (C) 2010 elastos
 *
 * package for CAR debugger with JDWP
 */

package elastos.CarDebugger;

public class CARObjDesc {
    String    name_CARClass;
    String    name_JavaClass;
    String    ID;
	int       CARObjSize;
    int       CARObjAddr;
    byte[]    MemDump;
    Class     CarModuleInfo;
    Class     CMethodInfo;
    boolean   IsSingleton;
    int       count_Method;
    int       count_Aspect;
    int       count_Aggregatee;
    int       count_Interface;
    int       count_Constructor;
    int       count_CallbackInterface;
    int       count_CallbackMethod;

    CARObjDesc()
    {
    	name_CARClass=null;
    	name_JavaClass=null;
    	ID=null;
    	CarModuleInfo=null;
		CARObjSize=-1;
    	CARObjAddr=-1;
    	MemDump=null;
    	CMethodInfo=null;
    	IsSingleton=false;
        count_Method=-1;
        count_Aspect=-1;
        count_Aggregatee=-1;
        count_Interface=-1;
        count_Constructor=-1;
        count_CallbackInterface=-1;
        count_CallbackMethod=-1;
    }

    void setCARClassName(String name)
    {
    	name_CARClass=name;
    }

    void setJavaClassName(String name)
    {
    	name_JavaClass=name;
    }

    void setID(String id)
    {
    	ID=id;
    }

	void setCARObjSize(int size)
    {
    	CARObjSize=size;
    }

    void setCARObjAddr(int addr)
    {
    	CARObjAddr=addr;
    }

    void setIsSingleton(boolean isSingleton)
    {
        IsSingleton=isSingleton;
    }

    void setMethodCount(int mc)
    {
        count_Method=mc;
    }

    void setAspectCount(int AsC)
    {
        count_Aspect=AsC;
    }

    void setAggregateeCount(int AgC)
    {
        count_Aggregatee=AgC;
    }

    void setInterfaceCount(int InC)
    {
        count_Interface=InC;
    }

    void setConstructorCount(int CoC)
    {
        count_Constructor=CoC;
    }

    void setCallbackInterfaceCount(int CabInC)
    {
        count_CallbackInterface=CabInC;
    }

    void setCallbackMethodCount(int CabMeC)
    {
        count_CallbackMethod=CabMeC;
    }

    void setMemDump(byte[] memDump)
    {
        MemDump=memDump;
    }
}


