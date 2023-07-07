/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#include "SettingsConversion.h"
#include <stdexcept>

using namespace Enigma;

/** 
 * These maps MUST be initalized in the cpp file.
 * It is imposible to create static map with initalization.
 * But it can bypassed this way.
*/ 
std::unordered_map<RotorID, std::pair<std::string, int>> SettingsConversion::RotorInfo = {
    {I, {"EKMFLGDQVZNTOWYHXUSPAIBRCJ", 16}},
    {II, {"AJDKSIRUXBLHWTMCQGZNPYFVOE", 4}},
    {III, {"BDFHJLCPRTXVZNYEIWGAKMUSQO", 21}},
    {IV, {"ESOVPZJAYQUIRHXLNFTGKDCMWB", 9}},
    {V, {"VZBRGITYUPSDNHLXAWMJQOFECK", 25}}};

std::unordered_map<ReflectorID, std::string> SettingsConversion::ReflectorInfo = {
    {ETW, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {B, "YRUHQSLDPXNGOKMIEBFZCWVJAT"},
    {C, "FVPJIAOYEDRZXWGCTKUQSBNMHL"}};

std::pair<std::string, int> SettingsConversion::GetRotorInfo(RotorID RotorName)
{
    auto it = RotorInfo.find(RotorName);
    if (it == RotorInfo.end())
        throw std::runtime_error("Invalid rotor name.");
    return it->second;
}

std::string SettingsConversion::GetReflectorAlp(ReflectorID ReflectorName)
{
    auto it = ReflectorInfo.find(ReflectorName);
    if (it == ReflectorInfo.end())
        throw std::runtime_error("Invalid reflector name.");
    return it->second;
}

int SettingsConversion::ConvertCharacterToDecimal(char Character)
{
    if (Character >= 'A' && Character <= 'Z')
        return (Character - 'A');
    else
        throw std::runtime_error("An incorrect character passed to the decimal conversion.");
}

 std::unordered_map<char, char> SettingsConversion::CreatePlugboardConnections(const std::vector<std::string>& Connections)
 {
    if(Connections.size() > MaxNumberOfConnections) throw std::runtime_error("Too many connections.");
    std::unordered_map<char, char> plugboard;
    for(std::string con : Connections)
    {
        if(con.length() > 2) throw std::runtime_error("Invalid connection."); 
        if(con[0] == con[1] || con[0] > 'Z' || con[0] < 'A' || con[1] > 'Z' || con[1] < 'A') throw std::runtime_error("Invalid connection.");
        if(plugboard.find(con[0]) != plugboard.end() || plugboard.find(con[1]) != plugboard.end()) throw std::runtime_error("Connection already used.");
        plugboard[con[0]] = con[1];
        plugboard[con[1]] = con[0];
    }

    // Sets every unused character to itelf. E.g. Z -> Z
    for (char i = 'A'; i <= 'Z'; i++)
        if (plugboard.find(i) == plugboard.end())
            plugboard[i] = i;
            
    return plugboard;
 }

EnigmaRotor SettingsConversion::ConvertRotor(const UserRotor& Rotor)
{
    auto rotorSpec = GetRotorInfo(Rotor.getID());
    return EnigmaRotor(rotorSpec.first, rotorSpec.second, ConvertCharacterToDecimal(Rotor.getPosition()), ConvertCharacterToDecimal(Rotor.getRing()));
}

std::vector<EnigmaRotor> SettingsConversion::ConvertRotors(const std::vector<UserRotor>& UserRotors)
{
    if(UserRotors.size() != ValidNumberOfRotors) throw new std::runtime_error("The number of rotors is not equal " + std::to_string(ValidNumberOfRotors));
    std::vector<EnigmaRotor> refinedRotors;
    for (int i = 0; i < UserRotors.size(); i++)
        refinedRotors.push_back(ConvertRotor(UserRotors[i]));
    return refinedRotors;
}

EnigmaSettings SettingsConversion::ConvertToEnigmaSettings(const UserSettings& UserOptions)
{
    std::string reflectorAlphabet = GetReflectorAlp(UserOptions.getReflectorID());
    std::vector<EnigmaRotor> rotors = ConvertRotors(UserOptions.getRotors());
    std::unordered_map<char, char> plugboardConnections = CreatePlugboardConnections(UserOptions.getPlugboardConnections());
    return EnigmaSettings(reflectorAlphabet, rotors, plugboardConnections);
}