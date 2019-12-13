#include "sql.h"

int SQLIndex::sqlFind(Msg msg,Users users[])
{
    //  pwd=MD5(passwd);
    connect();
    mtsLogin(msg);
    int err=sqlSelect(users);
    close();
    return err;
}

int SQLIndex::sqlFindAll(int uid,Users users[])
{
    //  pwd=MD5(passwd);
    connect();
    mtsAll(uid);
    int err=sqlSelect(users);
    close();
    return err;
}

int SQLIndex::sqlCreate(Msg msg)
{
    //        pwd=MD5(passwd);
    connect();
    mtsRegis(msg);
    int err=sqlUpdate();
    close();
    return err;
}

void SQLIndex::init()
{
    memset(sql,0,sizeof(sql));
    stmt=NULL;
}

void SQLIndex::connect()
{
    init();
    /* Open database */
    int err = sqlite3_open(path, &db);
    if( err ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
}

void SQLIndex::close()
{
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void SQLIndex::mtsAll(int uid)
{
    //        pwd=MD5(passwd);
    char str1[]="SELECT * FROM users WHERE uname != ";
    char str2[sizeof(int)];
    snprintf(str2, sizeof(int), "%d", uid);
    memcpy(sql,str1,strlen(str1));
    memcpy(sql+strlen(str1), str2, strlen(str2));
}

void SQLIndex::mtsLogin(Msg msg)
{
    //      pwd=MD5(passwd);
    char str1[]="SELECT * FROM users WHERE uname = '";
    char str2[]="' AND passwd = '";
    memcpy(sql,str1,strlen(str1));
    memcpy(sql+strlen(str1),msg.Body,msg.ParamSize[0]);
    memcpy(sql+strlen(str1)+msg.ParamSize[0],str2,strlen(str2));
    std::cout<<sql<<std::endl;
    memcpy(sql+strlen(str1)+msg.ParamSize[0]+strlen(str2),msg.Body+msg.ParamSize[0],msg.ParamSize[1]);
    std::cout<<sql<<std::endl;
    std::cout<<msg.ParamSize[1]<<std::endl;
    std::cout<<msg.Body<<std::endl;
    memcpy(sql+strlen(str1)+msg.ParamSize[0]+strlen(str2)+msg.ParamSize[1],"'",1);
    std::cout<<sql<<std::endl;
    std::cout<<msg.ParamSize[0]<<std::endl;
}

void SQLIndex::mtsRegis(Msg msg)
{
    //      pwd=MD5(passwd);
    char str[]="SELECT * FROM users where uname = '";
    memcpy(sql,str,strlen(str));
    memcpy(sql+strlen(str),msg.Body,msg.ParamSize[0]);
    memcpy(sql+strlen(str)+msg.ParamSize[0],"'",1);
    std::cout<<msg.ParamSize[0]<<std::endl;
    std::cout<<sql<<std::endl;
}

int SQLIndex::sqlSelect(Users users[])
{
    int err = sqlite3_prepare_v2(db,sql, -1,&stmt, &sqlErr);
    if( err != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", sqlErr);
        return -1;
    }else{
        int i=0;
        while (sqlite3_step(stmt)==SQLITE_ROW) {
            users[i].uid=sqlite3_column_int(stmt,0);
            strcpy(users[i].uname, (char*)sqlite3_column_text(stmt,1));
            users[i].status=sqlite3_column_int(stmt,3);
            i++;
        }
        std::cout<<sqlite3_changes(db)<<std::endl;//数据库更新行数
        std::cout<<sqlite3_column_name(stmt,0)<<std::endl;//数据库列名
        std::cout<<sqlite3_column_count(stmt)<<std::endl;//数据库列数
        if (i==0)
        {
            fprintf(stdout, "Records can't find\n");
            return 1;
        } else{
            fprintf(stdout, "Records find successfully\n");
        }
    }
    return 0;
}

int SQLIndex::sqlUpdate()
{
    int err = sqlite3_prepare_v2(db,sql, -1,&stmt, &sqlErr);
    if( err != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", sqlErr);
        return -1;
    }else if (sqlite3_changes(db)==0){
        fprintf(stdout, "Records not update\n");
        return 1;
    }
    return 0;
}
