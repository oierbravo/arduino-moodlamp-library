/*
  Moodlamp.h - Moodlamp library
  Copyright (C) 2013 Oier Bravo Urtasun.  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include "Arduino.h"
#include "Moodlamp.h"

/*! \brief Constructor
 \param redPin		Arduino pin for red led
 \param greenPin	Arduino pin for green led
 \param bluePin		Arduino pin for blue led
  */
Moodlamp::Moodlamp(int redPin,int greenPin,int bluePin)
{
  
  pinMode(redPin, OUTPUT);
  _redPin = redPin;
  
  pinMode(greenPin, OUTPUT);
  _greenPin = greenPin;
  
  pinMode(bluePin, OUTPUT);
  _bluePin = bluePin;
  
  //We put pins in an array for easy use.
  pinMapping[0] = _redPin;
  pinMapping[1] = _greenPin;
  pinMapping[2] = _bluePin;
  
  //Default values.
  _updateTime = 10;
  _mode = MODE_MANUAL;
  _updateStep = 1;
  
  //Cycle mode.
  _cycleUpdateTime = 5000;
  _currentCycleIndex = 0;
}
/*
/ PREDEFINED COLORS
*/
int Moodlamp::COLOR_RED[3] = {255,0,0};
int Moodlamp::COLOR_GREEN[3] = {0,255,0};
int Moodlamp::COLOR_BLUE[3] = {0,0,255};
int Moodlamp::COLOR_WHITE[3] = {255,255,255};
int Moodlamp::COLOR_BLACK[3] = {0,0,0};

int Moodlamp::COLOR_ORANGE[3] = {255,120,0};
int Moodlamp::COLOR_YELLOW[3] = {255,255,0};
int Moodlamp::COLOR_CYAN[3] = {0,255,255};
int Moodlamp::COLOR_PURPLE[3] = {255,0,255};

/*! \brief Set a new color.
 \param color		Array of 3 colors
*/
void Moodlamp::setColor(int* color)
{
  //Iterating over the 3 colors
  for(int i = 0;i<3;i++){
	//Setting finale value.
    _finalValues[i] = color[i];
	//Comparing finale value with current to set up direction.
    if(_finalValues[i] > _currentValues[i]){
	   //Final value bigger so positibe step.
       _updateAmount[i] = _updateStep;
    } else if(_finalValues[i] < _currentValues[i]){
      //Final value smaller so negative step.
	  _updateAmount[i] = -_updateStep;
    } else if(_finalValues[i] == _currentValues[i]){
	  //Final equal so positibe no step.
      _updateAmount[i] = 0;
    }
  }
  }
/*! \brief Data updater function. Call this as quick as posible.
 */
void Moodlamp::update(){
	long now = millis();
	update(now);
}
/*! \brief Data updater function. Call this as quick as posible.

	\param now	Time in millis. Optional.Default millis()
 */
void Moodlamp::update(long now){
   //Comparing time with last update
   if((now - _lastUpdate) >= _updateTime){
	  //Iterating over the 3 leds
	  for (int i = 0;i<3;i++){
	    //Applyng each step to the current values.
		_currentValues[i] += _updateAmount[i];
		//If reaches final value then set update amount to zero.
		if(_currentValues[i] == _finalValues[i]){
		  _updateAmount[i] = 0;
		}
	  }
	 //Sending data to leds.
	 _updateLed();
	 //Holding the current time as last update.
	  _lastUpdate = now;
  }
  
  // Cycle MODE
	if(_mode == MODE_CYCLE){
	  if((now - _cycleLastUpdate) >= _cycleUpdateTime){      
		_cycleUpdate();

	  }
	}
}
/*! \brief Sets update time between steps.

	\param time	Time in millis.
 */
void Moodlamp::setUpdateTime(long time){
	_updateTime = time;
}

/*! \brief Sets mode.

	\param mode	Moodlamp mode from Moodlamp::MODE
 */
void Moodlamp::setMode(Mode mode){
	_mode = mode;
}
/*! \brief Sets update time between cycle steps.

	\param time	Time in millis.
 */
void Moodlamp::setCycleUpdateTime(long time){
	_cycleUpdateTime = time;
}

/*! \brief Sets red color amount. Doesn't affect other colors.

	\param value  Amount to set.
 */
void Moodlamp::setRed(int value){
   int* color = _getFinalColor();
   color[0] = value;
   setColor(color);
}

/*! \brief Sets green color amount. Doesn't affect other colors.

	\param value  Amount to set.
 */
void Moodlamp::setGreen(int value){
   int* color = _getFinalColor();
   color[1] = value;
   setColor(color);
}

/*! \brief Sets blue color amount. Doesn't affect other colors.

	\param value  Amount to set.
 */
void Moodlamp::setBlue(int value){
   int* color = _getFinalColor();
   color[2] = value;
   setColor(color);
}

/*! \brief Sets red,green and blue color amount. 

	\param red  Red amount to set.
	\param green  Green amount to set.
	\param blue  Blue amount to set.
 */
void Moodlamp::setRGB(int red,int green, int blue){
   int color[3] = {red,green,blue};
   setColor(color);
}
/*! \brief Cycle updater function, changes and sets a color from the sequence.
 */
void Moodlamp::_cycleUpdate(){
//Number of colors.
  int sequence_num_colors = 9;
   //Color sequence.
  int* cycleSequence[9] = {COLOR_RED,COLOR_GREEN,COLOR_BLUE,COLOR_WHITE,COLOR_YELLOW,COLOR_PURPLE,COLOR_ORANGE,COLOR_CYAN,COLOR_WHITE}; 

  setColor( cycleSequence[_currentCycleIndex] );
  _currentCycleIndex++;
  if(_currentCycleIndex == sequence_num_colors){
    _currentCycleIndex = 0;
  }
  _cycleLastUpdate = millis();

}


/*! \brief Sends data to leds

	\param mode	Moodlamp mode from Moodlamp::MODE
 */
void Moodlamp::_updateLed()
{
  //Iterating over the 3 leds.
  for (int i = 0;i<3;i++){
    analogWrite(pinMapping[i], _currentValues[i]);
  }
}

int* Moodlamp::_getFinalColor()
{
  int color[] = {0,0,0};
  for(int i = 0;i<3;i++){
    color[i] = _finalValues[i];
  }
  return color;
}