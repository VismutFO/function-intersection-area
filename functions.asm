;%include "io.inc"

section .rodata
    float_1 dd 2.0
    float_2 dd 2.5
    float_3 dd 3.0
    float_4 dd 5.0
    float_5 dd 9.5
    float_6 dd -4.5
    float_7 dd -50.0
    float_8 dd -1.5
    float_9 dd -5.0
section .bss
    res1 resd 1

section .text
GLOBAL f1
GLOBAL f2
GLOBAL f3

GLOBAL f1d
GLOBAL f2d
GLOBAL f3d

f1:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld1
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fld1
    faddp
    fdivp
    fld dword[float_1]
    fdivp
    fld1
    faddp
    fld dword[float_3]
    fmulp
    pop ebp
    ret
f2:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fld dword[float_2]
    fmulp
    fld dword[float_5]
    fsubp
    pop ebp
    ret
f3:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[float_4]
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fdivp
    pop ebp
    ret
f1d:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[float_8]
    
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fld1
    faddp
    
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fld1
    faddp
    
    fmulp
    fdivp
    pop ebp
    ret
f2d:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[float_2]
    pop ebp
    ret
f3d:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[float_9]
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fmulp
    fdivp
    pop ebp
    ret
