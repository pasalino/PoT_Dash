#define BUTTON 8
#define BUSY 3
#define WIFI 4
#define RX_SW_SERIAL 10
#define TX_SW_SERIAL 11

#include "WiFiEsp.h"
#include "SoftwareSerial.h"

//CHANGE PARAMETERS
const char host[] = "[HOST]"; //ip or host
const char url[] = "/api/v1/counter/[COUNTER_NAME]"; //change meetingName
const int httpPort = 80; //Server port
char ssid[] = "[SSID]"; //name of ssid   
char pass[] = "[PWD]"; //wifi password       


// Initialize the Ethernet client object
int status = WL_IDLE_STATUS;     
WiFiEspClient client;
//Creare software serial port
SoftwareSerial Serial1(RX_SW_SERIAL, TX_SW_SERIAL); 

void setup()
{
  // Serial for monitor on PC
  Serial.begin(9600);
  //Serial for ESP8266 
  Serial1.begin(9600);

  //Assign Pin Behaviors
  pinMode(BUTTON, INPUT);
  pinMode(BUSY, OUTPUT);
  pinMode(WIFI, OUTPUT);

  Serial.println(*url);
  connectWifi();
  Serial.println("Ready!");
}

void loop()
{
  //Read button state
  int button = digitalRead(BUTTON);
  //Button in LOW State
  if (button == LOW) {
    digitalWrite(BUSY, HIGH);
    restCall();
    delay(2000);
  }

  //Ping connection
  long rssi = WiFi.RSSI();
  //Reconnect if disconnect
  if(WiFi.status()==WL_DISCONNECTED){
    Serial.println("Disconnected");
    connectWifi();
  }
  
  digitalWrite(BUSY, LOW);
}

void restCall() {
  Serial.println();
  Serial.println("Starting connection to server...");
  if (client.connect(host, httpPort)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println("PATCH " + String(url) + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();

    delay(100);
    // if there are incoming bytes available
    // from the server, read them and print them
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    // if the server's disconnected, stop the client
    if (!client.connected()) {
      Serial.println();
      Serial.println("Disconnecting from server...");
      client.stop();
    }
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void connectWifi() {
  status = WL_IDLE_STATUS;  
  digitalWrite(BUSY, HIGH);
  digitalWrite(WIFI, LOW);

  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  digitalWrite(BUSY, LOW);
  digitalWrite(WIFI, HIGH);

  printWifiStatus();
}

