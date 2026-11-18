const int trigPin = 11;
const int echoPin = 13;
const int buzzer_out = 3;

const float THRESHOLD_CM = 30.0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer_out, OUTPUT);
  digitalWrite(buzzer_out, LOW);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL);
  float distanceCm = (duration * 0.034) / 2.0;

  if (duration == 0) {
    Serial.println("Out of range");
    digitalWrite(buzzer_out, LOW);
  } else {
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");

    if (distanceCm < THRESHOLD_CM) {
      digitalWrite(buzzer_out, HIGH);
    } else {
      digitalWrite(buzzer_out, LOW);
    }
  }

  delay(200);
}