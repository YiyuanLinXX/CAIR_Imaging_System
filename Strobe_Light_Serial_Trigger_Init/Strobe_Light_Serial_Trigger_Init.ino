int dischargePin = 4;
int chargePin = 10;
int cam = 6;
int i = 0;

// ------ strobe light cable settting ------
// green-yellow: GND
// ONE: 72V
// TWO: discharge signal
// THREE: charge

// GREEN-YELLOW -> GND
// ONE -> 72V
// TWO -> 4
// CHARGE -> 10


// ------ camera GPIO cable settting ------
// brown: GND, camera power ground
// blue: Opto GND, Opto-isolated ground
// green: power input, auxiliary input voltage (DC)
// black: OPTOIN, Opto-isolated input

// BROWN, BLUE -> GND
// GREEN -> Power
// BLACK -> 6

int flag=0;

void setup() {
  Serial.begin(9600);
  pinMode(dischargePin, OUTPUT);
  pinMode(chargePin, OUTPUT);
  pinMode(cam, OUTPUT);

  // Pins Initialization
  digitalWrite(dischargePin, LOW);
  digitalWrite(chargePin, LOW);
  digitalWrite(cam, HIGH);
  
}

void loop() {
  if(flag==1){
    digitalWrite(dischargePin, HIGH); //start discharging
    
    // Serial.println("trigger camera");
    digitalWrite(cam, LOW); // trigger camera
    delayMicroseconds(500);
    digitalWrite(dischargePin,LOW); //stop discharging

    delayMicroseconds(1000); //1ms

    digitalWrite(chargePin,HIGH); //start charging
    digitalWrite(cam,HIGH); // set camera signal to HIGH, wait for next trigger signal
    delay(500); //frame rate
    digitalWrite(chargePin,LOW); //stop charging
  }

  char r = Serial.read();

  if(r=='s'){
    flag=1;
  }
  else if(r=='e'){
    flag=0;
  }
  else{
    flag=flag;
  }

  delay(5);
 
}