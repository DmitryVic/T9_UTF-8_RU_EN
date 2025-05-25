cmake_minimum_required(VERSION 3.10)
project(SocialGr)

# СПринудительно установить стандарт c++ 17
# Исправление опечатки в STANDART -> STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для MinGW в Windows
# Решает проблему с локализацией
if(MINGW)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# Если Линукс Решает проблему с локализацией
# передает компилятору флаг -DSET_GLOBAL_LOCALE_LINUX что SET_GLOBAL_LOCALE_LINUX существует в коде
# тоже самое если в коде написать #define SET_GLOBAL_LOCALE_LINUX
# -D(ИМЯ) сказать компилятору что макрос определен 
if(UNIX AND NOT APPLE)
    add_definitions(-DSET_GLOBAL_LOCALE_LINUX)
endif()

# Добавить исходники
add_executable(SocialGr 
src/main.cpp
src/Trie.cpp
)

# Подключить заголовки из include/
target_include_directories(SocialGr PUBLIC include/)