#ifndef UTILITIES_H
#define UTILITIES_H

#include <rtmidi/RtMidi.h>

unsigned int getPortNumber(RtMidi *midiObject, std::string name);

#endif