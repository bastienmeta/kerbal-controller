using namespace ace_button;

// DIGITAL IN
AceButton d11(11, HIGH, MENU);
AceButton d22(22, LOW, AG10);
AceButton d23(23, LOW, STAGE_LOCK);
AceButton d24(24, LOW, AG9);
AceButton d25(25, LOW, RCS);
AceButton d26(26, LOW, AG8);
AceButton d27(27, LOW, SAS);
AceButton d28(28, LOW, AG7);
AceButton d29(29, LOW, BRAKES);
AceButton d30(30, LOW, AG6);
AceButton d31(31, LOW, GEARS);
AceButton d32(32, LOW, AG5);
AceButton d33(33, LOW, LIGHTS);
AceButton d34(34, LOW, AG4);
AceButton d35(35, LOW, JOY_RIGHT);
AceButton d36(36, LOW, AG3);
AceButton d37(37, LOW, JOY_LEFT);
AceButton d38(38, LOW, AG2);
AceButton d39(39, LOW, STAGE);
AceButton d40(40, LOW, AG1);

void setButtons(){
  // DIGITAL
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(31, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(38, INPUT);
  pinMode(39, INPUT);
  pinMode(40, INPUT);  
  pinMode(11, INPUT_PULLUP);
  
  pinMode(LED_PIN, OUTPUT);

  d22.setEventHandler(handler);
  d23.setEventHandler(handler);
  d24.setEventHandler(handler);
  d25.setEventHandler(handler);
  d26.setEventHandler(handler);
  d27.setEventHandler(handler);
  d28.setEventHandler(handler);
  d29.setEventHandler(handler);
  d30.setEventHandler(handler);
  d31.setEventHandler(handler);
  d32.setEventHandler(handler);
  d33.setEventHandler(handler);
  d34.setEventHandler(handler);
  d35.setEventHandler(handler);
  d36.setEventHandler(handler);
  d37.setEventHandler(handler);
  d38.setEventHandler(handler);
  d39.setEventHandler(handler);
  d40.setEventHandler(handler);
  d11.setEventHandler(handler);
}

void checkButtons(){
  d22.check();
  d23.check();
  d24.check();
  d25.check();
  d26.check();
  d27.check();
  d28.check();
  d29.check();
  d30.check();
  d31.check();
  d32.check();
  d33.check();
  d34.check();
  d35.check();
  d36.check();
  d37.check();
  d38.check();
  d39.check();
  d40.check();
  d11.check();

  updateLED();
}


//void handler(AceButton* button , uint8_t eventType, uint8_t buttonState ) {
//      
//  int a = button->getPin();
//  switch (eventType) {
//    case AceButton::kEventReleased:
//      conditionnalPrint(String(a), 0, 0, true);
//      conditionnalPrint("Released", 1, 0, false);
//
//      if(a == 11){
//        digitalWrite(7, LOW);  
//      }
//      
//      break;
//    case AceButton::kEventPressed:
//      conditionnalPrint(String(a), 0, 0, true);
//      conditionnalPrint("Pressed", 1, 0, false);
//
//      if(a == 11){
//        digitalWrite(7, HIGH);  
//      }
//      
//      break;
//  }
//}

void handler(AceButton* button , uint8_t eventType, uint8_t buttonState ) {
  int id = button->getId();
  switch (eventType) {
    case AceButton::kEventReleased:
      buttonsState[id] = false;      
      triggerAction(id, false);
      break;
      
    case AceButton::kEventPressed:
      buttonsState[id] = true;      
      triggerAction(id, true);
      break;
  }
}

void triggerAction(int id, bool a){
  switch(id){
    case MENU:
      menuPushButton();
      break;
    case STAGE:
      if(a && buttonsState[STAGE_LOCK]){
        simpit.activateAction(STAGE_ACTION);
      }
      break;
      
    case RCS:
      a? simpit.activateAction(RCS_ACTION) : simpit.deactivateAction(RCS_ACTION);
      break;
      
    case SAS:
      a? simpit.activateAction(SAS_ACTION) : simpit.deactivateAction(SAS_ACTION);
      break;

    case STAGE_LOCK:
      if(a){
        startLED();
      }
      else{
        stopLED();
      }
      break;
                      
    case GEARS:
      a? simpit.activateAction(GEAR_ACTION) : simpit.deactivateAction(GEAR_ACTION);
      break;
      
    case LIGHTS:
      a? simpit.activateAction(LIGHT_ACTION) : simpit.deactivateAction(LIGHT_ACTION);
      break;
      
    case BRAKES:
      a? simpit.activateAction(BRAKES_ACTION) : simpit.deactivateAction(BRAKES_ACTION);
      break;
      
    case AG1:
      a? simpit.activateCAG((byte)1) : simpit.deactivateCAG((byte)1);
      break;
      
    case AG2:
      a? simpit.activateCAG((byte)2) : simpit.deactivateCAG((byte)2);
      break; 
      
    case AG3:
      a? simpit.activateCAG((byte)3) : simpit.deactivateCAG((byte)3);
      break;
      
    case AG4:
      a? simpit.activateCAG((byte)4) : simpit.deactivateCAG((byte)4);
      break;
      
    case AG5:
      a? simpit.activateCAG((byte)5) : simpit.deactivateCAG((byte)5);
      break;
      
    case AG6:
      a? simpit.activateCAG((byte)6) : simpit.deactivateCAG((byte)6);
      break;
      
    case AG7:
      a? simpit.activateCAG((byte)7) : simpit.deactivateCAG((byte)7);
      break;
      
    case AG8:
      a? simpit.activateCAG((byte)8) : simpit.deactivateCAG((byte)8);
      break;
      
    case AG9:
      a? simpit.activateCAG((byte)9) : simpit.deactivateCAG((byte)9);
      break;
      
    case AG10:
      a? simpit.activateCAG((byte)10) : simpit.deactivateCAG((byte)10);
      break;
  }
}

unsigned long lastLED;

void startLED(){
  st_led = true;
  lastLED = millis();
  digitalWrite(LED_PIN, HIGH);
}

void stopLED(){
  st_led = false;
  digitalWrite(LED_PIN, LOW);
}

void updateLED(){
  if(buttonsState[STAGE_LOCK]){
    unsigned long now = millis();
    if(now - lastLED > 1000){
      st_led ? digitalWrite(LED_PIN, LOW) : digitalWrite(LED_PIN, HIGH);
      st_led = !st_led;
      lastLED = now;
    }
  }
}

void alignStates(){
  
}



