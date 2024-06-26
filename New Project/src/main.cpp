#include "config.hpp"

byte joyLeftValues[2];
byte joyRightValue[2];

// byte ptr_l[2] = *joyLeftValues;
// byte ptr_r[2] = *joyLeftValues;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void joystick1_read();
void joystick2_read();
void getBatteryLevel();

void setup()
{
  // put your setup code here, to run once:
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, 200);
  tft.init(240, 320);
  tft.fillScreen(ST77XX_BLUE);
  tft.setRotation(2);
  tft.setTextSize(1);
  tft.setCursor(10, 40);
  tft.print("Hello");
}

PeriodicTask DETECT_LEFT_JOYSTICK_VALUE(100, joystick1_read), DETECT_RIGHT_JOYSTICK_VALUE(100, joystick2_read), DETECT_BATTERY(1000, getBatteryLevel);

// FIXME: detect correct values for buttons: t_hold_min & t_hold_max !!!
JoystickButton Button_1(100, 300, Butt_A), Button_2(300, 600, Butt_A), Button_3(600, 800, Butt_A), Button_4(800, 1000, Butt_A);

void loop()
{
  DETECT_LEFT_JOYSTICK_VALUE.run();
  DETECT_RIGHT_JOYSTICK_VALUE.run();

  if (millis() % 100 == 0)
  {
    tft.setCursor(10, 10);
    tft.print("Joystick 1X:   ");
    tft.print(String(joyLeftValues[0]));

    tft.setCursor(10, 20);
    tft.print("Joystick 1Y:   ");
    tft.print(String(joyLeftValues[1]));

    tft.setCursor(20, 10);
    tft.print("Joystick 2X:   ");
    tft.print(String(joyRightValue[0]));

    tft.setCursor(20, 20);
    tft.print("Joystick 2Y:   ");
    tft.print(String(joyRightValue[1]));
  }
}

void joystick1_read()
{
  read_Joystick(LEFT_JOY, joyLeftValues);
}

void joystick2_read()
{
  read_Joystick(RIGHT_JOY, joyRightValue);
}

void getBatteryLevel()
{
  float battery = getBattery(MODE_Prcnt);

  tft.setCursor(40, 10);
  tft.print("Battery: ");
  tft.print(String(battery));

  if (MODE_Prcnt)
  {
    tft.print("%");
  }
}