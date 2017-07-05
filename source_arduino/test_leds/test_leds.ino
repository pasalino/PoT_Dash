#define BUTTON 8
#define RED 3
#define BLUE 4

void setup()
{
  // Serial for monitor on PC
  Serial.begin(9600);

  //Assign Pin Behaviors
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, HIGH);
}

void loop()
{
  //Read button state
  int button = digitalRead(BUTTON);
  //Button in LOW State
  if (button == LOW) {
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
  } else {
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
  }
}

