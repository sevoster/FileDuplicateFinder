# File Duplicate Finder
Application to find file duplicates in a directory

## Prerequisites
* CMake >= 3.1
* Qt 5.12

## How to build
* Create build directory inside repo folder
```shell
mkdir build
cd build
```
* Run CMake
```shell
cmake ..
```
* Build
```shell
make
```

## Usage
* Run DuplicateFinder
* Choose directory
* Choose finder
  * __All__ - find duplicates for all files in all subdirectories
  * __Per Directory__ - find duplicates only per directory
* Choose comparator
  * __Byte__ - compare by content
  * __Hash__ - compare by SHA1 hash
* Click "Analyze" button
* As result you will see groups of duplicates
![Application](doc/images/app.png)

## Known limitations
* Application may be slow on a big amount of files or huge sizes
