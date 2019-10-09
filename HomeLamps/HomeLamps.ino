#include <WiFi.h>

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
typedef enum HomeLamps_e 
{
  EHOMELAMPS_MIN = 0,
  EHOMELAMPS_KITCHEN = EHOMELAMPS_MIN,
  EHOMELAMPS_BEDROOM,
  EHOMELAMPS_LIVINGROOM,
  EHOMELAMPS_CORRIDOR,
  EHOMELAMPS_ALARM_ACTIVE,
  EHOMELAMPS_ALARM_TRIGGERED,
  EHOMELAMPS_MAX
} HomeLamps_t;

String strOutputState[EHOMELAMPS_MAX] = {"off", "off", "off", "off", "off", "off"};
bool isLampStateOn[EHOMELAMPS_MAX] = { false, false, false, false, false, false};
const int lampPins[EHOMELAMPS_MAX] = { 19, 18, 15, 2, 4, 5};
const String strPeripheralNames[EHOMELAMPS_MAX]={ " Kitchen Lamp ", " Bedroom Lamp ", " LivingRoom Lamp ", " Corridor Lamp ", " Alarm Activated ", " Alarm Triggered "};

const int PIN_ADC_I = 34; // D34

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
  {
      pinMode(lampPins[index], OUTPUT);
      digitalWrite(lampPins[index], LOW);
  }

  init_WebServer();
  init_Lcd();

  // Initialize the mic
  pinMode(PIN_ADC_I, INPUT);
}

void loop(){
  WiFiClient client = getWebClient();

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
            {
                String searchOnString = String("GET /") + index + String("/on");
                if ( header.indexOf(searchOnString) >= 0 )
                {
                   Serial.print("GPIO ");
                   Serial.print(lampPins[index]);
                   Serial.println("on");
                   digitalWrite(lampPins[index], HIGH);
                   isLampStateOn[index] = true;
                   strOutputState[index] = "on";
                }
                searchOnString = String("");
                
                String searchOffString = String("GET /") + index + String("/off");
                if ( header.indexOf(searchOffString) >= 0 )
                {
                   Serial.print("GPIO ");
                   Serial.print(lampPins[index]);
                   Serial.println("off");
                   digitalWrite(lampPins[index], LOW);
                   isLampStateOn[index] = false;
                   strOutputState[index] = "off";
                }
                searchOffString = String("");              
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println("table, th, td { border: 1px solid black;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<center><table>");
            // Display current state, and ON/OFF buttons for GPIOs
            for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
            {
                if ( 0 == (index % 2) )
                {
                    client.println("<TR>");
                }
                
                String strGPIOLabel = String("<TD>GPIO ") + lampPins[index] + String(" </TD><TD> ") + strPeripheralNames[index] +String(" </TD><TD> State ") + strOutputState[index] + String(" </TD>");
                client.println(strGPIOLabel);
                strGPIOLabel = String("");
                if (isLampStateOn[index])
                {
                    // if the state is On it displays the Off button
                    String strButtonRequest = String("<TD><a href=\"/") + index + String("/off\"><button class=\"button button2\">OFF</button></a></TD>");
                    client.println(strButtonRequest);
                    strButtonRequest = String("");                    
                }
                else
                {
                    String strButtonRequest = String("<TD><a href=\"/") + index + String("/on\"><button class=\"button\">ON</button></a></TD>");
                    client.println(strButtonRequest);
                    strButtonRequest = String("");
                }

                if ( 1 == (index % 2) )
                {
                    client.println("</TR>");
                }
            }

            client.println("</table>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }

      if (true == isLampStateOn[EHOMELAMPS_ALARM_ACTIVE])
      {   
          int analog_value = 0;
          analog_value = analogRead(PIN_ADC_I);
          if (analog_value > 80)
          {
              digitalWrite(lampPins[EHOMELAMPS_ALARM_TRIGGERED], HIGH);
              Serial.print("mic value = ");
              Serial.println(analog_value);              
          }
          else if (false == isLampStateOn[EHOMELAMPS_ALARM_TRIGGERED])
          {
              digitalWrite(lampPins[EHOMELAMPS_ALARM_TRIGGERED], LOW);
          }
      }

      update_Lcd(isLampStateOn);
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
