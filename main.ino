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
  // Clear Trig pin and send a 10-microsecond HIGH pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);

  // Timeout 30 ms (~5 m) so the loop doesn't stall for 1 s on no echo
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
      digitalWrite(buzzer_out, HIGH);   // object closer than 10 cm
    } else {
      digitalWrite(buzzer_out, LOW);
    }
  }

  delay(200);
}