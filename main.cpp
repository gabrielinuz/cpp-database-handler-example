/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <DatabaseHandler.h>
#include <SqliteDatabaseHandler.h>
#include <IniReader.h>

int main()
{
    /*Another way:*/
    // //INIREADER:
    // /***ReadMe => sin puntero inteligente se hace así:
    //     IniReader* iniReader = new IniReader();
    //  ***/
    // std::shared_ptr<IniReader> iniReader( new IniReader() );
    
    // iniReader->open("configuration.ini");
    // std::string dbPath = iniReader->selectSection("SQLITE")->getValue("path");

    // //Database Handler:
    // std::shared_ptr<DatabaseHandler> dbh(new SqliteDatabaseHandler(dbPath));

    //Database Handler:
    std::shared_ptr<DatabaseHandler> dbh(new SqliteDatabaseHandler());
    dbh->setConfFile("configuration.ini");
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    dbh->execute();

    dbh->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbh->addParameter(1, "Juan");
    dbh->execute();

    dbh->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbh->addParameter(1, "Pedro");
    dbh->execute();

    //ROW DATA:
    dbh->prepareQuery("SELECT * FROM Users WHERE id=?");
    dbh->addParameter(1, "1");
    Row row = dbh->fetch();

    std::cout << "ROW DATA 1" << std::endl;
    std::cout << "id: " << row["id"] << std::endl;
    std::cout << "name: " << row["name"] << std::endl << std::endl;

    dbh->prepareQuery("SELECT * FROM Users WHERE id=?");
    dbh->addParameter(1, "23");
    row = dbh->fetch();

    std::cout << "ROW DATA 2" << std::endl;
    std::cout << "id: " << row["id"] << std::endl;
    std::cout << "name: " << row["name"] << std::endl << std::endl;

    //TABLE DATA:
    dbh->prepareQuery("SELECT * FROM Users");
    Table table = dbh->fetchAll();

    std::cout << "Table DATA row 1:" << std::endl;
    std::cout << "id: " << table[0]["id"] << std::endl;
    std::cout << "name: " << table[0]["name"] << std::endl << std::endl;

    std::cout << "Table DATA row 2:" << std::endl;
    std::cout << "id: " << table[1]["id"] << std::endl;
    std::cout << "name: " << table[1]["name"] << std::endl;

    return 0;
}
