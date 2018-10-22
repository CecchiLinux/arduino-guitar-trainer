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
    Instrument.cpp
    Purpose: Represent a stringhed musica instrument

    @author Enrico Ceccolini
    @version 1.0
*/

#include "InstrumentImpl.h"

InstrumentImpl::InstrumentImpl()
{
    this->name = "";

    this->numStrings = 0;
    this->register1State = new byte[NUM_OF_REGISTERS];
    // this->register2State = new byte[NUM_OF_REGISTERS];

    // this->currentNote = new Note();
}

InstrumentImpl::InstrumentImpl(String name, byte numStrings, byte* tune, ShiftRegister* shiftReg1)
{
    this->name = name;
    // this->tuning = new short[numStrings];
    
    for(byte i = 0; i < numStrings; i++){
      this->tuning[i] = tune[i];
    }

    this->numStrings = numStrings;
    this->register1State = new byte[NUM_OF_REGISTERS];
    // this->register2State = new byte[NUM_OF_REGISTERS];
    this->shiftReg1 = shiftReg1;
    // this->shiftReg2 = shiftReg2;
}

byte InstrumentImpl::getNumStrings() 
{ 
  return this->numStrings; 
}

byte InstrumentImpl::getNumFrets()
{ 
  return this->numFrets; 
}


byte* InstrumentImpl::getTuning()
{ 
  return this->tuning;
}

/**
    Show a chord on the guitar neck.

    @param str_tab The tab to play (like "x:0:2:2:2:0").
    @return True if the instrument can perform the chord, false otherwise.
*/
bool InstrumentImpl::show_chord(Chord* c)
{
  byte fret = 0;
  states = NULL;
  byte* tab = c->getTab(); 
  
  for (byte i = 0; i < NUM_OF_REGISTERS; i++) {
    this->register1State[i] = 0;
    // this->register2State[i] = 0;
  }

  for(byte i = 0; i < NUM_OF_REGISTERS; i++){
    if(tab[i] != 99){
      fret = tab[i];
      if(fret < REGISTERS_DIMENSION){
        states = &register1State[NUM_OF_REGISTERS-i-1];
      }else{
        fret -= REGISTERS_DIMENSION;
        // states = &register2State[NUM_OF_REGISTERS-i-1];
      }
      bitSet(*states, fret);
    }     
  }
  
  this->shiftReg1->setState(register1State);
  this->shiftReg1->shift();

  return true; //TODO verifica possibilità
}
 
/**
    Play a scale on the guitar neck.

    @param scale The scale to play.
    @return The played note name.
*/
String InstrumentImpl::play_scale(ScaleImpl* scale)
{
  short stringAndFret[2];
  bool end = scale->getNext(stringAndFret);
  
  if(end){
    show_scale(scale);
  }
  show_note(stringAndFret[0], stringAndFret[1], false);
  return this->obtainNote(stringAndFret[0], stringAndFret[1]);
}

String InstrumentImpl::obtainNote(byte string, byte fret)
{
    Note n;
    n.set(this->tuning[string-1], fret);
    return n.getName();
}

/**
    Show or clear a note on the neck.

    @param string The string number.
    @param fret The fret number.
    @param set Show or clear the note on the neck.
    @return True if the instrument can perform the note, false otherwise.
*/
bool InstrumentImpl::show_note(byte string, byte fret, bool set)
{
  if(fret < REGISTERS_DIMENSION){
    states = &register1State[string-1];
  }else{
    fret -= REGISTERS_DIMENSION;
    // states = &register2State[NUM_OF_REGISTERS-i-1];
  }
  if(set){
    bitSet(*states, fret);
  }else{
    bitClear(*states, fret);
  }
  
  this->shiftReg1->setState(register1State);
  this->shiftReg1->shift();

  return true; //TODO verifica possibilità
}

/**
    Show a scale on the guitar neck.

    @param scale The scale to performe.
*/
void InstrumentImpl::show_scale(ScaleImpl* scale)
{

  short* fingering;
  byte* notePerString = scale->getNotePerString();

  for(byte i=0; i<6; i++){
    fingering = scale->getFingering(i);
    for(byte j=0; j<notePerString[i]; j++){
       show_note(i+1, fingering[j], true);
    }
  }
  /*
  short stringAndFret[2];
  //DEBUG
  // scale->printFingering();
  //END DEBUG
  
  bool end = scale->getNext(stringAndFret);

  while(!end){
    show_note(stringAndFret[0], stringAndFret[1], true);
    end = scale->getNext(stringAndFret);  
  }
  */
}

/*
 * clear all the shift registers, shut down all the leds
 */
void InstrumentImpl::clearNeck()
{
  byte fret = 0;

  for(byte i = 0; i < NUM_OF_REGISTERS; i++){
    for(byte j = 0; j < REGISTERS_DIMENSION; j++){
      this->register1State[i] = 0;
      //this->register2State[i] = 0;
      this->shiftReg1->setState(register1State);
      this->shiftReg1->shift();
    }     
  }    
}

/*
void Instrument::test_leds() {
    
    byte* register1State = new byte[NUM_OF_REGISTERS];
    byte* register2State = new byte[NUM_OF_REGISTERS];
    for (short i = 0; i < NUM_OF_REGISTERS; i++) {
      register1State[i] = 0;
      register2State[i] = 0;
    }
    short fret = 0;
    byte* states = NULL;
    for(short i = 0; i < 6; i++){
      for(short j = 0; j < 8; j++){
        fret = j;
        states = &register1State[i];
        bitSet(*states, fret);
        this->shiftReg1->setState(register1State);
        this->shiftReg1->shift();
        delay(100);
        register1State[i] = 0;
        this->shiftReg1->setState(register1State);
        this->shiftReg1->shift();
      }     
    }    
}
*/


