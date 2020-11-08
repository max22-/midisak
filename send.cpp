#include <rtmidi/RtMidi.h>
#include <vector>
#include "send.h"
#include "utilities.h"
#include "midi_constants.h"

using namespace std;

void send(string portName, string command, string param1, string param2, string param3)
{
    RtMidiOut *midiOut = nullptr;
    vector<unsigned char> message;

    try {
        midiOut = new RtMidiOut();
        const unsigned int nPorts = midiOut->getPortCount();
        midiOut->openPort(getPortNumber(midiOut, portName));
    }
    catch(RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }

    const unsigned char channel = std::stoi(param1) - 1;
    if(channel > 15) {
        cerr << "invalid channel" << endl;
        exit(EXIT_FAILURE);
    }
    const unsigned char byte2 = stoi(param2), byte3 = stoi(param3);

    if(command == "noteon") {
        unsigned char byte1 = NOTEON | channel;
        message.push_back(byte1);
        message.push_back(byte2);
        message.push_back(byte3);
    }
    else if(command == "noteoff") {
        unsigned char byte1 = NOTEOFF | channel;
        message.push_back(byte1);
        message.push_back(byte2);
        message.push_back(byte3);       
    }
    else if(command == "cc") {
        unsigned char byte1 = CONTROL_CHANGE | channel;
        message.push_back(byte1);
        message.push_back(byte2);
        message.push_back(byte3);  
    }
    else if(command == "pc") {
        unsigned char byte1 = PROGRAM_CHANGE | channel;
        message.push_back(byte1);
        message.push_back(byte2);
        message.push_back(byte3);        
    }
    else {
        cerr << command << " : unknown command." << endl;
        delete midiOut;
        exit(EXIT_FAILURE);
    }

    midiOut->sendMessage( &message );

    delete midiOut;

}