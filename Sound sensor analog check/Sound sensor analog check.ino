int Led=13;
int buttonpin = A0;
int val;

void setup() {
  // put your setup code here, to run once:
  pinMode(Led, OUTPUT);
  pinMode(buttonpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(buttonpin);
  Serial.println(val);
  delay(200);
}
