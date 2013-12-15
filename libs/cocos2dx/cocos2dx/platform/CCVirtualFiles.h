#pragma once
#include "cocos2d.h"

struct sqlite3;
struct sqlite3_stmt;

NS_CC_BEGIN

// Access files as blobs in database
class CCVirtualFiles
{
public:
	static void init(const char* asset = nullptr);
	static void close();

	/** Allocates memmory using new[] should be deleted **/
	static void getBlob(const char* virtualPath, void** data, unsigned long* size);

	/** Calculates file size **/
	static unsigned long getBlobSize(const char* virtualPath);

	/** Copies file content to provided allocated memmory **/
	static void getBlobToAllocated(const char* virtualPath, void** data);

	static bool doesFileExists(const char* virtualPath);

private:

	static int s_initialized;
	static sqlite3 *s_db;
	static sqlite3_stmt *s_stmt_select;
};

NS_CC_END
