#include <Moodlamp.h>
//pin mapping.
int red_pin = 3;
int green_pin = 5;
int blue_pin = 6;

//Initializing moodlamp.
Moodlamp mood(red_pin,green_pin,blue_pin);

void setup(){
  //Setting predefined red color.
  mood.setColor(Moodlamp::COLOR_RED);
}
void loop(){
  //Calling update function.
  mood.update(); 
}


