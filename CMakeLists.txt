cmake_minimum_required(VERSION 3.24)
project(code_week)

set(CMAKE_CXX_STANDARD 17)

add_executable(code_week datastore.h FileRW.c gettime.c interface.c list_func.h listedit.c main.c qualityassurance.c chkinput.c)
