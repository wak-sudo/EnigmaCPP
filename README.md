# EnigmaCPP
C++ implementation of Enigma M3 (plug board supported) as a static library and a command line tool for Linux.

## Details

Supports:
- Wheel order (Walzenlage) (three-rotor machine)
- Starting position of the rotors (Grundstellung) 
- Ring settings (Ringstellung)
- Plug connections (Steckerverbindungen)

Supported wiring tables:
```
Rotors:

I   EKMFLGDQVZNTOWYHXUSPAIBRCJ
II  AJDKSIRUXBLHWTMCQGZNPYFVOE
III BDFHJLCPRTXVZNYEIWGAKMUSQO
IV  ESOVPZJAYQUIRHXLNFTGKDCMWB
V   VZBRGITYUPSDNHLXAWMJQOFECK

Reflectors:

ETW ABCDEFGHIJKLMNOPQRSTUVWXYZ
B   YRUHQSLDPXNGOKMIEBFZCWVJAT
C   FVPJIAOYEDRZXWGCTKUQSBNMHL
```

Starting positions and ring settings are defined by an alphabet:
```
A B C D E F G H I J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
| | | | | | | | | |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
```

## How to build

You will need g++ compiler with C++17 support.

#### Library

1. Go to `EnigmaCPP/Lib/`
2. Use `make`
3. `LibEnigmaCPP.a` will be build.

#### Command-line tool 

1. In `EnigmaCPP/CLI/include/` put:
    * `EnigmaCPP.h`
    * `EnigmaRotor.h`
    * `EnigmaSettings.h`
From library project: `EnigmaCPP/Lib/`
2. Put `LibEnigmaCPP.a` into `EnigmaCPP/CLI/libs` folder.
3. Go to `EnigmaCPP/CLI`
4. Use `make`
5. `EnigmaCPP` will be build.

## API

See [this.](https://github.com/wak-sudo/EnigmaCPP/tree/main/Docs/API.MD)

## Help
```
Enigma M3 CLI (plug board supported):

    -e -> Create encrypted copy of a file
    EnigmaSharpCLI.exe -e [file path] [reflector B/C/ETW] 3x [rotor number I-V] 3x [rotor initial position] + 3x [rotor ring setting] (optional plug board connections max. 13)

    -s -> Encrypt string
    EnigmaSharpCLI.exe -s [string] [reflector B/C/ETW] 3x [rotor number I-V] 3x [rotor initial position] + 3x [rotor ring setting] (optional plug board connections max. 13)

    -h -> Display this help.

    Example:
    EnigmaCPP -e text.txt B I II III C B D F G D AZ BC;
```
