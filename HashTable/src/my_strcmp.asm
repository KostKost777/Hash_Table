global MyStrCmp

MyStrCmp:
    vmovdqu  ymm0, [rdi]  
    vmovdqu  ymm1, [rsi]

    vmovdqu  ymm2, ymm0
    vmovdqu  ymm3, ymm1
    
    vpxor    ymm4, ymm4, ymm4
    vpcmpeqb ymm4, ymm2, ymm4  ;где байт из ymm2 и ymm4 равны ставит FF и все сохраняет в ymm4

    vpmovmskb ecx, ymm4        ;копирует каждый страший бит байта 
    bsf      ecx, ecx          ;находит первую 1 (по сути тут уже длина слова)
    
    vpcmpeqb ymm2, ymm2, ymm3  ;сравнивает по байтно два слова
    vpmovmskb eax, ymm2        ;копирует каждый страший бит байта 

    mov      edx, 0xFFFFFFFF
    shl      edx, cl
    not      edx
    
    and      eax, edx
    cmp      eax, edx
    je       .equal
    
    mov      eax, 1
    ret
    
.equal:
    xor      eax, eax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits