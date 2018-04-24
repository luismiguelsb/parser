CFLAGS = -std=c++11

all: parser

parser: Circuit.o Element.o main.o 
	g++ $^ -o $@ $(CFLAGS)

Circuit.o: Circuit.cpp Element.h Circuit.h 
	g++ -c -o $@ $< $(CFLAGS)

Element.o: Element.cpp Element.h
	g++ -c -o $@ $< $(CFLAGS)

main.o: main.cpp Element.h Circuit.h 
	g++ -c -o $@ $< $(CFLAGS)

clean:
	rm *.o parser
