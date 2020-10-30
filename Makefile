all: midisak

midisak: main.cpp
	g++ main.cpp -o midisak -lrtmidi

.PHONY: clean

clean:
	rm -f midisak