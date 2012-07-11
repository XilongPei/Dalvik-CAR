set ADB_PATH=E:\swap\android-sdk-windows-23\platform-tools\

%ADB_PATH%\adb push ecoloader.dso /data/data/com.elastos.runtime/elastos
%ADB_PATH%\adb push Elastos.Archiving.zlib.eco /data/data/com.elastos.runtime/elastos
%ADB_PATH%\adb push Elastos.Runtime.CarRuntime.eco /data/data/com.elastos.runtime/elastos
%ADB_PATH%\adb push Elastos.Runtime.eco /data/data/com.elastos.runtime/elastos
%ADB_PATH%\adb push JniBridge.so /data/data/com.elastos.runtime/elastos
%ADB_PATH%\adb push KD.dso /data/data/com.elastos.runtime/elastos

set ADB_PATH=