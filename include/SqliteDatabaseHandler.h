/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef SQLITE_DATABASE_HANDLER_H
#define SQLITE_DATABASE_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include <DatabaseHandler.h>
#include <IniReader.h>

/*Row and Table are synonyms for C++ STL structures.
defined in the pure virtual class DatabaseHandler*/
class SqliteDatabaseHandler : public DatabaseHandler
{
    private:
        sqlite3* pDB;
        sqlite3_stmt* stmt;
        bool errorStatus;
        Row row;
        Table table;
        std::string columnName;
        std::string columnValue;
        int columnCount;
        std::shared_ptr<IniReader> iniReader;

        void openDb(std::string dbPath)
        {
            errorStatus = false;

            int iReturn = sqlite3_open(dbPath.c_str(), &pDB);
            if (iReturn != SQLITE_OK) 
            {  
                errorStatus = true;
                std::cerr << "Error open DB " << sqlite3_errmsg(pDB) << std::endl; 
                exit(-1);
            }
            stmt = nullptr;
        }

    public:
        SqliteDatabaseHandler()
        {
            this->iniReader = std::make_shared<IniReader>();
        }
        
        SqliteDatabaseHandler(std::string dbPath)
        {
            this->openDb(dbPath);
        }

        ~SqliteDatabaseHandler()
        {
            sqlite3_finalize(stmt);
            sqlite3_close(pDB);
        }

        void setConfFile(std::string confFilePath)
        {
            iniReader->open("configuration.ini");
            std::string dbPath = iniReader->selectSection("SQLITE")->getValue("path");
            this->openDb(dbPath);         
        }

        void prepareQuery( std::string query )
        {
            int iReturn = sqlite3_prepare_v2(pDB, query.c_str(), query.size() + 1, &stmt, 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; sqlite3_close(pDB); exit(-1); }
        }

        void addParameter( int index, std::string value )
        {
            int iReturn = sqlite3_bind_text(stmt, index, value.c_str(), value.size(), 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; exit(-1); }
        }

        void execute()
        {
            sqlite3_step(stmt);
        }

        Row fetch()
        {
            row.clear();
            sqlite3_step(stmt);
            columnCount = sqlite3_column_count(stmt);
            for( int i = 0; i < columnCount; i++ )
            {
                columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                try
                {
                    columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                }
                catch(const std::exception& e)
                {
                    columnValue = "";
                }
                
                row[columnName] = columnValue;           
            }   
            return row; 
        }

        Table fetchAll()
        {
            table.clear();
            row.clear();
            columnCount = sqlite3_column_count(stmt);
            while(sqlite3_step(stmt)==SQLITE_ROW)
            {
                row.clear();
                for( int i = 0; i < columnCount; i++ )
                {
                    columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                    columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                    row[columnName] = columnValue;
                } 
                table.push_back(row);
            }

            return table;
        }

        bool getErrorStatus()
        { 
            return this->errorStatus; 
        } 
};

#endif // SQLITE_DATABASE_HANDLER_H
