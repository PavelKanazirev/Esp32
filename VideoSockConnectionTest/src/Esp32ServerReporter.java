import java.net.*;
import java.io.*;

public class Esp32ServerReporter implements Runnable {
	
	int port = 80;
	String strUrl = null;
	URL u = null;
	boolean on = false;
	
	public Esp32ServerReporter(boolean _on)
	{
		strUrl = new String("http://192.168.0.103:80");
		on = _on;
	}
	
	public void run()
	{
		Socket sIn = null;
		Socket sOut = null;
		InputStream in = null;
		InputStreamReader isr = null;
		BufferedReader br = null;
		if ( true == on )
		{
			try {					
		        	URL u = new URL(strUrl);
		        	if (u.getPort() != -1) port = u.getPort();
			  		if (!(u.getProtocol().equalsIgnoreCase("http"))) {
			            System.err.println("Sorry. I only understand http.");
			        }
			  
			  		System.out.println("Socket " + u.toString());
					sOut = new Socket(u.getHost(), port);
					OutputStream theOutput = sOut.getOutputStream();
					// no auto-flushing
					PrintWriter pw = new PrintWriter(theOutput, false);
					// native line endings are uncertain so add them manually
					pw.print("GET " + u.getFile() + " HTTP/1.1\r\n");
					pw.print("Accept: text/plain, text/html, text/*\r\n");
					pw.print("\r");
					pw.print("\n");
					pw.flush();
					
					sIn = new Socket(u.getHost(), port);
					theOutput = sIn.getOutputStream();					
					System.out.println("1");
					in = sIn.getInputStream();
					System.out.println("2");
					isr = new InputStreamReader(in);
					System.out.println("3");
					br = new BufferedReader(isr);
					System.out.println("4");
					
					int c;
					String response = new String();
					while ((c = br.read()) != -1) {
						System.out.print((char) c);
						response += c;
					}
					
					System.out.println("5");
					if ( response.contains("Alarm Activated  </TD><TD> State on") )
					{ // if 4 is on
						// raise 5 for the buzzer and wait for 1 second
						System.out.print("Alarm Activated is On");
			        	u = new URL(strUrl + "/5/on");
			        	if (u.getPort() != -1) port = u.getPort();
				  		if (!(u.getProtocol().equalsIgnoreCase("http"))) {
				            System.err.println("Sorry. I only understand http.");
				        }
//				  
////						Socket s = new Socket(u.getHost(), port);
////						OutputStream theOutput = s.getOutputStream();
//						// no auto-flushing
//						// native line endings are uncertain so add them manually
						pw.print("GET " + u.getFile() + " HTTP/1.1\r\n");
						pw.print("Accept: text/plain, text/html, text/*\r\n");
						pw.print("\r\n");
						pw.flush();
//						
//						System.out.println("6");
						Thread.sleep(1000);
//						
//						System.out.println("7");
			        	u = new URL(strUrl + "/5/off");
			        	if (u.getPort() != -1) port = u.getPort();
				  		if (!(u.getProtocol().equalsIgnoreCase("http"))) {
				            System.err.println("Sorry. I only understand http.");
				        }
//				  
////						Socket s = new Socket(u.getHost(), port);
////						OutputStream theOutput = s.getOutputStream();
//						// no auto-flushing
////						PrintWriter pw = new PrintWriter(theOutput, false);
//						// native line endings are uncertain so add them manually
						pw.print("GET " + u.getFile() + " HTTP/1.1\r\n");
						pw.print("Accept: text/plain, text/html, text/*\r\n");
						pw.print("\r\n");
						pw.flush();
//						System.out.println("8");
					}
					else
					{
						System.out.println("The alarm is turned off - nothing to do ");
					}
					
					System.out.println("5");
			}
			catch (MalformedURLException ex) {
				System.err.println(strUrl + " is not a valid URL");
			}
			catch (IOException ex) {
				System.err.println(ex);
			}
			catch (InterruptedException ex)
			{
				System.err.println(ex);
			}
			finally 
			{
			    try {
			    	br.close();
			    	isr.close();
			    	in.close();
			    	sIn.close();
			    	sOut.close();
			    } 
			    catch (IOException e) 
			    {
			        e.printStackTrace();
			    }
			}
		}
	}

}
