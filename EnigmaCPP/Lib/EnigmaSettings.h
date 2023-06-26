/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#pragma once

#include "EnigmaRotor.h"

#include <unordered_map>
#include <vector>

namespace Enigma
{
    /**
     * Class holding settings in enigma friendly way.
     */
    class EnigmaSettings
    {
    public:
        /**
         * Constructor.
         * 
         * Params:
         * std::string ReflectorAlphabet - alphabet of reflector.
         * std::vector<EnigmaRotor> Rotors - enigma firendly rotors.
         * std::unordered_map<char, char> PlugboardConnections - plugboard connections in map form.
        */
        EnigmaSettings(std::string ReflectorAlphabet, std::vector<EnigmaRotor> Rotors, std::unordered_map<char, char> PlugboardConnections) noexcept :
        ReflectorAlphabet(ReflectorAlphabet), Rotors(Rotors), PlugboardConnections(PlugboardConnections) {};

        /**
         * Copy constructor.
         * 
         * Params:
         * const EnigmaSettings& ES - object to be copied.
        */
        EnigmaSettings(const EnigmaSettings& ES) noexcept :
        ReflectorAlphabet(ES.getRefAlp()), Rotors(ES.getRotors()), PlugboardConnections(ES.getConnections()) {};

        /**
         * Default constructor.
         * 
         * ReflectorAlphabet is empty.
         * Rotors are empty.
         * PlugboardConnections are empty.
        */
        EnigmaSettings() noexcept :
        ReflectorAlphabet(""), Rotors(std::vector<EnigmaRotor>()), PlugboardConnections(std::unordered_map<char, char>()) {};

        /**
         * Returns reflector alphabet.
         * 
         * Returns:
         * std::string - reflector alphabet.
        */
        std::string getRefAlp() const noexcept { return ReflectorAlphabet; }

        /**
         * Returns rotors.
         * 
         * Returns:
         * std::vector<EnigmaRotor> - rotors (from left to right).
        */
        std::vector<EnigmaRotor> getRotors() const noexcept { return Rotors; }

        /**
         * Returns plugboard connections.
         * 
         * Returns:
         * std::unordered_map<char, char> - plugboard connections.
        */
        std::unordered_map<char, char> getConnections() const noexcept { return PlugboardConnections; }

        friend class Encoder;
    private:
        /* Reflector alphabet. */
        std::string ReflectorAlphabet;

        /* Rotors (from left to right). Size should be equal 3. */
        std::vector<EnigmaRotor> Rotors;

        /* Plugboard connections. 
         * If map contains A -> B it should also contain B -> A.
         * Every unused letter should be mapped to itself e.g. Z -> Z
        */
        std::unordered_map<char, char> PlugboardConnections;
    };
}