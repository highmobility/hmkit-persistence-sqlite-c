/*
The MIT License

Copyright (c) 2014- High-Mobility GmbH (https://high-mobility.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "hm_persistence_sqlite.h"
#include <sqlite3.h>
#include <string.h>

#define DATABASE_NAME "hmdata.db"

//PROTOTYPES
void hm_persistence_sqlite_create_tables(sqlite3 *db);
sqlite3* hm_persistence_sqlite_open_database(void);
void hm_persistence_sqlite_close_database(sqlite3 *db);
uint8_t hm_persistence_sqlite_check_cert(uint8_t *serial);

void hm_persistence_sqlite_create_tables(sqlite3 *db){
    const char *pSQL[1];
    char *szErrMsg = 0;
    pSQL[0] = "CREATE TABLE IF NOT EXISTS AccessCert(serial blob(9),cert blob(200),Integer size)";
    sqlite3_exec(db, pSQL[0], NULL, 0, &szErrMsg);
}

sqlite3* hm_persistence_sqlite_open_database(void){
    sqlite3 *db;
    sqlite3_open(DATABASE_NAME, &db);
    hm_persistence_sqlite_create_tables(db);
    return db;
}

void hm_persistence_sqlite_close_database(sqlite3 *db){
    sqlite3_close(db);
}

uint8_t hm_persistence_sqlite_check_cert(uint8_t *serial){

    sqlite3 *db = hm_persistence_sqlite_open_database();

    char *sql = "SELECT cert, size FROM AccessCert WHERE serial = ?";
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    sqlite3_bind_blob(pStmt, 1, serial, 9, SQLITE_STATIC);
    rc = sqlite3_step(pStmt);

    if (rc == SQLITE_ROW) {

    }else{
        hm_persistence_sqlite_close_database(db);
        return 1;
    }

    rc = sqlite3_finalize(pStmt);

    hm_persistence_sqlite_close_database(db);

    return 0;
}

void hm_persistence_sqlite_add_access_cert(uint8_t *serial, uint8_t *cert, uint8_t size){

    SQUNUSED(size);

    if(hm_persistence_sqlite_check_cert(serial) == 1){
        sqlite3 *db = hm_persistence_sqlite_open_database();

        sqlite3_stmt *pStmt;
        char *sql = "INSERT INTO AccessCert(serial,cert) VALUES(?,?)";
        sqlite3_prepare(db, sql, -1, &pStmt, 0);
        sqlite3_bind_blob(pStmt, 1, serial, 9, SQLITE_STATIC);
        sqlite3_bind_blob(pStmt, 2, cert, 178, SQLITE_STATIC);
        sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);

        hm_persistence_sqlite_close_database(db);
    }else{
        sqlite3 *db = hm_persistence_sqlite_open_database();

        sqlite3_stmt *pStmt;
        char *sql = "UPDATE AccessCert(cert) VALUES(?) WHERE serial = ?";
        sqlite3_prepare(db, sql, -1, &pStmt, 0);
        sqlite3_bind_blob(pStmt, 1, cert, 178, SQLITE_STATIC);
        sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);

        hm_persistence_sqlite_close_database(db);
    }


}

void hm_persistence_sqlite_get_access_cert(uint8_t *serial, uint8_t *cert, uint8_t *size){

    sqlite3 *db = hm_persistence_sqlite_open_database();

    char *sql = "SELECT * FROM AccessCert WHERE serial = ?";
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    sqlite3_bind_blob(pStmt, 1, serial, 9, SQLITE_STATIC);
    rc = sqlite3_step(pStmt);

    if (rc == SQLITE_ROW) {
        memcpy(cert, sqlite3_column_blob(pStmt, 1),178);
        *size = 178;
    }

    rc = sqlite3_finalize(pStmt);

    hm_persistence_sqlite_close_database(db);

}

void hm_persistence_sqlite_remove_access_cert(uint8_t *serial){

    sqlite3 *db = hm_persistence_sqlite_open_database();

    sqlite3_stmt *pStmt;
    char *sql = "DELETE from AccessCert WHERE serial = ?";
    sqlite3_prepare(db, sql, -1, &pStmt, 0);
    sqlite3_bind_blob(pStmt, 1, serial, 9, SQLITE_STATIC);
    sqlite3_step(pStmt);
    sqlite3_finalize(pStmt);

    hm_persistence_sqlite_close_database(db);
}
