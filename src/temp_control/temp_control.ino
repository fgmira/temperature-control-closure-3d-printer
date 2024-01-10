#include <Adafruit_SSD1306.h>
#include <splash.h>

/* **
 *  Control temperature of a room using a fan and a heater
 *  Before uploading this code please run `sudo chmod a+rw /dev/ttyUSB*` in the terminal
 */
#include <Keypad.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const byte ROWS = 4; // four rows
const byte COLS = 3; // four columns

// SETUP KEYPAD
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}}; // keypad layout

byte rowPins[ROWS] = {3, 8, 7, 5}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 2, 6};    // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// SETUP DHT
#define DHTTYPE DHT22
#define DHTPIN 9
DHT dht(DHTPIN, DHTTYPE);

// SETUP OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char btm_logo[] PROGMEM = {
    // 'impressora3d (1), 128x64px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x87, 0xfe, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x8f, 0xff, 0x03, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x03, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3c, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x07, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x07, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x4f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xc1, 0xc3, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x03, 0xe0, 0x7f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x07, 0xf8, 0x3f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x81, 0xe0, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x70, 0x07, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x0e, 0x1c, 0x1f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x83, 0xe0, 0x1f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xf0, 0xc3, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xfc, 0x8f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xfc, 0x9f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xfc, 0x9f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xfc, 0x9f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0xfc, 0x9f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x7c, 0x9f, 0x9f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x1c, 0x9e, 0x1f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x84, 0x98, 0x7f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xe0, 0x81, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x87, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfe, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x70, 0x00, 0x00, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char logo_alert[] PROGMEM = {
    // 'alert (2)', 20x20px
    0xff, 0x9f, 0xf0, 0xff, 0x6f, 0xf0, 0xfe, 0x67, 0xf0, 0xfe, 0xf7, 0xf0, 0xfc, 0xf3, 0xf0, 0xfd,
    0x9b, 0xf0, 0xf9, 0x09, 0xf0, 0xfb, 0x6d, 0xf0, 0xf3, 0x6c, 0xf0, 0xf7, 0x0e, 0xf0, 0xe7, 0x0e,
    0x70, 0xef, 0x9f, 0x70, 0xcf, 0x9f, 0x30, 0xdf, 0xff, 0xb0, 0x9f, 0x9f, 0x90, 0xbf, 0x0f, 0xd0,
    0x3f, 0x0f, 0xc0, 0x7f, 0x9f, 0xe0, 0x3f, 0xff, 0xc0, 0x80, 0x00, 0x10};

// SETUP relay MODULE
const int relay_pin1 = 10;
const int relay_pin2 = 11;
const int relay_pin3 = 12;
const int relay_pin4 = 13;

// LOGICAL VARIABLES

int fan_on_off = 0; // 0=OFF 1=ON
int fan_mode = 0;   // 0=AUTO 1=MANUAL
int temp_limit = 60;
int humi_limit = 90;

float h = 0;
float t = 0;
float f = 0;
float hif = 0;
float hic = 0;

char key;

void setup()
{

  // warmap components
  Serial.begin(9600);
  pinMode(relay_pin1, OUTPUT);
  pinMode(relay_pin2, OUTPUT);
  pinMode(relay_pin3, OUTPUT);
  pinMode(relay_pin4, OUTPUT);

  // sensor temp hum
  dht.begin();

  // display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.drawBitmap(0, 0, btm_logo, 128, 64, WHITE);
  display.display();

  // relay test
  digitalWrite(relay_pin1, LOW);
  digitalWrite(relay_pin2, LOW);
  digitalWrite(relay_pin3, LOW);
  digitalWrite(relay_pin4, LOW);
  delay(1000);
  digitalWrite(relay_pin1, HIGH);
  delay(1000);
  digitalWrite(relay_pin2, HIGH);
  delay(1000);
  digitalWrite(relay_pin3, HIGH);
  delay(1000);
  digitalWrite(relay_pin4, HIGH);
  relay_off();
}

void loop()
{
  key = keypad.getKey();
  get_temp_humid();
  print_status();
  Serial.print(F("key: "));
  Serial.println(key);
  if (key == '#')
  {
    menu();
  }
}

