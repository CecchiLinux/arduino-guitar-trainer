/*
 * 
 *  Created by Evan Minto on 2/25/11.
 *  Copyright 2011 Smart-Guitar-Chords. All rights reserved.
 *
 */

#include "Note.h"

void Note::generateName()
{
    switch (relPitch) {
    case 0:
        setName("C");
        break;
    case 1:
        setName("Db", "C#");
        break;
    case 2:
        setName("D");
        break;
    case 3:
        setName("Eb", "D#");
        break;
    case 4:
        setName("E");
        break;
    case 5:
        setName("F");
        break;
    case 6:
        setName("Gb", "F#");
        break;
    case 7:
        setName("G");
        break;
    case 8:
        setName("Ab", "G#");
        break;
    case 9:
        setName("A");
        break;
    case 10:
        setName("Bb", "A#");
        break;
    case 11:
        setName("B");
        break;
    default:
        break;
    }
}

Note::Note()
{
    this->absPitch = 0;
    this->relPitch = 0;
    this->octave = 0;
}

byte Note::encodeAbsPitch(byte t, byte f)
{
    return t + f;
}

void Note::set(byte t, byte f)
{
    this->absPitch = encodeAbsPitch(t, f);
    this->octave = this->absPitch / 12;

    this->relPitch = this->absPitch % 12;
    while (this->relPitch<0)
        this->relPitch += 12;

    generateName();
}

void Note::set(byte newPitch)
{
    this->absPitch = newPitch;
    this->octave = this->absPitch / 12;

    this->relPitch = this->absPitch % 12;
    while (this->relPitch<0)
        this->relPitch += 12;

    generateName();
}

void Note::setName(String n)
{
    this->name = n;
}

void Note::setName(String n1, String n2)
{
    this->name = n1;
    this->altName = n2;
}
