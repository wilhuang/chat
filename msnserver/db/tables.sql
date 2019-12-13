CREATE TABLE users (
    uid INTEGER PRIMARY KEY AUTOINCREMENT,
    uname NVARCHAR(36) NOT NULL,
    passwd VARCHAR(128) NOT NULL,
    status INTEGER NOT NULL default 0,
    UNIQUE (uname)
);

CREATE TABLE groups (
    gid INTEGER PRIMARY KEY AUTOINCREMENT,
    gname NVARCHAR(36) NOT NULL default "new group",
    gnum INTEGER NOT NULL default 2,
    createtime datetime NOT NULL
);

PRAGMA FOREIGN_KEYS = ON;

CREATE TABLE groupstousers (
    gtuid INTEGER PRIMARY KEY AUTOINCREMENT,
    gid INTEGER,
    uid INTEGER,
    foreign key(gid) references groups(gid),
    foreign key(uid) references users(uid)
);

CREATE TABLE messages (
    mid INTEGER PRIMARY KEY AUTOINCREMENT,
    message txt NOT NULL,
    sendtime datetime,
    gid INTEGER,
    uid INTEGER,
    foreign key(gid) references groups(gid),
    foreign key(uid) references users(uid)
);