void menu()
{
  int exit_loop = 0;
  int new_value = 0;

  display.clearDisplay();
  Serial.println(F("Menu: Choose '1' for Temperature, '2' for Humidity, '3' for Fan, or '*' to exit"));
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("     --- MENU ---"));
  display.println(F("Options:"));
  display.println(F("1.Set Temp Limit"));
  display.println(F("2.Set Humi Limit"));
  display.println(F("3.ON/OFF Fan manual"));
  display.println(F("4.Set Fan mode"));
  display.println(F("*.Exit"));
  display.print(F("TL:"));
  display.print(temp_limit);
  display.print(F(" HL:"));
  display.print(humi_limit);
  display.print(F(" F:"));
  if (fan_on_off == 0)
  {
    display.print(F("OFF "));
  }
  else
  {
    display.print(F("ON "));
  }
  if (fan_mode == 0)
  {
    display.print(F("A"));
  }
  else
  {
    display.print(F("M"));
  }
  display.display();

  while (key != '*')
  {
    key = keypad.getKey();
    Serial.print(F("Principal Menu: key = "));
    Serial.println(key);
    if (key != NO_KEY)
    {
      switch (key)
      {
      case '1':
        exit_loop = 0;
        new_value = 0;
        while (exit_loop == 0)
        {
          Serial.println(F("Set Temperature"));
          Serial.print(F("key = "));
          Serial.println(key);
          Serial.print(F("new_value = "));
          Serial.println(new_value);
          display.clearDisplay();
          display.setTextSize(1);
          display.setCursor(0, 0);
          display.println(F("Enter new value from Temperature Limit"));
          display.setTextSize(2);
          if (new_value == 0)
          {
            Serial.println(F("new_value zero"));
            display.println(F("  00"));
          }
          if (new_value > 0 && new_value < 10)
          {
            Serial.println(F("new_value < 10"));
            display.print(F("  0"));
            display.println(new_value);
          }
          if (new_value >= 10 && new_value < 100)
          {
            Serial.println(F("new_value > 10"));
            display.print(F("  "));
            display.println(new_value);
          }
          if (new_value >= 100)
          {
            Serial.println(F("new_value >= 100"));
            new_value = 0;
          }
          display.setTextSize(1);
          display.println(F("Press * to confirm and exit"));
          display.println(F("Press # to cancel"));
          display.display();
          key = keypad.getKey();
          if (key == '*')
          {
            Serial.println(F("Set temp_limit and exit"));
            if (new_value < 20 || new_value > 60)
            {
              Serial.println(F("new_tem invalid"));
              display.clearDisplay();
              display.setTextSize(1);
              display.drawBitmap(0, 0, logo_alert, 20, 20, WHITE);
              display.setCursor(22, 10);
              display.print(F("Invalid Value!"));
              display.setCursor(0, 30);
              display.print(F("Limit temperature must be greater than or equal to 20 and less than or equal to 60"));
              display.display();
              delay(5000);
              new_value = 0;
            }
            else
            {
              Serial.println(F("Set temp_limit"));
              temp_limit = new_value;
              exit_loop = 1;
              break;
            }
          }
          if (key == '#')
          {
            Serial.println(F("Cancel"));
            exit_loop = 1;
            break;
          }
          if (key != '*' && key != '#' && key != NO_KEY)
          {
            Serial.println(F("Calculate new_value"));
            if (new_value < 99)
            {
              Serial.println(F("Calculate"));
              Serial.println(key - 0x30);
              new_value = new_value * 10 + (key - 0x30);
              Serial.print(F("new_value: "));
              Serial.println(new_value);
            }
            else
            {
              new_value = 0;
            }
          }
        }
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(F("Press * to exit"));
        display.display();
        break;
      case '2':
        Serial.println(F("Set Humidity"));
        exit_loop = 0;
        new_value = 0;
        while (exit_loop == 0)
        {
          Serial.println(F("Set Humidity"));
          Serial.print(F("key = "));
          Serial.println(key);
          Serial.print(F("new_value = "));
          Serial.println(new_value);
          display.clearDisplay();
          display.setTextSize(1);
          display.setCursor(0, 0);
          display.println(F("Enter new value from Humidity Limit"));
          display.setTextSize(2);
          if (new_value == 0)
          {
            Serial.println(F("new_value zero"));
            display.println(F("  00"));
          }
          if (new_value > 0 && new_value < 10)
          {
            Serial.println(F("new_value < 10"));
            display.print(F("  0"));
            display.println(new_value);
          }
          if (new_value >= 10 && new_value < 100)
          {
            Serial.println(F("new_value > 10"));
            display.print(F("  "));
            display.println(new_value);
          }
          if (new_value >= 100)
          {
            Serial.println(F("new_value >= 100"));
            new_value = 0;
          }
          display.setTextSize(1);
          display.println(F("Press * to confirm and exit"));
          display.println(F("Press # to cancel"));
          display.display();
          key = keypad.getKey();
          if (key == '*')
          {
            Serial.println(F("Set humi_limit and exit"));
            if (new_value < 60 || new_value > 90)
            {
              Serial.println(F("humi_limit invalid"));
              display.clearDisplay();
              display.setTextSize(1);
              display.drawBitmap(0, 0, logo_alert, 20, 20, WHITE);
              display.setCursor(22, 10);
              display.print(F("Invalid Value!"));
              display.setCursor(0, 30);
              display.print(F("Limit Humidity must be greater than or equal to 60 and less than or equal to 90"));
              display.display();
              delay(5000);
              new_value = 0;
            }
            else
            {
              Serial.println(F("Set humi_limit"));
              humi_limit = new_value;
              exit_loop = 1;
              break;
            }
          }
          if (key == '#')
          {
            Serial.println(F("Cancel"));
            exit_loop = 1;
            break;
          }
          if (key != '*' && key != '#' && key != NO_KEY)
          {
            Serial.println(F("Calculate new_value"));
            if (new_value < 99)
            {
              Serial.println(F("Calculate"));
              Serial.println(key - 0x30);
              new_value = new_value * 10 + (key - 0x30);
              Serial.print(F("new_value: "));
              Serial.println(new_value);
            }
            else
            {
              new_value = 0;
            }
          }
        }
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(F("Press * to exit"));
        display.display();
        break;
      case '3':
        Serial.println(F("Set Fan ON/OFF"));
        while (key != '*')
        {
          key = keypad.getKey();
          Serial.println(F("Set Fan ON/OFF"));
          display.clearDisplay();
          display.setCursor(0, 0);
          display.setTextSize(2);
          display.println(F("FAN ON/OFF"));
          display.println(F("1 ON"));
          display.println(F("2 OFF"));
          display.setTextSize(1);
          display.print(F("Fan:"));
          if (fan_on_off == 0)
          {
            display.print(F("OFF "));
          }
          else
          {
            display.print(F("ON "));
          }
          if (fan_mode == 0)
          {
            display.println(F("Auto"));
          }
          else
          {
            display.println(F("Manual"));
          }
          display.print(F("PRESS * TO EXIT"));
          display.display();
          if (key != NO_KEY)
          {
            if (key == '1')
            {
              fan_on_off = 1;
            }
            if (key == '2')
            {
              fan_on_off = 0;
            }
            if (key != '2' && key != '1' && key != '*')
            {
              display_invalid_key();
            }
          }
        }
        break;
      case '4':
        Serial.println(F("Set Fan MODE"));
        while (key != '*')
        {
          key = keypad.getKey();
          Serial.println(F("Set Fan MODE"));
          display.clearDisplay();
          display.setCursor(0, 0);
          display.setTextSize(2);
          display.println(F("FAN MODE"));
          display.println(F("1 AUTO"));
          display.println(F("2 MANUAL"));
          display.setTextSize(1);
          display.print(F("Fan:"));
          if (fan_on_off == 0)
          {
            display.print(F("OFF "));
          }
          else
          {
            display.print(F("ON "));
          }
          if (fan_mode == 0)
          {
            display.println(F("Auto"));
          }
          else
          {
            display.println(F("Manual"));
          }
          display.print(F("PRESS * TO EXIT"));
          display.display();
          if (key != NO_KEY)
          {
            if (key == '1')
            {
              fan_mode = 0;
            }
            if (key == '2')
            {
              fan_mode = 1;
            }
            if (key != '2' && key != '1' && key != '*')
            {
              display_invalid_key();
            }
          }
        }
        break;
      case '*':
        break;
      default:
        break;
      }
    }
  }
  Serial.println(F("Exit"));
}

