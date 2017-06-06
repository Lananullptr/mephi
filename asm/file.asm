.model small
.stack 100h
.data
handle dw 0								;описатель файла (handle), возвращенный при открытии. 
public inplen
inplen db 0 							;длина входящей строки 
outFileName db 'out.txt',0  
inFileName  db 'in.txt',0
s_item db 13,10,"Select menu item: $"	;подсказка 

extrn item:byte
extrn string:byte
.code

public keybrd
keybrd proc near					;считывание строки 
lea dx, string
mov string[0], 99
mov ah, 0ah							;ввод строки в буфер 
int 21h
ret
keybrd endp 

public OpenFile
OpenFile    PROC           ;stack = 0 - open for read (load file); 1 - open for write (save file)
	push dx
	push bp
	push cx
	push bx
	mov bp, sp
	mov bx, [bp+10]
		push ax
			cmp bx, 0 			;1 - запись, в этом случае вначале файл создается/перезаписывается пустым
			je only_open_file
				mov ah, 3ch 	;создание файла 
				mov cx,0 		;атрибуты файла 
				lea dx, outFileName
				int 21h
				jmp end_of_open
			only_open_file:
				mov ah, 3dh 	;открытие файла 
				mov al, bl 		;грузится из стека, 0 - чтение, 1 - запись 
				lea dx, inFileName
				int 21h
			end_of_open:
			mov handle, ax
			;lea ax, MsgSuccess
			;call PrintString
		pop ax
	pop bx
	pop cx
	pop bp
	pop dx
	ret 2		
OpenFile    ENDP   

public CloseFile
CloseFile    PROC              ;закрыть
     		mov ah,3eh
     		mov bx,[handle] 		
		int 21h
		ret			
CloseFile    ENDP

public outputf					;сохранение в файл 
outputf proc near
	
	push bx
	push cx
	push dx
		push 1
		call OpenFile
		cmp string, 0 	;если строка нулевая, то и сохранять нечего 
		je end_save
			mov ah, 40h		; писать в файл через описатель BX = описатель файла DS:DX = адрес буфера, содержащего записываемые данные CX = число записываемых байт 
			xor cx,cx		;очищаем сх

			mov cl, inplen	;загружаем длину строки которую будем писат
			lea dx, string ;эффективный адрес этой строки 
			mov bx, handle	;и описатель 
			int 21h			;непосредственно прерывание 
		end_save:
		call CloseFile
	pop dx
	pop cx
	pop bx
	ret
outputf endp

public inputf
inputf proc near
	push bx
	push cx
	push dx
		push 0
		call OpenFile
			mov ah, 3fh			;читать файл через описатель 
			mov cx, 90			;число считываемых байт 
			lea dx, string		;куда
			add dx, 2			;
			mov bx, handle		;тут описатель файла
			int 21h
			mov inplen, al		;записываем длину строки в inplen 
			mov string[1], al		;и в саму строку 
		call CloseFile
	pop dx
	pop cx
	pop bx
	ret
inputf endp

end