const int button = 17;
int buttonState = 0;


void setup() {
  Serial.begin(115200);
   pinMode(button, INPUT);

}

void loop() {
   buttonState = digitalRead(button); // cteni stavu tlacitka
   delay(100);
   Serial.println("Probiha");
  if (buttonState == HIGH)
  {
    Serial.println("Tlacitko bylo zmacknuto");
  }

}
