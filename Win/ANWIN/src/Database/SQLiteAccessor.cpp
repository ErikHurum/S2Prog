//---------------------------------------------------------------------------

#pragma hdrstop

#include <iostream>
#include <string>

#include "SQLiteAccessor.h"
#include "Litecall.hpp"

using namespace std;
using namespace Litecall;

//---------------------------------------------------------------------------
#pragma package(smart_init)


/// ***************************************************
/// Public functions
/// ***************************************************

SQLiteAccessor::SQLiteAccessor(const char *databaseFilePath)
{
	SqlAPI = new TSQLite3API;
	//SqlAPI->Direct = true;
	SqlAPI->Initialize();

	if (databaseFilePath == NULL) {
        throw "missing databaseFilePath parameter";
	}

	dbFilePath = string(databaseFilePath);
	errorMessage = "";
}


SQLiteAccessor::~SQLiteAccessor()
{
	delete SqlAPI;
}


void SQLiteAccessor::GetErrorMessage(string& dest)
{
	dest = errorMessage;
}

int SQLiteAccessor::RunQuery(const char *sqlStmt, void (*rowParserCallback)(void *context, sqlite3_stmt *stmtHandle), void *contextToPassToCallback)
{
	int returnValue = DATABASE_READ_SUCCESS;
	errorMessage = "";

	// Get DB connection
	TSQLite3Db *conn;

	//int status = sqlite3_open16(dbFilePath.c_str(), &conn);
	int status = SqlAPI->sqlite3_open_v2((char*)dbFilePath.c_str(), (void*&)conn, SQLITE_OPEN_READWRITE, (char*)NULL);

	if (status == SQLITE_OK && conn != NULL) {
		// Prepare the query on the database for running
		sqlite3_stmt *stmtHandle = NULL;
		const char *pzTail = NULL;            	// pzTail is not really used here, but passed in as a paremeter
	  //typedef int __cdecl (*Tsqlite3_prepare_v2)(void * db, char * zSql, int nByte, /* out */ void * &ppStmt, /* out */ void * &pzTail);
		status = SqlAPI->sqlite3_prepare_v2((void*)conn, (char*)sqlStmt, strlen(sqlStmt), (void*&)stmtHandle, (void*&)pzTail);

		if (status == SQLITE_OK && stmtHandle != NULL) {

			// Get each result row from the database, and invoke the callback for each row
			status = SqlAPI->sqlite3_step(stmtHandle);

			while (status == SQLITE_ROW)
			{
				if (rowParserCallback != NULL) {
					rowParserCallback(contextToPassToCallback, stmtHandle);
				}
				status = SqlAPI->sqlite3_step(stmtHandle);
			}

			if (status == SQLITE_DONE) {
                SqlAPI->sqlite3_finalize(stmtHandle);
			}
			else
			{
				string userMessage("Error on sqlite3_step(...)");
				GetLastDetailedSQLiteError(conn, userMessage, errorMessage);
				returnValue = DATABASE_READ_ERROR;
			}
		}
		else
		{
			string userMessage("Error on sqlite3_prepare(...)");
			GetLastDetailedSQLiteError(conn, userMessage, errorMessage);
			returnValue = DATABASE_READ_ERROR;    /* TODO -oEHS -cSerious : Multiple failures during startup */
		}
	}
	else
	{
		string userMessage("Error on sqlite3_open16(...)");

		userMessage += "Failed to open database at path " + '\\';
		userMessage += dbFilePath;
		userMessage += '\n';

		GetLastDetailedSQLiteError(conn, userMessage, errorMessage);
		returnValue = DATABASE_READ_ERROR;
	}

	SqlAPI->sqlite3_close(conn);
	return returnValue;
}


/// ***************************************************
/// Protected functions
/// ***************************************************

