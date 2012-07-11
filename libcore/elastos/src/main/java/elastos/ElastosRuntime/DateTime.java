/*
 * Copyright (C) 2010 elastos
 *
 * package for CAR base datatype
 */

package elastos.runtime;

import dalvik.annotation.ElastosClass;

@ElastosClass(Module="ElastosRuntime.dll", Class="DateTime")
public class DateTime {
    short year;
    byte  month;
    byte  dayofweek;
    byte  day;
    byte  hour;
    byte  minute;
    byte  second;

    //construct a DateTime through Parse
    DateTime(String time, String fmt){};

    native boolean IsValid();
    native boolean ToLocalTime();
    native boolean ToUniversalTime();
    native boolean GetInt64Data();
    native boolean SetInt64Data();
}

