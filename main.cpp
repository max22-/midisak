#include <iostream>
#include <rtmidi/RtMidi.h>
#include "send.h"
#include "receive.h"

using namespace std;

void usage();

int main(int argc, char *argv[])
{
    if(argc == 3 && string(argv[1]) == "-l")
        receive(argv[2]);
    else if(argc == 3 && string(argv[2]) == "-") {
        send(argv[2]);
        return EXIT_SUCCESS;
    }
    else if(argc == 6 && string(argv[2]) != "pc") {
        send(argv[1], argv[2], argv[3], argv[4], argv[5]);
    }
    else if(argc == 5 && string(argv[2]) == "pc") {
        send(argv[1], argv[2], argv[3], argv[4]);
    }
    else usage();

    return EXIT_SUCCESS;
}


void usage()
{
    cerr << "Invalid arguments" << endl;
    exit(EXIT_FAILURE);
}