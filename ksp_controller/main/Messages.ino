
void messageHandler(byte messageType, byte msg[], byte msgSize) {
  switch(messageType){
  case ALTITUDE_MESSAGE:
    Altitude = parseAltitude(msg);
    break;
  case VELOCITY_MESSAGE:
    Velocity = parseVelocity(msg);
    break;
  case APSIDES_MESSAGE:
    Apsides = parseApsides(msg);
    break;
  case TARGETINFO_MESSAGE:
    Target = parseTarget(msg);
    break;
  case APSIDESTIME_MESSAGE:
    ApsidesTime = parseApsidesTime(msg);
    break;
  }
}

void registerMessages(){
  simpit.inboundHandler(messageHandler);
  simpit.registerChannel(ALTITUDE_MESSAGE);
  simpit.registerChannel(APSIDES_MESSAGE);
  simpit.registerChannel(VELOCITY_MESSAGE);
  simpit.registerChannel(TARGETINFO_MESSAGE);
  simpit.registerChannel(APSIDESTIME_MESSAGE);
}

long prev_t = 0;
float prev_v = 0;
float getSurfaceAccel(){
  long t = millis();
  float dt = (float(t) - float(prev_t)) * 1e-3;
  float dv = Velocity.surface-prev_v;
  prev_t = t;
  prev_v = Velocity.surface;

  float a;
  if(dt != 0)
    a = dv / dt;
  else
    a = 0;

  return a;
}


