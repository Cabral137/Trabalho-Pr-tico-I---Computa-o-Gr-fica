# Versão mínima do CMake
cmake_minimum_required(VERSION 3.16)

# Nome do projeto
project(TrabalhoCG LANGUAGES CXX)

# Define onde o executável final será criado
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Configurações essenciais para o Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra o Qt6 no sistema
# Aponte o CMAKE_PREFIX_PATH para a pasta do Qt se o CMake não encontrar automaticamente
# Ex: set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Adiciona o executável e seus arquivos fonte
add_executable(TrabalhoCG
  main.cpp
)

# Linka as bibliotecas do Qt com seu executável
target_link_libraries(TrabalhoCG PRIVATE Qt6::Widgets)