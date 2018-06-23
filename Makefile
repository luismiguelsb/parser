CFLAGS = -std=c++11

INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/
TST_DIR = tests/


all: parser

parser: $(OBJ_DIR)Circuit.o $(OBJ_DIR)Element.o $(OBJ_DIR)Matrix.o $(OBJ_DIR)main.o 
	g++ $^ -o $(TST_DIR)$@ $(CFLAGS)

$(OBJ_DIR)Circuit.o: $(SRC_DIR)Circuit.cpp $(INC_DIR)Element.h $(INC_DIR)Circuit.h 
	g++ -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)Element.o: $(SRC_DIR)Element.cpp $(INC_DIR)Element.h
	g++ -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)Matrix.o: $(SRC_DIR)Matrix.cpp $(INC_DIR)Matrix.h
	g++ -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp $(INC_DIR)Element.h $(INC_DIR)Circuit.h $(INC_DIR)Matrix.h
	g++ -c -o $@ $< $(CFLAGS)

clean:
	rm $(OBJ_DIR)*.o $(TST_DIR)parser
