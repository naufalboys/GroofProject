/*
 * Groof Project using IoT Discovery Kit
 */
 
#include <SPI.h>
#include <WiFiST.h>
#include <PubSubClient.h>

SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);

//SSID + Password WiFi
char ssid[] = "INNOVATIONLABS";         
char pass[] = "sebatdulu";  
int status = WL_IDLE_STATUS;     

//Analog Pin 
int pH  = 0;
int TDS = 1;

//Digital Pin
int Tandon          = 0;
int Penampungan     = 1;
int RelaySumur      = 2;
int RelayDistribusi = 3;
int RelayPenampungan= 4;
int RelayAsam       = 5;
int RelayBasa       = 6;
int RelayA          = 7;
int RelayB          = 8;

//Value
int Nilai_Tandon      = 0;
int Nilai_Penampungan = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(Tandon, INPUT);
  pinMode(Penampungan, INPUT);
  pinMode(RelaySumur, OUTPUT);
  pinMode(RelayDistribusi, OUTPUT);
  pinMode(RelayPenampungan, OUTPUT);
  pinMode(RelayAsam, OUTPUT);
  pinMode(RelayBasa, OUTPUT);
  pinMode(RelayA, OUTPUT);
  pinMode(RelayB, OUTPUT);
}

void baca_pH()
{
  
}

void baca_TDS()
{
  
}

void pompa()
{
  Nilai_Tandon = digitalRead(Tandon);
  Nilai_Penampungan = digitalRead(Penampungan);

  if (Nilai_Tandon == HIGH)
  {
    digitalWrite(RelaySumur, HIGH);
  }

  else if (Nilai_Tandon == LOW)
  {
    digitalWrite(RelaySumur, LOW);
  }

  if(Nilai_Penampungan == HIGH)
  {
    digitalWrite(RelayPenampungan, HIGH);
  }

  else if(Nilai_Penampungan == LOW)
  {
    digitalWrite(RelayPenampungan, LOW);
  }

  digitalWrite(RelayDistribusi, HIGH);
}

void loop() 
{
  

}
