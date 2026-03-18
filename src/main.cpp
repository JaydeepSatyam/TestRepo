#include <Arduino.h>

#define PWM_PIN 5

struct Data{
  int rpm;
  float temp;
  int throttle;
};
Data current;

unsigned long lastTime = 0;
const int cycle_time = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ledcAttachPin(PWM_PIN, 0);
  ledcSetup(0, 5000, 8);

}

void loop() { 
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if (now - lastTime >= cycle_time){
    current.rpm = random(1000, 8000);
    current.temp = random(20, 120);
    current.throttle = random(0, 100);

    if (current.temp > 90){
      current.throttle -= 20;
    }
    
    if (current.rpm > 7000){
      current.throttle = 0;
    }

    int pwm_value = map(current.throttle, 0, 100, 0, 255);
    ledcWrite(0, pwm_value);

    Serial.printf("%d, %.2f, %d\n", current.rpm, current.temp, current.throttle);
    Serial.println(current.rpm);
    Serial.println(current.temp);
    Serial.println(current.throttle);
  }    
}

