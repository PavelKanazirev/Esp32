import java.net.MalformedURLException;

import javax.swing.JFrame;

import com.github.sarxos.webcam.Webcam;
import com.github.sarxos.webcam.WebcamPanel;
import com.github.sarxos.webcam.ds.ipcam.IpCamDeviceRegistry;
import com.github.sarxos.webcam.ds.ipcam.IpCamDriver;
import com.github.sarxos.webcam.ds.ipcam.IpCamMode;


/**
 * Example of how to stream MJPEG with Webcam Capture.
 * 
 * @author Bartosz Firyn (SarXos)
 */
public class VideoSockConnectionTest {

	/**
	 * Remember to add IP camera driver JAR to the application classpath!
	 * Otherwise you will not be able to use IP camera driver features. Driver
	 * has to be set at the very beginning, before any webcam-capture related
	 * method is being invoked.
	 */
	static {
		Webcam.setDriver(new IpCamDriver());
	}

	public static void main(String[] args) throws MalformedURLException {

		IpCamDeviceRegistry.register("", "http://192.168.0.121:8081/", IpCamMode.PUSH);

		WebcamPanel panel = new WebcamPanel(Webcam.getWebcams().get(0));
		new DetectMotionExample();
		// System.in.read(); // keep program open
		
		panel.setFPSLimit(1);

		JFrame f = new JFrame("Security system");
		f.add(panel);
		f.pack();
		f.setVisible(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}