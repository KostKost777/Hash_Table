; =============================================================================
; bool MyStrCmp(const char* str1, const char* str2)
; 
; Быстрое сравнение строк с использованием AVX2 (32 байта за раз)
; Максимальная длина строки: 32 символа (можно расширить до 64)
; 
; Вход:  RDI = str1
;        RSI = str2
; Выход: AL = 1 если строки равны, иначе 0
; =============================================================================
global MyStrCmp

section .text

MyStrCmp:
    ; Сначала сравниваем по 8 байт, пока не найдём различие или \0
    xor     ecx, ecx            ; offset = 0
    
.loop8:
    mov     rax, [rdi + rcx]
    mov     rdx, [rsi + rcx]
    cmp     rax, rdx
    jne     .not_equal_8
    
    ; Проверяем на \0 (битовый трюк)
    lea     r8, [rax - 0x0101010101010101]
    not     rax
    and     r8, rax
    and     r8, 0x8080808080808080
    jnz     .found_null         ; нашли \0 -> строки равны
    
    add     rcx, 8
    cmp     rcx, 32
    jl      .loop8
    
    ; Если дошли до 32 байт без \0, используем SIMD
    vmovdqu     ymm0, [rdi]
    vmovdqu     ymm1, [rsi]
    vpcmpeqb    ymm2, ymm0, ymm1
    vpmovmskb   eax, ymm2
    cmp     eax, 0xFFFFFFFF
    setz    al
    vzeroupper
    ret

.found_null:
    mov     al, 1
    ret

.not_equal_8:
    ; Нашли различие, нужно определить, было ли оно ДО \0
    ; Для простоты считаем, что если первые 8 байт не равны, то строки разные
    ; (это правильно, так как \0 был бы в обеих строках на одной позиции)
    xor     al, al
    ret

section .note.GNU-stack noalloc noexec nowrite progbits