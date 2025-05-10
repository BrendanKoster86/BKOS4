#if HARDWARE == 2
  #if RESOLUTIE == 2432
    void ts_begin(){
      // digitalWrite(TS_CS, HIGH);
      ts.begin();
    }
    
    void ts_setup(){
      spi_ts.begin(TS_SCK, TS_MISO, TS_MOSI, TS_CS);
      ts_begin();
      ts.setRotation(2);
    }
  #else
    void ts_begin(){
      digitalWrite(TS_CS, HIGH);
      ts.begin();
    }
    
    void ts_setup(){
      // spi_ts.begin(TS_SCK, TS_MISO, TS_MOSI, TS_CS);
      ts_begin();
      ts.setRotation(2);
    }
  #endif

#elif HARDWARE == 3
  void ts_begin(){
    ts.begin(spi_ts);
  }
  void ts_setup(){
    spi_ts.begin(TS_SCK, TS_MISO, TS_MOSI, TS_CS);
    ts_begin();
    ts.setRotation(0);
  }
#elif HARDWARE == 4
  void ts_begin(){
    ts.read();
  }
  void ts_setup(){
    ts.begin();
    ts.setRotation(0);
  }
#elif HARDWARE == 5
  void ts_begin(){
    ts.read();
  }
  void ts_setup(){
    ts.begin();
    ts.setRotation(0);
  }
#else
  void ts_begin(){
    ts.begin();
  }
  void ts_setup(){
    ts_begin();
    ts.setRotation(ROTATIE);
  }
#endif

#if TS_DRIVER == 3
  bool ts_touched() {
    // ts.read();
    if (ts.isTouched) {
      return true;
    }
    return false;
  }

  #if ORIENTATIE == 1
    #if HARDWARE == 4
      int touch_x() {
        ts.read();
        return map(ts.points[0].x, 5, 275, 0, 240);
      }
      int touch_y() {
        ts.read();
        return map(ts.points[0].y, 5, 480, 0, 320);
      }
    #elif HARDWARE == 5
      int touch_x() {
        ts.read();
        return map(ts.points[0].x, 5, 500, 0, 240);
      }
      int touch_y() {
        ts.read();
        return map(ts.points[0].y, 5, 800, 0, 320);
      }
    #endif
  #elif ORIENTATIE == 0
    #if HARDWARE == 4
      int touch_x() {
        ts.read();
        return map(ts.points[0].y, 5, 480, 0, 240);
      }
      int touch_y() {
        ts.read();
        return map(ts.points[0].x, 275, 5, 0, 320);
      }
    #elif HARDWARE == 5
      int touch_x() {
        ts.read();
        return map(ts.points[0].y, 5, 800, 0, 240);
      }
      int touch_y() {
        ts.read();
        return map(ts.points[0].x, 500, 5, 0, 320);
      }
    #endif
  #endif
#else
  bool ts_touched(){
    if (ts.tirqTouched()) {
      if (ts.touched()) {
        return true;
      }
    }
    return false;
  }

  int touch_x() {
    TS_Point p = ts.getPoint();
    float x = (p.x - xcorrectie) / xfactor;
    // actie = 1;
    return x;
  }

  int touch_y() {
    TS_Point p = ts.getPoint();
    float y = (p.y - ycorrectie) / yfactor;
    // actie = 1;
    return y;
  }
#endif