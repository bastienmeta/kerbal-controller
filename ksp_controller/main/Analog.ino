int right_x, right_y, right_z;
int left_x, left_y, left_z;
int slider;

#define JOY_DEADZONE 2000
#define SLI_DEADZONE 1000

#define TRANSLATE_Y_INVERSED
#define TRANSLATE_Z_INVERSED

void setAnalogPins(){
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
}

void updateAnalog(){
  right_y = analogRead(A5);
  right_x = analogRead(A6);
  right_z = analogRead(A7);

  left_x = analogRead(A2);
  left_y = analogRead(A3);
  left_z = analogRead(A4);

  slider = analogRead(A8);

  handleRotation();
  handleTranslation();
  handleThrottle();
}

int16_t old_rx = 0;
int16_t old_ry = 0;
int16_t old_rz = 0;

void handleRotation(){
  int16_t rotate_x = transformAnalogInput(left_x);
  int16_t rotate_y = transformAnalogInput(left_y);
  int16_t rotate_z = transformAnalogInput(left_z);

  rotationMessage r;
  r.mask = 0;

  if(rotate_x != old_rx){
    #ifdef ROTATE_X_INVERSED 
      r.pitch = -rotate_x;
    #else
      r.pitch = rotate_x;
    #endif

    old_rx = rotate_x;
    r.mask = r.mask|1;
  }

  if(rotate_y != old_ry){
    #ifdef ROTATE_Y_INVERSED    
      r.yaw = -rotate_y;
    #else
      r.yaw = rotate_y; 
    #endif

    old_ry = rotate_y;
    r.mask = r.mask|4;
  }

  if(rotate_z != old_rz){
    #ifdef ROTATE_Z_INVERSED             
      r.roll = -rotate_z;
    #else
      r.roll = rotate_z;
    #endif

    old_rz = rotate_z;
    r.mask = r.mask|2;
  }

//  String s1 = String("x")+rotate_x/32+" y"+rotate_y/32+" z"+rotate_z/32;
//  lcd.setCursor(0,0);
//  lcd.print(s1);
//  lcd.print(r.mask);

  if(r.mask != 0){
    simpit.send(ROTATION_MESSAGE, r);
  }
}

int16_t old_tx = 0;
int16_t old_ty = 0;
int16_t old_tz = 0;

void handleTranslation(){
  int16_t translate_x = transformAnalogInput(right_x);
  int16_t translate_y = transformAnalogInput(right_y);
  int16_t translate_z = transformAnalogInput(right_z);


    translationMessage t;
    t.mask = 0;

  if(translate_x != old_tx){
    #ifdef TRANSLATE_X_INVERSED
      t.X = -translate_x;
    #else
      t.X = translate_x;
    #endif

    old_tx = translate_x;
    t.mask = t.mask|1;
  }

  if(translate_y != old_ty){
    #ifdef TRANSLATE_Y_INVERSED    
      t.Y = -translate_y;
    #else
      t.Y = translate_y; 
    #endif

    old_ty = translate_y;
    t.mask = t.mask|2;
  }

  if(translate_z != old_tz){
    #ifdef TRANSLATE_Z_INVERSED             
      t.Z = -translate_z;
    #else
      t.Z = translate_z;
    #endif

    old_tz = translate_z;
    t.mask = t.mask|4;
  }

//  String s1 = String("x")+translate_x/32+" y"+translate_y/32+" z"+translate_z/32;
//  lcd.setCursor(0,1);
//  lcd.print(s1);
//  lcd.print(t.mask);

  if(t.mask != 0){
    simpit.send(TRANSLATION_MESSAGE, t);
  }
}

uint16_t old_t;

void handleThrottle(){
  int16_t throttle = map(slider, 0, 1023, 0, 32767);
  if(throttle <= SLI_DEADZONE){
    throttle = 0;
  }
  else if(throttle >= 32676-SLI_DEADZONE){
    throttle = 32767;
  }

  if(throttle != old_t){
    old_t = throttle;
    simpit.send(THROTTLE_MESSAGE, (unsigned char*)(&throttle), 2);
  }
}

int16_t transformAnalogInput(int input){
  int16_t output = map(input, 0, 1023, -32768, 32767);
  if(output >= -JOY_DEADZONE && output <= JOY_DEADZONE){
    output = 0;
  }  

  return output;
}



//void printAnalog(){
//  String s1 = String("x")+right_x+" y"+right_y+" z"+right_z;
//  conditionnalPrint(s1, 0, 1, true);
//  String s2 = String("x")+left_x+" y"+left_y+" z"+left_z;
//  conditionnalPrint(s2, 1, 1, false);
//}


