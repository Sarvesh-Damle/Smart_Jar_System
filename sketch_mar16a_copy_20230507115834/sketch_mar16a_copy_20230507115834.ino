#include <ESP8266WiFi.h>
const int trigPin1 = D2;
const int echoPin1 = D1;

const int trigPin2 = D5;
const int echoPin2 = D6;

long duration;
int distance; 
float level;
const char* ssid = "Tanmay"; //wifi
const char* password = "1234567890";   //pass
void send_event(const char *event);
const char *host = "maker.ifttt.com";
const char *privateKey = "gQz71FQ81h6nfpm7zxw7TSNURrnx_WUuzI3Tw1HswqD";
WiFiServer server(80);
void setup() {
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 Serial.begin(9600);
 Serial.print("Connecting to Wifi Network");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("Successfully connected to WiFi.");
 Serial.println("IP address is : ");
 Serial.println(WiFi.localIP());
 server.begin();
 Serial.println("Server started");
}
void loop() {
    // Reading distance from first sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  int durationf = pulseIn(echoPin1, HIGH);
  int distancef = durationf * 0.034 / 2;


  // Reading distance from second sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  int durations = pulseIn(echoPin2, HIGH);
  int distances = durations * 0.034 / 2;

  float levelf =((13-distancef)/13.0)*100;
  float levels =((7-distances)/7.0)*100;

  if ( levelf <= 25 || levels <=25) {
        send_event("jar_event");
        Serial.println("Email_sent");
        }

  // Printing the distance readings
  Serial.print("Distance 1: ");
  Serial.print(distancef);
  Serial.print(" cm | Level Filled of Taller Jar ");
  Serial.print(levelf);
  Serial.println(" %");

  Serial.print("Distance 2: ");
  Serial.print(distances);
  Serial.print(" cm | Level Filled of Shorter Jar ");
  Serial.print(levels);
  Serial.println(" %");
  Serial.println("............");




  delay(5000);
  WiFiClient client = server.available();
  if (client) 
{ 
Serial.println("Web Client connected ");
String request = client.readStringUntil('\r'); 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 10");  // update the page after 10 sec
client.println();


client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<head>");
client.println("<style>");
client.println("div { font-family: Cairo; display; font-size: 1.4rem}");
client.println("* { margin: 0; padding: 0;}");
client.println("html { font-family: Cairo; display: block; margin: 0px auto; text-align: center;color: #333333; background-color: #FBFBFB; overflow: hidden;}");
client.println(" body { margin:0%; padding: 0%;}");
client.println(".info{position:absolute ; display: flex; flex-direction: column; padding: 1rem ; background: white; border-radius: 1rem; top: 5rem;box-shadow: 2px 2px 2px 0px rgba(0 0 0 /25%) ;}");
client.println(".col{display: flex; gap :2rem; margin-bottom: 1rem; }");
client.println(".red{background-color: rgb(213 0 35); width: 0.8rem; height:0.8rem}");
client.println(".yellow{background-color: rgb(213, 213, 0); width: 0.8rem;height:0.8rem}");
client.println(".green{background-color: rgb(1.5 213 0); width: 0.8rem;height:0.8rem}");
client.println("h1 {width: 100%; font-size: 2rem; background-color: rebeccapurple; padding: 1rem; color: white;}");
client.println("h2 {font-family:Poppins;font-size: 1.4rem;margin-bottom: 1.5rem; }");
client.println("h4 {font-size: 0.8rem;margin-bottom: 1.5rem; }");
client.println(".container{ display: flex; margin: auto;justify-content: center; gap: 5rem; top: 2rem;position: relative; }");
client.println(".level{ display: flex; justify-content: center;}");
client.println(".lid{position: relative; width:20rem; height: 3rem; background: rgb(50, 38, 38);border-radius: .4rem; outline: #000000 solid 1px;z-index: 1;}");
client.println(".jarr{ position: relative; width: 20rem; background-color: rgb(255, 255, 255); height: 20rem; border-radius: 0rem 0rem 1rem 1rem ;border-left: 2px solid lightgray;border-right: 2px solid lightgray; border-bottom: 2px solid lightgray;}");

if(levelf < 25 ){
client.println(".indir{ position: absolute; width: 100%;background-color: rgb(213 0 35); height:" + String(levelf) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ; }");
}
else if(levelf <= 50 && levelf>25){
client.println(".indir{ position: absolute; width: 100%;background-color: rgb(213, 213, 0); height:" + String(levelf) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ;}");
}
else{
client.println(".indir{ position: absolute; width: 100%; background-color: rgb(105 213 0); height:" + String(levelf) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ;}");

}

client.println(".jarl{ position: relative; width: 20rem; background-color: rgb(255, 255, 255); height: 20rem; border-radius: 0rem 0rem 1rem 1rem ; border-left: 2px solid lightgray;border-right: 2px solid lightgray; border-bottom: 2px solid lightgray;}");

if(levels < 25 ){
client.println(".indil{ position: absolute; width: 100%;background-color: rgb(213 0 35); height:" + String(levels) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ;}");
}
else if(levels <= 50 && levels>25){
client.println(".indil{ position: absolute; width: 100%;background-color: rgb(213, 213, 0); height:" + String(levels) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ; }");
}
else{
client.println(".indil{ position: absolute; width: 100%; background-color: rgb(105 213 0); height:" + String(levels) + "%;bottom: 0rem; border-radius: 0rem 0rem 1rem 1rem ; }");

}

client.println(" </style>");
client.println("</head>");
client.println("<body>");
client.println("<div  class=\"info\">");
client.println(" <div class=\"col\">");
client.println("<div class=\"green\">");
client.println("</div>");
client.println("<h4> Level > 50%</h4>");
client.println("</div>");
client.println("<div class=\"col\">");
client.println("<div class=\"yellow\">");
client.println("</div>");
client.println("<h4> 25% < Level < 50% </h4>");
client.println("</div>");
client.println("<div class=\"col\">");
client.println("<div class=\"red\">");
client.println("</div>");
client.println("<h4> 0% < Level < 25%</h4>");
client.println("</div>");
client.println("</div>");

client.println(" <div>");
client.println("<h1>IOT based Jar Monitoring system </h1>");
client.println(" <div class=\"container\">");
client.println("<div class=\"conright\">");
client.println("<h2>First Jar</h2>");
client.println("<div class=\"level\">");
client.println("<h2>Level : </h2>" );
client.print(levelf);
client.println("<h2> % Filled</h2>");
client.println(" </div>");
client.println("<div class=\"lid\"></div>");
client.println("<div class=\"jarr\">");
client.println("<div class=\"indir\">");
client.println("</div>");
client.println("</div>");
client.println("</div>");
client.println("<div class=\"conleft\">");
client.println("<h2>Second Jar</h2>");
client.println("<div class=\"level\">");
client.println("<h2>Level : </h2>");
client.println(levels);
client.println("<h2> % Filled</h2>");
client.println("</div>");
client.println("<div class=\"lid\"></div>");
client.println("<div class=\"jarl\">");
client.println("<div class=\"indil\">");
client.println("</div>");
client.println(" </div>");
client.println(" </div>");
client.println("</div>");
client.println("</div>");
client.println("</body>");

client.println("</html>");




   if ( level >= 10) {
        // send_event("jar_event");
        }
} 
}
void send_event(const char *event)
{
  Serial.print("Connecting to "); 
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  // We now create a URI for the request
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      // No data yet, wait a bit
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}