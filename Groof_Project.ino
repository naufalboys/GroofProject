/*
 * Groof Project using IoT Discovery Kit
 */
 
#include <SPI.h>
#include <WiFiST.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>

const int rs = 15, en = 14, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);

//SSID + Password WiFi
char ssid[] = "INNOVATIONLABS";         
char pass[] = "sebatdulu";  
int status = WL_IDLE_STATUS;    
const char* mqtt_server = "broker.hivemq.com";

WiFiClient STM32;
PubSubClient client(STM32);
long lastMsg = 0;
char msg[50];
int value = 0;
int x = 0;
int y = 0;
int j = 0;

//Analog Pin 
#define pH  A0
#define TDS A1

//Digital Pin
#define Tandon           8
#define Penampungan      9
#define RelaySumur       0
#define RelayDistribusi  1
#define RelayPenampungan 2
#define RelayAsam        10
#define RelayBasa        11
#define RelayA           12
#define RelayB           13

//Value
int Nilai_Tandon      = 0;
int Nilai_Penampungan = 0;
int Nilai_pH  = 0;
int Nilai_TDS = 0;

void setup() 
{
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Selamat Datang   ");
  lcd.setCursor(0,1);
  lcd.print("  Di Groof Project  ");
  delay(2000);
  customset1();
  lcd.clear();
  for(int asd=1;asd<=3;asd++)
  {
    fillset();  
  }
  lcd.clear();
  
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(Tandon, INPUT_PULLUP);
  pinMode(Penampungan, INPUT_PULLUP);
  pinMode(RelaySumur, OUTPUT);
  pinMode(RelayDistribusi, OUTPUT);
  pinMode(RelayPenampungan, OUTPUT);
  pinMode(RelayAsam, OUTPUT);
  pinMode(RelayBasa, OUTPUT);
  pinMode(RelayA, OUTPUT);
  pinMode(RelayB, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void customclear() 
{
 byte blank[8] =
 {
   B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000
 };
 for(int i = 0; i < 8; i++)
 {
   lcd.createChar(i, blank);
 }
}

void customset1()
{
  customclear();
  j = 4;
  
  byte line1[8] = 
  {
    B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000 
  };
  byte line2[8] =
  {
    B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000 
  };
  byte line3[8] =
  {
    B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100
  };
  byte line4[8] =
  {
    B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110
  };

 lcd.createChar(0, line1);
 lcd.createChar(1, line2);
 lcd.createChar(2, line3);
 lcd.createChar(3, line4);  
}

void fillset()
{
  lcd.setCursor(0,0);
  lcd.print("   Selamat Datang   ");
  lcd.setCursor(0,1);
  lcd.print("  Di Groof Project  ");
  lcd.setCursor(0,2);
  lcd.print("    Now Loading~    ");
 for(int i = 0; i < j; i++)
 {
   //lcd.setCursor(x,0);
   //lcd.write(i);
   lcd.setCursor(x,3);
   lcd.write(i);
   delay(25);
 }
 //lcd.setCursor(x, 0);
 //lcd.write(255);
 lcd.setCursor(x, 3);
 lcd.write(255); 
 delay(25);
 x++;
 if(x < 20)
 {
   fillset();
 }
 if(x > 19)
 {
   x = 0;
   lcd.clear();
 }
}

void setup_wifi() 
{
  delay(10);

  // Initialize the WiFi device :
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module not present");
    // don't continue:
    while (true);
  }

  // Print firmware version
  String fv = WiFi.firmwareVersion();
  Serial.print("Firwmare version : ");
  Serial.println(fv);

  if (fv != "C3.5.2.3.BETA9")
  {
    Serial.println("Please upgrade the firmware");
  }
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address : ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED1, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(LED1, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("STM32Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("GroofTopic54321", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic12345");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void baca_pH()
{
  Nilai_pH = analogRead(pH);
  //Terus laopo gak ero wkwkwk
}

void baca_TDS()
{
  Nilai_TDS = analogRead(TDS);
  //Iki yo lapo gak ero wkwkwk
}

void pompa()
{
  Nilai_Tandon = digitalRead(Tandon);
  Serial.println(Nilai_Tandon);

  Nilai_Penampungan = digitalRead(Penampungan);
  Serial.println(Nilai_Penampungan);

  if (Nilai_Tandon == HIGH)
  {
    digitalWrite(RelaySumur, HIGH);
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Relay Sumur : HIGH");
  }

  else if (Nilai_Tandon == LOW)
  {
    digitalWrite(RelaySumur, LOW);
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Relay Sumur : LOW ");
  }

  if(Nilai_Penampungan == HIGH)
  {
    digitalWrite(RelayPenampungan, HIGH);
    //lcd.clear();
    lcd.setCursor(0,2);
    lcd.print("Relay Tampung : HIGH");
  }

  else if(Nilai_Penampungan == LOW)
  {
    digitalWrite(RelayPenampungan, LOW);
    //lcd.clear();
    lcd.setCursor(0,2);
    lcd.print("Relay Tampung : LOW ");
  }

  digitalWrite(RelayDistribusi, HIGH);
}

void peristaltik()
{
  
}

void loop() 
{
  pompa();

  /*MQTT
  if (!client.connected()) 
  {
    reconnect();
  }
  
  //Publish and Subscribe
  client.publish("GroofTopic54321", "hello world");
  // ... and resubscribe
  client.subscribe("inTopic12345");
      
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Groof Test 123 #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("GroofTopic54321", msg);
  }*/
}
