/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#pragma once

#include "EnigmaCPP.h"

#include <utility>

namespace Enigma
{
    /* Static class used for conversion from UserSettings to EnigmaSettings. */
    class SettingsConversion
    {
        /* Valid number of rotors. */
        const static int ValidNumberOfRotors = 3;

        /* Max number of plugboard connections. */
        const static int MaxNumberOfConnections = 13;

        /* Map from RotorID to pair of corresponding alphabet and notch. Defined in the cpp file. */
        static std::unordered_map<RotorID, std::pair<std::string, int>> RotorInfo;

        /* Map from ReflectorID of the reflector to a corresponding alphabet. Defined in the cpp file. */
        static std::unordered_map<ReflectorID, std::string> ReflectorInfo;

    public:
        /**
         * Converts UserSettings to EnigmaSetttings.
         * 
         * Params:
         * const UserSettings &UserOptions - UserSettings to be converted.
         * 
         * Exceptions:
         * If @UserOptions are invalid, an exception will be thrown.
         * 
         * Returns:
         * EnigmaSettings - converted UserSettings to EnigmaSettings.
        */
        static EnigmaSettings ConvertToEnigmaSettings(const UserSettings &UserOptions) noexcept(false);

    private:
        SettingsConversion() noexcept;

        /**
         * Converts rotors
         * 
         * Params:
         * const std::vector<UserRotor> &UserRotors - rotors to be converted.
         * 
         * Exceptions:
         * If rotors are invalid or vector size is > than ValidNumberOfRotors, then an exception will be thrown.
         * 
         * Returns:
         * std::vector<EnigmaRotor> - converted rotors.
        */
        static std::vector<EnigmaRotor> ConvertRotors(const std::vector<UserRotor> &UserRotors) noexcept(false);

        /**
         * Converts rotor
         * 
         * Params:
         * const UserRotor &Rotor - rotor to be converted.
         * 
         * Exceptions:
         * If rotor ID is undefined (shouldn't happen) or position or ring setting characters are invalid,
         * an exception will be thrown.
         * 
         * Returns:
         * EnigmaRotor - converted rotor.
        */
        static EnigmaRotor ConvertRotor(const UserRotor &Rotor) noexcept(false);

        /**
         * Converts character to decimal as follows:
         * A -> 0, B->1, ... Z -> 25.
         * 
         * Params:
         * char Character - character to be converted.
         * 
         * Exceptions:
         * If character is invalid (is not in the alphabet) or is in lowercase, an exception will be thrown.
         * 
         * Returns:
         * int - converted value.
        */
        static int ConvertCharacterToDecimal(char Character) noexcept(false);

        /**
         * Creates plugboard connections.
         * 
         * In the resulting map, if A -> B then B -> A
         * If there is a letter unused in connections (e.g. Z) then
         * Z -> Z.
         * 
         * Params:
         * const std::vector<std::string> &Connections - connections in user friendly form.
         * 
         * Exceptions:
         * if(Connections.size() > MaxNumberOfConnections) or
         * there is an invalid character or
         * there is a repeating connection or
         * there is a letter linking to itself,
         * then an exception will be thrown.
         * 
         * Return:
         * std::unordered_map<char, char> - connections in map form.
        */
        static std::unordered_map<char, char> CreatePlugboardConnections(const std::vector<std::string> &Connections) noexcept(false);

        /**
         * Returns corresponding element from RotorInfo map, that is alphabet and notch.
         * 
         * Params:
         * RotorID RotorName - ID to be lookup-ed in RotorInfo
         * 
         * Exceptions:
         * If RotorName cannot be found in RotorInfo, an exception will be thrown.
         * 
         * Returns:
         * std::pair<std::string, int> - corresponding pair consisitng of alphabet and notch
        */
        static std::pair<std::string, int> GetRotorInfo(RotorID RotorName) noexcept(false);

        /**
         * Returns corresponding element from ReflectorInfo map, that is alphabet.
         * 
         * Params:
         * ReflectorID ReflectorName - ID to be lookup-ed in ReflectorInfo
         * 
         * Exceptions:
         * If ReflectorName cannot be found in ReflectorInfo, an exception will be thrown.
         * 
         * Returns:
         * std::string - corresponding alphabet.
        */
        static std::string GetReflectorAlp(ReflectorID ReflectorName) noexcept(false);
    };
}
