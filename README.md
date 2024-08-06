# 4-func-calc

A simple four function calculator made with Raylib

## building the project

There is a CMake script provided that will build the project and download the raylib dependency if needed. The `full.sh` script will build the project and run the executable. Note that the script is a shell so only works on windows. The script also expects you to have configured the project in a `build` directory.

The full process of building the project is as follows:

In the root directory of the project make a directory (use `build` if you want to use the script`)

From the root directory of the project run `cmake -S . -B [name of directory created]` and `cmake --build build`.

Use `./bin/4-func-calc` (linux) or `.\bin\4-func-calc.exe` (windows) to run the program
