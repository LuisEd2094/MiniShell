#!/bin/bash



INCLUDES="-I/home/luised2094/MiniShell/includes -I/home/luised2094/MiniShell/src/execute_arguments -I./"

gcc $INCLUDES mytest.c ../*.c  ../../print_error/* ./*.c ../../../Libft/src/* ../../../Libft/ftprintf/* /home/luised2094/MiniShell/src/builtins/env/*  /home/luised2094/MiniShell/src/builtins/shared/* /home/luised2094/MiniShell/Libft/get_next_line/* \
-L./ -lunity -o my_test