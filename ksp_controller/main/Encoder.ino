void updateEncoder(){
  encoder.tick();
  
  int newPos = encoder.getPosition();
  if (currentScreen != newPos) {
    currentScreen = newPos;
    if(currentScreen >= NB_SCREEN){
      currentScreen = 0; 
      encoder.setPosition(0);
    }
    else if(currentScreen < 0){
      currentScreen = NB_SCREEN-1;
      encoder.setPosition(NB_SCREEN-1);
    }

    lcd.clear();
  }
}


