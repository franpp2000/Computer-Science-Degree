SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g -I$(INC) -c

pruebarotacion: $(BIN)/pruebarotacion

$(BIN)/pruebarotacion: $(OBJ)/imagen.o $(OBJ)/imagenES.o $(OBJ)/pruebarotacion.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/imagenES.o $(OBJ)/pruebarotacion.o -o $@

$(OBJ)/pruebarotacion.o: $(SRC)/pruebarotacion.cpp $(SRC)/imagen.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $< -o $@


pruebapegado: $(BIN)/pruebapegado

$(BIN)/pruebapegado: $(OBJ)/imagen.o $(OBJ)/imagenES.o $(OBJ)/pruebapegado.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/imagenES.o $(OBJ)/pruebapegado.o -o $@

$(OBJ)/pruebapegado.o: $(SRC)/pruebapegado.cpp $(SRC)/imagen.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $< -o $@

pruebapunto: $(BIN)/pruebapunto

$(BIN)/pruebapunto: $(OBJ)/pruebapunto.o $(OBJ)/punto.o
	$(CXX) $(OBJ)/pruebapunto.o $(OBJ)/punto.o -o $@

$(OBJ)/pruebapunto.o: $(SRC)/pruebapunto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/punto.o: $(SRC)/punto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

pruebaruta: $(BIN)/pruebaruta

$(BIN)/pruebaruta: $(OBJ)/pruebaruta.o $(OBJ)/ruta.o $(OBJ)/punto.o
	$(CXX) $(OBJ)/pruebaruta.o $(OBJ)/ruta.o $(OBJ)/punto.o -o $@

$(OBJ)/pruebaruta.o: $(SRC)/pruebaruta.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/ruta.o: $(SRC)/ruta.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/punto.o: $(SRC)/punto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

pruebaalmacenrutas: $(BIN)/pruebaalmacenrutas

$(BIN)/pruebaalmacenrutas: $(OBJ)/pruebaalmacenrutas.o $(OBJ)/almacen_rutas.o $(OBJ)/ruta.o $(OBJ)/punto.o
	$(CXX) $(OBJ)/pruebaalmacenrutas.o $(OBJ)/almacen_rutas.o $(OBJ)/ruta.o $(OBJ)/punto.o -o $@

$(OBJ)/pruebaalmacenrutas.o: $(SRC)/pruebaalmacenrutas.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/almacen_rutas.o: $(SRC)/almacen_rutas.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/ruta.o: $(SRC)/ruta.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/punto.o: $(SRC)/punto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

main: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/almacen_rutas.o $(OBJ)/ruta.o $(OBJ)/punto.o $(OBJ)/imagen.o $(OBJ)/imagenES.o
	$(CXX) -I$(INC) $(OBJ)/main.o $(OBJ)/almacen_rutas.o $(OBJ)/ruta.o $(OBJ)/punto.o $(OBJ)/imagen.o $(OBJ)/imagenES.o -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/paises.o: $(INC)/paises.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pais.o: $(INC)/pais.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/almacen_rutas.o: $(SRC)/almacen_rutas.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/ruta.o: $(SRC)/ruta.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/punto.o: $(SRC)/punto.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagen.o: $(SRC)/imagen.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp
	$(CXX) $(CPPFLAGS) $< -o $@



# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean:
	rm -fr $(OBJ)/* $(BIN)/*
