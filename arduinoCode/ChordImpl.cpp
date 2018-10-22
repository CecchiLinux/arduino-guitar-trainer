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
    ChordImpl.cpp
    Purpose: Represent a guitar chord

    @author Enrico Ceccolini
    @version 1.0
*/

#include "ChordImpl.h"

ChordImpl::ChordImpl()
{
    this->name = "";
    this->numNotes = 0;
    this->tabSet = false;
}

ChordImpl::ChordImpl(String name, byte* tab, byte numNotes)
{
    this->name = name;
    this->numNotes = numNotes;
    for(byte i=0; i<MAX_NUM_STRINGS; i++){
      this->tab[i] = tab[i];
    }
    this->tabSet = true;
}

/*
Note* ChordImpl::obtainNotes()
{
    Note temp;
    Note *notes = new Note[this->instrument->getNumStrings()];
    byte *tune = this->instrument->getTuning();
    
    for (byte i=0; i<this->instrument->getNumStrings(); i++)
    {
        if (tab[i] == -1){
            temp.invalidate();
        }else{
          temp.set(tune[i], capo, tab[i]);
        }
        notes[i] = temp;
    }
    return notes;
}
*/

void ChordImpl::setTab(byte* t){
  for(byte i=0; i<MAX_NUM_STRINGS; i++){
    this->tab[i] = t[i];
  }
  this->tabSet = true;
}

byte* ChordImpl::getTab(){
  return this->tab;
}

/*
String* ChordImpl::getNotes(){
  String* n = new String[this->instrument->getNumStrings()];
  Note *notes = this->obtainNotes();
  for(byte i; i<this->instrument->getNumStrings(); i++){
    n[i] = notes[i].getName();
  }
  return n;
}
*/


