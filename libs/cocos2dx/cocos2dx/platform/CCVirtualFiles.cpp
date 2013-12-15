#include "cocos2d.h"
#include "CCVirtualFiles.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sqlite3.h>


NS_CC_BEGIN

int CCVirtualFiles::s_initialized = 0;
sqlite3* CCVirtualFiles::s_db = nullptr;
sqlite3_stmt* CCVirtualFiles::s_stmt_select = nullptr;

bool CCVirtualFiles::doesFileExists(const char* key)
{
	init();
	std::string sql_count("select count() from files where path like '");
	sql_count += std::string(key) + "'";

	sqlite3_stmt *stmt;
	int ok = sqlite3_prepare_v2(s_db, sql_count.c_str(), -1, &stmt, NULL);
	ok |= sqlite3_step(stmt);
	int ret = sqlite3_column_int(stmt, 0);
	ok |= sqlite3_finalize(stmt);

	return ret > 0;
}


unsigned long CCVirtualFiles::getBlobSize(const char *key)
{
	std::string sql_size("select length(data) from files where path like '");
	sql_size += std::string(key) + "'";

	assert(s_initialized);

	sqlite3_stmt *stmt;

	int ok = sqlite3_prepare_v2(s_db, sql_size.c_str(), -1, &stmt, NULL);
	ok |= sqlite3_step(stmt);
	unsigned int ret = sqlite3_column_int(stmt, 0);
	ok |= sqlite3_finalize(stmt);


	if (ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
		printf("Error in localStorage.getItem()\n");

	return (unsigned long)ret;
}

void CCVirtualFiles::getBlobToAllocated(const char* virtualPath, void** data)
{
	assert(s_initialized);
	int ok = sqlite3_reset(s_stmt_select);

	ok |= sqlite3_bind_text(s_stmt_select, 1, virtualPath, -1, SQLITE_TRANSIENT);
	ok |= sqlite3_step(s_stmt_select);


	if (ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
		printf("Error in localStorage.getItem()\n");

	const void* result = sqlite3_column_blob(s_stmt_select, 0);
	unsigned int sz = sqlite3_column_bytes(s_stmt_select, 0);
	memcpy(*data, result, sz);
}

void CCVirtualFiles::getBlob(const char* virtualPath, void** data, unsigned long* size)
{
	*size = getBlobSize(virtualPath);
	*data = new char[*size];
	getBlobToAllocated(virtualPath, data);

#if 0
	std::string sql_size("SELECT data FROM files WHERE path LIKE '");
	sql_size += std::string(virtualPath) + "'";
	assert(s_initialized);

	sqlite3_stmt *stmt;

	int ok = sqlite3_prepare_v2(s_db, sql_size.c_str(), -1, &stmt, NULL);
	ok |= sqlite3_step(stmt);

	const void* result = sqlite3_column_blob(s_stmt_select, 0);
	unsigned int sz = sqlite3_column_bytes(s_stmt_select, 0);
	*data = new char[sz];
	memcpy(*data, result, sz);
	ok |= sqlite3_finalize(stmt);
	
	if (ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
		printf("Error in localStorage.getItem()\n");
#endif
}

void CCVirtualFiles::init(const char *fullpath)
{
	if(!s_initialized)
	{
		int ret = 0;
		
		if (!fullpath)
			ret = sqlite3_open("asset.db", &s_db);
		else
			ret = sqlite3_open(fullpath, &s_db);

		// SELECT
		const char *sql_select = "SELECT data FROM files WHERE path=?;";
		ret |= sqlite3_prepare_v2(s_db, sql_select, -1, &s_stmt_select, NULL);

		if( ret != SQLITE_OK ) {
			printf("Error initializing DB\n");
			// report error
		}		
		s_initialized = 1;
	}
}

void CCVirtualFiles::close()
{
	if(s_initialized)
	{
		sqlite3_finalize(s_stmt_select);
		sqlite3_close(s_db);		
		s_initialized = 0;
	}
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

