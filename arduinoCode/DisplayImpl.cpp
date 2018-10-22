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
    DisplayImpl.cpp
    Purpose: I2C display controll class

    @author Enrico Ceccolini
    @version 1.0
*/

#include "DisplayImpl.h"

DisplayImpl::DisplayImpl()
{ 
  this->lcd = new LiquidCrystal_I2C(0x27, COL, ROW); 
  this->lcd->init();
  this->lcd->backlight();
}


/**
    Show one string per display row

    @param s1 The first row string
    @param s2 The second row string
*/
void DisplayImpl::show(String s1, String s2){
  this->lcd->clear();
  this->lcd->setCursor(0, 0); // first col of the first row
  this->lcd->print(s1); 
  this->lcd->setCursor(0, 1); // first col of the second row
  this->lcd->print(s2);
}
  
  

