#include "utilities.h"

unsigned int getPortNumber(RtMidi *midiObject, std::string name)
{
    unsigned int nPorts = midiObject->getPortCount();
    for (unsigned int i=0; i<nPorts; i++ ) {
        std::string portName = midiObject->getPortName(i);
        if(portName.rfind(name, 0) == 0)      // sort of "startsWith" : https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-stdstring-starts-with-a-certain-string-and-convert-a
            return i;
            
    }
    throw std::runtime_error("Port " + name + " not found");
}