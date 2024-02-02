CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);
CREATE TABLE stocks(user_id INTEGER NOT NULL, symbol TEXT NOT NULL,
                    comp_name TEXT NOT NULL, shares INTEGER,
                    price TEXT, total TEXT);
CREATE UNIQUE INDEX symbol ON stocks (symbol);
CREATE UNIQUE INDEX comp_name ON stocks (comp_name);
CREATE TABLE history(user_id INTEGER NOT NULL, symbol TEXT NOT NULL,
                    comp_name TEXT NOT NULL, shares INTEGER NOT NULL,
                    price TEXT NOT NULL, method TEXT NOT NULL, total TEXT NOT NULL, date_time TEXT NOT NULL);


DROP TABLE users;
DROP TABLE stocks;
DROP TABLE history;