/**
 * LibEnigmaCPP
 * Wojciech Kieloch 2023 
*/

#include "EnigmaCPP.h"
#include "SettingsConversion.h"

using namespace Enigma;

bool UserSettings::CanBeConverted() const
{
    try
    {
        auto test = SettingsConversion::ConvertToEnigmaSettings(*this);
        return true;
    }
    catch(...)
    {
        return false;
    }
}