/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef INIREADER_H
#define INIREADER_H

#include <string>
#include <fstream>
#include <sstream>

class IniReader
{
    private:
        std::ifstream fileInput;
        std::string  dataSection ;
        std::string BufferData ;

        void readFile()
        {
            while( !fileInput.eof())
            {
                std::string buffer;
                fileInput >> buffer;
                BufferData += " " + std::string(buffer);
            }
        }

    public:
        IniReader(){/*ctor*/}

        virtual ~IniReader(){/*dtor*/}

        bool open( std::string fileName)
        {
            fileInput.open(fileName.c_str());
            return  !fileInput ? false : true;
        }

        IniReader* selectSection( std::string section )
        {
            readFile();
            std::string buffer;
            size_t posInitialBuffer = BufferData.find("["+section+"]");

            if (BufferData.find("["+section+"]") == (std::string::npos))
            {
                return this;
            }
            else
            {
                buffer = BufferData.substr(posInitialBuffer);
                size_t posInitial = buffer.find("["+section+"]");
                size_t posEnd = buffer.find_first_of("[",posInitial+1);

                size_t sizeOfString = posEnd-posInitial;
                dataSection = buffer.substr(posInitial,sizeOfString );

                return this;
            }
        }

        std::string getValue( std::string key )
        {
            unsigned int pos ;
            pos  = dataSection.find(key);

            if ((pos==std::string::npos) || (dataSection == ""))
            {
                return "";
            }
            else
            {
                int posValue = (dataSection.find_first_of("=",pos) + 2);
                int posEndValue = dataSection.find_first_of(" ",posValue);
                size_t sizeOfString = posEndValue-posValue;

                std::string value = dataSection.substr(posValue,sizeOfString);

                return value ;
            }
        }
        
        void close()
        {
            fileInput.close();
        }
};

#endif // INIREADER_H
