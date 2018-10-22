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

#ifndef DISPLAYIMPL_H
#define DISPLAYIMPL_H

#define COL 16
#define ROW 2

#include "Arduino.h"
#include "Display.h"

#include <LiquidCrystal_I2C.h>

class DisplayImpl: public Display {
  private:
    LiquidCrystal_I2C* lcd;
    
  public:
    DisplayImpl();
    void show(String s1, String s2);
    
};

#endif // DISPLAYIMPL_H

