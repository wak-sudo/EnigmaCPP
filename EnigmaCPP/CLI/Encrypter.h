/**
 * EnigmaCPP
 * Wojciech Kieloch 2023 
*/

#pragma once

#include <string>

#include "include/EnigmaCPP.h"

namespace EnigmaCLI
{
    /* Class for handling program logic: flags, communication and encryption. */
    class Encrypter
    {
        /**
         * Map: Custom rotor name -> RotorID 
        */
        std::unordered_map<std::string, Enigma::RotorID> sToRoID_Map = {
            {"I", Enigma::RotorID::I},
            {"II", Enigma::RotorID::II},
            {"III", Enigma::RotorID::III},
            {"IV", Enigma::RotorID::IV},
            {"V", Enigma::RotorID::V}
        };

        std::unordered_map<std::string, Enigma::ReflectorID> sToRefID_Map = {
            {"B", Enigma::ReflectorID::B},
            {"C", Enigma::ReflectorID::C},
            {"ETW", Enigma::ReflectorID::ETW}
        };

        /* Min number of args for program, with program name and first param included. */ 
        const int minNumberOfArgs = 13;

        /* Max number of args for program, with program name and first param included. */ 
        const int maxNumberOfArgs = 26;

        /* Generic error message. */ 
        const std::string genericErrorMsg = "Pass valid arguments.";

        /**
         * Builds UserSettings from raw arguments provied from user terminal.
         * 
         * Params:
         * int argc - number of arguments.
         * char *argv[] - arguments.
         * 
         * Exceptions:
         * Same as for void ChangeSettings(...)
         * 
         * Returns:
         * UserSettings - UserSettings build from provided arguments.
        */
        Enigma::UserSettings BuildUserSettings(int argc, char *argv[]) noexcept(false);

        /**
         * Takes text and converts it to RotorID.
         * 
         * Params:
         * const char *arg - text to be converted.
         * 
         * Exceptions:
         * If @arg will not be found in sToRoID_Map, then an exception will be thrown.
        */
        Enigma::RotorID sToRoID(const char *arg) noexcept(false);

        /**
         * Takes text and converts it to ReflectorID.
         * 
         * Params:
         * const char *arg - text to be converted.
         * 
         * Exceptions:
         * If @arg will not be found in sToRefID_Map, then an exception will be thrown.
        */
        Enigma::ReflectorID sToRefID(const char *arg) noexcept(false);

        /**
         * Provides name for a new encrypted file.
         * 
         * That is:
         * If "XXX (encrypted)" name is free, then the function will return it.
         * If not, then "XXX (encrypted) (1)" will be checked and presumbly returned.
         * Otherwise, "XXX (encrypted) (2)" will be checked and so on.
         * 
         * Params:
         * const char *orgFp - original file path.
         * 
         * Exceptions:
         * If function will be unable to find free name by 1000 time, then it will throw an exception.
         * 
         * Returns:
         * std::string - free name for a new file.
        */
        std::string provideEncryptedFilepathPretendent(const char *orgFp) noexcept(false);

        /**
         * Prints rotors position of a given Encoder to std::cout.
         * 
         * Params:
         * const Enigma::Encoder& en - encoder with wanted rotors.
        */
        void printRotorsPosition(const Enigma::Encoder& en) noexcept;

        /* Settings used for encryption. */
        Enigma::UserSettings settings;

    public:
        /**
         * Constructor.
         * 
         * Takes raw arguments from terminal and builds settings from them.
         * 
         * Params:
         * int argc - number of arguments
         * char *argv[] - arguments.
         * 
         * Exceptions:
         * If number of arguments is invalid or settings can't be build from these arguments,
         * then an exception will be thrown.
        */
        Encrypter(int argc, char *argv[]) noexcept(false);

        /**
         * Handles -s flag. User communication and encryption.
         * 
         * Params:
         * const char* orgText - text to be encrypted.
        */
        void EncryptString(const char* orgText) noexcept;

        /**
         * Handles -e flag. User communication and encryption.
         * 
         * Params:
         * const char* filePath - file path which copy will be encrypted.
         *
         * Exceptions:
         * If any unrecoverable problem appears during writing or reading (std::ios::bad), or
         * program will not be able to find free file name for saving,  
         * then an exception will be thrown.
        */
        void EncryptFile(const char* filePath) noexcept(false);

        /**
         * Changes encryption settings using raw arguments provied from user terminal.
         * 
         * Params:
         * int argc - number of arguments.
         * char *argv[] - arguments.
         * 
         * Exceptions
         * If rotor positions or rotor ring settings lengths are not equal 1, or
         * If rotors/reflector name is undefined,
         * then an exception will be thrown.
        */
        void ChangeSettings(int argc, char *argv[]) noexcept(false);
    };
}