const long REFRESH_TIME = 200;

void initLCD(){
  lcd.init();
  lcd.cursor_on();
  lcd.backlight();
  lcd.setCursor(0, 0);      
  lcd.print("  Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("  KSP Process");
}

long last_update = 0;
void updateScreen(){
  long now = millis();
  if(now - last_update < REFRESH_TIME){
    return;
  }
  last_update = now;
  
  switch(currentScreen){
  case TAKEOFF:
    printTakeOff();
    break;
  case ORBITAL:
    printOrbital();
    break;
  case LANDING:
    printLanding();
    break;
  case TARGET:
    printTarget();
    break;
  }
}

void menuPushButton(){
  encoder.setPosition(0);
  updateEncoder();
}

void printTakeOff(){
  printSurfaceVelocity(0);
  printApoapsisInfo(1);
}

void printOrbital(){
  printApoapsisInfo(1 - (ApsidesTime.periapsis > ApsidesTime.apoapsis));
  printPeriapsisInfo(ApsidesTime.periapsis > ApsidesTime.apoapsis);
}

void printLanding(){
  printSurfaceAltitude(0);
  printHVVelocities(1);
}

void printTarget(){
  printTargetDistance(0);
  printTargetVelocity(1);
}

