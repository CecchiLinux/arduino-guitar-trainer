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

#ifndef __METRONOMEIMPL__
#define __METRONOMEIMPL__

#include "Arduino.h"
#include "Metronome.h"

#define STEP 20
#define DEFAULT_BPM 60
#define DEFAULT_BPM_C 4
#define MAX_BPM 220
#define MIN_BPM 20
#define MAX_CYCLE 8

class MetronomeImpl: public Metronome{
  private:
    short pin;
    short bpm;
    byte beatsPerCycle;
    byte currentBeatOnCycle = 0;
      
  public:
    MetronomeImpl(short pin);
    void init();
    bool tick();
    void setBeatsPCycle();
    void reset();
    void updateBPM();
    void updateBeatsPCycle();

    short getBPM();
    byte getBeatsPCycle();

};

#endif //__METRONOMEIMPL__

