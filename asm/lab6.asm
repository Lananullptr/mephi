.model small
.stack 100h
.data
menu    db '1 - Input from keyboard',13,10
        db '2 - Input from file',13,10
        db '3 - Output on screen',13,10
        db '4 - Output to file',13,10
        db '5 - Encode',13,10
        db '6 - Decode',13,10
        db '0 - Exit',13,10,'$'
select  db 13,10,'Select>$'
;next_line db 13, 10, '$'			;пустая строка

result db 'Result :$'

public string
public item

string db 100 dup(0)					;входная строка
item db ?								;пункт меню
cipher db 'Itisjustthetopofcryptography$'

.code
.386

INCLUDE  macro.asm
;extrn SELECT:far
extrn inputf:far
extrn OpenFile:far
extrn outputf:far
extrn CloseFile:far
extrn keybrd:far
extrn inplen:byte

mov ax, @data
mov ds, ax

start:
	lea dx,menu			;\
    mov ah,09h          ; > Вывод меню
    int 21h             ;/
 
select_loop:
    SEL
    cmp item,'1'          ;Сравнение введённого символа с '1'
    je c1               ;Переход, если равно
    cmp item,'2'          
    je c2               
    cmp item,'3'
    je c3
    cmp item,'4'
    je c4
    cmp item,'5'
    je c5
    cmp item,'6'
    je c5
    cmp item,'0'          
    je exit             
    jmp select_loop     ;Безусловный переход

c1:
	call keybrd
	call format
	PRNT
    jmp start
c2:	
	call inputf 
	jmp start
c3:
	PRNT
    jmp start
c4:	
	call outputf
	jmp start
c5:
	lea si, string
	add si,2
	xor di,di
	call encode
	lea dx, result
	call print_line
	PRNT
	jmp start

exit:
	mov ah,4ch
	int 21h

format proc near; legacy code
	xor ax, ax
	mov al, string[1];берём длину введенной строки
	cbw
	add si, ax; si указатель источника
	add si, 2
	mov string[si], '$'
	ret
format endp 

print_line proc near
	push bp
	mov bp, sp
	mov dx, [bp + 4]
	mov ah, 09h			;Выдать строку на дисплей
	int 21h
	pop bp
	ret 2				;количество байтов стека, которые будут вытолкнуты после выталкивания адреса возврата
print_line endp 

encode proc near
cld
	
m2:	xor bx,bx
m1:
	lodsb
m3:	cmp al,'$'
	je en
	xor al,cipher[bx] ;27 c 0
	add bx,1
	mov string[di],al
	inc di
	cmp bx,27
	je m2
	jmp m1

en: 
	     
 ; code...
        ret
encode endp

end