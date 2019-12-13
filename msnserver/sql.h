#ifndef SQL_H
#define SQL_H

#include <string.h>

#include <string>
#include <iostream>

#include "sqlite3.h"
#include "include/tip.h"


using namespace std;

typedef struct
{
    int  uid;
    char  uname[36];
    int status;
}Users;

class SQLIndex {
public:
    const char *sqlErr;
    int sqlFind(Msg msg,Users users[]);
    int sqlCreate(Msg msg);
    int sqlFindAll(int uid,Users users[]);

private:
    void init();
    // 连接sql
    void connect();
    // 关闭数据库连接并清空缓存
    void close();
    //msg转sql
    void mtsLogin(Msg msg);
    void mtsAll(int uid);
    void mtsRegis(Msg msg);
    //查找
    int sqlSelect(Users users[]);
    int sqlUpdate();
    char sql[100];
    sqlite3 *db;
    const char *path = "chat.db";
    sqlite3_stmt *stmt;
};

//class SQLite {
//public :
//       sqlfind(std::string table, std::string uname, std::string passwd)

//}

//static int callback(void *NotUsed, int argc, char **argv, char **azColName){
//        int i;
//        for(i=0; i<argc; i++){
//                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//        }
//        printf("\n");
//        return 0;
//}



//int sqlfind()
//{
////        pwd=MD5(passwd);
//        sqlite3 *db;
//        char *zErrMsg = 0;
//        int rc;
//        char *sql;

//        /* Open database */
//        rc = sqlite3_open("chat.db", &db);
//        if( rc ){
//                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//                exit(0);
//        }else{
//                fprintf(stderr, "Opened database successfully\n");
//        }
//        //sql语句
//        sql = "SELECT * from hello";

//        /* Execute SQL statement */
//        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//        if( rc != SQLITE_OK ){
//                fprintf(stderr, "SQL error: %s\n", zErrMsg);
//                sqlite3_free(zErrMsg);
//        }else{
//                fprintf(stdout, "Records created successfully\n");
//        }
//        sqlite3_close(db);
//        return 0;
//}

#endif // SQL_H
