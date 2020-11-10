#ifndef SEND_H
#define SEND_H

#include <vector>
#include <string>

void send(
    RtMidiOut *midiOut, 
    const unsigned char command, 
    const unsigned char channel, 
    const unsigned char param1, 
    const unsigned char param2 = 255);

void send(RtMidiOut *midiOut, std::vector<std::string> arguments);

void send(RtMidiOut *midiOut, std::istream &stream);    // send commands from stdin

#endif