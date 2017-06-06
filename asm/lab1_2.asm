.model small
.data

a dd 1
b dd 1
c dd 1
d dd 1
e dd 1
x dd ?
y dd ?

.code
.486

mov ax, @data
mov ds, ax

mov eax, a
imul eax,2
add eax, b    ;a+b
mov ebx, eax  ;
imul eax, ebx ;(a+b)^2
imul eax, ebx ;(a+b)^3
mov ebx, a    ;
imul ebx, 3   ;3*a
xor edx, edx  ;обнуление регистра
idiv ebx      ;первая дробь 
	      ;mov ebx, eax ; â ebx ïåðâîå äåëåíèå
mov x, eax    ;
mov y, edx    ;

mov eax, c
imul eax, 3   ;3*c
mov edx, d    ;
imul edx, edx ;d^2 
imul edx, d   ;d^3
sub eax, edx  ;3*c - d^3
imul eax, a   ;a* (3*c - d^3)
mov ecx, e    ;
imul ecx, ecx ;e^2
imul ecx, 2   ;2*e^2
xor edx, edx  ;
idiv ecx      ;вторая дробь
	      ;add eax, ebx îïòèìàëüíî
              ;add ebx, ecx 
              ;mov eax, ebx
add x, eax    ;сложить частное
add y, edx    ;сложить остаткив


mov ah, 4ch
int 21h
end
