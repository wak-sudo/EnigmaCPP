/**
 * EnigmaCPP
 * Wojciech Kieloch 2023 
*/

#include "Encrypter.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>

#define MB 1048576
#define KB 1024

using namespace EnigmaCLI;

Encrypter::Encrypter(int argc, char *argv[])
{
    if (argc < minNumberOfArgs || argc > maxNumberOfArgs)
        throw std::runtime_error("Invalid number of arguments.");
    ChangeSettings(argc, argv);
}

void Encrypter::ChangeSettings(int argc, char *argv[])
{
    settings = BuildUserSettings(argc, argv);
}

Enigma::UserSettings Encrypter::BuildUserSettings(int argc, char *argv[])
{
    // Information about argument order can be found in DisplayHelp()

    int numberOfConnections = argc - minNumberOfArgs;
    std::vector<std::string> plugboardConnections(numberOfConnections);
    for (int i = 0; i < numberOfConnections; i++)
        plugboardConnections[i] = argv[i + minNumberOfArgs];

    for (int i = 7; i <= 9; i++) // checks whether rotor positions and ring settings are single character.
        if (argv[i][1] != 0 || argv[i + 3][1] != 0)
            throw std::runtime_error(genericErrorMsg);

    std::vector<Enigma::UserRotor> Rotors = {
        Enigma::UserRotor(sToRID(argv[4]), argv[7][0], argv[10][0]),
        Enigma::UserRotor(sToRID(argv[5]), argv[8][0], argv[11][0]),
        Enigma::UserRotor(sToRID(argv[6]), argv[9][0], argv[12][0])};

    return Enigma::UserSettings(sToRID(argv[3]), Rotors, plugboardConnections);
}

Enigma::RotorID Encrypter::sToRID(const char *arg)
{
    auto it = sToRid_Map.find(std::string(arg));
    if (it == sToRid_Map.end())
        throw std::runtime_error("Invalid conversion from string to RID.");
    return it->second;
}

void Encrypter::printRotorsPosition(const Enigma::Encoder& en) noexcept
{
    auto rotFinal = en.ReturnRotorsPosition(); 
    std::cout << rotFinal[0] << rotFinal[1] << rotFinal[2];
}

void Encrypter::EncryptString(const char *orgText) noexcept
{
    Enigma::Encoder en(settings);
    std::cout << "Creating encrypted message...\n";
    std::string enText = en.EncryptString(orgText);
    std::cout << "Message: \n\n"
              << enText << '\n'
              << std::endl;
    std::cout << "Final rotors position: "; printRotorsPosition(en); std::cout << std::endl;   
}


void Encrypter::EncryptFile(const char *filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.good())
        throw std::runtime_error("Error while reading file.");
    uintmax_t fileLength = std::filesystem::file_size(std::filesystem::path(filePath));
    if (fileLength > 50 * MB)
    {
        std::string ans;
        do
        {
            std::cout << "The file is bigger than 50MB, the encryption can take a while. Do you still wish to continue? [Y/n]:" << std::endl;
            std::cin >> ans;
            if (ans.size() != 1)
                continue;
            ans[0] = std::toupper(ans[0]);
        } while (ans[0] != 'N' && ans[0] != 'Y');
        if (ans[0] == 'N')
        {
            file.close();
            return;
        }
    }

    std::string outFilepath = provideEncryptedFilepathPretendent(filePath);
    std::ofstream outFile(outFilepath, std::ios::binary);

    if(!outFile.good()) throw std::runtime_error("Error while writing to a file.");

    Enigma::Encoder en(settings);

    const unsigned bufferSize = 4 * KB;
    std::vector<char> buffer(bufferSize);

    std::cout << "Creating encrypted copy..." << std::endl;
    
    const uintmax_t noBlocks = fileLength / bufferSize;
    const uintmax_t restofDataSize = fileLength % bufferSize;

    for(int i = 0; i < noBlocks; i++)
    {
        file.read(reinterpret_cast<char *>(buffer.data()), bufferSize);
        outFile << en.EncryptString(std::string(buffer.begin(), buffer.end()));
    }

    if(restofDataSize != 0)
    {
        file.read(reinterpret_cast<char *>(buffer.data()), restofDataSize);
        outFile << en.EncryptString(std::string(buffer.begin(), buffer.begin() + restofDataSize));
    }

    outFile.flush();
    file.close();
    outFile.close();

    std::cout << "Done. File saved under name: " << outFilepath << std::endl;
    std::cout << "Final rotors position: "; printRotorsPosition(en); std::cout << std::endl;   
}

std::string Encrypter::provideEncryptedFilepathPretendent(const char *orgF)
{
    std::ifstream fileTester;
    std::string orgFilepath(orgF);
    size_t extDot = orgFilepath.rfind('.');

    std::string ext = "";
    std::string fileName;

    if (extDot != std::string::npos)
    {
        ext = orgFilepath.substr(extDot);
        fileName = orgFilepath.substr(0, extDot) + " (encrypted)";
    }
    else
    {
        fileName = orgFilepath + " (encrypted)";
    }

    std::string pretendent = fileName + ext;

    fileTester.open(pretendent);
    for (int i = 1; fileTester.good(); i++)
    {
        fileTester.close();
        if(i == 1000) throw std::runtime_error("Error at name searching.");
        pretendent = fileName + " (" + std::to_string(i) + ')' + ext;
        fileTester.open(pretendent);
    }
    fileTester.close();
    return pretendent;
}