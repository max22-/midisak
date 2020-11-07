all: midisak

midisak: main.cpp
	g++ main.cpp -o midisak -lrtmidi

.PHONY: clean install uninstall

clean:
	rm -f midisak

install: midisak
	cp midisak /usr/local/bin

uninstall:
	rm -f /usr/local/bin/midisak