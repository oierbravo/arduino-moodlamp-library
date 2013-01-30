#include <Moodlamp.h>
//pin mapping.
int red_pin = 3;
int green_pin = 5;
int blue_pin = 6;

//Initializing moodlamp.
Moodlamp mood(red_pin,green_pin,blue_pin);

void setup(){
  //Setting cycle mode.
  mood.setMode(Moodlamp::MODE_CYCLE);
  //setting a bigger update time.
  mood.setUpdateTime(100);
  //setting a bigger cycle update time.
  mood.setCycleUpdateTime(10000);
}
void loop(){
  //Calling update function.
  mood.update(); 
}


