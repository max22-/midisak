all: midits

midits: main.o receive.o send.o utilities.o
	g++ main.o receive.o send.o utilities.o -o midits -lrtmidi

main.o: main.cpp send.h receive.h
	g++ main.cpp -c -o main.o

receive.o: receive.cpp receive.h utilities.h midi_constants.h
	g++ receive.cpp -c -o receive.o

send.o: send.cpp send.h utilities.h midi_constants.h
	g++ send.cpp -c -o send.o

utilities.o: utilities.cpp utilities.h
	g++ utilities.cpp -c -o utilities.o

.PHONY: clean install uninstall

clean:
	rm -f midits *.o

install: midits
	cp midits /usr/local/bin

uninstall:
	rm -f /usr/local/bin/midits