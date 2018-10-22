#ifndef NOTE_H
#define NOTE_H

#include "Arduino.h"

class Note
{
  private:
      byte absPitch;
      byte relPitch;
      byte octave;
  
      String name;
      String altName;
      void generateName();
  
  public:
      Note();

      byte getAbsPitch() const { return this->absPitch; }
      byte getRelPitch() const { return this->relPitch; }
      byte getRelPitch(byte offset) const { return (this->relPitch + offset)%12; }
      byte getOctave() const { return this->octave; }
      String getName() const { return this->name; }
  
      byte encodeAbsPitch(byte t, byte f);
      void set(byte t, byte f);
      void set(byte newPitch);
      void setName(String n);
      void setName(String n1, String n2);
};

#endif // NOTE_H
