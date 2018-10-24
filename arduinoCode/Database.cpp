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

#include "Database.h"

Database::Database()
{ 
}

String Database::getStateString(byte state){
  String select = "SELECT";
  switch(state){
    case 0:
      return "0";
    break;
    case 1:
      return select + " ES";
    break;
    case 2:
      return select + " TONE";
    break;
    case 3:
      return select + " TYPE";
    break;
    case 4:
      return "VISUALIZE";
    break;
    case 5:
      return select;
    break;
    case 6:
      return "BPM ";
    break;
  }
}

void Database::getChordsProg(ChordsProgImpl* hp, String str_chords_prog)
{
   hp->setName(str_chords_prog);
   hp->reset();
   if(str_chords_prog.equals(this->notes[2])){ // C
      hp->addChord("Cmaj");
      hp->addChord("Amin");
      hp->addChord("Dmin");
      hp->addChord("G7");
   }else if(str_chords_prog.equals(this->notes[6])){ // G
      hp->addChord("Gmaj");
      hp->addChord("Emin");
      hp->addChord("Amin");
      hp->addChord("D7");
   }else if(str_chords_prog.equals(this->notes[3])){ // D
      hp->addChord("Dmaj");
      hp->addChord("Bmin");
      hp->addChord("Emin");
      hp->addChord("A7");
   }else if(str_chords_prog.equals(this->notes[0])){ // A
      hp->addChord("Amaj");
      hp->addChord("F#min");
      hp->addChord("Bmin");
      hp->addChord("E7");
   }else if(str_chords_prog.equals(this->notes[4])){ // E
      hp->addChord("Emaj");
      hp->addChord("C#min");
      hp->addChord("F#min");
      hp->addChord("B7");
   }else if(str_chords_prog.equals(this->notes[1])){ // B
      hp->addChord("Bmaj");
      hp->addChord("G#min");
      hp->addChord("C#min");
      hp->addChord("F#7");
   }else if(str_chords_prog.equals(this->notes[5])){ // F
      hp->addChord("Fmaj");
      hp->addChord("Dmin");
      hp->addChord("Gmin");
      hp->addChord("C7");
   }
}

