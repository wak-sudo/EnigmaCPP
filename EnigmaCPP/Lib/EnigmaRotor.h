/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#pragma once

#include <string>

namespace Enigma
{
    /**
     * Class holding rotor information in enigma friendly way.
     */
    class EnigmaRotor
    {
    public:
        /**
         * Constructor.
         * 
         * Params:
         * std::string AlphabetRing - alphabet of rotor.
         * int Notch - turnover position of rotor (index in the alphabet).
         * int InitialPosition - initial position of rotor.
         * int RingSetting - ring setting of rotor.
        */
        EnigmaRotor(std::string AlphabetRing, int Notch, int InitialPosition, int RingSetting) noexcept :
        AlphabetRing(AlphabetRing), Notch(Notch), Position(InitialPosition), RingSetting(RingSetting) {};

        /**
         * Returns alphabet of rotor.
         * 
         * Returns:
         * std::string - alphabet of rotor.
        */
        std::string getAlphabet() const noexcept { return AlphabetRing; }

        /**
         * Returns turnover position of rotor (index in the alphabet).
         * 
         * Returns:
         * int - turnover position
        */
        int getNotch() const noexcept { return Notch; }

        /**
         * Returns current position of rotor. 
         * 
         * Returns:
         * int - position of rotor;
         */
        int getPos() const noexcept { return Position; }

        /**
         * Returns ring setting of rotor. 
         * 
         * Returns:
         * int - ring setting of rotor.
         */
        int getRingS() const noexcept { return RingSetting; }

        friend class Encoder;
    private:
        /* Alphabet of rotor. */
        std::string AlphabetRing;

        /* Turnover position of rotor (index in the alphabet). */
        int Notch;

        /* Current position of rotor. */
        int Position;

        /* Ring setting of rotor. */
        int RingSetting;
    };
}