/// Get a ready formatted string with the last error message that occured in SQLite3
///
void SQLiteAccessor::GetLastDetailedSQLiteError(TSQLite3Db* connection, string& userMessage, string& dest)
{
	char strBuff[1024];
	int lastErrorCode  = SqlAPI->sqlite3_errcode(connection);
	const char* errMsg = SqlAPI->sqlite3_errmsg(connection);

	// Ugly string appending ..
	dest = "";
	dest += userMessage;
	dest += ": ";
	dest += errMsg;
	dest += " (err.code=";

	sprintf(strBuff, "%d)\n", lastErrorCode);
	dest += strBuff;
}




TDateTime* SQLiteAccessor::ConvertToTDateTime(const wchar_t* sqlite3DateTime)
{
	TDateTime* retval = NULL;

	if (sqlite3DateTime != NULL) {
		UnicodeString dateStr(sqlite3DateTime);

		// SQLite3 date strings look like this (string indexes added underneath)
		// YYYY-MM-DD HH:MM:SS.SSS format
		// 2013-01-29 12:01:02.000 example date
		// 1  4 6  9  12 15 18 21  pascal indexing

		unsigned short year = (unsigned short) dateStr.SubString(1,4).ToInt();
		unsigned short month = (unsigned short) dateStr.SubString(6,2).ToInt();
		unsigned short day = (unsigned short) dateStr.SubString(9,2).ToInt();
		unsigned short hour = (unsigned short) dateStr.SubString(12,2).ToInt();
		unsigned short minute = (unsigned short) dateStr.SubString(15,2).ToInt();
		unsigned short second = (unsigned short) dateStr.SubString(18,2).ToInt();
		unsigned short ms = 0;

		retval = new TDateTime(year, month, day, hour, minute, second, ms);
	}

	return retval;
}




void SQLiteAccessor::ConvertToDateTimeString(double unixTimestamp, AnsiString& dest)
{
	double secInDay = 86400;
	double unixTSDays = (double)unixTimestamp / secInDay;
	TDateTime unixEpoch(1970, 1, 1, 0, 0, 0, 0);

	TDateTime date(double(unixEpoch) + unixTSDays);
	dest = date.DateTimeString();
}



void SQLiteAccessor::ConvertToDateString(double unixTimestamp, AnsiString& dest)
{
	double secInDay = 86400;
	double unixTSDays = (double)unixTimestamp / secInDay;
	TDateTime unixEpoch(1970, 1, 1, 0, 0, 0, 0);

	TDateTime date(double(unixEpoch) + unixTSDays);
	dest = date.DateString();
}


/// Same a ConvertToDateTimeString, but returns the "replacementString" if the timestamp is less than "minTimeStamp".
/// Useful for displaying eg "--:--" for dates which have not been set yet, are essentially NULL, etc.
///
/// @param toLocalTime Set this to true to convert to local time zone, otherwise the time returned will be UTC (or whatever time zone to input time stamp is).
///
void SQLiteAccessor::ConvertToDateTimeStringWithCutoff(double unixTimestamp, AnsiString& dest, double minTimestamp, AnsiString replacementStr, bool toLocalTime)
{
	if (unixTimestamp <= minTimestamp)
	{
		dest = replacementStr;
	}
	else if (toLocalTime == false)
	{
		SQLiteAccessor::ConvertToDateTimeString(unixTimestamp, dest);
	}
	else
	{
		long assumedUTCTime = (long) unixTimestamp;
		tm *localTm = localtime(&assumedUTCTime);

		TDateTime convDT(localTm->tm_year + 1900,
						 localTm->tm_mon + 1,
						 localTm->tm_mday,
						 localTm->tm_hour,
						 localTm->tm_min,
						 localTm->tm_sec,
						 0);
		dest = convDT.DateTimeString();
	}
}



void SQLiteAccessor::ConvertToTimeString(double unixTimestamp, AnsiString& dest)
{
	double secInDay = 86400;
	TDateTime baseDay(1970, 1, 1, 0, 0, 0, 0);
	TDateTime calcTime(double(baseDay) + (unixTimestamp / secInDay));

	dest = calcTime.TimeString();
}


