#define TRIG_PIN 9    //arduino to sensor
#define ECHO_PIN 10    //sensor to arduino
#define LED_PIN 13    //lampu
#define BUZZER_PIN 8   //buzzer
// bagian atas ini adalah definisi dari pin pin yg kita pake

bool objectDetected = false; // status sebelumnya

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);  // ini adalah serial untuk kecepatan komunikasi
}

void loop() {    // loop artinya berulang
  int distance = 0;   //ini insial jaraknya, dibuat nol karna takut tabrakan dengan sampah

  if (Serial.available()) {    //ini jika punya monitoring seperti pake pc atau wokwi
    distance = Serial.parseInt();   // Baca nilai dari Serial Monitor
    Serial.read();    // Bersihkan buffer

  } else {    //ini kalo gada serial monitoring kayak wokwi, kodingan realnya
    digitalWrite(TRIG_PIN, LOW);  
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
  }

  Serial.print("Jarak terdeteksi: ");    // ini untuk menampilkan info simulasi di serialnya
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 4) {    //ini jarak ketriggernya
    digitalWrite(LED_PIN, HIGH);  // lampu nyala trus

    if (!objectDetected) { //buzzernya berbunyi sekali
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      objectDetected = true;  // jika sudah berbunyi sekali maka di tandai sudah terdeteksi
    }

  } else {
    digitalWrite(LED_PIN, LOW);   //lampunya mati
    digitalWrite(BUZZER_PIN, LOW);  //buzzernya mati
    objectDetected = false; // ketika objek menjauh maka statusnya akan tereset ulang menjadi tidak terdeteksi
  }

  delay(100);
}
