MAKEFLAGS += --silent

SRC := Encoder.cpp SettingsConversion.cpp UserSettings.cpp
HED := EnigmaCPP.h EnigmaRotor.h EnigmaSettings.h SettingsConversion.h
BIN := Encoder.o SettingsConversion.o UserSettings.o

all: LibEnigmaCPP clean

Objects: $(SRC) $(HED)
	g++ -c -std=c++11 -O3 $(SRC)

LibEnigmaCPP: Objects
	ar rvs LibEnigmaCPP.a $(BIN)

clean:
	rm -f $(BIN)