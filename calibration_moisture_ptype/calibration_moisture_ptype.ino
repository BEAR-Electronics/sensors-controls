#define sensorPin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("<Arduino is ready>");
  
}

boolean hasCalibrated = false;
String yes = "y";
int n = 100;

// todo: function to run a measurement and custom calibration routines
// todo: wire the temperature sensor and figure out code for that!
// todo: figure out file saving on arduino!

void loop() {
  // put your main code here, to run repeatedly:
  

  if(hasCalibrated==false) {
    Serial.println("Please expose moisture sensor to air. When done, type y and enter. Only first char will be considered in the response.");
    while(Serial.available() == 0){}
    String input = Serial.readString();

    if(String(yes[0])==String(input[0])){
      Serial.println("Sampling...");
      float air [n];
      float t [n];
      float avgAir = 0;

      for (int sample = 0; sample<n; sample++) {
        float point = 0;
        for (int sample=0; sample<10; sample++) {
          point = point + analogRead(sensorPin);
          delay(10);
        }

        t[sample] = millis();
        air[sample] = point/10;
        avgAir = avgAir + point/10;
      }

      avgAir = avgAir/n;
      

    }


    hasCalibrated=true;
  }

}
