#include <rtmidi/RtMidi.h>
#include <sstream>
#include "send.h"
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

void send(RtMidiOut *midiOut, const vector <string> arguments)
{

    const string command = arguments.at(0);
    const unsigned char channel = std::stoi(arguments.at(1));
    const unsigned char byte2 = std::stoi(arguments.at(2));
    const unsigned char byte3 = arguments.size() > 3 ? std::stoi(arguments.at(3)) : 255;

    if(command == "noteon")
        send(midiOut, NOTEON, channel, byte2, byte3);
    else if(command == "noteoff")
        send(midiOut, NOTEOFF, channel, byte2, byte3);  
    else if(command == "cc")
        send(midiOut, CONTROL_CHANGE, channel, byte2, byte3);
    else if(command == "pc")
        send(midiOut, PROGRAM_CHANGE, channel, byte2);      
    else
        cerr << command << " : unknown command." << endl;

}

void send(RtMidiOut *midiOut, std::istream &stream)
{
    string line;
    while(getline(stream, line)) {
        stringstream ss(line);
        string token;
        vector<string> arguments;
        while(ss >> token)
            arguments.push_back(token);
        send(midiOut, arguments);
    }
}