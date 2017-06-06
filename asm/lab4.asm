.model small
.stack 100h
.data

cipher db 'Itisjustthetopofcryptography$'

string db 'abcdefghigklmnopqrstuvwxyz1234567890$'					;входная строка
out_str db 50 dup(0)

.code
.386
mov ax, @data
mov ds, ax

	lea si, string
	xor di,di
	call encode
	mov out_str[di],'$'
	lea si, out_str
	xor di,di
	call encode

mov ah,4ch
	int 21h

encode proc near
cld
	
m2:	xor bx,bx
m1:
	lodsb
m3:	cmp al,'$'
	je en
	xor al,cipher[bx] ;27 c 0
	add bx,1
	mov out_str[di],al
	inc di
	cmp bx,27
	je m2
	jmp m1

en: 
	     
 ; code...
        ret
encode endp

end