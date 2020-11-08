#ifndef SEND_H
#define SEND_H

#include <string>

void send(
    RtMidiOut *midiOut, 
    const unsigned char command, 
    const unsigned char param1, 
    const unsigned char param2, 
    const unsigned char param3 = 255);

void send(
    const std::string portName,
    const std::string command,
    const std::string param1,
    const std::string param2,
    const std::string param3 = "");

void send(const std::string portName);    // send commands from stdin

#endif