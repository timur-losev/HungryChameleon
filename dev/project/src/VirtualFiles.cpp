#include "Precompiled.h"
#include "VirtualFiles.h"

#include <sqlite3.h>

int VirtualFiles::s_initialized = 0;
sqlite3* VirtualFiles::s_db = nullptr;
sqlite3_stmt* VirtualFiles::s_stmt_select = nullptr;

bool VirtualFiles::doesFileExists(const char* key)
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


unsigned long VirtualFiles::getBlobSize(const char *key)
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

void VirtualFiles::getBlobToAllocated(const char* virtualPath, void** data)
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

void VirtualFiles::getBlob(const char* virtualPath, void** data, unsigned long* size)
{
    *size = getBlobSize(virtualPath);
    *data = new char[*size];
    getBlobToAllocated(virtualPath, data);
}

void VirtualFiles::init(const char *fullpath)
{
    if (!s_initialized)
    {
        int ret = 0;
        std::string file;

        if (!fullpath)
            file = "asset.db";
        else
            file = fullpath;

#ifndef _WIN32
        NSURL* url = [[NSBundle mainBundle] URLForResource:@"asset" withExtension:@"db"];
        file = [[url absoluteString] UTF8String];
#endif
        ret = sqlite3_open(file.c_str(), &s_db);
        // SELECT
        const char *sql_select = "SELECT data FROM files WHERE path=?;";
        ret |= sqlite3_prepare_v2(s_db, sql_select, -1, &s_stmt_select, NULL);

        if (ret != SQLITE_OK) {
            printf("Error initializing DB\n");
            // report error
        }
        s_initialized = 1;
    }
}

void VirtualFiles::close()
{
    if (s_initialized)
    {
        sqlite3_finalize(s_stmt_select);
        sqlite3_close(s_db);
        s_initialized = 0;
    }
}
