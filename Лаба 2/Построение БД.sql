CREATE TABLE Abonent ( --АБОНЕНТ
    tel VARCHAR(10) PRIMARY KEY
                     CHECK (tel LIKE '8 ___ ___ __-__'),
    FIO VARCHAR (50) NOT NULL
);

CREATE TABLE Library ( --БИБЛИОТЕКА
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Address VARCHAR(100) NOT NULL,
Name VARCHAR(25) NOT NULL UNIQUE,
Time INTEGER 
     CHECK (Time BETWEEN 1 AND 12)
);  

CREATE TABLE Work_Days ( --ДНИ РАБОТЫ
  ID INTEGER,
  Day INTEGER
      CHECK (Day BETWEEN 1 AND 7),
  FOREIGN KEY(ID) REFERENCES Library(ID) ON DELETE CASCADE    
);

CREATE TABLE Vydacha ( --ВЫДАЧА
 ID INTEGER PRIMARY KEY AUTOINCREMENT,
 Library INTEGER,
 CHTO_VYDAETSYA INTEGER NOT NULL UNIQUE,
 tel VARCHAR(10)      NOT NULL
                     CHECK (tel LIKE '8 ___ ___ __-__'),
 Srok INTEGER NOT NULL,
 FOREIGN KEY(tel) REFERENCES Abonent(tel) ON DELETE CASCADE,
 FOREIGN KEY(Library) REFERENCES Library(ID) ON DELETE CASCADE,
 FOREIGN KEY(CHTO_VYDAETSYA) REFERENCES Journal(ID) ON DELETE CASCADE                    
);

Create Table Organization ( --ОРГАНИЗАЦИЯ
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Name VARCHAR(150) NOT NULL UNIQUE,
Address VarChar(100) UNIQUE,
Web VARCHAR(100) 
);

Create Table Journal ( --ЖУРНАЛ
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Name VARCHAR(100) NOT NULL UNIQUE,
Publisher INTEGER,
Start_Date DATE NOT NULL,
End_Date DATE,
CHECK (Start_Date <= End_Date)
FOREIGN KEY(Publisher) REFERENCES Organization(ID) ON DELETE CASCADE
);

Create Table Lib_Jour ( --ПРОМЕЖУТОЧНАЯ ТАБЛИЦА БИБЛИОТЕЧНЫЙ ЖУРНАЛ
ID_Lib INTEGER,
ID_Jour INTEGER,
FOREIGN KEY(ID_Lib) REFERENCES Library(ID) ON DELETE CASCADE,
FOREIGN KEY(ID_Jour) REFERENCES Journal(ID) ON DELETE CASCADE
);

Create Table Subgroup ( --ПОДРАЗДЕЛЕНИЯ
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Name VARCHAR(150) UNIQUE NOT NULL,
Orgs INTEGER,
Specs VARCHAR(50),
FOREIGN KEY(Orgs) REFERENCES Organization(ID) ON DELETE CASCADE
);

Create Table Conference ( --Конференция
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Name VARCHAR(100) UNIQUE NOT NULL,
City VARCHAR(40),
Date DATE NOT NULL,
Descr TEXT,
Topic VARCHAR(75)
);

Create Table Conf_Org ( --ПРОМЕЖУТОЧНАЯ ТАБЛИЦА ОРГАНИЗАЦИЯ МЕРОПРИЯТИЙ
ID_Org INTEGER,
ID_Conf INTEGER,
FOREIGN KEY(ID_Org) REFERENCES Organization(ID) ON DELETE CASCADE,
FOREIGN KEY(ID_Conf) REFERENCES Conference(ID) ON DELETE CASCADE
);

Create Table Person ( --ПЕРСОНАЛИЯ
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Name VARCHAR(50),
Mail VARCHAR(60) UNIQUE,
Spec VARCHAR(30) NOT NULL,
Degree VARCHAR(20)
);

Create Table Member_Committee ( --ПРОМЕЖУТОЧНАЯ ТАБЛИЦА ЧЛЕН ОРГАНИЗАЦИОННОГО КОМИТЕТА
ID_Pers INTEGER,
ID_Conf INTEGER,
Position VARCHAR(30),
FOREIGN KEY(ID_Pers) REFERENCES Person(ID) ON DELETE CASCADE,
FOREIGN KEY(ID_Conf) REFERENCES Conference(ID) ON DELETE CASCADE
);

Create Table Article ( --СТАТЬЯ
ID INTEGER PRIMARY KEY AUTOINCREMENT,
Rate REAL NOT NULL,
Date Date NOT NULL,
Annotation TEXT,
Content TEXT,
Quotes INTEGER UNIQUE,
Journal INTEGER,
FOREIGN KEY(Journal) REFERENCES Journal(ID) ON DELETE CASCADE
);

Create Table Quotes ( --ЦИТИРОВАНИЯ
ID_Article INTEGER,
ID_Quote INTEGER,
FOREIGN KEY(ID_Article) REFERENCES Article(Quotes) ON DELETE CASCADE,
FOREIGN KEY(ID_Quote) REFERENCES Article(ID) ON DELETE CASCADE
);

Create Table Author ( --АВТОР
ID_Person INTEGER,
ID_Article INTEGER,
ID_Org INTEGER,
FOREIGN KEY(ID_Person) REFERENCES Person(ID) ON DELETE CASCADE,
FOREIGN KEY(ID_Article) REFERENCES Article(ID) ON DELETE CASCADE,
FOREIGN KEY(ID_Org) REFERENCES Subgroup(ID) ON DELETE CASCADE
);