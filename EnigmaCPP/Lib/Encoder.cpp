/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#include "EnigmaCPP.h"
#include "SettingsConversion.h"

using namespace Enigma;

Encoder::Encoder(const UserSettings& USettings)
{
    this->Settings = SettingsConversion::ConvertToEnigmaSettings(USettings);
}

void Encoder::setNewSettings(const UserSettings& nSettings)
{
    this->Settings = SettingsConversion::ConvertToEnigmaSettings(nSettings);
}

std::string Encoder::EncryptString(const std::string& origninalText) noexcept
{
    std::string encryptedText = "";
    for (int i = 0; i < origninalText.length(); i++)
    {
        char letter = std::toupper(origninalText[i]);
        if (letter >= 'A' && letter <= 'Z')
            encryptedText += EncryptChar(letter);
    }
    return encryptedText;
}

std::vector<char> Encoder::ReturnRotorsPosition() const noexcept
{
    std::vector<char> res = {
        (char)(Settings.Rotors[0].Position + 'A'),
        (char)(Settings.Rotors[1].Position + 'A'),
        (char)(Settings.Rotors[2].Position + 'A'),
    };
    return res;
}

char Encoder::EncryptChar(char letter) noexcept
{
    StepRotors();

    letter = Settings.PlugboardConnections[letter];

    // Pre-reflector encoding
    for (int i = Settings.Rotors.size() - 1; i >= 0; i--)
        letter = EnigmaPreRefEncoding(letter, i);

    letter = Settings.ReflectorAlphabet[letter - 'A'];

    // Post-reflector encoding
    for (int i = 0; i < Settings.Rotors.size(); i++)
        letter = EnigmaPostRefEncoding(letter, i);

    letter = Settings.PlugboardConnections[letter];

    return letter;
}

char Encoder::EnigmaPreRefEncoding(char originalCharacter, int encryptionSet) const noexcept
{
    int index = Mod((originalCharacter - 'A') + Settings.Rotors[encryptionSet].Position - Settings.Rotors[encryptionSet].RingSetting);

    char modifiedChar = Settings.Rotors[encryptionSet].AlphabetRing[index];

    index = Mod((modifiedChar - 'A') + Settings.Rotors[encryptionSet].RingSetting - Settings.Rotors[encryptionSet].Position);

    return (char)(index + 'A');
}

char Encoder::EnigmaPostRefEncoding(char originalCharacter, int encryptionSet) const noexcept
{
    int index = Mod((originalCharacter - 'A') + Settings.Rotors[encryptionSet].Position - Settings.Rotors[encryptionSet].RingSetting);

    char modifiedChar = (char)(index + 'A');

    index = Mod(Settings.Rotors[encryptionSet].AlphabetRing.find(modifiedChar) + Settings.Rotors[encryptionSet].RingSetting - Settings.Rotors[encryptionSet].Position);

    return (char)(index + 'A');
}

void Encoder::StepRotors() noexcept
{
    if (Settings.Rotors[1].Position == Settings.Rotors[1].Notch)
    {
        // Double step sequence, ex.:
        // ADV -> step -> AEW -> step -> BFX

        Settings.Rotors[1].Position = (Settings.Rotors[1].Position + 1) % alphabetLength;
        Settings.Rotors[0].Position = (Settings.Rotors[0].Position + 1) % alphabetLength;
    }
    else if (Settings.Rotors[2].Position == Settings.Rotors[2].Notch)
    {
        Settings.Rotors[1].Position = (Settings.Rotors[1].Position + 1) % alphabetLength;
    }
    Settings.Rotors[2].Position = (Settings.Rotors[2].Position + 1) % alphabetLength;
}

int Encoder::Mod(int i, int k) noexcept
{
    int reminder = i % k;
    if (reminder >= 0)
        return reminder;
    else
        return reminder + k;
}