
void ftoa2(float f, char* s){
  if(f<100){
    ftoa(s, f, 2);
  }
  else if(f<1000){
    ftoa(s, f, 1);
  }
  else if(f<10000){
    ftoa(s, f, 0);
  }
  else{
    ftoa(s, f, 0);
  }
}

char *ftoa(char *a, double f, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
  
  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  if(precision > 0){
    *a++ = '.';
    long desimal = abs((long)((f - heiltal) * p[precision]));
    if(desimal < 10 && precision > 1)
      for(int i=1; i<precision; i++)
        *a++ = '0';
    itoa(desimal, a, 10);
  }
  return ret;
}

void format(float f, char* t, unsigned char& u){
  if(f < 1e1){
    ftoa2(f*1e3, t);
    u = 'm';
  }   
  else if(f < 1e4){
    ftoa2(f, t);
    u = ' ';
  }
  else if(f < 1e7){
    ftoa2(f*1e-3, t);
    u = 'k';  
  }
  else if(f < 1e10){
    ftoa2(f*1e-6, t);
    u = 'M';  
  }
  else if(f < 1e13){
    ftoa2(f*1e-9, t);
    u = 'G';  
  }
  else if(f < 1e16){
    ftoa2(f*1e-12, t);
    u = 'T';  
  }
  else{
    ftoa2(1234, t);
    u = '?';
  }
}

void timeToString(int32_t t, char* str)
{
 int32_t h = t / 3600;
 t = t % 3600;
 int32_t m = t / 60;
 int32_t s = t % 60;

 sprintf(str, "%02ld:%02ld:%02ld", h, m, s);
}

void printSurfaceVelocity(int line){
  float v = Velocity.surface;

  char sv[8];
  unsigned char su;
  format(v, sv, su);

  char s1[17];
  sprintf(s1, "Sv: %s %cm/s", sv, su);

  char line1[17];
  sprintf(line1, "%-16s", s1);
  lcd.setCursor(0,line);  
  lcd.print(line1);  
}

void printOrbitVelocity(int line){
  float v = Velocity.orbital;

  char sv[8];
  unsigned char su;
  format(v, sv, su);

  char s1[17];
  sprintf(s1, "Ov: %s %cm/s", sv, su);

  char line1[17];
  sprintf(line1, "%-16s", s1);
  lcd.setCursor(0,line);  
  lcd.print(line1);   
}

void printHVVelocities(int line){
  float v = Velocity.surface;
  float vert = Velocity.vertical;
  float hori = sqrt(pow(v,2)-pow(vert,2));

  char hv[6];
  unsigned char hu=' ';
  format(hori, hv, hu);

  char vv[6];
  unsigned char vu=' ';
  format(vert, vv, vu);
  
  char s1[17];
  sprintf(s1,"H%s%c  V%s%c",hv,hu,vv,vu);
  char line1[17];
  sprintf(line1, "%-16s", s1);  
  lcd.setCursor(0,line);
  lcd.print(line1);
}

void printApoapsisInfo(int line){
  float ap = Apsides.apoapsis;
  int32_t tap = ApsidesTime.apoapsis;

  char str_ap[6];
  unsigned char unit=' ';
  format(ap, str_ap, unit);

  char str_tap[9];
  timeToString(tap, str_tap);

  char s[17];
  sprintf(s, "A%s%c %s", str_ap, unit, str_tap);
  char line1[17];
  sprintf(line1, "%-16s", s);  
  lcd.setCursor(0,line);
  lcd.print(line1);  
}

void printPeriapsisInfo(int line){
  float pe = Apsides.periapsis;
  int32_t tpe = ApsidesTime.periapsis;

  char str_pe[6];
  unsigned char unit=' ';
  format(pe, str_pe, unit);

  char str_tpe[9];
  timeToString(tpe, str_tpe);

  char s[17];
  sprintf(s, "P%s%c %s", str_pe, unit, str_tpe);
  char line1[17];
  sprintf(line1, "%-16s", s);
  lcd.setCursor(0,line);
  lcd.print(line1);  
}

void printSurfaceAltitude(int line){
  float v = Altitude.surface;

  char sv[8];
  unsigned char su;
  format(v, sv, su);

  char s1[17];
  sprintf(s1, "Sa: %s %cm", sv, su);

  char line1[17];
  sprintf(line1, "%-16s", s1);
  lcd.setCursor(0,line);  
  lcd.print(line1);   
}

void printTargetDistance(int line){
  float v = Target.distance;

  char sv[8];
  unsigned char su;
  format(v, sv, su);

  char s1[17];
  sprintf(s1, "Td: %s %cm", sv, su);

  char line1[17];
  sprintf(line1, "%-16s", s1);
  lcd.setCursor(0,line);  
  lcd.print(line1);    
}

void printTargetVelocity(int line){
  float v = Target.velocity;

  char sv[8];
  unsigned char su;
  format(v, sv, su);

  char s1[17];
  sprintf(s1, "Tv: %s %cm/s", sv, su);

  char line1[17];
  sprintf(line1, "%-16s", s1);
  lcd.setCursor(0,line);  
  lcd.print(line1);    
}