void print_status()
{

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.drawBitmap(0, 0, logo_alert, 20, 20, WHITE);
    display.setCursor(22, 0);
    display.print(F("Failed to read"));
    display.setCursor(22, 10);
    display.print(F("  from DHT"));
    display.setCursor(22, 20);
    display.print(F("   sensor!"));
  }
  else
  {
    if (fan_mode == 0)
    {
      if (t > temp_limit || h > humi_limit)
      {
        fan_on_off = 1;
      }
      else
      {
        fan_on_off = 0;
      }
    }
    if (fan_on_off == 1)
    {
      relay_on();
    }
    else
    {
      relay_off();
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(F("T: "));
    display.print(t);
    display.println(F("C"));

    display.print(F("H: "));
    display.print(h);
    display.println(F("%"));

    display.setTextSize(1);
    display.print(F("Fan ON/OFF: "));
    if (fan_on_off == 0)
    {
      display.println(F("OFF"));
    }
    else
    {
      display.println(F("ON"));
    }
    display.print(F("Fan Mode: "));
    if (fan_mode == 0)
    {
      display.println(F("AUTO"));
    }
    else
    {
      display.println(F("MANUAL"));
    }
  }
  display.print(F("TL:"));
  display.print(temp_limit);
  display.print(F(" HL:"));
  display.println(humi_limit);
  display.print(F("HOLD # TO MENU"));
  display.display();
}

void get_temp_humid()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);

  hif = dht.computeHeatIndex(f, h);
  hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.print(F("Temperature Limit: "));
  Serial.print(temp_limit);
  Serial.print(F(" Humidity Limit: "));
  Serial.print(humi_limit);
  Serial.print(F(" Fan on/off: "));
  Serial.print(fan_on_off);
  Serial.print(F(" 0=OFF, 1=ON Fan mode: "));
  Serial.print(fan_mode);
  Serial.println(F(" 0=AUTO, 1=Manual"));
}

void relay_on()
{
  digitalWrite(relay_pin1, LOW);
  digitalWrite(relay_pin2, LOW);
  digitalWrite(relay_pin3, LOW);
  digitalWrite(relay_pin4, LOW);
}

void relay_off()
{
  digitalWrite(relay_pin1, HIGH);
  digitalWrite(relay_pin2, HIGH);
  digitalWrite(relay_pin3, HIGH);
  digitalWrite(relay_pin4, HIGH);
}

void display_invalid_key()
{
  display.clearDisplay();
  display.setCursor(0, 5);
  display.setTextSize(3);
  display.println(F("   ?   "));
  display.display();
  delay(1000);
}