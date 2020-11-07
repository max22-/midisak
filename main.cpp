#include <iostream>
#include <rtmidi/RtMidi.h>

using namespace std;

unsigned int getPortNumber(RtMidiOut *midiOut, string name);

int main(int argc, char *argv[])
{
    RtMidiOut *midiOut = nullptr;
    vector<unsigned char> message;

    if(argc != 4) {
        cerr << "Invalid arguments" << endl;
        return EXIT_FAILURE;
    }

    try {
        midiOut = new RtMidiOut();
    }
    catch(RtMidiError &error) {
        error.printMessage();
        return EXIT_FAILURE;
    }
    unsigned int nPorts = midiOut->getPortCount();
    cout << "There are " << nPorts << " MIDI output ports available." << endl;

    midiOut->openPort(getPortNumber(midiOut, argv[1]));


    message.push_back(176);
    message.push_back(stoi(argv[2]));
    message.push_back(stoi(argv[3]));
    midiOut->sendMessage( &message );

    delete midiOut;
    return EXIT_SUCCESS;
}

unsigned int getPortNumber(RtMidiOut *midiOut, string name)
{
    unsigned int nPorts = midiOut->getPortCount();
    for (unsigned int i=0; i<nPorts; i++ ) {
        try {
            string portName = midiOut->getPortName(i);
            if(portName.rfind(name, 0) == 0)      // sort of "startsWith" : https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-stdstring-starts-with-a-certain-string-and-convert-a
                return i;
            
        }
        catch ( RtMidiError &error ) {
            error.printMessage();
            delete midiOut;
            return EXIT_FAILURE;
        }
    }
    throw runtime_error("Port " + name + " not found");
}