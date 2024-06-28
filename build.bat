REM g++ -Wall -std=c++14 -I.\include .\lib\sqlite3.dll main.cpp -o .\build\ms_windows\dbh_example.exe
g++ -o .\build\ms_windows\dbh_example.exe main.cpp .\lib\sqlite3.dll -I.\include
