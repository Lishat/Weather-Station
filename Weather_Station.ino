#include <Adafruit_BMP085.h>
#include <dht.h>
#include <Wire.h>
Adafruit_BMP085 mySensor;
dht DHT;
#define DHT_PIN 2
String str;
unsigned long previousmillis = 0;
void setup(){
  Serial.begin(9600);
  mySensor.begin();
}
bool flag = 0;
void loop() {
         unsigned long currentmillis = millis();
         float sensorValue = analogRead(A0);
         if(currentmillis - previousmillis >= 500)
         {
          DHT.read11(DHT_PIN);
         str = "";
         str += "Temperature in Celsius = ";
         str += mySensor.readTemperature();
         str += "\n";
         str += "Humidity (in %) = ";
         str += DHT.humidity;
         str += "\n";
         str += DHT.temperature;
         str += "\n";
         str += "Altitude (in metres) =";
         str += mySensor.readAltitude();
         str += "\n";
        if(sensorValue > 300)
        {
          str += "It is not raining";
        }
        else if(sensorValue > 200)
        {
          str += "Moderate Rain";
        }   
        else if(sensorValue < 200)
        {
          str += "Heavy Rain";
        }
        str += "\n";
        str += "Pressure (in Pascals) =";
        str += mySensor.readPressure();
        str += "\n";
        Serial.println(str);
        previousmillis = currentmillis;
         }
        while(Serial.available())
        {
          flag  = 1;
          if(Serial.read() == 49)
          {
            str = "";
            float c = mySensor.readTemperature();
            str += "Temperature in Celsius = ";
            str += c;
            str += "\n";
            str += "Temperature in Kelvin = ";
            str += float(c+273.15);
            str += "\n";
            str += "Temperature in Fahrenheit = ";
            str += float(9/5.0)*(c+32);
            str += "\n";
          }
          else if(Serial.read() == 50)
          {
            str = "";
            float c = mySensor.readAltitude();
            str += "Altitude(in metres) = ";
            str += float(c);
            str += " above sea level";
            str += "\n";
            str += "Altitude(in kilometres) = ";
            str += float(c/1000.0);
            str += " above sea level";
            str += "\n";
            str += "Altitude(in feet) = ";
            str += float(c*(3+3.37/12.0));
            str += " above sea level";
            str += "\n";
          }
          else if(Serial.read() == 51)
          {
            str = "";
            float c = mySensor.readPressure();
            str += "Pressure(in Pascals) = ";
            str += float(c);
            str += "\n";
            str += "Pressure(in atmospheres) = ";
            str +=  float(c/101325.0);
            str += "\n";
            str += "Pressure(in bars) = ";
            str += float(c/100000.0);
            str += "\n";
          }
          else if(Serial.read() == 52)
          {
            str = "";
            str += "Humidity in %: ";
            str += float(DHT.humidity);
            str += "\n";
          }
          else if(Serial.read() == 53)
          {
            str = "";
            if(sensorValue > 200)
            {
              str += "It is not raining.\nEnjoy your day without a worry\n";
            }
            else
            {
              str += "It is raining.\nIt would be good if you carry an umbrella with you\n";
            }   
          }
          else if(Serial.read() == 54)
          {
            str = "";
            str += "Dew Point(in degrees Centigrade): ";
            float c = mySensor.readTemperature();
            double a = 17.271;
            double b = 237.7;
            double temp = ((a*c)/(b*c)) + log(DHT.humidity*0.1);
            str += float((b*temp)/(a-temp));
            str += "\n";
          }
          else if(Serial.read() == 55)
          {
            str = "";
            float c = mySensor.readTemperature();
            int i = 0;
            while(i != 10)
            {
              c += mySensor.readTemperature();
              i += 1;
            }
            c /= 10.0;
            if(c <= 10)
            {
              str += "It's very cool. Wear a jacket and ";
              c -= 2.0;
              str += float(c);
              str += " can be expected in further 2 days.\n";
            }
            else if( c <= 20)
            {
              str += "It's chilly weather outside. Take care.\n";
              c -= 1.0;
              str += "A rough temperature of ";
              str += float(c);
              str += " can be expected tomorrow\n";
            }
            else if(c <= 30) 
            {
              str += "The weather is moderate. You can have a good walk outside.\n";
              str += "A temperature of ";
              str += float(c);
              str += " shall be seen on the forthcoming days.\n";
            }
            else if(c <= 40)
            {
              str += "It is quite hot today. It is advisable to wear light coloured clothes.\n";
              c += 1.0;
              str += "It can be more hotter tomorrow with a temperature of ";
              str += float(c);
              str += ". So please take care.\n";
            }
            else if(c <= 50)
            {
              str += "It is extremely hot today. So better stay at homes.\n";
              c += 2.0;
              str += "It will be more hot tomorrow with an expected temperature of ";
              str += float(c);
              str += "\n";
            }
            c = analogRead(A0);
            if(c > 300)
            {
              str += "It's a dry day. Enjoy your day.\n";
            }
            else
            {
              str += "It's a wet day. Storms expected.\n";
            }
          }
        }
        if (flag == 1)
        {
          int i = 0;
          while(i <= 100)
          {
          Serial.println(str);
          i += 1;
          }
          flag = 0;
        }
       
}
