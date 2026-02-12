# Search Engine

C++ Search Engine with Inverted Index, Multithreading, and JSON API

## Project Description

This project implements a search engine with:
- Multithreaded document indexing
- Inverted index for fast searching
- Relevance-based result ranking
- Configurable result limit
- JSON configuration and query interface
- Modular unit testing

## Technologies

- **Language**: C++20
- **Libraries**:
  - nlohmann/json (v3.11.2) - JSON processing
  - Google Test (v1.13.0) - unit testing
- **Multithreading**: std::thread + std::mutex
- **Build System**: CMake ≥ 3.8

## Building and Running

### Requirements
- C++20 compatible compiler
- CMake ≥ 3.8
- Git

### Installation
```bash
git clone https://github.com/acidhood999/Search_Engine.git
cd Search_Engine
```
2. Project build:
```bash
cmake -B build -S
cmake --build build
```
3. Running tests:
```bash
cd build && ctest --verbose
```

## Configuration

### File format
1. config.json:
```bash
{
    "config": {
        "name": "SearchEngine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": [
        "resources/file1.txt",
        "resources/file2.txt",
        "resources/file3.txt",
        "resources/file4.txt",
        "resources/file5.txt"
    ]
}
```
2. requests.json:
```bash
{
    "requests": [
           "some words..",
           "some words..",
           "some words..",
           "some words..",
           ...
    ]
}
```
3.  answers.json:
```bash
{
     "answers": {
           "request001": {
                 "result": "true",
                 "relevance": {
                        "docid": 0, “rank” : 0.989,
                        "docid": 1, “rank” : 0.897,
                        "docid": 2, “rank” : 0.750,
                        "docid": 3, “rank” : 0.670,
                        "docid": 4, “rank” : 0.561
                 }
            },
            "request002": {
                  "result": "true",
                  "docid": 0, “rank” : 0.769
            },
            "request003": {
                  "result": "false"
            }
     }
}
```
<div align="center">
  
# [Русская версия](README_RU.md)  

</div>
