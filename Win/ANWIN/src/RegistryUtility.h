//---------------------------------------------------------------------------

#ifndef RegistryUtilityH
#define RegistryUtilityH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Win.Registry.hpp>

// Note: code is documented with Doxygen compatible comments

class RegistryUtility
{
private:
	/// Name of the registry key where active software settings are stored minus the ANWin version number.
	UnicodeString registryKeyBasePath;

	/// Name of the registry key where active software settings are stored.
	UnicodeString registryKeyName;

	/// API interface object to the windows registry.
	TRegistry *registry;


public:

	RegistryUtility();

	~RegistryUtility();

	bool SettingsKeyExists();

	void DeleteSettings();

	void CopySettings(const UnicodeString& sourceKey, const UnicodeString& destinationKey);

	void UpgradeSettings(int fromVersion, int toVersion);

	/// Name of the registry key where active software settings are stored.
	///
	__property UnicodeString RegistryKeyName = { read=registryKeyName };

	/// Name of the registry key where active software settings are stored, minus the ANWin version number
	///
	__property UnicodeString RegistryKeyBasePath = { read=registryKeyBasePath };
};

#endif

