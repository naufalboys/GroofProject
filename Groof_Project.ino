/*
 * Groof Project using IoT Discovery Kit
 */

//Analog Pin 
#define pH  = A0
#define TDS = A1

//Digital Pin
#define Tandon          = 0;
#define Penampungan     = 1;
#define RelaySumur      = 2;
#define RelayDistribusi = 3;
#define RelayPenampungan= 4;
#define RelayAsam       = 5;
#define RelayBasa       = 6;
#define RelayA          = 7;
#define RelayB          = 8;

//Value
int Nilai_Tandon      = 0;
int Nilai_Penampungan = 0;
int Nilai_pH  = 0;
int Nilai_TDS = 0;

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

void peristaltik()
{
  
}

void loop() 
{
  pompa();
}
