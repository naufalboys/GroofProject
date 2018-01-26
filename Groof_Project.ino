
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

void setup() {
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

void baca_pH(){
  
}

void baca_TDS(){
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
