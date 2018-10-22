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
    ButtonImpl.cpp
    Purpose: Implementation of a button

    @author Enrico Ceccolini
    @version 1.0
*/

#include "ButtonImpl.h"
#include "Arduino.h"

ButtonImpl::ButtonImpl(short pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 

/**
   Return true if the button is pressed, false otherwise
*/  
bool ButtonImpl::isPressed(){
  return digitalRead(pin) == HIGH;
}


