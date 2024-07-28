cmake_minimum_required(VERSION 3.5)

project(Individual LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC on)

find_package(Qt6 COMPONENTS Widgets SQL Core  REQUIRED)#здесь можно большими

add_executable(Individual main.cpp


    win.h
    databas.h generic.h
)


include(GNUInstallDirs)
install(TARGETS Individual
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}r
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(Individual Qt6::Widgets Qt6::Sql Qt6::Core)#тут нужно только большую С

