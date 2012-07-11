import dalvik.annotation.ElastosClass;
@ElastosClass(Module="TestBasicType.eco", Class="CTestBasicType")
class CTestBasicType{
	native boolean boolNon(boolean i);

	native boolean boolAnd(boolean i, boolean j);

	native boolean boolOr(boolean i, boolean j);

	native StringBuffer strCopy(String i);

	native StringBuffer strCon(String i, String j);

	native boolean strStartwith(String i, String j);

}
