#include <RotaryEncoder.h>
#include <AceButton.h>
#include <KerbalSimpit.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define AG1 0
#define AG2 1
#define AG3 2
#define AG4 3
#define AG5 4
#define AG6 5
#define AG7 6
#define AG8 7
#define AG9 8
#define AG10 9
#define RCS 10
#define SAS 11
#define GEARS 12
#define LIGHTS 13
#define BRAKES 14
#define STAGE_LOCK 15
#define STAGE 16
#define MENU 17
#define JOY_LEFT 18
#define JOY_RIGHT 19
bool buttonsState[20] = {false};

#define LED_PIN 7

using namespace ace_button;

KerbalSimpit simpit(Serial);
LiquidCrystal_I2C lcd(0x27,16,2);
RotaryEncoder encoder(2, 3);

#define NB_SCREEN 4
enum Screen{TAKEOFF, ORBITAL, TARGET, LANDING};
Screen currentScreen = 0;

bool st_led;

altitudeMessage Altitude;
targetMessage Target;
velocityMessage Velocity;
apsidesTimeMessage ApsidesTime;
apsidesMessage Apsides;


void setup() {
  Serial.begin(115200); // start the serial monitor link

  initLCD();

  while (!simpit.init()) {
    delay(100);
  }

  lcd.clear();    

  registerMessages();
  setButtons();
}

void loop() {
  simpit.update();
  
  checkButtons();

  updateEncoder();
  updateAnalog();
  updateScreen();  
}





