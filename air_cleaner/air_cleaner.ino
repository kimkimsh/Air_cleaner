#include <Wire.h>

//I used 'Arduino-LiquidCrystal-I2C-library', You can get it from here
// https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <LiquidCrystal_I2C.h>

//(I2C address, chars, lines), put in your device's own
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0;
int ledPin = 2;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float sensor_value = 0;
float voltage_value = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {

  detect();
  if (dustDensity > 30)
  {
    Serial.print(dustDensity);
    Serial.println(" ug/m3");
    lcd.setCursor(5, 0);
    lcd.print(dustDensity);
    lcd.setCursor(5, 1);
    lcd.print("ug/m3");
  }
  delay(1000);
}


//function that get the dustDensity value
void detect()
{
  digitalWrite(ledPin, LOW);
  delayMicroseconds(samplingTime);
  sensor_value = analogRead(sensorPin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(sleepTime);

  //change analoge input value to voltage value
  voltage_value = sensor_value * (5.0 / 1024.0);

  //get dustDensity from voltage value (ug/m3)
  dustDensity = (0.17 * voltage_value - 0.1) * 1000;
}
