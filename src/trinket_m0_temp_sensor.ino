#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <math.h>

// the value of the 'other' resistor
#define SERIESRESISTOR 10000
// What pin to connect the sensor to
#define THERMISTORPIN A4
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950

#define NUMPIXELS 1 
#define DATAPIN 7
#define CLOCKPIN 8
#define RED_LED 13

#define SECOND 1000

#define AMBIENT_TEMP 23
#define MAX_TEMP 60
#define IDLE_TEMP 30

#define RGB_OFF 0x000000 
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define RED 0xFF0000
#define PINK 0xFF0EF0

#define TEMP_OFFSET 20
int temp_to_colors[40][2] = {
  //ambient
  { 0, 0x00D4FF },
  { 1, 0x00E4FF },
  { 2, 0x00fff4  },
  { 3, 0x00ffd0 },
  { 4, 0x00ffa8 },
  { 5, 0x00ff83 },
  { 6, 0x00ff5c },
  { 7, 0x00ff36 },
  { 8, 0x00ff10 },
  { 9, 0x17ff00 },
  
  //idle
  { 10, 0x3eff00 },
  { 11, 0x65ff00 },
  { 12, 0x8aff00 },
  { 13, 0xb0ff00 },
  { 14, 0xd7ff00 },
  { 15, 0xfdff00 },
  { 16, 0xFFfa00 },
  { 17, 0xFFf000 },
  { 18, 0xFFe600 },
  { 19, 0xFFdc00 },

  // load
  { 20, 0xFFd200 },
  { 21, 0xFFc800 },
  { 22, 0xFFbe00 },
  { 23, 0xFFb400 },
  { 24, 0xFFaa00 },
  { 25, 0xFFa000 },
  { 26, 0xFF9600 },
  { 27, 0xFF8c00 },
  { 28, 0xFF8200 },
  { 29, 0xFF7800 },
  { 30, 0xFF6e00 },
  { 31, 0xFF6400 },
  { 32, 0xFF5a00 },
  { 33, 0xFF5000 },
  { 34, 0xFF4600 },
  { 35, 0xFF3c00 },
  { 36, 0xFF3200 },
  { 37, 0xFF2800 },
  { 38, 0xFF1e00 },
  { 39, 0xFF1400 },
};

Adafruit_DotStar rgbLed(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

void setup() {
  pinMode(RED_LED, OUTPUT);
  
  led_off();
  Serial.begin(9600);
  rgbLed.begin();  
  rgbLed.show();
  rgbLed.setBrightness(60);
  rgbLed.show();
}

void led_on() { digitalWrite(RED_LED, HIGH); }

void led_off() { digitalWrite(RED_LED, LOW); }

void set_rgb_color(int color) {
  rgbLed.setPixelColor(0, color);
  rgbLed.show();
}

float take_reading() {
  float average = 0.0;
  for(byte i = 0; i < NUMSAMPLES; i++) {
    float currentRead = analogRead(THERMISTORPIN);
    // convert the value to resistance
    currentRead = 1023 / currentRead - 1;
    currentRead = SERIESRESISTOR / currentRead;
    average += currentRead;  
  }
  return average / NUMSAMPLES;
}

float calculate_temp(float resistance) {
  float steinhart = resistance / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart;
}

void send_temp(float temp) {
  led_on();
  Serial.println(temp);
  delay(SECOND);
  led_off();
}

int temp_to_rgb(float temp) {
  int i = (int)round(temp) - TEMP_OFFSET;
  if (i >= 40) { return PINK; }
  if (i < 0) { return BLUE; }
  return temp_to_colors[i][1];
}

void loop()
{
  float reading = take_reading();
  float temp = calculate_temp(reading);
  int rgb = temp_to_rgb(temp);
  set_rgb_color(rgb);
  send_temp(temp);
}
