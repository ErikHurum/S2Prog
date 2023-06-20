//---------------------------------------------------------------------------

#ifndef SQLiteAccessorH
#define SQLiteAccessorH

#include <string>
#ifdef ANWIN
#include <System.hpp>
#include "LiteCall.hpp"

using namespace std;
#endif
//---------------------------------------------------------------------------

/// A useful but admittedly arbitrary buffer size define
#define SQL_SMALL_QUERY_BUFFSZ 1024

/// A useful but admittedly arbitrary buffer size define
#define SQL_LARGE_QUERY_BUFFSZ 16384


#define DATABASE_READ_SUCCESS 0

#define DATABASE_READ_ERROR 1

// Tue, 01 Jan 2013 00:00:00 GMT. No dates can possibly be lower, since the
// the version of ANWin with a database was unreleased at that date:
#define DATABASE_MIN_DATE 1356998400



/// Adapter class for accessing the SQLite 3 database. An object of this class
/// is used by all the Repository classes for reading and writing data to the
/// database.
///
typedef struct sqlite3_stmt sqlite3_stmt;
typedef struct sqlite3 sqlite3;
class SQLiteAccessor {

private:
	string dbFilePath;
	string errorMessage;
    TSQLite3API *SqlAPI;

public:
	SQLiteAccessor(const char *databaseFilePath);
	~SQLiteAccessor();

	/// Fills in string with the last error message
	void GetErrorMessage(string& dest);

	/// Runs a query in UTF8 encoding and calls the rowParserCallback function for each row in the result set.
	///
	/// @param 		sqlStmt	The SQL query to execute.
	/// @param		rowParserCallback callback function to invoke for each row read from the database.
	/// @param      contextToPassToCallback a piece of data to pass into rowParserCallback each time it is called - may be NULL.
	/// @return 	0 if all OK, 1 otherwise. Use the GetErrorMessage() function to get a description of the error - may be NULL.
	int RunQuery(const char *sqlStmt, void (*rowParserCallback)(void *context, sqlite3_stmt *stmtHandle), void *contextToPassToCallback);


	// Time and date convenience functions:
	static void ConvertToDateTimeString(double unixTimestamp, AnsiString& dest);
	static void ConvertToDateTimeStringWithCutoff(double unixTimestamp, AnsiString& dest, double minTimestamp, AnsiString replacementStr, bool toLocalTime = false);
	static void ConvertToTimeString(double unixTimestamp, AnsiString& dest);
	static void ConvertToDateString(double unixTimestamp, AnsiString& dest);
	static TDateTime* ConvertToTDateTime(const wchar_t* sqlite3DateTime);

protected:
	void GetLastDetailedSQLiteError(TSQLite3Db* connection, string& userMessage, string& dest);
};

#endif
