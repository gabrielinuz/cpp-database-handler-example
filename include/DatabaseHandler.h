/**
* Copyright (c) 2020 Compset Development Group. All rights reserved.
* Contact: compset@protonmail.com
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef DATABASE_HANLDER_H
#define DATABASE_HANLDER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class DatabaseHandler
{
    public:
        virtual void setConfFile(std::string confFilePath) = 0;
        virtual void prepareQuery( std::string query ) = 0;
        virtual void addParameter( int key, std::string value ) = 0;
        virtual void execute() = 0;
        virtual Row fetch() = 0;
        virtual Table fetchAll() = 0;
        virtual bool getErrorStatus() = 0;
};

#endif // DATABASE_HANLDER_H