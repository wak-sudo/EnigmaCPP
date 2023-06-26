/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#pragma once

#include "EnigmaSettings.h"

#include <vector>

namespace Enigma
{
    /**
     * Rotor/reflector IDs.
     * 
     * Durning conversion from UserSettings to EnigmaSettings 
     * every ID will have their corresponding alphabet assigned.
     * E.g. I = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
    */
    enum RotorID { I, II, III, IV, V, ETW, B, C};
    
    /**
     * Class holding rotor information in user friendly way.
     */
    class UserRotor
    {
    public:
        /**
         * Constructor.
         * 
         * Params:
         * RotorID RotorNumber - rotor ID.
         * char InitialPosition - initial position of rotor.
         * char RingSetting - ring setting of rotor.
        */
        UserRotor(RotorID RotorNumber, char InitialPosition, char RingSetting) noexcept : 
        RotorNumber(RotorNumber), Position(InitialPosition), RingSetting(RingSetting) {};

        /**
         * Returns rotor ID.
         *
         * Returns:
         * RotorID - rotor ID.
         */
        RotorID getID() const noexcept { return RotorNumber; }

        /**
         * Returns current position of rotor.
         *
         * Returns:
         * char - current position of rotor.
         */
        char getPosition() const noexcept { return Position; }

        /**
         * Returns ring setting of rotor.
         *
         * Returns:
         * char - ring setting of rotor.
         */
        char getRing() const noexcept { return RingSetting; }

        /**
         * Sets rotor id.
         * 
         * Params:
         * RotorID id - new rotor id.
         */
        void setRotorNumber(RotorID id) noexcept {RotorNumber = id;}

        /**
         * Sets rotor position.
         * 
         * Params:
         * char nPos - new rotor position.
         */
        void setPosition(char nPos) noexcept { Position = nPos; }

        /**
         * Sets rotor ring setting.
         * 
         * Params:
         * char nSet - new rotor ring setting.
         */
        void setRingSetting(char nRingSetting) noexcept { RingSetting = nRingSetting; }

    private:
        /* ID of rotor. */
        RotorID RotorNumber;

        /* Position of rotor. */
        char Position;

        /* Ring setting of rotor. */
        char RingSetting;
    };

    /**
     * Class holding settings in user friendly way.
     */
    class UserSettings
    {
    public:
        /**
         * Constructor,
         * 
         * Params:
         * RotorID ReflectorName - ID of the reflector.
         * std::vector<UserRotor>& Rotors - vector storing rotors (from left to right).
         * std::vector<std::string>& PlugboardConnections - vector storing plugboard connections.
         */
        UserSettings(RotorID ReflectorName, const std::vector<UserRotor>& Rotors, const std::vector<std::string>& PlugboardConnections) noexcept :
        ReflectorName(ReflectorName), Rotors(Rotors), PlugboardConnections(PlugboardConnections) {};

        /**
         * Default constructor.
         * 
         * Reflector is set to be B.
         * Rotors are empty.
         * Connections are empty.
         */
        UserSettings() noexcept :
        ReflectorName(B), Rotors(std::vector<UserRotor>()), PlugboardConnections(std::vector<std::string>()) {};

        /**
         * Returns true if settings can be converted (can be safely passed to the encoder).
         * 
         * Returns:
         * True if settings are valid, else False.
         */
        bool CanBeConverted() const;

        /**
         * Returns reflector ID.
         *
         * Returns:
         * RotorID - reflector ID.
         */
        RotorID getReflectorID() const noexcept { return ReflectorName; }

        /**
         * Returns rotors.
         *
         * Returns:
         * std::vector<UserRotor> - rotors.
         */
        std::vector<UserRotor> getRotors() const noexcept { return Rotors; }

        /**
         * Returns plugboard connections.
         *
         * Returns:
         * std::vector<std::string> - plugboard connections.
         */
        std::vector<std::string> getPlugboardConnections() const noexcept { return PlugboardConnections; }

        /**
         * Sets reflector id.
         * 
         * Params:
         * RotorID id - new reflector id.
         */
        void setReflectorName(RotorID id) noexcept { ReflectorName = id; }

