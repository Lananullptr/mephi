.model small

.data

a dw 5
b dw 10

.code
.486

mov ax,@data
mov ds,ax

mov ax, a
push ax
mov ax, b
push ax

call pr

add sp,6

mov ah,4ch
int 21h



pr proc
    	push bp                 ;Сохранение регистра BP
    	mov bp,sp               ;BP=SP

	mov ax,[bp+4]
	add ax,[bp+6]
	
	pop bp
	push ax
	
	ret 2
 	
	
pr endp

end
