#include <Wire.h>
#include <Adafruit_ADS1015.h>

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

float   multiplier;
  
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
   ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  //ads.begin(4,5);   // for ESP8266  SDA, SCL can be specified
  ads.begin();
  
  multiplier = ads.voltsPerBit()*1000.0F;    /* Sets the millivolts per bit */
  
  /* Use this to set data rate for the 12-bit version (optional)*/
  //ads.setSPS(ADS1015_DR_3300SPS);      // for ADS1015 fastest samples per second is 3300 (default is 1600)
  
  /* Use this to set data rate for the 16-bit version (optional)*/
  ads.setSPS(ADS1115_DR_8SPS);      // for ADS1115 fastest samples per second is 860 (default is 128)

  // Run test for each SPS
  
  Serial.println("********* 8 SPS ************");
  ads.setSPS(ADS1115_DR_8SPS);     
  runTest();
  
  Serial.println("********* 16 SPS ************");
  ads.setSPS(ADS1115_DR_16SPS);     
  runTest();
  
  Serial.println("********* 32 SPS ************");
  ads.setSPS(ADS1115_DR_32SPS);     
  runTest();
  
  Serial.println("********* 64 SPS ************");
  ads.setSPS(ADS1115_DR_64SPS);     
  runTest();
  
  Serial.println("********* 128 SPS ************");
  ads.setSPS(ADS1115_DR_128SPS);     
  runTest();
  
  Serial.println("********* 250 SPS ************");
  ads.setSPS(ADS1115_DR_250SPS);     
  runTest();
  
  Serial.println("********* 475 SPS ************");
  ads.setSPS(ADS1115_DR_475SPS);     
  runTest();
  
  Serial.println("********* 860 SPS ************");
  ads.setSPS(ADS1115_DR_860SPS);     
  runTest();
}

void loop(void)
{

}

void runTest() 
{
  int16_t results0_1, results0_3, results1_3, results2_3;   

  results0_1 = ads.readADC_Differential_0_1();
  Serial.print("Differential 0-1: "); Serial.print(results0_1); Serial.print("("); Serial.print(results0_1 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_Differential_0_1_V());

  results0_3 = ads.readADC_Differential_0_3();
  Serial.print("Differential 0-3: "); Serial.print(results0_3); Serial.print("("); Serial.print(results0_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_Differential_0_3_V());

  results1_3 = ads.readADC_Differential_1_3();
  Serial.print("Differential 1-3: "); Serial.print(results1_3); Serial.print("("); Serial.print(results1_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_Differential_1_3_V());

  results2_3 = ads.readADC_Differential_2_3();
  Serial.print("Differential 2-3: "); Serial.print(results2_3); Serial.print("("); Serial.print(results2_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_Differential_2_3_V());

  results0_1 = ads.readADC_SingleEnded(0);
  Serial.print("Single 0: "); Serial.print(results0_1); Serial.print("("); Serial.print(results0_1 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_SingleEnded_V(0));

  results0_3 = ads.readADC_SingleEnded(1);
  Serial.print("Single 1: "); Serial.print(results0_3); Serial.print("("); Serial.print(results0_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_SingleEnded_V(1));

  results1_3 = ads.readADC_SingleEnded(2);
  Serial.print("Single 2: "); Serial.print(results1_3); Serial.print("("); Serial.print(results1_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_SingleEnded_V(2));

  results2_3 = ads.readADC_SingleEnded(3);
  Serial.print("Single 3: "); Serial.print(results2_3); Serial.print("("); Serial.print(results2_3 * multiplier); Serial.println("mV)");
  Serial.println(1000.0F*ads.readADC_SingleEnded_V(3));

  Serial.print("Read Time Microseconds: ");
  uint32_t sampleTime = micros();
  results2_3 = ads.readADC_SingleEnded(3);
  Serial.println(micros() - sampleTime);
  Serial.println();

  delay(2000);
}

