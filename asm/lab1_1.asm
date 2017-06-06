.model small
.data

a dd 2
b dd 2
c dd 2
d dd 5
e dd 2
x dd ? ;частное первой дроби
y dd ? ;остаток первой дроби
z dd ? ;частное второй дроби
v dd ? ;остаток второй дроби
k dd ?
l dd ?
m dd ?

.code
.486

mov ax, @data
mov ds, ax

mov k,-29
mov l,-119
mov m,-238
mov eax, a
imul eax,2    ;2*a
add eax, b    ;2a+b
mov ebx, eax  ;
imul eax, ebx ;(2a+b)^2
imul eax, ebx ;(2a+b)^3
mov ebx, a    ;
imul ebx, 3   ;3*a
xor edx, edx  ;обнуление регистра
idiv ebx      ;первая дробь 
	      
mov x, eax    ;частное 36
mov y, edx    ;остаток 0

mov eax, c
imul eax, 3   ;3*c
mov edx, d    ;
imul edx, edx ;d^2 
imul edx, d   ;d^3
sub eax, edx  ;3*c - d^3
xor edx,edx
imul eax, a   ;a* (3*c - d^3)
mov ecx, e    ;
imul ecx, ecx ;e^2
imul ecx, 2   ;2*e^2
mov ebx,ecx
cdq	      ;
idiv ebx       ;вторая дробь

mov z, eax    ;частное -39
mov v, edx    ;остаток 6


mov ah, 4ch
int 21h
end
