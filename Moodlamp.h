/*
  Moodlamp.h - Moodlamp library
  Copyright (C) 2013 Oier Bravo Urtasun.  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef Moodlamp_h
#define Moodlamp_h

#include "Arduino.h"
class Moodlamp
	{
	  public:
	    //Mode enums for easy calling.
	    enum Mode { MODE_MANUAL, MODE_CYCLE };
		//-- Color definition, initialized in the cpp file.
		static int COLOR_RED[3];
		static int COLOR_GREEN[3];
		static int COLOR_BLUE[3];
		static int COLOR_WHITE[3];
		static int COLOR_BLACK[3];

		static int COLOR_ORANGE[3];
		static int COLOR_YELLOW[3];
		static int COLOR_CYAN[3];
		static int COLOR_PURPLE[3];
		//Constructor and basic functions.
	    Moodlamp();
		Moodlamp(int redPin,int greenPin,int bluePin);
		
		void setColor(int* color);
		void setColor(const int* color);
		void update();
		void update(long now);
		void setUpdateTime(long time);
		long getUpdateTime() const { return _updateTime; };
		void setMode(Mode mode);
		Mode getMode() const { return _mode; };
		void setCycleUpdateTime(long time);
		long getCycleUpdateTime() const { return _cycleUpdateTime; };
		void setRed(int value);
		void setGreen(int value);
		void setBlue(int value);
		void setRGB(int red,int green, int blue);
		
	  private:
		int _redPin;
		int _greenPin;
		int _bluePin;
		int pinMapping[3];
		
		//Mode holder
		Mode _mode;
		//Last update holder.
		long _lastUpdate;
		//Millis between each led update.
		long _updateTime;
		
		//Holder for current led values.
		int _currentValues[3];
		//Holder for ending values. Used for fading effect.
		int _finalValues[3];
		//Holder for steps to be done in the current step.
		//This changes when setting a new color or reaches final values.
		int _updateAmount[3];
		//Amount to add or substract on each update
		int _updateStep;
		
		//Cycle mode
		//Holder for last cycle color update.
		long _cycleLastUpdate;
		//Millis between each cycle update.
		long _cycleUpdateTime;
		//Holder for current index in the color sequence.
		int _currentCycleIndex;
		void _cycleUpdate();
		
		void _updateLed();
		int* _getFinalColor();
	};
#endif