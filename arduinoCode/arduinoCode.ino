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
    arduino-guitar-trainer.ino
    Purpose: guide to the beginner student in the metronome approach

    @author Enrico Ceccolini
    @version 1.0
*/
 
#include "InstrumentImpl.h"
#include "ChordImpl.h"
#include "ChordsProgImpl.h"
#include "Database.h"
#include "ButtonImpl.h"
#include "DisplayImpl.h"
#include "Timer.h"
#include "MetronomeImpl.h"
#include "ScaleImpl.h"
#include "avr/io.h"
#include "avr/wdt.h"

#define BASE_PERIOD 100  // clock tick period
#define DEBOUNCE_DELAY 220 // the debounce time

// 74HC595
#define DATA_PIN 11
#define LATCH_PIN 8
#define CLOCK_PIN 12
#define NUM_OF_REGISTERS 6 // num of 74HC595 in series
#define REGISTERS_DIMENSION 8 // 74HC595 bits

#define METRONOME_PIN 7

#define BUTTON_G_PIN A2 // green (select) button's pin
#define BUTTON_R_PIN A1 // red (back) button's pin
#define BUTTON_Y_PIN A0 // yellow (change selection) button's pin

#define NOTES 6

#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {} 

// program states and substate
enum{START, ES_SELECTION, TONE_SELECTION, TYPE_SELECTION, VISUALIZE, METRONOME, PLAY} state;
enum{CHORDS, CP, SCALES, WARM_UP} esState;
enum{BEATS, CYCLE} stateMetronome;

Timer timer;
// I2C display
DisplayImpl* my_display;

//tasks handling buttons
ButtonImpl buttonG(BUTTON_G_PIN);
ButtonImpl buttonR(BUTTON_R_PIN);
ButtonImpl buttonY(BUTTON_Y_PIN);

ShiftRegister shiftReg1(LATCH_PIN, CLOCK_PIN, DATA_PIN, NUM_OF_REGISTERS, REGISTERS_DIMENSION);
// ShiftRegister shiftReg2(LATCH_PIN_2, CLOCK_PIN_2, DATA_PIN_2, NUM_OF_REGISTERS, REGISTERS_DIMENSION);

MetronomeImpl metronome(METRONOME_PIN);

// contains all the data: chords, chord progressions, scales, notes...
Database db;

// representation of a stringed musical instrument with frets
InstrumentImpl* my_instrument;

//
ChordImpl* currentChord;
ChordsProgImpl* currentChordsProg;
ScaleImpl* currentScale;
String currentNote = "";

// Menu variables, lists and indices
byte nState1List = 0;
byte iState1List = 0;

byte nState2List = 0;
byte iState2List = 0;

bool justEntered;
long lastDebounceTime;  // the last time the output pin was toggled

//DEBUG
long lastTime;
// bool* chordsTypes;
//end DEBUG

void setup() {
  Serial.begin(9600);
  timer.setupPeriod(BASE_PERIOD);  //timer's period is set to 50ms
  
  // set the default states and substate
  state = START;
  esState = CHORDS;
  stateMetronome = BEATS;
  
  my_display = new DisplayImpl();
  // creates a guitar with the classic tune EADGBE
  byte tuning[] = {4, 9, 2, 7, 11, 4};
  my_instrument = new InstrumentImpl("EADGBE", 6, tuning, &shiftReg1);
  // my_instrument->test_leds();
  
  currentChord = new ChordImpl();
  // iState1List = 0;
  // iState2List = 0;
  justEntered = true;
  lastDebounceTime = 0; 
  }

/*
 * 
 */
void loop() { 
  /* wait for timer signal */
  timer.waitForNextTick();
  
  lastTime = millis();
  step();
  Serial.println(millis() - lastTime);
  
}

