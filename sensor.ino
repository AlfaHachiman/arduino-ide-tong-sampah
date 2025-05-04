#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED_PIN 13
// bagian atas ini adalah definisi dari pin pin yg kita pake

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);   // ini adalah serial untuk kecepatan komunikasi
}

void loop() {    // loop artinya berulang
  int distance;   //ini insial jaraknya
  
  if (Serial.available()) {   //ini jika punya monitoring seperti pake pc atau wokwi
    distance = Serial.parseInt(); // Baca nilai dari Serial Monitor
    Serial.read(); // Bersihkan buffer

  } else {  //ini kalo gada serial monitoring kayak wokwi, kodingan realnya
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
  }

  Serial.print("Jarak terdeteksi: "); // ini untuk menampilkan info simulasi di serialnya
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(100);
}