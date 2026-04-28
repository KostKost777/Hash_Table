global MyStrCmp

MyStrCmp:
    vmovdqu  ymm0, [rdi]  
    vmovdqu  ymm1, [rsi]
    
    vpcmpeqb ymm0, ymm0, ymm1
    vpmovmskb eax, ymm0
    
    ; Формируем маску для нужной длины
    mov      ecx, 0xFFFFFFFF
    shl      ecx, cl           ; сдвиг на длину (младший байт rdx)
    not      ecx               ; ecx = маска с единицами для первых len байт
    
    and      eax, ecx          ; обрезаем результат
    cmp      eax, ecx
    sete     al
    movzx    eax, al
    ret

section .note.GNU-stack noalloc noexec nowrite progbits