bool Database::getChord(ChordImpl* c, String inst, String str_chord)
{
  byte tab[6];

  if(inst.equals("EADGBE")){
    if(str_chord.equals("Amaj"))
    {
      tab[0] = 99;
      tab[1] = 0;
      tab[2] = 2;
      tab[3] = 2;
      tab[4] = 2;
      tab[5] = 0; 
    }
    else if(str_chord.equals("Amin"))
    {
      tab[0] = 99;
      tab[1] = 0;
      tab[2] = 2;
      tab[3] = 2;
      tab[4] = 1;
      tab[5] = 0;
    }
    else if(str_chord.equals("A7"))
    {
      tab[0] = 99;
      tab[1] = 0;
      tab[2] = 2;
      tab[3] = 2;
      tab[4] = 2;
      tab[5] = 3;
    }
    else if(str_chord.equals("Bmaj"))
    {
      tab[0] = 99;
      tab[1] = 2;
      tab[2] = 4;
      tab[3] = 4;
      tab[4] = 4;
      tab[5] = 2;
    }
    else if(str_chord.equals("Bmin"))
    {
      tab[0] = 99;
      tab[1] = 2;
      tab[2] = 4;
      tab[3] = 4;
      tab[4] = 3;
      tab[5] = 2;
    }
    else if(str_chord.equals("B7"))
    {
      tab[0] = 99;
      tab[1] = 2;
      tab[2] = 1;
      tab[3] = 2;
      tab[4] = 0;
      tab[5] = 2;
    }
    else if(str_chord.equals("Cmaj"))
    {
      tab[0] = 99;
      tab[1] = 3;
      tab[2] = 2;
      tab[3] = 0;
      tab[4] = 1;
      tab[5] = 0;
    }
    else if(str_chord.equals("Cmin"))
    {
      tab[0] = 99;
      tab[1] = 3;
      tab[2] = 5;
      tab[3] = 5;
      tab[4] = 4;
      tab[5] = 3;
    }
    else if(str_chord.equals("C#min"))
    {
      tab[0] = 99;
      tab[1] = 4;
      tab[2] = 6;
      tab[3] = 6;
      tab[4] = 5;
      tab[5] = 4;
    }
    else if(str_chord.equals("C7"))
    {
      tab[0] = 99;
      tab[1] = 3;
      tab[2] = 2;
      tab[3] = 3;
      tab[4] = 1;
      tab[5] = 0;
    }
    else if(str_chord.equals("Dmaj"))
    {
      tab[0] = 99;
      tab[1] = 99;
      tab[2] = 0;
      tab[3] = 2;
      tab[4] = 3;
      tab[5] = 2;
    }
    else if(str_chord.equals("Dmin"))
    {
      tab[0] = 99;
      tab[1] = 99;
      tab[2] = 0;
      tab[3] = 2;
      tab[4] = 3;
      tab[5] = 1;
    }
    else if(str_chord.equals("D7"))
    {
      tab[0] = 99;
      tab[1] = 99;
      tab[2] = 0;
      tab[3] = 2;
      tab[4] = 1;
      tab[5] = 2;
    }
    else if(str_chord.equals("Emaj"))
    {
      tab[0] = 0;
      tab[1] = 2;
      tab[2] = 2;
      tab[3] = 1;
      tab[4] = 0;
      tab[5] = 0;
    }
    else if(str_chord.equals("Emin"))
    {
      tab[0] = 0;
      tab[1] = 2;
      tab[2] = 2;
      tab[3] = 0;
      tab[4] = 0;
      tab[5] = 0;
    }
    else if(str_chord.equals("E7"))
    {
      tab[0] = 0;
      tab[1] = 2;
      tab[2] = 2;
      tab[3] = 1;
      tab[4] = 3;
      tab[5] = 0;
    }
    else if(str_chord.equals("Fmaj"))
    {
      tab[0] = 1;
      tab[1] = 3;
      tab[2] = 3;
      tab[3] = 2;
      tab[4] = 1;
      tab[5] = 1;
    }
    else if(str_chord.equals("Fmin"))
    {
      tab[0] = 1;
      tab[1] = 3;
      tab[2] = 3;
      tab[3] = 1;
      tab[4] = 1;
      tab[5] = 1;
    }
    else if(str_chord.equals("F#min"))
    {
      tab[0] = 2;
      tab[1] = 4;
      tab[2] = 4;
      tab[3] = 2;
      tab[4] = 2;
      tab[5] = 2;
    }
    else if(str_chord.equals("F#7"))
    {
      tab[0] = 2;
      tab[1] = 4;
      tab[2] = 2;
      tab[3] = 3;
      tab[4] = 5;
      tab[5] = 2;
    }
    else if(str_chord.equals("Gmaj"))
    {
      tab[0] = 3;
      tab[1] = 2;
      tab[2] = 0;
      tab[3] = 0;
      tab[4] = 0;
      tab[5] = 3;
    }
    else if(str_chord.equals("Gmin"))
    {
      tab[0] = 3;
      tab[1] = 5;
      tab[2] = 5;
      tab[3] = 3;
      tab[4] = 3;
      tab[5] = 3;
    }
    else if(str_chord.equals("G#min"))
    {
      tab[0] = 4;
      tab[1] = 6;
      tab[2] = 6;
      tab[3] = 4;
      tab[4] = 4;
      tab[5] = 4;
    }
    else if(str_chord.equals("G7"))
    {
      tab[0] = 3;
      tab[1] = 2;
      tab[2] = 0;
      tab[3] = 0;
      tab[4] = 0;
      tab[5] = 1;
    }else{
      c->set(false);
      return false;
    }
    c->setName(str_chord);
    c->setNumNotes(6);
    c->setTab(tab);
    c->set(true);
  }
  return true;
}


