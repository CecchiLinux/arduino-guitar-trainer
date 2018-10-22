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

#ifndef CHORDIMPL_H
#define CHORDIMPL_H

#include "Arduino.h"
#include "Chord.h"
#include "Note.h"

#define MAX_NUM_STRINGS 6

class ChordImpl: public Chord {
  private:
      String name;
      byte numNotes;
      byte tab[MAX_NUM_STRINGS];
      bool tabSet;
  
  public:
      ChordImpl();
      ChordImpl(String  s, byte* tab, byte numNotes);
  
      String getName() const { return this->name; }
      byte* getTab();
      // String* getNotes();
      
      void setName(String s) { this->name = s; };
      void setNumNotes(byte n) { this->numNotes = n; };
      void setTab(byte* t);
      bool isSet() { return this->tabSet; }
      void set(bool s) { this->tabSet = s; }
      
};


#endif // CHORDIMPL_H
