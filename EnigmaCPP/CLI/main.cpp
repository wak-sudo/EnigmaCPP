/**
 * EnigmaCPP
 * Wojciech Kieloch 2023 
*/

#include "Encrypter.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace EnigmaCLI;

void DisplayHelp();

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        try
        {
            std::string com = argv[1];
            if (com == "-e")
            {
                Encrypter Enigma(argc, argv);
                Enigma.EncryptFile(argv[2]);
            }
            else if (com == "-s")
            {
                Encrypter Enigma(argc, argv);
                Enigma.EncryptString(argv[2]);
            }
            else if (com == "-h")
            {
                DisplayHelp();
            }
            else
                DisplayHelp();
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else
        DisplayHelp();
    return 0;
}

/* Displays help (-h argument). */
void DisplayHelp()
{
    const std::string info =
    "Enigma M3 CLI (plug board supported): \n\n \
    -e -> Create encrypted copy of a file \n \
    EnigmaSharpCLI.exe -e [file path] [reflector B/C/ETW] 3x [rotor number I-V] 3x [rotor initial position] + 3x [rotor ring setting] (optional plug board connections max. 13) \n\n \
    -s -> Encrypt string \n \
    EnigmaSharpCLI.exe -s [string] [reflector B/C/ETW] 3x [rotor number I-V] 3x [rotor initial position] + 3x [rotor ring setting] (optional plug board connections max. 13) \n\n \
    -h -> Display this help \n\n \
    Example: \n \
    EnigmaCPP -e text.txt B I II III C B D F G D AZ BC \n";
    std::cout << info << std::endl;
}
