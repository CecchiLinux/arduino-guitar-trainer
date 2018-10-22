/*
 * This file is part of Arduino-Guitar-Training.
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

#ifndef INSTRUMENTIMPL_H
#define INSTRUMENTIMPL_H

#define NUM_OF_REGISTERS 6
#define REGISTERS_DIMENSION 8

#include "Arduino.h"
#include "Instrument.h"
#include "ScaleImpl.h"
#include "ShiftRegister.h"
#include "Note.h"
#include "Chord.h"

class InstrumentImpl: public Instrument {

  private:
      String name;
      
      //NECK
      //short* tuning; // RELATIVE PITCH, NOT ABSOLUTE
      byte tuning[NUM_OF_REGISTERS];
      byte numStrings;
      byte numFrets;
  
      byte* register1State;
      // byte* register2State;
      byte* states;
      ShiftRegister* shiftReg1;
      // ShiftRegister* shiftReg2;
      // Note* currentNote;
  
  public:
      InstrumentImpl();
      InstrumentImpl(String name, byte numStrings, byte *tune, ShiftRegister* shiftReg1);
  
      String getName() const { return this->name; }

      //NECK
      byte* getTuning();
      byte getNumStrings();
      byte getNumFrets();
  
      void clearNeck();
      bool show_chord(Chord* c);
      bool show_note(byte string, byte fret, bool set);
      void show_scale(ScaleImpl* scale);
      String play_scale(ScaleImpl* scale);
      String obtainNote(byte string, byte fret);

      // void test_leds();
  };

#endif // INSTRUMENTIMPL_H
