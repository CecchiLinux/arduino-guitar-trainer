/*
 * This file is part of Arduino-Guitar-Trainer.
 * 
 * Created by Enrico Ceccolini on 09/10/2018.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
    ShiftRegister.cpp
    Purpose: 74HC595 controll class

    @author Enrico Ceccolini
    @version 1.0
*/

#include "ShiftRegister.h"
#include "Arduino.h"

ShiftRegister::ShiftRegister(short latchPin, short clockPin, short dataPin, byte numOfRegisters, byte registerDimension){
  this->latchPin=latchPin;
  this->clockPin=clockPin;
  this->dataPin=dataPin;
  this->numOfRegisters = numOfRegisters;
  this->registerDimension = registerDimension;
  this->registerState = new byte[numOfRegisters];
  for (byte i = 0; i < this->numOfRegisters; i++) {
    registerState[i] = 0;
  }
  pinMode(this->latchPin,OUTPUT);
  pinMode(this->clockPin,OUTPUT);
  pinMode(this->dataPin,OUTPUT);
}

void ShiftRegister::setState(byte* state){
  this->registerState = state;
}

void ShiftRegister::shift(){
  /*
  byte* states = NULL;
  for(byte i = 0; i < this->numOfRegisters; i++){
    states = &this->registerState[i];
  }
  */
  this->refreshShiftRegister();
}

/**
    Resets the led row
*/
void ShiftRegister::reset(){
  this->registerState = new byte[numOfRegisters];
  this->refreshShiftRegister();
};

/**
    Move the new register states on the shift registers.
*/
void ShiftRegister::refreshShiftRegister(){
  digitalWrite(this->latchPin, LOW);
  for(byte i = 0; i < this->numOfRegisters; i++){
    //Get actual states for register
    byte* states = &this->registerState[i];
    shiftOut(this->dataPin, this->clockPin, MSBFIRST, *states);
  }
  digitalWrite(this->latchPin, HIGH);
}

