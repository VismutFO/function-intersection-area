;%include "io.inc"

section .rodata
    float_1 dd 2.0
    float_2 dd 2.5
    float_3 dd 3.0
    float_4 dd 5.0
    float_5 dd 9.5
section .bss
    res1 resd 1

section .text
_f1:
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
_f2:
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
_f3:
    push ebp ; Стандартный пролог для соглашения cdecl
    mov ebp, esp
    xor eax, eax ; Предварительно обнуляем возвращаемое значение
    finit
    fld dword[float_4]
    fld dword[ebp+8] ; Помещаем на стек первый параметр a
    fdivp
    pop ebp
    ret
