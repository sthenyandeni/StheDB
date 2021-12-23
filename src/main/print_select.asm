; rdi - char* table
; rsi - struct Database* db
; rdx - void** select_data
; rcx - int record_count
segment .data
struc Database
    .head resq 1
    .name resq 1
    .table_count resd 1
    align 4
endstruc

struc Attribute
    .name resq 1
    .type resd 1
    .size resd 1
    .record_offset resd 1
    align 4
endstruc


segment .text
    global _print_select
    extern printf
    extern get_table_from_name
    extern malloc

_print_select:
    push rbp
    mov rbp, rsp

    sub rsp, 36
    mov [rsp], rdi ; char* table
    mov [rsp + 8], rsi ; struct Database* db
    mov [rsp + 16], rdx ; void** select_data
    mov [rsp + 24], ecx ; int record_count
    mov [rsp + 28], 0

    mov rdi, [rsp + 8]
    mov rsi, [rsp]
    call get_table_from_name
    mov [rsp + 28], rax

    cmp [rsp + 28], 0
    je _table_not_found

_table_not_found:



    leave
    ret