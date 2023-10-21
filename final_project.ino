/*
  Smart bed: 
  two in the pillow, two in the bed
  all has temperature
  if the temperature is too cold, need to flip
  one pillow: pulsing sensor, check for fever
  one pillow under the knee, and is has the thermistor to know if its too cold, cause if it's cold, the blood is not flowing -> Billy
  one on the metress, is has two photocells do check if the patient is moving -> Murnal
  one sense the environment, if the environment is too loud, get rid of the visitors
*/

#include <WiFi.h>
#include <WiFiUdp.h>

#define PHCELLPIN 15
#define UDPPORT 8888
#define WIFI_SSID "UCInet Mobile Access"
#define WIFI_PASSWORD ""

#define PHCELLTHRESHOLD 300

void udp_send(char* data);

static WiFiUDP Udp;
static IPAddress remoteIp;
static char packetBuffer[32];

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    delay(5000);
  }
  Serial.println("\nWi-Fi Connected");

  Serial.println("\nIP obtained: " + WiFi.localIP().toString());
  Udp.begin(UDPPORT);
  delay(1000);
}

void loop() {
  if (Udp.parsePacket()) {
    remoteIp = Udp.remoteIP();
    Serial.print("Received packet from IP <"); Serial.print(remoteIp);
    Serial.print(":"); Serial.print(Udp.remotePort()); Serial.println(">");
    
    memset(packetBuffer, '\0', sizeof(packetBuffer));
    int packetLength = Udp.read(packetBuffer, sizeof(packetBuffer));
    if (packetLength > 0) packetBuffer[packetLength] = '\0';
    
    Serial.print("Message received: "); Serial.println(packetBuffer);

    // TODO: design commands
  }

  int photocellValue = analogRead(PHCELLPIN);

  if (photocellValue >= PHCELLTHRESHOLD) {
    // TODO: Upload data?
  }

  delay(1000);
}

void udp_send(char* data){
  int i;
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Serial.println(data);
  while (data[i] != '\0') Udp.write((uint8_t)data[i++]);
  Udp.endPacket();
}
