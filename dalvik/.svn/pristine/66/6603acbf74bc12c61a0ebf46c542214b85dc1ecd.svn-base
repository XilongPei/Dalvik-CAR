package kortide.samples;

import dalvik.annotation.ElastosClass;
import java.lang.Callbacks;

@ElastosClass(Module="ClockAssembly.eco", Class="CClockAssembly")
public class ClockAssembly {

	public native void setTime(int hour,int minute,int second);
	public native void SetAlarm();

    public static class TimeTickCallback extends Callbacks {
		void OnTimeTickCallback(){}
    }
    public static class AlarmCallback extends Callbacks {
		void OnAlarmCallback(){}
    }
	
	public void AddAlarmCallback(AlarmCallback alarmCallback){
		AlarmCallback = alarmCallback;
	}

    private AlarmCallback AlarmCallback;
}
