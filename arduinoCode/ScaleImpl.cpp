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
    ScaleImpl.cpp
    Purpose: Represent a guitar scale.

    @author Enrico Ceccolini
    @version 1.0
*/

#include "ScaleImpl.h"

ScaleImpl::ScaleImpl()
{
  this->currentString = MAX_NUM_STRINGS;
  this->currentNote = 0;
}

/*
void Scale::printFingering(){
  for(byte i=0; i<6; i++){
    for(byte j=0; j<this->notePerString[i]; j++){
      Serial.print(this->fingering[i][j]);
    }
    Serial.println();
  }
}
*/

/**
    When a scale is performed, return the next string and fret to be played.
    It goes up and down the scale, initialy up: from the quite to loud.
    

    @return True if the next note is the last.
*/
bool ScaleImpl::getNext(short* stringAndFret)
{
  bool end = false;
  switch(this->up){
    case true:
      if(this->currentNote == this->notePerString[this->currentString-1]){
        this->currentNote=0;
        this->currentString--;
        if(this->currentString == 0){
          this->up = false;
          end = true;
        }   
      }
    break;
    case false:
      if(this->currentNote == this->notePerString[this->currentString]){
        this->currentNote=0;
        this->currentString++;
        if(this->currentString == MAX_NUM_STRINGS){
          this->up = true;
          end = true;
        }   
      }
    break;
  } 

  switch(this->up){
    case true:
      stringAndFret[0] = this->currentString;
      stringAndFret[1] = this->fingering[this->currentString-1][this->currentNote];
      this->currentNote++;
    break;
    case false:
      stringAndFret[0] = this->currentString+1;
      stringAndFret[1] = this->fingering[this->currentString][this->notePerString[this->currentString]-this->currentNote-1];
      this->currentNote++;
    break;
  }
  return end;
}

void ScaleImpl::setString(byte string, byte nPerString, short f1, short f2, short f3, short f4)
{
  this->notePerString[string-1] = nPerString; 
  this->fingering[string-1][0] = this->tonic + f1;
  this->fingering[string-1][1] = this->tonic + f2;
  this->fingering[string-1][2] = this->tonic + f3;
  this->fingering[string-1][3] = this->tonic + f4;
}

void ScaleImpl::reset(){
  this->currentNote=0;
  this->currentString=MAX_NUM_STRINGS;  
  this->up = true;   
}

bool ScaleImpl::checkOverFret(byte numFrets){
  bool error = false;
  for(byte i=0; i<MAX_NUM_STRINGS; i++){
    for(byte j=0; j<notePerString[i]; j++){
       if(this->fingering[i][j] < 0 || this->fingering[i][j] > numFrets){
        error = true;
       }
    }
  }
  return error;
}

