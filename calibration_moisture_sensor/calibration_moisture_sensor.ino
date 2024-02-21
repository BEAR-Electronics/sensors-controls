// Define analog input
// todo: eliminate need for 2 for loops
#define sensorPin A0

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("<Arduino is ready>");
  
}


String yes = "y";
void loop() {
  // Read the Analog Input
  int n = 100;
  boolean hasCalibrated = false;

  if(hasCalibrated == false) {
    Serial.println("Please expose moisture sensor to air. When done, type y and enter. ");

    while(Serial.available() == 0){
      }


    String input = Serial.readString();
    if(!strcmp(input.c_str(),yes.c_str())){
      Serial.println("Sampling...");
      float air [n];
      float time [n];

      float avgAir = 0;

      for (int sample = 0; sample < n; sample++) {
        float point = 0;
          for (int sample = 0; sample < 10; sample++) {
            point = point + analogRead(sensorPin);
            delay(10);
          }

        time[n] = millis();
        air[n] = point/10;
        avgAir = avgAir + point/10

        float num = air[n];
        Serial.println(String(num));
        // delay(1000);
        // pinMode(thisPin, OUTPUT);
        
    }
    }
      else
        Serial.println("Password incorrect");


    Serial.println("Please expose moisture sensor to water. When done, type y and enter. ");

    while(Serial.available() == 0){
      }


    String input = Serial.readString();
    if(!strcmp(input.c_str(),yes.c_str())){
      Serial.println("Sampling...");
      float water [n];
      float timeWater [n];

      float avgWater = 0;

      for (int sample = 0; sample < n; sample++) {
        float point = 0;
          for (int sample = 0; sample < 10; sample++) {
            point = point + analogRead(sensorPin);
            delay(10)
          }

        timeWater[n] = millis();
        water[n] = point/10;
        avgWater = avgWater + point/10

        float num = foo[n];
        Serial.println(String(num));
        delay(1000);
        // pinMode(thisPin, OUTPUT);
        
    }
    }
      else
        Serial.println("Password incorrect");

    Serial.println("Insert probe into soil. Sampling...");
    hasCalibrated = true;
  }

  avgWater = avgWater/n;
  avgAir = avgAir/n;

  m = 1/(avgWater - avgAir)
  
  float moisture = analogRead(sensorPin)*m;
  Serial.println(String(moisture)); // todo: save to file


  // delay(1000);
  // delay(10*n);
  // Serial.println("Thing");

  // for (int i = n - 1; i >= 0; i--) 
  //   Serial.println(foo[i]);

  // delay(10000);
  
  // Print the value to the serial monitor
  // Serial.print("Analog output: ");
  
  
  // Wait for 1 second before the next reading
  
}



// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   String password = "ABCDEF";
//   Serial.println("Please enter your password: ");

//   while(Serial.available() == 0){
//     }

//   String input = Serial.readString();

//   if(!strcmp(input.c_str(),password.c_str())){
//     Serial.println("Password correct");
//   }
//     else
//       Serial.println("Password incorrect");
//       Serial.println(password);
//       Serial.println(input);
// }