## Technical information

LibEnigmaCPP provides API defined in `Enigma` namespace.

To use library a programmer must include in his project 3 headers:
* `EnigmaCPP.h`
* `EnigmaRotor.h`
* `EnigmaSettings.h`

Programmer should only bother about the content of `EnigmaCPP.h`. Due to the nature of static libraries of CPP the implementations inside other files should be left ignored and are omitted in this doc.

## General information

Library implements logic behind Enigma M3.

Supports:
- Encryption/decryption
- Rotors position peeking
- Specifying settings
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

## API Documentation ##
### Globals ###
#### enum RotorID ####
Enum that represents IDs of supported rotors.

#### enum ReflectorID ####
Enum that represents IDs of supported reflectors.

### UserRotor class ###
##### Description: #####
Class holds rotor information in user friendly way.

#### Constructor ####
```
UserRotor(RotorID RotorNumber, char InitialPosition, char RingSetting) noexcept : 
        RotorNumber(RotorNumber), Position(InitialPosition), RingSetting(RingSetting) {};
```
##### Description: #####
Constructor.

##### Params: #####
`RotorID RotorNumber` - rotor ID.

`char InitialPosition` - initial position of rotor.

`char RingSetting` - ring setting of rotor.

#### RotorID getID() const noexcept ####
##### Description: #####
Returns rotor ID.

##### Returns: #####
`RotorID` - rotor ID.

#### char getPosition() const noexcept ####
##### Description: #####
Returns current position of rotor.

##### Returns: #####
`char` - current position of rotor.

#### char getRing() const noexcept ####
##### Description: #####
Returns ring setting of rotor.

##### Returns: #####
`char` - ring setting of rotor.

#### void setRotorNumber(RotorID id) noexcept ####
##### Description: #####
Sets rotor id.

##### Params: #####
`RotorID id` - new rotor id.
        
#### void setPosition(char nPos) noexcept ####
##### Description: #####
Sets rotor position.

##### Params: #####
`char` nPos - new rotor position.

#### void setRingSetting(char nRingSetting) noexcept ####
##### Description: #####
Sets rotor ring setting.

##### Params: #####
`char nSet` - new rotor ring setting.

### UserSettings class ###
##### Description: #####
Class holding settings in user friendly way.

#### Default constructor ####
```
UserSettings() noexcept :
        ReflectorName(B), Rotors(std::vector<UserRotor>()), PlugboardConnections(std::vector<std::string>()) {};
```
##### Description: #####
Default constructor.
Reflector is set to be B.
Rotors are empty.
Connections are empty.

#### Constructor ####
```
UserSettings(RotorID ReflectorName, const std::vector<UserRotor>& Rotors, const std::vector<std::string>& PlugboardConnections) noexcept :
        ReflectorName(ReflectorName), Rotors(Rotors), PlugboardConnections(PlugboardConnections) {};
```
##### Description: #####
Constructor.

##### Params: #####
`RotorID ReflectorName` - ID of the reflector.

`std::vector<UserRotor>& Rotors` - vector storing rotors (from left to right).

`std::vector<std::string>& PlugboardConnections` - vector storing plugboard connections.

#### bool CanBeConverted() ####
##### Description: #####
Returns true if settings can be converted (can be safely passed to the encoder).

##### Returns: #####
`True` if settings are valid, else `False`.

#### RotorID getReflectorID() const noexcept ####
##### Description: #####
Returns reflector ID.

##### Returns: #####
`RotorID` - reflector ID.

#### std::vector<UserRotor> getRotors() const noexcept ####
##### Description: #####
Returns rotors.

##### Returns: #####
`std::vector<UserRotor>` - rotors.

#### std::vector\<std::string\> getPlugboardConnections() const noexcept ####
##### Description: #####
Returns plugboard connections.

##### Returns: #####
`std::vector\<std::string\>` - plugboard connections.

#### void setReflectorName(RotorID id) noexcept ####
##### Description: #####
Sets reflector id.

##### Params: #####
`RotorID id - new reflector id.`

#### void setRotors(const std::vector<UserRotor>& nRotors) noexcept ####
##### Description: #####
Sets rotors.

##### Params: #####
`const std::vector<UserRotor>& nRotors` - new rotors.

#### void setPlugboard(const std::vector\<std::string\>& nPG) noexcept ####
##### Description: #####
Sets plugboard connections.

##### Params: #####
`const std::vector<std::string>& nPG` - new connections.

### Encoder class ###
##### Description: #####
Handles text encryption/decryption.

#### Constructor ####
```
Encoder(const UserSettings& USettings) noexcept(false);
```
##### Description: #####
Constructs an Encoder object that utilities passed settings. If settings are not valid, an exception will be thrown.

#### std::string EncryptString(const std::string& origninalText) noexcept; ####
##### Description: #####
Encrypts/decrypts given text. Ignores whitespaces and characters out of English alphabet.

##### Params: #####
Params:
`const std::string& origninalText` - text to be encrypted/decrypted

##### Returns: #####
`std::string` - encrypted/decrypted text.

#### char EncryptChar(char letter) noexcept; ####
##### Description: #####
Encrypts/decrypts given character.
**Read exceptions.**

##### Params: #####
`char letter` - letter to be encrypted/decrypted.

##### Exceptions #####
Function can throw an exception if the passed character is not in the uppercase or does not belong in the English alphabet.

##### Returns: #####
`Char` - encrypted/decrypted character.

#### std::vector<char> ReturnRotorsPosition() const noexcept; ####
##### Description: #####
Returns current rotors position.

##### Returns: #####
`std::vector<char>` size 3 - rotors position from left to right.

#### void setNewSettings(const UserSettings& nSettings) noexcept(false); ####
##### Description: #####
Sets new settings.

##### Params: #####
`const UserSettings& nSettings` - new settings.

##### Exceptions #####
If `nSettings` are invalid an exception will be thrown.

##### Returns: #####
`void`

## Example ##
```
#include "include/EnigmaCPP.h"

#include <string>
#include <iostream>

using namespace Enigma;

int main()
{
    std::string test = "The quick brown fox jumps over the lazy dog.";
    std::vector<UserRotor> UR = {
        UserRotor(RotorID::I, 'A', 'A'),
        UserRotor(RotorID::V, 'Q', 'A'),
        UserRotor(RotorID::II, 'L', 'A')};

    std::vector<std::string> connections = {"AZ", "BC"};

    UserSettings SU(ReflectorID::B, UR, connections);
    if (SU.CanBeConverted())
    {
        Encoder enc(SU);
        std::cout << enc.EncryptString(test) << std::endl;
    }
    else
        std::cout << "Error";

    // g++ -O3 main.cpp LibEnigmaCPP.a -o main
    // Output: MOMNVPJFXOSRYUKIQQQFFUKLWSVIMSBMXQF
}
```
