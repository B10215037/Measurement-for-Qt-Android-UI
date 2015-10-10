#include "Sqlite.h"

Sqlite::Sqlite() : QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "Mdb"))
{
	setDatabaseName("Mdb");

	if(open())
	{
		QSqlQuery query(this->database("Mdb"));

		query.exec(
			"CREATE TABLE GROUPS ("
				"Id INTEGER,"
				"Name CHAR(10) NOT NULL UNIQUE,"
				"Amount INTEGER NOT NULL,"
				"PRIMARY KEY(Id)"
			");"
		);
		query.exec(
			"CREATE TABLE PEOPLE ("
				"Id INTEGER,"
				"Name CHAR(10) NOT NULL UNIQUE,"
				"Bust REAL,"
				"Length REAL,"
				"SleeveLength REAL,"
				"GroupId TEXT,"
				"ProjectId TEXT,"
				"PicturePath TEXT,"
				"PRIMARY KEY(Id)"
			");"
		);
		query.exec(
			"CREATE TABLE PROJECTS ("
				"Id INTEGER,"
				"Name CHAR(10) NOT NULL UNIQUE,"
				"Amount INTEGER NOT NULL,"
				"IconPath TEXT,"
				"Description TEXT,"
				"PRIMARY KEY(Id)"
			");"
		);

		query.exec("INSERT INTO GROUPS(Name, Amount) VALUES('台北人', 2);");
		query.exec("INSERT INTO GROUPS(Name, Amount) VALUES('JA', 49);");
		query.exec("INSERT INTO GROUPS(Name, Amount) VALUES('CN', 123);");

		query.exec("INSERT INTO PEOPLE(Name, GroupId, ProjectId) "
			"VALUES('台北人', '<1><3>', '<2><3>');");
		query.exec("INSERT INTO PEOPLE(Name, Bust, Length, GroupId, ProjectId) "
			"VALUES('Andy', 149.1, 56.7, '<2>', '<1>');");
		query.exec("INSERT INTO PEOPLE(Name, Bust, Length, SleeveLength, GroupId, ProjectId) "
			"VALUES('abc', 2, 4.56, 79, '<3>', '<1><2><3>');");

		query.exec("INSERT INTO PROJECTS(Name, Amount, Description) VALUES('戲服', 2, 'to show !?');");
		query.exec("INSERT INTO PROJECTS(Name, Amount, Description) VALUES('系外套', 49, '保暖');");
		query.exec("INSERT INTO PROJECTS(Name, Amount) VALUES('T-shirt', 123);");
	}
}
