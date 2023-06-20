//---------------------------------------------------------------------------

#pragma hdrstop

#include "RegistryUtility.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


RegistryUtility::RegistryUtility()
{
	registryKeyBasePath = L"\\software\\Scanjet Ariston\\AnWin\\";
	registryKeyName = L"\\software\\Scanjet Ariston\\AnWin\\1.0";

	registry = new TRegistry;
	registry->RootKey = HKEY_LOCAL_MACHINE;
	registry->Access = KEY_WRITE | KEY_READ;

}


RegistryUtility::~RegistryUtility()
{
	if (registry != 0) {
		delete registry;
	}
}


/// Determines if config settings exist or not in the windows registry.
///
/// If true then user may delete or otherwise modify settings, but if false
/// then the user should be prevented from doing changes to settings.
///
bool RegistryUtility::SettingsKeyExists()
{
	return (registry->KeyExists(RegistryKeyName));
}


/// Removes all settings stored in the Windows registry
///
void RegistryUtility::DeleteSettings()
{
	// Fail if not exists
	if (! registry->KeyExists(RegistryKeyName)) {
		TVarRec param[] = { RegistryKeyName };
		throw new Exception(L"Registry key \"%s\" does not exist", param, 1 );
	}

	if (! registry->DeleteKey(RegistryKeyName)) {
		throw new Exception(L"Failed to delete group key");
	}
}


/// Copy software settings from original reg key to a new key
///
void RegistryUtility::CopySettings(const UnicodeString& sourceKey, const UnicodeString& destinationKey)
{
	// Fail if source key does not exist
	if (! registry->KeyExists(sourceKey)) {
		TVarRec param[] = { sourceKey };
		throw new Exception(L"Source registry key \"%s\" does not exist.", param, 1 );
	}

	// Fail if destination already exists
	if (registry->KeyExists(destinationKey)) {
		TVarRec param[] = { destinationKey };
		throw new Exception(L"Destination registry key \"%s\" already exists, it must be deleted first.", param, 1 );
	}

	// Copy key, don't delete source key.
	registry->MoveKey(sourceKey, destinationKey, false);
	registry->CloseKey();	// Destination key has been opened, so close it.
}


/// TBD - upgrade active settings from old version of ANWin to the version
/// of the currently running application.
void RegistryUtility::UpgradeSettings(int fromVersion, int toVersion)
{
	throw new Exception(L"Not implemented yet");
	//int currentVersion = fromVersion;

	//while (currentVersion != toVersion)
	//{

	//}
}

