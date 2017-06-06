.model small

.data

mas dw 1,2,3,4,5
    dw 2,3,4,5,6
    dw 3,4,5,6,7
    dw 4,5,6,7,8

n dw 4
m dw 5
i dw 1
	
.code
.486

mov ax,@data
mov ds,ax

	shr dl,2
	mov cx,0
	mov di,m
	sar di,1
	mov ax,m
	sal ax,1		; инкремент для перехода на строку ниже
	xor si,si 		; stroka
	mov bp,n
				;dec bp		
	sal bp,1		; pravo		
		
	xor bx,bx 		; levo
	xor dx,dx
	
m1:	
	xchg dx, mas[bx+si]
	xchg dx, ds:mas[bp+si]
	xchg dx, mas[bx+si]
	add si,ax
	inc cx
	cmp cx,n
	jne m1

	xor cx,cx
	xor si,si
	add bx,2
	sub bp,2
	inc i
	cmp i,di
	jle m1

	mov ah,4ch
	int 21h
end
