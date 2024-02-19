#include "TSNIncludes.h"
#ifdef ANWIN
	#include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
	#include "ChildUnit.h"
	#include "Anpro_Net.h"
	#include "MainUnit.h"
#endif

#pragma hdrstop

#include "TWCleaningMediaRepository.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



TankWashingCleaningMediaRepository::TankWashingCleaningMediaRepository(void)
{
	LiteQuery = new TLiteQuery(NULL);
	LiteTable = new TLiteTable(NULL);
	try {
		MainForm->WashTrackLiteConnection->Connected = true;
		LiteQuery->Connection 	= MainForm->WashTrackLiteConnection;
		LiteTable->Connection 	= MainForm->WashTrackLiteConnection;

		LiteTable->TableName 	= "CleaningMediaTypes";
		LiteTable->Options->QueryRecCount = true;
		LiteTable->ReadOnly 	= true;
		LiteTable->OrderFields 	= "Id";
		LiteTable->Active 		= true;

		TankWashingCleaningMedia cleaningMedia;
		cleaningMedia.Name = "Not selected";
		CreateOrUpdateFromConfiguration(cleaningMedia);
	}
	__finally{
	}
}

TankWashingCleaningMediaRepository::~TankWashingCleaningMediaRepository(void)
{
	try {
		LiteQuery->Free();
		LiteTable->Free();
	}
	__finally{
	}
}

bool TankWashingCleaningMediaRepository::Create(TankWashingCleaningMedia& cleaningMedia)
{

	AnsiString Query("SELECT * FROM CleaningMediaTypes");

	try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Append();
		LiteQuery->FieldByName("Name")->AsAnsiString = cleaningMedia.Name;
		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}



/// Only creates the data if it does not exist in the database already. In the future might also do an actual update.
///
bool TankWashingCleaningMediaRepository::CreateOrUpdateFromConfiguration(TankWashingCleaningMedia& cleaningMedia)
{
	bool exists;
	bool opSuccess;

	opSuccess = ExistsByName(cleaningMedia.Name, exists);

	if (opSuccess) {
		if (!exists) {
			opSuccess = Create(cleaningMedia);
        }
	}
    return opSuccess;
}


bool TankWashingCleaningMediaRepository::ExistsByName(AnsiString cleaningMediaName, bool& exists)
{

	AnsiString Query("SELECT Count(*) AS Count FROM CleaningMediaTypes WHERE Name LIKE ");
	Query.cat_sprintf("'%s'", cleaningMediaName.c_str());

    try {
        LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		exists = bool( LiteQuery->FieldByName("Count")->AsInteger);
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}



bool TankWashingCleaningMediaRepository::ReadAllCleaningMedia(vector<TankWashingCleaningMedia>& dest)
{
    try {
		LiteTable->First();
		while (!LiteTable->Eof) {
			TankWashingCleaningMedia twcm;
			twcm.Id 	= LiteTable->FieldByName("Id")->AsInteger;
			twcm.Name 	= LiteTable->FieldByName("Name")->AsString;
			dest.push_back(twcm);
			LiteTable->Next();
		}
	}
	__finally{
	}
	return true;
}



void TankWashingCleaningMediaRepository::ParseOneRecord(TankWashingCleaningMedia& twcm, TLiteQuery *LiteQuery)
{
	twcm.Id = LiteQuery->FieldByName("Id")->AsInteger;
	twcm.Name =LiteQuery->FieldByName("Name")->AsString;
}