bool Database::getScale(ScaleImpl* sc, String str_inst, String str_tone, String str_type)
{
  bool error = false;
  sc->setTone(str_tone);
  sc->setType(str_type);

  if(str_tone.equals(this->notes[2])){ // C
    sc->setTonic(8);
  }else if(str_tone.equals(this->notes[6])){ // G
    sc->setTonic(3);
  }else if(str_tone.equals(this->notes[3])){ // D
    sc->setTonic(10);
  }else if(str_tone.equals(this->notes[0])){ // A
    sc->setTonic(5);
  }else if(str_tone.equals(this->notes[4])){ // E
    sc->setTonic(0);
  }else if(str_tone.equals(this->notes[1])){ // B
    sc->setTonic(7);
  }else if(str_tone.equals(this->notes[5])){ // F
    sc->setTonic(1);
  }else{
    error = true;
  }
  if(str_type.equals("Maj")){
    sc->setString(6, 3, -1, 0, 2, 0);
    sc->setString(5, 3, -1, 0, 2, 0);
    sc->setString(4, 3, -1, 1, 2, 0);
    sc->setString(3, 3, -1, 1, 2, 0);
    sc->setString(2, 2, 0, 2, 0, 0);
    sc->setString(1, 3, -1, 0, 2, 0);
  }else if(str_type.equals("Nat. Min")){
    sc->setString(6, 3, 0, 2, 3, 0);
    sc->setString(5, 3, 0, 2, 3, 0);
    sc->setString(4, 2, 0, 2, 0, 0);
    sc->setString(3, 3, -1, 0, 2, 0);
    sc->setString(2, 3, 0, 1, 3, 0);
    sc->setString(1, 3, 0, 2, 3, 0);
  }else if(str_type.equals("Pent. Min")){
    sc->setString(6, 2, 0, 3, 0, 0);
    sc->setString(5, 2, 0, 2, 0, 0);
    sc->setString(4, 2, 0, 2, 0, 0);
    sc->setString(3, 2, 0, 2, 0, 0);
    sc->setString(2, 2, 0, 3, 0, 0);
    sc->setString(1, 2, 0, 3, 0, 0);
  }else if(str_type.equals("wu1")){
    sc->setString(6, 4, 0, 1, 2, 3);
    sc->setString(5, 4, 0, 1, 2, 3);
    sc->setString(4, 4, 0, 1, 2, 3);
    sc->setString(3, 4, 0, 1, 2, 3);
    sc->setString(2, 4, 0, 1, 2, 3);
    sc->setString(1, 4, 0, 1, 2, 3);
  }
  else if(str_type.equals("wu2")){
    sc->setString(6, 4, 0, 3, 1, 2);
    sc->setString(5, 4, 0, 3, 1, 2);
    sc->setString(4, 4, 0, 3, 1, 2);
    sc->setString(3, 4, 0, 3, 1, 2);
    sc->setString(2, 4, 0, 3, 1, 2);
    sc->setString(1, 4, 0, 3, 1, 2);
  }
  else if(str_type.equals("wu3")){
    sc->setString(6, 4, 0, 2, 1, 3);
    sc->setString(5, 4, 0, 2, 1, 3);
    sc->setString(4, 4, 0, 2, 1, 3);
    sc->setString(3, 4, 0, 2, 1, 3);
    sc->setString(2, 4, 0, 2, 1, 3);
    sc->setString(1, 4, 0, 2, 1, 3);
  }
  return sc->checkOverFret(7);
}

void Database::getChordByNum(ChordImpl* c, String inst, byte note, byte type)
{
  String str_chord;
  str_chord = this->notes[note] + this->chords_types[type];
  // str_chord.replace(" ", ""); 
  getChord(c, inst, str_chord);
}

/*
 * input: "A" 
 * output: A_cords array
 */
 /*
bool* Database::getChordsTypes(byte note)
{
  switch(note){
    case 0:
      return this->A_chords;
    break;
    case 1:
      return this->B_chords;
    break;
    case 2:
      return this->C_chords;
    break;
    case 3:
      return this->D_chords;
    break;
    case 4:
      return this->E_chords;
    break;
    case 5:
      return this->F_chords;
    break;
    case 6:
      return this->G_chords;
    break;
  }
}
*/
