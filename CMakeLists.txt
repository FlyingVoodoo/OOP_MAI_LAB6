cmake_minimum_required(VERSION 3.10)
project(OOP_MAI_LAB6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Включаем директорию с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Список всех исходных файлов
set(SOURCES
    src/fight_visitor.cpp
    src/npc.cpp
    src/npc_factory.cpp
    src/ConsoleLogger.cpp
    src/FileLogger.cpp
)

# Создаем исполняемый файл для основного приложения
add_executable(main src/main.cpp ${SOURCES})

# Опции компиляции
if(MSVC)
    target_compile_options(main PRIVATE /W4)
else()
    target_compile_options(main PRIVATE -Wall -Wextra)
endif()

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(tests tests/test_main.cpp ${SOURCES})
target_link_libraries(tests gtest)
if(MSVC)
    target_compile_options(tests PRIVATE /W4)
else()
    target_compile_options(tests PRIVATE -Wall -Wextra)
endif()

include(GoogleTest)
gtest_discover_tests(tests)
