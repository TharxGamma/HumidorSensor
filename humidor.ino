// Using Arduino Nano and ATmega328P 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302), Check which sensor you're using

// Parameters as follows. Starting location of screen and size of LCD screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create object of DHT pass in pin and type, defined above
DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  
  dht.begin();

}

void loop()
{
   delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float Humidity = dht.readHumidity();
  
  ErrorChecking(Humidity);
  
  DisplayHumidty(Humidity);


}

void ErrorChecking(float H)
{
  // Check if any reads failed and exit early (to try again).
  if (isnan(H)) 
  {
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }
}

void DisplayHumidty(float H)
{
  
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print(F("Humidity: "));
  lcd.print(H);

  if(H >= 73.0)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humidty is high");
  } 
  else if (H <= 60.0)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humidty is low");
  }
  else 
  {
    lcd.setCursor(0, 1);
    lcd.print("Cigars chilling");
  }
}
