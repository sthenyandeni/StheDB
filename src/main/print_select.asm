; rdi - char* table
; rsi - struct Database* db
; rdx - void** select_data
; rcx - int record_count
segment .data
table_not_found_message db "Table %s not found", 0x0a

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

struc Table
    .name resq 1
    .attributes resq 1
    .attr_count resd 1
    .offset_file_id resd 1
    align 4
endstruc

segment .text
    global print_select
    extern printf
    extern get_table_from_name
    extern malloc

print_select:
    push rbp
    mov rbp, rsp

    ; move to stack
    sub rsp, 68
    mov [rsp], rdi ; char* table
    mov [rsp + 8], rsi ; struct Database* db
    mov [rsp + 16], rdx ; void** select_data
    mov [rsp + 24], ecx ; int record_count
    mov [rsp + 28], dword 0 ; struct Table* t
    mov [rsp + 36], dword 0 ; void *record
    mov [rsp + 44], dword 0 ; int attr_count
    mov [rsp + 48], dword 0 ; struct Attribute* attr
    mov [rsp + 56], dword 0 ; int offset
    mov [rsp + 60], dword 0 ; int size
    mov [rsp + 64], dword 0 ; ATTR_TYPE (int) type

    ; Call get_table_from_name function
    mov rdi, [rsp + 8] ; rdi <-- struct Database* db
    mov rsi, [rsp] ; rsi <-- char* table 
    call get_table_from_name
    mov [rsp + 28], rax ;move Table pointer to stack

    ; Check if table is not found
    cmp qword [rsp + 28], 0
    je _table_not_found

    mov r12, 0

    ; r12 --> int i
_for_each_record:
    mov r8, [rsp + 16]
    mov r8, [r8 + r12]
    mov [rsp + 36], r8
    mov r9, [rsp + 28]
    mov r9d, dword [r9 + Table.attr_count] ; get table attribute count
    mov [rsp + 44], r9

    mov r13, 0

    ; r13 --> int j
_for_each_attribute:
    mov r10, [rsp + 28]
    mov r10, [r10 + Table.attributes]
    mov r10, [r10 + r13]
    mov [rsp + 48], r10 ; struct Attribute* attr

    mov r11, [r10 + Attribute.record_offset]
    mov [rsp + 56], r11
    mov r11, [r10 + Attribute.size]
    mov [rsp + 60], r11
    mov r11, [r10 + Attribute.type]
    mov [rsp + 64], r11


    inc r13
    cmp r13, [rsp + 44]
    jne _for_each_attribute

    inc r12
    cmp r12, [rsp + 24]
    jne _for_each_record


_table_not_found:
    mov rdi, table_not_found_message
    mov rsi, [rsp]
    call printf

    leave
    ret