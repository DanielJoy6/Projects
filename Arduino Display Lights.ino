int a=5;
int b=6;
int c=7;
int d=8;
int e=9;
int f=10;
int g=11;
int D1=13;
int D2=12;
int trigPin = 3;
int echoPin = 4;
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  for(int x = 5; x < 14; x++)
  {
    pinMode(x, OUTPUT);
  }
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long distance = pulseIn(echoPin, HIGH);
  int cm = (distance/2) / 30;
  Serial.println(cm);
  delay(10);
  if(cm < 3)
  {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
    
  }
  else if (cm < 6)
  {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    
  }
  else if (cm < 11)
  {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    
  }
  else if (cm < 16)
  {
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    delay(1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    
  }
  else if (cm < 21)
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    delay(1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    
  }
  else if(cm < 26)
  {
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
    delay(1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(g, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    
  }
  else if(cm < 31)
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
    delay(1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  else if(cm > 30)
  {
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(g, LOW);
    delay(1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
}
