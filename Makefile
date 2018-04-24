all: parser

parser: Circuit.o Element.o main.o 
	g++ $^ -o $@

Circuit.o: Circuit.cpp Circuit.h Element.h
	g++ $< -o $@

Element.o: Element.cpp Element.h
	g++ $< -o $@

main.o: main.cpp Element.h Circuit.h
	g++ $^ -o $@

clean:
	rm *.o parser
