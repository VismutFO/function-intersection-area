program : main.o functions.o
        cc -m32 -o program main.o functions.o

main.o : main.c functions.asm
        cc -m32 -march=i386 -o main.o -c -g main.c
functions.o : functions.asm
        nasm -o functions.o -f win32 -g functions.asm
clean :
        rm -f program main.o functions.o
