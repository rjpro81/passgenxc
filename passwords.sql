DROP TABLE userPassword;
DROP TABLE userLogin;
DROP TABLE masterPass;

CREATE TABLE masterPass (
  masterPassId INT NOT NULL GENERATED ALWAYS AS IDENTITY,
  masterPassword VARCHAR(50) NOT NULL,
  PRIMARY KEY (masterPassId, masterPassword)
);

CREATE TABLE userLogin (
  userName VARCHAR(50) NOT NULL,
  userPassword VARCHAR(50) NOT NULL,
  masterPassword VARCHAR(50) NOT NULL,
  masterPassId INT NOT NULL,
  PRIMARY KEY (userName, userPassword),
  FOREIGN KEY (masterPassId, masterPassword) REFERENCES masterPass ON DELETE CASCADE
);

CREATE TABLE userPassword (
  id INT NOT NULL GENERATED ALWAYS AS IDENTITY,
  userName VARCHAR(50) NOT NULL,
  userPassword VARCHAR(50) NOT NULL,
  Password VARCHAR(100) NOT NULL, 
  Description VARCHAR(100) NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (userName, userPassword) REFERENCES userLogin ON DELETE CASCADE
);



