MAKEFLAGS += --silent

SRC := main.cpp Encrypter.cpp
INC := include/EnigmaCPP.h include/EnigmaRotor.h include/EnigmaSettings.h
LIB := libs/LibEnigmaCPP.a
HED := Encrypter.h

all: EnigmaCPP

EnigmaCPP: $(SRC) $(LIB) $(INC) $(HED)
	g++ -O3 -std=c++17 $(SRC) $(LIB) -o EnigmaCPP