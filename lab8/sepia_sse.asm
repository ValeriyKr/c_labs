section .text
global sepia_sse

align 16
c1: dd 0.272, 0.349, 0.393, 0.272
align 16
c2: dd 0.543, 0.686, 0.769, 0.543
align 16
c3: dd 0.131, 0.168, 0.189, 0.131

; Limits for threshold filter
align 16
;filter: dd 0.0, 0.0, 0.0, 0.0
filter: dd 255.0, 255.0, 255.0, 255.0


%macro proc4vals 1
    movq xmm0, [rdi]
    movq xmm1, [rsi]
    movq xmm2, [rdx]
    shufps xmm0, xmm0, %1
    shufps xmm1, xmm1, %1
    shufps xmm2, xmm2, %1
    mulps xmm0, xmm3    ; r *= c1
    mulps xmm1, xmm4    ; g *= c2
    mulps xmm2, xmm5    ; b *= c3
    addps xmm0, xmm1    ; r += g
    addps xmm0, xmm2    ; r += b
    ; Thresholding
    pminsw xmm0, xmm6
    movdqa [rel rcx], xmm0
%endmacro


%macro next 0
    add rdi, 4
    add rsi, 4
    add rdx, 4
    add rcx, 16
    shufps xmm3, xmm3, 0b01001001
    shufps xmm4, xmm4, 0b01001001
    shufps xmm5, xmm5, 0b01001001
%endmacro
    

sepia_sse:
    ; Load thresholding limits
    movdqa xmm6, [rel filter]
    ; Load coefficients
    movdqa xmm3, [rel c1]
    movdqa xmm4, [rel c2]
    movdqa xmm5, [rel c3]
    ; 0b01000000:
    ; 0000x2x1 -> x1x1x1x2
    proc4vals 0b01000000
    ; 0b01010000:
    ; 0000x3x2 -> x2x2x2x3
    next
    proc4vals 0b01010000
    ; 0b01010100:
    ; 0000x4x3 -> x3x3x3x4
    next
    proc4vals 0b01010100
    ret
