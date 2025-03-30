cmake_minimum_required(VERSION 3.15)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(ENV{PKG_CONFIG_PATH} "C:/msys64/ucrt64/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(VentanaApp ventana.c)
target_link_libraries(VentanaApp ${GTK4_LIBRARIES})