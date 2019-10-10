import com.github.sarxos.webcam.Webcam;
import com.github.sarxos.webcam.WebcamMotionDetector;
import com.github.sarxos.webcam.WebcamMotionEvent;
import com.github.sarxos.webcam.WebcamMotionListener;

public class DetectMotionExample implements WebcamMotionListener  {
	Esp32ServerReporter reporter = null;
	Thread t = null;
	
	public DetectMotionExample() {
		WebcamMotionDetector detector = new WebcamMotionDetector(Webcam.getDefault());
		detector.setInterval(100); // one check per 100 ms
		detector.addMotionListener(this);
		detector.start();
	}

	@Override
	public void motionDetected(WebcamMotionEvent wme) {
		System.out.println("Detected motion I, alarm turn on you have");
		
		// place here a call to the ESP32 
		// http://192.168.0.103:80/motion
		if ( null == reporter)
		{
			reporter = new Esp32ServerReporter(true);

		}
		
		// spawn in a new Thread
		if ( null == t )
		{
			t = new Thread(reporter);
			t.start();
		}
		
//		if ( null != t )
//		{
//			System.out.println("New thread started");			
//		}
	}
}
