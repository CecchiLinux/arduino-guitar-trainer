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

#ifndef SCALEIMPL_H
#define SCALEIMPL_H

#include "Arduino.h"
#include "Scale.h"

#define MAX_NUM_STRINGS 6
#define MAX_NUM_NOTES 4

class ScaleImpl: public Scale {

  private:
    String tone;
    String type;
    short tonic;

    byte currentString;
    byte currentNote;
    short fingering[MAX_NUM_STRINGS][MAX_NUM_NOTES];
    byte notePerString[MAX_NUM_STRINGS];
    bool up = true;

    
  public:
    ScaleImpl();
    void setString(byte string, byte nPerString, short f1, short f2, short f3, short f4);
    void reset();

    bool getNext(short* stringAndFret);
    String getTone() { return this->tone; }
    String getType() { return this->type; }
    short getTonic() { return this->tonic; }
    void setTone(String tone) { this->tone = tone; }
    void setType(String type) { this->type = type; }
    void setTonic(short tonic) { this->tonic = tonic; }
    short* getFingering(byte string) { return this->fingering[string]; }
    byte* getNotePerString() { return this->notePerString; }
    bool checkOverFret(byte numFrets);

    //DEBUG
    // void printFingering();
  
};

#endif // SCALEIMPL_H
