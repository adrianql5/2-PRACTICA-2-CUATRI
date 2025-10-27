Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

cmake_minimum_required(VERSION 4.0)
project(Practica3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Practica3
        opt1_cons.c
        opt1_prod.c
        opt2_prod_cons.c
        opt3_prod_cons.c
        prod_cons.c)
