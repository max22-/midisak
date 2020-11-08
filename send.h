#ifndef SEND_H
#define SEND_H

#include <string>

void send(std::string portName, std::string command, std::string param1, std::string param2, std::string param3 = "");
void send(std::string portName);    // send commands from stdin

#endif