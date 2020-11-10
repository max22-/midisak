#ifndef RECEIVE_H
#define RECEIVE_H

#include <string>
#include <iostream>
#include <rtmidi/RtMidi.h>

void receive(RtMidiIn *midiIn,  std::string portName);

#endif