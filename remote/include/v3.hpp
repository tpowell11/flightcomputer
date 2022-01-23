/*
Author: Tom Powell, 2021
Purpose: 3-dimensional vector library for motion processing
Platform: ATmega with Arduino bootloader/firmware
Build: Platformio
*/
#include <Arduino.h>
struct v3 {
  float x;
  float y;
  float z;
  v3(){ //default
    x=0.0;
    y=0.0;
    z=0.0;
  }
  v3 (int v) {
    x=v;
    y=v;
    z=v;
  }
  /*
  This template declaration will ONLY work for sensors_event_t
  from Adafruit's sensor libraries.
  */
  template <typename t>
  v3 (t v){
    x=v.acceleration.x;
    y=v.acceleration.y;
    z=v.acceleration.z;
  }
  String to_str(String unit){ //! using adafruit's string library, not std::
    String *r;
    r->concat(x);
    r->concat("x ");
    r->concat(y);
    r->concat("y ");
    r->concat(z);
    r->concat("z ");
    r->concat(unit);
    return *r;
    delete r;
  }
  v3 operator + (const v3& other){
    v3 v;
    v.x = this->x+other.x;
    v.y = this->y+other.y;
    v.z = this->z+other.z;
    return v;
  }
  void operator = (const float& other){
    x=other;
    y=other;
    z=other;
  }
  void operator = (const double& other){
    x=other;
    y=other;
    z=other;
  }
  void operator += (const v3& other){
    x=other.x+x;
    y=other.y+y;
    x=other.z+z;
  }
};
template <typename T>
v3 cpV3 (T v, v3 other){
    //vector format constructor
    other.x=v.x;
    other.y=v.y;
    other.z=v.z;
    return other;
}
template <typename T>
v3 tV3 (T v){
    //vector format constructor
    v3* vector(0);
    vector->x=v.x;
    vector->y=v.y;
    vector->z=v.z;
    return vector;
    delete vector;
}
v3 integrate(v3 a, v3 b, float dt){
  /*
  Simple trapezoidal numerical integral
  */
  v3 r;
  r.x = a.x+(.5*dt*(b.x-a.x));
  r.y = a.y+(.5*dt*(b.y-a.y));
  r.z = a.z+(.5*dt*(b.z-a.z));
  return r;
}
