//import elastos.platform.runtime;
import kortide.samples.ClockAssembly;

class WallClock {

	void setTime(int hour,int minute,int second) { clockAssembly.setTime(hour,minute,second); }
	void setAlarm(){ clockAssembly.SetAlarm();}

	class TimeTickCallback extends ClockAssembly.TimeTickCallback {
		void OnTimeTickCallback() {
			System.out.println("OnTimeTickCallback");
		}
	}
	class AlarmCallback extends ClockAssembly.AlarmCallback {
		void OnAlarmCallback() {
			System.out.println("OnAlarmCallback");
		}
	}

	WallClock(){
		clockAssembly = new ClockAssembly();

		clockAssembly.AddAlarmCallback(new AlarmCallback());
	}

	ClockAssembly clockAssembly;
}



