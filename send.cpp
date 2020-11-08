#include <rtmidi/RtMidi.h>
#include <vector>
#include "send.h"
#include "utilities.h"
#include "midi_constants.h"

using namespace std;

void send(RtMidiOut *midiOut, const unsigned char command, const unsigned char channel, const unsigned char param1, const unsigned char param2) {
    vector<unsigned char> message;

    if(midiOut == nullptr)
        throw runtime_error("send() : midiOut == nullptr");

    if(channel > 15)
        throw runtime_error("send() : invalid channel");

    message.push_back(command | channel);
    message.push_back(param1);
    if(param2 < 128)
        message.push_back(param2);
    midiOut->sendMessage(&message);
}

void send(const string portName, const string command, const string channel, const string param1, const string param2)
{
    RtMidiOut *midiOut = nullptr;

    try {
        midiOut = new RtMidiOut();
        const unsigned int nPorts = midiOut->getPortCount();
        midiOut->openPort(getPortNumber(midiOut, portName));
    }
    catch(RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }

    const unsigned char ichannel = std::stoi(channel) - 1;
    const unsigned char byte2 = stoi(param1), byte3 = stoi(param2);

    if(command == "noteon")
        send(midiOut, NOTEON, ichannel, byte2, byte3);
    else if(command == "noteoff")
        send(midiOut, NOTEOFF, ichannel, byte2, byte3);  
    else if(command == "cc")
        send(midiOut, CONTROL_CHANGE, ichannel, byte2, byte3);
    else if(command == "pc")
        send(midiOut, PROGRAM_CHANGE, ichannel, byte2);      
    else {
        cerr << command << " : unknown command." << endl;
        delete midiOut;
        exit(EXIT_FAILURE);
    }

    delete midiOut;

}

void send(const string portName)
{
    cout << "Not implemented yet." << endl;
}