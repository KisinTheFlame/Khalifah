DROP TABLE IF EXISTS user;
CREATE TABLE user (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    username        VARCHAR(20),
    password        VARCHAR(20),
    password_salt   VARCHAR(20)
);
