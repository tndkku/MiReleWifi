*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/Relay01=0 will set the GPIO4 low,
 *    http://server_ip/Relay01=1 will set the GPIO4 high
 
 *    http://server_ip/Relay02=0 will set the GPIO5 low,
 *    http://server_ip/Relay02=1 will set the GPIO5 high
 *    
 *    http://server_ip/Relay03=0 will set the GPIO14 low,
 *    http://server_ip/Relay03=1 will set the GPIO14 high
 
 *    http://server_ip/Relay04=0 will set the GPIO12 low,
 *    http://server_ip/Relay04=1 will set the GPIO12 high
 
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>


const char* ssid = "tndkku";
const char* password = "tnd4182065";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  

  // prepare GPIO4 PIN D2 NodeMcu
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  
  // prepare GPIO5 PIN D1 NodeMcu
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);

   // prepare GPIO14 PIN D5 NodeMcu
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  
  // prepare GPIO12 PIN D6 NodeMcu
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);

  
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Conecting to  ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conected");
  
  // Start the server
  server.begin();
  Serial.println("Web server On");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
  String wifi=String(WiFi.localIP());
}

  // Match the request
  int val01;
  int val02;
  int val03;
  int val04;

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("New Client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("Relay01=1") != -1){
    val01 = 1;
  }else if (req.indexOf("Relay01=0") != -1){
    val01 = 0;
  }
 
  if (req.indexOf("Relay02=1") != -1){
    val02 = 1;
  }else if (req.indexOf("Relay02=0") != -1){
    val02 = 0;
  }

  if (req.indexOf("Relay03=1") != -1){
    val03 = 1;
  }else if (req.indexOf("Relay03=0") != -1){
    val03 = 0;
  }

  if (req.indexOf("Relay04=1") != -1){
    val04 = 1;
  }else if (req.indexOf("Relay04=0") != -1){
    val04 = 0;
  }

  // Set GPIO3 according to the request
  digitalWrite(4, val01);
  
  // Set GPIO4 according to the request
  digitalWrite(5, val02);

  // Set GPIO14 according to the request
  digitalWrite(14, val03);
  
  // Set GPIO12 according to the request
  digitalWrite(12, val04);
  
  client.flush();

  // Prepare the response

    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: application/json;charset=utf-8"));
    client.println(F("Connection: close"));  
    //String sr = "<!DOCTYPE HTML>\n";
    //sr += "<html>\n";
    //sr += "<body>\n";
    String sr = "[{\"REL01\":\"";
    sr += val01;
    sr += "\",\"REL02\":\"";
    sr += val02;
    sr += "\",\"REL03\":\"";
    sr += val03;
    sr += "\",\"REL04\":\"";
    sr += val04;
    sr += "\",\"IP\":\"";
    sr += String(WiFi.localIP().toString().c_str());
    sr += "\"}]";
    client.print(F("Content-Length:"));
    client.print(sr.length());
    client.print(F("\r\n\r\n"));
    client.print(sr);
   

  // Send the response to the client
 // client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
