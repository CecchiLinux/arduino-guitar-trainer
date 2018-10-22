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

/*
 * ChordProgression
 * 
 * Ordered list of chords
 * 
 * example: C major chord progression (Cmaj, Amin, Dmin, G7)
 * 
 */


#ifndef CHORDS_PROGIMPL_H
#define CHORDS_PROGIMPL_H

#define MAX_NUM_CHORDS 4

#include "Arduino.h"
#include "ChordsProg.h"

class ChordsProgImpl: public ChordsProg {
  private:
    String name;
    byte numChords;
    String chords[MAX_NUM_CHORDS];
    byte currentChord;
    
  public:
    ChordsProgImpl();
    ChordsProgImpl(String name);
    
    String getName() { return this->name; }
    void addChord(String cname);
    String getChord(byte cnum) { return this->chords[cnum]; }
    byte getNumChords() { return this->numChords; }
    void setName(String name);
    void reset();
    String getNext();
};

#endif // CHORDS_PROGIMPL_H
