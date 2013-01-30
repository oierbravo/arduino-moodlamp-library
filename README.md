Arduino Moodlamp library
========================
Installation
------------

Like normal arduino libraries.
[More info](http://www.arduino.cc/en/Hacking/Libraries)

Features
--------
- This library uses millis to trigger each update so is non blocking.
- Manual and cycle mode.

###Example: cycle mode
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
	}
	void loop(){
	  //Calling update function.
	  mood.update(); 
	}
###Example: Predefined color

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
##Predefined colors
- Moodlamp::COLOR_RED
- Moodlamp::COLOR_BLUE
- Moodlamp::COLOR_GREEN
- Moodlamp::COLOR_BLACK
- Moodlamp::COLOR_WHITE
- Moodlamp::COLOR_YELLOW
- Moodlamp::COLOR_ORANGE
- Moodlamp::COLOR_PURPLE
- Moodlamp::COLOR_CYAN

##Modes
- Moodlamp::MODE_MANUAL
- Moodlamp::MODE_CYCLE



Autor
-----
[Oier Bravo Urtasun](https://github.com/oierbravo)
