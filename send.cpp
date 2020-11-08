#include <rtmidi/RtMidi.h>
#include <vector>
#include "send.h"
#include "utilities.h"
#include "midi_constants.h"

using namespace std;

void send(RtMidiOut *midiOut, const unsigned char command, const unsigned char param1, const unsigned char param2, const unsigned char param3) {
    vector<unsigned char> message;

    if(midiOut == nullptr)
        throw runtime_error("send() : midiOut == nullptr");

    const unsigned char channel = param1;
    if(channel > 15)
        throw runtime_error("send() : invalid channel");

    message.push_back(command | channel);
    message.push_back(param2);
    if(param3 < 128)
        message.push_back(param3);
    for(auto e: message)
        cout << (int) e << endl;
    midiOut->sendMessage(&message);
}

void send(const string portName, const string command, const string param1, const string param2, const string param3)
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

    const unsigned char channel = std::stoi(param1) - 1;
    const unsigned char byte2 = stoi(param2), byte3 = stoi(param3);

    if(command == "noteon")
        send(midiOut, NOTEON, channel, byte2, byte3);
    else if(command == "noteoff")
        send(midiOut, NOTEOFF, channel, byte2, byte3);  
    else if(command == "cc")
        send(midiOut, CONTROL_CHANGE, channel, byte2, byte3);
    else if(command == "pc")
        send(midiOut, PROGRAM_CHANGE, channel, byte2);      
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