        /**
         * Sets rotors.
         * 
         * Params:
         * const std::vector<UserRotor>& nRotors - new rotors.
         */
        void setRotors(const std::vector<UserRotor>& nRotors) noexcept { Rotors = nRotors; }

        /**
         * Sets plugboard connections.
         * 
         * Params:
         * const std::vector<std::string>& nPG - new connections.
         */
        void setPlugboard(const std::vector<std::string>& nPG) noexcept { PlugboardConnections = nPG; }

    private:
        /* ID of relfector. */
        RotorID ReflectorName;

        /* User rotors from left to right. Size should be equal 3. */
        std::vector<UserRotor> Rotors;

        /* Plugboard connections. 
         * Min size = 0, max size = 13 (for English alphabet).
         * Stored strings should be size 2, e.g. "AB".
         * That means that A links to B and B links to A.
         */
        std::vector<std::string> PlugboardConnections; 
    };

    /**
     * Handles main Enigma logic.
     */ 
    class Encoder
    {
    public:
        /**
         * Class constructor, takes user settings and converts them to enigma-friendly settings
         *
         * Params:
         * const UserSettings& USettings - settings to be used durning encryption.
         * 
         * Exceptions:
         * If @USettings are invalid an exception will be thrown.
         * 
         * Params:
         * @USettings - instance of UserSettings that will be used for encryption.
         */
        Encoder(const UserSettings& USettings) noexcept(false);

        /**
         * Encrypts/decrypts given text.
         * 
         * Params:
         * const std::string& origninalText - text to be encrypted/decrypted
         * 
         * Returns:
         * String - encrypted/decrypted text.
         */
        std::string EncryptString(const std::string& origninalText) noexcept;

        /**
         * Encrypts/decrypts given character.
         * Read exceptions.
         * 
         * Params:
         * char letter - letter to be encrypted/decrypted.
         * 
         * Exceptions:
         * Function can throw an exception if the passed character is not in the uppercase
         * or does not belong in the English alphabet.
         * 
         * Returns:
         * Char - encrypted/decrypted character.
         */
        char EncryptChar(char letter) noexcept;

        /**
         * Returns current rotors position.
         * 
         * Returns:
         * std::vector<char> size 3 - rotors position from left to right.
        */
        std::vector<char> ReturnRotorsPosition() const noexcept;

        /**
         * Sets new settings.
         * 
         * Params:
         * const UserSettings& nSettings - new settings.
         * 
         * Exceptions:
         * If @nSettings are invalid an exception will be thrown.
         * 
         * Returns:
         * void
         */
        void setNewSettings(const UserSettings& nSettings) noexcept(false);

    private: 
        /* Length of the alphabet (asserted to be English). */
        static const int alphabetLength = 26;

        /* Enigma friendly settings build from UserSettings. */
        EnigmaSettings Settings;

        /**
         * Handles encryption in the pre-reflector encoding phase. 
         * 
         * Params:
         * char originalCharacter - character to be modified.
         * int encryptionSet - index of the rotor that should be used.
         * 
         * Returns:
         * Char - modified character.
         */ 
        inline char EnigmaPreRefEncoding(char originalCharacter, int encryptionSet) const noexcept;
        
        /**
         * Handles encryption in the post-reflector encoding phase.
         * 
         * Params:
         * char originalCharacter - character to be modified.
         * int encryptionSet - index of the rotor that should be used.
         * 
         * Returns:
         * Char - modified character.
         */
        inline char EnigmaPostRefEncoding(char originalCharacter, int encryptionSet) const noexcept;
        
        /** 
         * Handles stepping and checks turnover positions
         * 
         * Returns:
         * void
         */
        inline void StepRotors() noexcept;

        /**
         * Modulo implementation, ex. Mod(-3, 26) = 23
         * 
         * Params:
         * int i - first argument of modulo.
         * int k - second argument of modulo.
         * if not specified, @k is equal @alphabetLength.
         * 
         * Returns:
         * int z - such that modulo(i, k) = z
         */
        inline static int Mod(int i, int k = alphabetLength) noexcept;
    };
}