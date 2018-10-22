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
    MetronomeImpl.cpp
    Purpose: Imlementation of a metronome

    @author Enrico Ceccolini
    @version 1.0
*/
#include "MetronomeImpl.h"

MetronomeImpl::MetronomeImpl(short pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->bps = DEFAULT_BPS;
  this->beatsPerCycle = DEFAULT_BPS_C;
}

void MetronomeImpl::init()
{
  TaskPeriod::init(60000 / this->bps);  //60000 ms in a s
}

/**
    Play the metronome sound.
    The sound is different if the beat is the first of the cycle.

    @return True if the beat is the first on the cycle.
*/
bool MetronomeImpl::tick()
{
  this->currentBeatOnCycle = (this->currentBeatOnCycle+1)%this->beatsPerCycle;
  if(this->currentBeatOnCycle == 1){ //the first on the cycle
    tone(this->pin, 3000, 200);
    return true;
  }
  tone(this->pin, 2000, 200);
  return false;
}

/**
    Add a STEP at the metronome bps period up to the maximum.
*/
void MetronomeImpl::updateBPS()
{
  this->bps = (this->bps+STEP)%(MAX_BPS+STEP);
  if(this->bps == 0)
    this->bps = MIN_BPS;
}

/**
    Add a beat per cycle up to the maximum.
*/
void MetronomeImpl::updateBeatsPCycle()
{
  this->beatsPerCycle = (this->beatsPerCycle+1)%(MAX_CYCLE+1);
  if(this->beatsPerCycle == 0)
    this->beatsPerCycle = 1;
}

short MetronomeImpl::getBPS()
{
  return this->bps;
}

byte MetronomeImpl::getBeatsPCycle()
{
  return this->beatsPerCycle;
}


void MetronomeImpl::reset()
{
  this->currentBeatOnCycle = 0;
  this->bps = DEFAULT_BPS;
  this->beatsPerCycle = DEFAULT_BPS_C;
}


