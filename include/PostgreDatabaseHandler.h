/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef POSTGRE_DATABASE_HANDLER_H
#define POSTGRE_DATABASE_HANDLER_H

#include "libpq-fe.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include <DatabaseHandler.h>
#include <IniReader.h>


/*Row and Table are synonyms for C++ STL structures.
defined in the pure virtual class DatabaseHandler*/
class PosgreSQLDatabaseHandler : public DatabaseHandler
{
    private:
        const char* host ;
        const char* dataBase ;
        const char* port ;
        const char* user ;
        const char* passwd ;
        bool isError ;
        PGconn* cnn ;
        PGresult* result ;
        bool connected ;
        std::string qSQL ;
        void ReadConfig() ;

        int referenceCounter ;
        bool implemented ;
        
    public:
        PosgreSQLDatabaseHandler() ;
        virtual ~PosgreSQLDatabaseHandler() ;
        virtual bool getErrorStatus() ;
        virtual void prepareQuery( std::string query ) ;
        virtual void addParameter( int key, std::string value ) ;
        virtual void execute() ;
        virtual Row fetch() ;
        virtual Table fetchAll() ;

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance() ;
        void release() ;

    private:
        const char* host ;
        const char* dataBase ;
        const char* port ;
        const char* user ;
        const char* passwd ;
        bool isError ;
        PGconn* cnn ;
        PGresult* result ;
        bool connected ;
        std::string qSQL ;
        void ReadConfig() ;

        int referenceCounter ;
        bool implemented ;
};

PosgreSQLDatabaseHandler::PosgreSQLDatabaseHandler () {
    // ReadConfig() ;

    cnn = NULL ;
    result = NULL ;
    qSQL = "" ;

	cnn = PQsetdbLogin( "127.0.0.1" ,
                        "5432" , NULL , NULL ,
                        "compset" , 
                        "postgres" ,
                        "root");
                        
    if (PQstatus(cnn) != CONNECTION_BAD) {
        connected = true ;
        result = PQexec(cnn, "");
        isError = false ;
	} else {
		PQfinish( cnn ) ;
		connected = false ;
        isError = true ;
	}
}

PosgreSQLDatabaseHandler::~PosgreSQLDatabaseHandler() {
	if ( connected ) {
    	PQclear( result ) ;
    	PQfinish( cnn ) ;
	}
}

void PosgreSQLDatabaseHandler::prepareQuery( std::string query ) {
    qSQL = query ;
}

void PosgreSQLDatabaseHandler::ReadConfig() {
	std::string data[6];
    std::ifstream inifile;

	inifile.open( "config.ini", std::ios::in );

	if ( inifile.fail() ){
		std::cout << "no se pudo leer" ;
	}

	int i = 0 ;
	while( !inifile.eof() ) {

		std::getline( inifile , data[i] ) ;
		std::cout << data[i] << std::endl ;
                i++;
    }

    host = data[1].c_str() ;
    dataBase = data[2].c_str() ;
    port = data[3].c_str() ;
    user = data[4].c_str() ;
    passwd = data[5].c_str() ;
}

void PosgreSQLDatabaseHandler::execute() {
    
    if ( connected ) {
        PQclear( result );
        result = PQexec( cnn , qSQL.c_str() ) ;
        if ( result != NULL ) {
            isError = false ;
            // printf( "%s\n", PQerrorMessage( cnn ));
        } else {
            isError = true ;
            // printf( "%s\n", PQerrorMessage( cnn ));
        }
    }
}

bool PosgreSQLDatabaseHandler::getErrorStatus() {
    return isError ;
}

void PosgreSQLDatabaseHandler::addParameter( int key, std::string value ) {
    std::cout<< "parametro " << value << std::endl ;
}

Row PosgreSQLDatabaseHandler::fetch() {
    Row row ;
    int columnCount = PQnfields(result);
    for ( int i = 0 ; i < columnCount ; i++ ) {
        std::string columnName = std::string( PQfname( result, i ) );
        std::string columnValue = std::string( PQgetvalue( result , 0 , i ) );
        row[columnName] = columnValue;    
    }
    return row; 
}

Table PosgreSQLDatabaseHandler::fetchAll() {
    Table result ;
    return result ;
}

//ComponentInterface:
bool PosgreSQLDatabaseHandler::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "DatabaseHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* PosgreSQLDatabaseHandler::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void PosgreSQLDatabaseHandler::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new PosgreSQLDatabaseHandler;
}

#endif // SQLITE_DATABASE_HANDLER_H