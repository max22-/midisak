#include <iostream>
#include <rtmidi/RtMidi.h>
#include "send.h"
#include "receive.h"
#include "utilities.h"

using namespace std;

RtMidiIn *midiIn = nullptr;
RtMidiOut *midiOut = nullptr;

void usage();
void cleanup();

int main(int argc, char *argv[])
{
    try {
        if(argc == 3 && string(argv[1]) == "-l") {
            midiIn = new RtMidiIn();
            string portName = argv[2];
            unsigned int portNumber = getPortNumber(midiIn, portName);
            midiIn->openPort(portNumber);
            receive(midiIn, argv[2]);
        }
        else {
            midiOut = new RtMidiOut();
            string portName = argv[1];
            midiOut->openPort(getPortNumber(midiOut, portName));
            if(argc == 3 && string(argv[2]) == "-")
                send(midiOut, cin);
            else {
                vector<string> arguments;
                for(unsigned int i = 2; i < argc; i++)
                    arguments.push_back(argv[i]);
                send(midiOut, arguments);
            }
        }

    }
    catch(RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    catch(runtime_error &error) {
        cerr << "Caught exception : " << error.what() << endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void cleanup()
{
    if(midiIn != nullptr)
        delete midiIn;
    if(midiOut != nullptr)
        delete midiOut;
}  