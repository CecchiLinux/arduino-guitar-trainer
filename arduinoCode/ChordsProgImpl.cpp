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
    ChordsProgrImpl.cpp
    Purpose: Represent an ordered list of chords
    Example: C major chord progression is [Cmaj, Amin, Dmin, G7]

    @author Enrico Ceccolini
    @version 1.0
*/
 
#include "ChordsProgImpl.h"


ChordsProgImpl::ChordsProgImpl()
{
  this->name = "";
  this->numChords = 0;
  this->currentChord = 0;
}

ChordsProgImpl::ChordsProgImpl(String name)
{
  this->name = name; 
  this->numChords = 0;
  this->currentChord = 0;
}

/**
    Add a chord to the progression
*/
void ChordsProgImpl::addChord(String cname)
{
  if(this->numChords < MAX_NUM_CHORDS){ 
    this->chords[this->numChords] = cname;
    this->numChords++;
  }
}

void ChordsProgImpl::setName(String name)
{
  this->name = name;
}

/**
    Reset the chord progression simply by reset the number of chords
*/
void ChordsProgImpl::reset()
{
  // this->numChords = 0;
  this->currentChord = 0;
}

String ChordsProgImpl::getNext(){
  String str_chord = this->chords[this->currentChord];
  this->currentChord = (this->currentChord+1)%this->numChords;
  
  return str_chord;
}


