# Search Engine 

C++ поисковая система с инвертированным индексом, многопоточной обработкой и JSON интерфейсом.

## Описание проекта

Проект реализует поисковую систему с:
- Многопоточной индексацией документов
- Инвертированным индексом для быстрого поиска
- Результаты по релевантности
- С ограничением вывода результатов
- JSON-для конфигурации и запросов
- И с модульным тестированием

## Технологии

- **Язык**: C++20
- **Библиотеки**:
  - nlohmann/json (v3.11.2) - работа с JSON
  - Google Test (v1.13.0) - модульное тестирование
- **Многопоточность**: std::thread + std::mutex
- **Система сборки**: CMake ≥ 3.8

## Сборка и запуск

### Требования
- Компилятор C++20
- CMake ≥ 3.8
- Git

### Инструкция

1. Клонирование репозитория:
```bash
git clone https://github.com/acidhood999/Search_Engine.git
cd Search_Engine
```
2. Сборка проекта:
```bash
cmake -B build -S
cmake --build build
```
3. Запуск тестов:
```bash
cd build && ctest --verbose
```

## ⚙️ Конфигурация

### Формат файлов
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
  
# [English version](README.md)  

</div>