/*
 * Simulate a state machine
 * 
 * START
 *  \ + ES_SELECTION
 *    | - CHORDS
 *    | - CHORD PROGRESSION
 *    | - WARM UP
 *        \ + TONE_SELECTION
 *          | - A, B, C, D, E, F, G
 *              \ + TYPE_SELECTION
 *                | - maj, min, dom7, #maj, #min, #dom7
 *                | - A, B, C, D, E, F, G 
 *                | - Maj, Nat. Min, Pent. Min
 *                    \ + VISUALIZE
 *                      \ + METRONOME
 *                        | - SELECT BPM
 *                          | - 20, 40, 60, 80, 120, 160, 180, 200, 220
 *                        | - SELECT BEATS PER CYCLE
 *                          | - 1, 2, 3, 4, 5, 6, 7, 8  
 *                          \ + PLAY
 */
void step() {
  switch (state) {
    /*------------------------ 1. START ------------------------------------------*/  
    case START:
      if(isJustEntered()){
        my_instrument->clearNeck();
        my_display->show("Hi!", "press Green");
      }
      if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
        justEntered = true;
        state = ES_SELECTION;
        // DEBUG
        Serial.println(freeMemory());
        //
      }
    break;
    /*------------------------ 2. ES_SELECTION --------------------------------*/
    case ES_SELECTION:
      switch(esState){
        /*------------------------2. ES_SELECTION / CHORDS ----------------------*/     
        case CHORDS:
          if(isJustEntered()){
            my_display->show(db.getStateString(ES_SELECTION), "Chords");
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = TONE_SELECTION;   
            nState1List = db.getNNotes();          
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            esState = CP;
            justEntered = true;
          }
        break;
        /*------------------------2. ES_SELECTION / CP --------------------------*/
        case CP:
          if(isJustEntered()){
            my_display->show(db.getStateString(ES_SELECTION), "Chord Prog.");
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = TONE_SELECTION;
            nState1List = db.getNChordsProg();           
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            esState = SCALES;
          }
        break;
        /*------------------------2. ES_SELECTION / SCALES ----------------------*/
        case SCALES:
          if(isJustEntered()){
            my_display->show(db.getStateString(ES_SELECTION), "Scales");
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            nState1List = db.getNNotes();
            state = TONE_SELECTION;
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            esState = CHORDS;
          }
        break;
      }
      if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
        justEntered = true;
        state = START;
        esState = CHORDS;
      }
    break;
    /*------------------------3. TONE_SELECTION ---------------------------------*/
    case TONE_SELECTION:
      switch(esState){
        /*------------------------ 3. TONE_SELECTION / CHORDS -------------------*/
        case CHORDS:
          if(isJustEntered()){        
            my_display->show(db.getStateString(TONE_SELECTION), db.getNote(iState1List));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = TYPE_SELECTION;
            nState2List = db.getNChordsTypes();
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState1List = (iState1List+1)%(nState1List);
          }
        break;
        /*------------------------ 3. TONE_SELECTION / CP -----------------------*/
        case CP:
          if(isJustEntered()){          
            my_display->show(db.getStateString(TONE_SELECTION), db.getNote(iState1List));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = VISUALIZE;
            currentChordsProg = new ChordsProgImpl();

            // DEBUG
            Serial.println(freeMemory());
            //

            db.getChordsProg(currentChordsProg, db.getNote(iState1List));
            nState2List = currentChordsProg->getNumChords();
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState1List = (iState1List+1)%(nState1List);
          }
        break;
        /*------------------------ 3. TONE_SELECTION / SCALES --------------------------*/
        case SCALES:
          if(isJustEntered()){          
            my_display->show(db.getStateString(TONE_SELECTION), db.getNote(iState1List));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;          
            state = TYPE_SELECTION;
            nState2List = db.getNScalesTypes();
            currentScale = new ScaleImpl();
            
            // DEBUG
            Serial.println(freeMemory());
            //
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState1List = (iState1List+1)%(nState1List);
          }
        break;
      }
      if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
        justEntered = true;
        state = ES_SELECTION;
        iState1List = 0;
      }
    break;
    /*------------------------4. TYPE_SELECTION ---------------------------------*/    
    case TYPE_SELECTION:
      switch(esState){
        /*------------------------4. TYPE_SELECTION / CHORDS --------------------*/
        case CHORDS:
          if(isJustEntered()){
            my_display->show(db.getStateString(TYPE_SELECTION), db.getChordType(iState2List));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            db.getChordByNum(currentChord, my_instrument->getName(), iState1List, iState2List);
            state = VISUALIZE;
          }      
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState2List = (iState2List+1)%(nState2List);
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = TONE_SELECTION;
            iState2List = 0;
          }
        break;
        /*------------------------4. TYPE_SELECTION / SCALES --------------------*/
        case SCALES:
          if(isJustEntered()){
            my_display->show(db.getStateString(TYPE_SELECTION), db.getScaleType(iState2List));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            bool error = db.getScale(currentScale, my_instrument->getName(), db.getNote(iState1List), db.getScaleType(iState2List));
            if(!error){
              state = VISUALIZE;
            }
          }      
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState2List = (iState2List+1)%(nState2List);
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = TONE_SELECTION;
            iState2List = 0;
            // DEBUG
            Serial.print(freeMemory());
            Serial.print(":");
            //
            delete currentScale;
            // DEBUG
            Serial.println(freeMemory());
            //
          }
        break;
      }
    break;
    /*------------------------5. VISUALIZE ---------------------------------*/ 
    case VISUALIZE:
      switch(esState){
        /*------------------------5. VISUALIZE / CHORDS --------------------*/
        case CHORDS:
          if(isJustEntered()){
            if(currentChord->isSet()){
              my_display->show(db.getStateString(VISUALIZE), currentChord->getName());
              my_instrument->clearNeck();
              my_instrument->show_chord(currentChord);
            }else{
              my_display->show("can't"," "); // chord absent on database
            }
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = METRONOME;
            db.getChordByNum(currentChord, my_instrument->getName(), iState1List, iState2List);
          } 
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = TYPE_SELECTION;
          }
        break;
        /*------------------------5. VISUALIZE / CP -------------------------*/
        case CP:           
          if(isJustEntered()){
            db.getChord(currentChord, my_instrument->getName(), currentChordsProg->getChord(iState2List));
            // db.getChord(currentChord, my_instrument->getName(), currentChordsProg->getNext());
            my_display->show(db.getStateString(VISUALIZE), currentChord->getName());
            my_instrument->clearNeck();
            my_instrument->show_chord(currentChord);
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            iState2List = (iState2List+1)%(nState2List);
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = METRONOME;
            iState2List = 0;
            currentChordsProg->reset();
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = TONE_SELECTION;
            iState2List = 0;
            // DEBUG
            Serial.print(freeMemory());
            Serial.print(":");
            //
            delete currentChordsProg;
            // DEBUG
            Serial.println(freeMemory());
            //
            my_instrument->clearNeck();
          }
        break;
        /*------------------------5. VISUALIZE / SCALES --------------------*/
        case SCALES:
          if(isJustEntered()){
            my_display->show(db.getStateString(VISUALIZE), currentScale->getTone() + " " + currentScale->getType());
            my_instrument->clearNeck();
            my_instrument->show_scale(currentScale);
            currentScale->reset();
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            state = METRONOME;
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = TYPE_SELECTION;
            my_instrument->clearNeck();
          }
        break;
      }
      if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
        justEntered = true;
        state = TYPE_SELECTION;
        my_instrument->clearNeck();
      }
    break;
    /*------------------------ 6. METRONOME ---------------------------------*/ 
    case METRONOME:
      switch(stateMetronome){
        /*------------------------ 6. METRONOME / BEATS ---------------------*/
        case BEATS:
          if(isJustEntered()){
            my_display->show(db.getStateString(METRONOME) + " BPM", String(metronome.getBPM()));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            stateMetronome = CYCLE;
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            metronome.updateBPM();
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = VISUALIZE;
          }
        break;
        /*------------------------ 6. METRONOME / CYCLE ---------.------------*/
        case CYCLE:
          if(isJustEntered()){
            my_display->show(db.getStateString(METRONOME) + " cycle", String(metronome.getBeatsPCycle()));
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (SELECT)
            justEntered = true;
            metronome.init(); 
            state = PLAY;
            stateMetronome = BEATS;
          }
          if(buttonY.isPressed() && my_debounce()){     // Yellow button pressed (CHANGE)
            justEntered = true;
            metronome.updateBeatsPCycle();
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            stateMetronome = BEATS;
          }
        break;
      }
    break;
    /*------------------------7. PLAY ----------------------------------------*/ 
    case PLAY:
      switch(esState){
        /*------------------------7. PLAY / CHORDS----------------------------------------*/
        case CHORDS:
          if(isJustEntered()){
            my_display->show(db.getStateString(PLAY) + String(metronome.getBPM()), currentChord->getName());
          }
          if (metronome.updateAndCheckTime(BASE_PERIOD)) {
            metronome.tick();
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = METRONOME;
            metronome.reset();
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (BACK)
            Reset_AVR();
          }
        break;
        /*------------------------7. PLAY / CP --------------------------------*/
        case CP:
          if(isJustEntered()){
            my_display->show(db.getStateString(PLAY) + String(metronome.getBPM()), "");
          }
          if (metronome.updateAndCheckTime(BASE_PERIOD)) {
            // db.getChord(currentChord, my_instrument->getName(), currentChordsProg->getChord(iState2List)); 
            if(metronome.tick()){
              db.getChord(currentChord, my_instrument->getName(), currentChordsProg->getNext());
              my_display->show(db.getStateString(PLAY) + String(metronome.getBPM()), currentChord->getName());
              my_instrument->clearNeck();
              my_instrument->show_chord(currentChord);
            }
          }          
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            metronome.reset();
            state = METRONOME;
            iState2List = 0;
            currentChordsProg->reset();
          }
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (BACK)
            Reset_AVR();
          }
        break;
        /*------------------------7. PLAY / SCALES -------------------------------*/
        case SCALES:
          if(isJustEntered()){
            my_display->show(db.getStateString(PLAY) + String(metronome.getBPM()), db.getNote(iState1List));
          }
          if(metronome.updateAndCheckTime(BASE_PERIOD)) {
            metronome.tick();
            currentNote = my_instrument->play_scale(currentScale);
            my_display->show(db.getStateString(PLAY) + String(metronome.getBPM()), currentNote);
          }
          if(buttonR.isPressed() && my_debounce()){     // Red button pressed (BACK)
            justEntered = true;
            state = METRONOME;
            metronome.reset();
            currentScale->reset();
            my_instrument->show_scale(currentScale);
          }        
          if(buttonG.isPressed() && my_debounce()){     // Green button pressed (BACK)
            Reset_AVR();
          }
        break;
      }
    break;
    }

}

/**
    Used to avoid continuous display updates.
*/
bool isJustEntered(){
  if(justEntered){
    justEntered = false;
    return true;
  }
  return false;
}

/**
    Button debounce function

    @return true if the time elapsed from the last press is sufficient.
*/
bool my_debounce() {
  if ( (millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    lastDebounceTime = millis(); //set the current time
    return true;
  }
  return false;
}


// DEBUG, calculates the free memory
#ifdef __arm__
    // should use uinstd.h to define sbrk but Due causes a conflict
    extern "C" char* sbrk(int incr);
    #else  // __ARM__
    extern char *__brkval;
    #endif  // __arm__
     
int freeMemory() {
      char top;
    #ifdef __arm__
      return &top - reinterpret_cast<char*>(sbrk(0));
    #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
      return &top - __brkval;
    #else  // __arm__
      return __brkval ? &top - __brkval : &top - __malloc_heap_start;
    #endif  // __arm__
}
