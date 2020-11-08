#include <rtmidi/RtMidi.h>
#include "receive.h"
#include "utilities.h"
#include "midi_constants.h"

using namespace std;

void callback(double deltatime, std::vector< unsigned char > *message, void *userData);

void receive(string portName)
{
    RtMidiIn *midiIn;
    unsigned int portNumber;
    cout << "receive(\"" << portName << "\")" << endl;
    try {
        midiIn = new RtMidiIn();
        portNumber = getPortNumber(midiIn, portName);
        midiIn->openPort(portNumber);
    }
    catch (RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    catch (runtime_error &error) {
        cerr << error.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    midiIn->setCallback(&callback);
    midiIn->ignoreTypes(false, false, false);
    cout << "\nReading MIDI input ... press <enter> to quit." << endl;
    char input;
    cin.get(input);
    delete midiIn;
}

void callback(double deltatime, std::vector< unsigned char > *message, void *userData)
{
    unsigned char byte1 = message->at(0);
    unsigned char command = byte1 & 0b11110000;
    unsigned char channel = (byte1 & 0b00001111) + 1;

    switch(command) {
        case NOTEON: {
            unsigned int note = message->at(1);
            unsigned int velocity = message->at(2);
            cout << "noteon " << (int) channel << " " << note << " " << velocity << endl;
            break;
        }
        case NOTEOFF: {
            unsigned int note = message->at(1);
            unsigned int velocity = message->at(2);
            cout << "noteoff " << (int) channel << " " << note << " " << velocity << endl;
            break;
        }
        case CONTROL_CHANGE: {
            unsigned int controller = message->at(1);
            unsigned int value = message->at(2);
            cout << "cc " << (int) channel << " " << controller << " " << value << endl;
            break;
        }
        case PROGRAM_CHANGE: {
            unsigned int program = message->at(1);
            cout << "pc " << (int) channel << " " << program << endl; 
            break;
        }
        default: {
            cout << "unknown_message" << endl;
            break;
        }
    }
}