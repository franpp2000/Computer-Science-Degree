INC = include
OBJ = obj
SRC = src
BIN = bin
CXX = g++


uso_diccionario: $(BIN)/uso_diccionario

$(BIN)/uso_diccionario: $(OBJ)/uso_diccionario.o
	$(CXX) -o $(BIN)/uso_diccionario $(OBJ)/uso_diccionario.o

$(OBJ)/uso_diccionario.o:
	$(CXX) -c -g -I$(INC) $(SRC)/uso_diccionario.cpp -o $(OBJ)/uso_diccionario.o

uso_guia: $(BIN)/uso_guia

$(BIN)/uso_guia: $(OBJ)/uso_guia.o $(OBJ)/guia.o
	$(CXX) -o $(BIN)/uso_guia $(OBJ)/uso_guia.o $(OBJ)/guia.o

$(OBJ)/uso_guia.o:
	$(CXX) -c -g -I$(INC) $(SRC)/uso_guia.cpp -o $(OBJ)/uso_guia.o

$(OBJ)/guia.o:
	$(CXX) -c -g -I$(INC) $(SRC)/guia.cpp -o $(OBJ)/guia.o



clean:
	rm -fr $(OBJ)/* $(BIN)/*

documentation:
	doxygen doc/Doxyfiles