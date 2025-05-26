cmake_minimum_required(VERSION 3.10)
project(T9_UTF-8_RU_EN)

# СПринудительно установить стандарт c++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для MinGW в Windows
# Решает проблему с локализацией
if(MINGW)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# Если Линукс Решает проблему с локализацией
if(UNIX AND NOT APPLE)
    add_definitions(-DSET_GLOBAL_LOCALE_LINUX)
endif()

# Добавить исходники
add_executable(T9_UTF-8_RU_EN 
src/main.cpp
src/Trie.cpp
)

# Подключить заголовки из include/
target_include_directories(T9_UTF-8_RU_EN PUBLIC include/)

# Копируем файл при сборке
add_custom_command(
    TARGET T9_UTF-8_RU_EN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/7853-russian-words.txt
            ${CMAKE_CURRENT_BINARY_DIR}/7853-russian-words.txt
)