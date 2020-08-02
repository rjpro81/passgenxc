DROP TABLE IF EXISTS userPasswords;
DROP TABLE IF EXISTS userLogin;
DROP TABLE IF EXISTS masterPassword;

CREATE TABLE IF NOT EXISTS masterPassword (
  mPasswordId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  mPassword VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS userLogin (
  userId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  userName VARCHAR(100) NOT NULL,
  userPassword VARCHAR(100) NOT NULL,
  mPasswordId INT NOT NULL,
  FOREIGN KEY (mPasswordId) REFERENCES masterPassword ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS userPasswords (
  userPasswordId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  Password VARCHAR(100) NOT NULL, 
  Description VARCHAR(100) NOT NULL,
  userId INTEGER NOT NULL,
  FOREIGN KEY (userId) REFERENCES userLogin ON DELETE CASCADE
);



