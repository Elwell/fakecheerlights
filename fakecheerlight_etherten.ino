
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

EthernetClient client;

int led = 13;
byte server[] = { 
  10, 1, 1, 251 };

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800);

char message_buff[30];
void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  long colour = strtol(message_buff, NULL, 16);
  strip.setPixelColor(0, colour);
  strip.show();
}

PubSubClient psclient(server, 1883, callback, client);

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(115200);

  strip.begin();
  strip.setPixelColor(0, 0xFFFFFF);
  strip.show();


  // MAC address grabbed from NanodeMac earlier 
  // uint8_t mac[6] = {0x00,0x04,0xA3,0x2C,0x1D,0xE1};

  // etherten needs a mac assigning
  uint8_t mac[6] = {
    0x00,0x04,0xA3,0x2C,0x1D,0xF0    };
  Ethernet.begin(mac);


  //Serial.print("Mac Addr: ");
  //Serial.println(mac);
  // dammit, the above needs iterating through to work
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  digitalWrite(led, LOW);

  if (psclient.connect("EthertenClient")) {
    Serial.println("Connected to Broker");
    psclient.publish("nanode/status","Booted");
    psclient.subscribe("nanode/rgb");
  }
}

void loop() {
  psclient.loop();
}


