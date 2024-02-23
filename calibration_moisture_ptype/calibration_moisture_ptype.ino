#define sensorPin A0
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

boolean hasCalibrated = false;
String yes = "y";
int n = 5;
float avgWater = 0;
float avgAir = 0;
float m = 1;

float takeMoistureMeasurement(int tdelay=10, int sampleSize=10) {
  float point = 0;
  for (int sample=0; sample<sampleSize; sample++) {
    point = point + analogRead(sensorPin);
    delay(tdelay);

  }
  return point/sampleSize;
}

float takeTempMeasurement(int tdelay=10, int sampleSize=10) {
  sensors.requestTemperatures();
  float point = 0;
  for (int sample=0; sample<sampleSize; sample++) {
    point = point + float(sensors.getTempFByIndex(0));
    delay(tdelay);

  }
  return point/sampleSize;
}

float measurementScheme(float * ar, float * temp_ar, float * time, float size, float * arr) {
  float avgMoisture = 0;
  float avgTemp = 0;
  for (int sample = 0; sample<size; sample++){
    float moisture = takeMoistureMeasurement();
    float temp = takeTempMeasurement();
    Serial.println(String(temp) + " " + String(moisture));
    //Serial.println("DEBUG: " + String(avgMoisture) + " " + String(moisture) + " " + String(avgMoisture + moisture));
    avgMoisture = avgMoisture + moisture;
    avgTemp = avgTemp + temp;
    ar[sample] = moisture;
    temp_ar[sample] = temp;
    time[sample] = millis();

    }
  //Serial.println("DEBUG: " + String(avgMoisture/size));
  //float arr [2];
  arr[0] = avgMoisture/size;
  arr[1] = avgTemp/size;
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("<Arduino is ready>");
  
}

// todo: function to run a measurement and custom calibration routines
// todo: wire the temperature sensor and figure out code for that!
// todo: figure out file saving on arduino!

void loop() {
 
  // put your main code here, to run repeatedly:
  //Serial.println(Serial.readString();
  if(hasCalibrated==false) {
    // Serial.println("Please expose moisture sensor to air. When done, type y and enter. Only first char will be considered in the response.");
    while(Serial.available() == 0){}
    String input = Serial.readString();
    Serial.println(String(input)==String(yes));
    if(String(yes[0])==String(input[0])){
      Serial.println("Sampling Air...");
      float air [n];
      float temp [n];
      float t [n];
      float avgTemp = 0;

      float avgs [2];
      measurementScheme(air, temp, t, n, avgs);
      //Serial.println("DEBUG 2: " + String(avgs[0]));
      avgAir = avgs[0];
      avgTemp = avgs[1];
      Serial.println("END: Average Moisture: " + String(avgs[0]) + " Average Temperature: " + String(avgs[1]) + " deg F");

    while(Serial.available() == 0){}
    String input = Serial.readString();
    Serial.println(String(input)==String(yes));
    if(String(yes[0])==String(input[0])){
      Serial.println("Sampling Water...");
      float water [n];
      float temp [n];
      float t [n];

      float avgTemp = 0;

      float avgs [2];
      measurementScheme(water, temp, t, n, avgs);
      avgWater = avgs[0];
      avgTemp = avgs[1];
      Serial.println("END: Average Moisture: " + String(avgs[0]) + " Average Temperature: " + String(avgs[1]) + " deg F");


    }
      // for (int sample = 0; sample<n; sample++) {
      //   float point = 0;
      //   for (int sample=0; sample<10; sample++) {
      //     point = point + analogRead(sensorPin);
      //     delay(10);
      //   }

      //   t[sample] = millis();
      //   air[sample] = point/10;
      //   Serial.println(analogRead(sensorPin));
      //   avgAir = avgAir + point/10;
      // }

      // avgAir = avgAir/n;
      

    }
    m = 1/(avgWater - avgAir);
    Serial.println("Sensor has been calibrated. Dry analog measurement at " + String(avgAir) + " and wet measurement at " + String(avgWater));
    Serial.println("Calibration slope at " + String(m));
    Serial.println("Please expose sensor to soil in 10 seconds.");
    delay(1000);
    Serial.println("Sampling soil...");
    hasCalibrated=true;
  }
   // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  // sensors.requestTemperatures();
  // Serial.print("Celsius temperature: ");
  // // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  // Serial.print(sensors.getTempCByIndex(0));
  // Serial.print(" - Fahrenheit temperature: ");
  // Serial.println(sensors.getTempFByIndex(0));
  // delay(1000);
  // Serial.println(analogRead(sensorPin));

  float moisture = takeMoistureMeasurement();
  float temp = takeTempMeasurement();
  float perc = m*moisture;
  Serial.println(String(temp) + " " + String(moisture) + " " +  String(perc));

}

