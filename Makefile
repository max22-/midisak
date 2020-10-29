all: midisak

midisak: main.cpp
	g++ main.cpp -o midisak

.PHONY: clean

clean:
	rm -f midisak