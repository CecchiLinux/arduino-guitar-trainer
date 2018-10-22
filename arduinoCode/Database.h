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

#ifndef DATABASE_H
#define DATABASE_H

#include "Arduino.h"
#include "InstrumentImpl.h"
#include "Note.h"
#include "ChordImpl.h"
#include "ChordsProgImpl.h"
#include "ScaleImpl.h"

#define NUM_NOTES 7
#define NUM_CHORDS_TYPES 6
#define NUM_CP 7
#define NUM_SCALES_TYPES 6

class Database
{
  private:
    String notes[NUM_NOTES] = {"A", "B", "C", "D", "E", "F", "G"};

    String chords_types[NUM_CHORDS_TYPES] = {"maj", "min", "7", "#maj", "#min", "#7"};

    // String harmonic_progressions[NUM_CP] = {"A", "B", "C", "D", "E", "F", "G"};

    String scale_types[NUM_SCALES_TYPES] = {"wu1", "wu2", "wu3", "Maj", "Nat. Min", "Pent. Min"};
    
    // String warm_ups[NUM_WU_P] = {"1"};
    
  public:
    Database();
    bool getChord(ChordImpl* c, String inst, String str_chord);
    void getChordsProg(ChordsProgImpl* hp, String str_chords_prog);
    void getChordByNum(ChordImpl* c, String inst, byte note, byte type);
    bool getScale(ScaleImpl* sc, String str_inst, String str_tone, String str_type);

    /*
    String* getNotes() { return this->notes; }
    String* getChordProgressions() { return this->notes; }
    String* getWarmUps() { return this->notes; }
    String* getChordsTypes() { return this->chords_types; }
    String* getScalesTypes() { return this->scale_types; }
    String* getWarmUpsTypes() { return this->warm_ups; }
    */

    byte getNNotes() { return NUM_NOTES; }
    byte getNChordsProg() { return NUM_CP; }
    byte getNChordsTypes() { return NUM_CHORDS_TYPES; }
    byte getNScalesTypes() { return NUM_SCALES_TYPES; }

    String getNote(byte n) { return this->notes[n]; }
    String getChordsProg(byte n) { return this->notes[n]; }
    String getChordType(byte n) { return this->chords_types[n]; }
    String getScaleType(byte n) { return this->scale_types[n]; }
    
    String getStateString(byte state);
};

#endif
