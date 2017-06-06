.model small

.data

menu    db '1 - Input vs keyboard',13,10
        db '2 - Input from file',13,10
        db '3 - Output on screen',13,10
        db '4 - Output to file',13,10
        db '5 - Encode',13,10
        db '6 - Decode',13,10
        db '0 - Exit',13,10,'$'


.code
.486
mov ax, @data
mov ds, ax
mov es, ax

 mov ah,09h          ;\
    mov dl,menu         ; > Вывод меню
    int 21h 
	mov ah,4ch
	int 21h
end
