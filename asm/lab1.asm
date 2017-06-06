.model small
.data

a dd 1
b dd 1
c dd 1
d dd 1
e dd 1

.code
.486

mov ax, @data
mov ds, ax

mov eax, a
add eax, b
mov ebx, eax
imul eax, ebx
imul eax, ebx
mov ebx, a
imul ebx, 3
xor edx, edx
idiv ebx
mov ebx, eax
mov eax, c
imul eax, 3
mov edx, d
imul edx, edx
imul edx, d
sub eax, edx
imul eax, a
mov ecx, e
imul ecx, ecx
imul ecx, 2
xor edx, edx
idiv ecx
add ebx, ecx
mov eax, ebx


mov ah, 4ch
int 21h
end
