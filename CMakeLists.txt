cmake_minimum_required(VERSION 3.24)
project(code_week)

set(CMAKE_CXX_STANDARD 17)

add_executable(code_week datastore.h main.c gettime.c FileRW.c interface.c listedit.c qualityassurance.c list_func.h testonly_linkedlist.c)
