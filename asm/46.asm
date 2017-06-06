.model small
.stack 100h
.data
.386
menu    db '1 - Input vs keyboard',13,10
        db '2 - Input from file',13,10
        db '3 - Output on screen',13,10
        db '4 - Output to file',13,10
        db '5 - Encode',13,10
        db '6 - Decode',13,10
        db '0 - Exit',13,10,'$'
select  db 13,10,'Select>$'
string  db 100 dup ('$') 
outputs db 100 dup ('$')
cipher  db 'Itisjustthetopofcryptography$'
f_Handle    dw ? ; дескриптор файла для вывода
outFileName db 'out.txt',0  
inFileName  db 'in.txt',0
msg_fileError db 13,10,'Ошибка создания файла$'
handle dw ?
a db ?
i db ?
c db ?

.code
mov ax, @data
mov ds, ax
mov es, ax
;----------------------------------------------------------
start:
    mov ah,09h          ;\
    mov dl,menu         ; > Вывод меню
    int 21h             ;/
 
select_loop:
    mov ah,09h          ;\
    mov dl,select       ; > Вывод строки 'Select>'
    int 21h             ;/
 
    mov ah,01h          ;Функция DOS 01h - ввод символа
    int 21h             ;Введённый символ помещается в AL
 
    cmp al,'1'          ;Сравнение введённого символа с '1'
    je c1               ;Переход, если равно
    cmp al,'2'          ;Сравнение введённого символа с '2'
    je c2               ;Переход, если равно
    cmp al,'3'
    je c3
    cmp al,'4'
    je c4
    cmp al,'5'
    je c5
    cmp al,'6'
    je c6
    cmp al,'0'          ;Сравнение введённого символа с '0'
    je exit             ;Переход, если равно
    jmp select_loop     ;Безусловный переход

c1:
	mov ah,0ah        ;Считать строку символов из STDIN в буфер
        lea dx,string       ;адрес буфера  (где, 0байт - кол-во введённых символов не будет превышать этого значения, у меня там 100, хотя надо было 102)
        int 21h             ;/
    	jmp start
c2:	
	call inputf 
	jmp start
c3:
	mov string+1,0ah ;поскольку первые 2 байта - тех. характер. массива, то выводить мне их не надо, поэтому в 1 я пишу символ перехода на новую строку.
	mov ah,9
        lea dx,string+1 ;вывод +1 (т.е. вывожу символ новой строки и саму строчку)
        int 21h
        jmp start
c4:	
	call outputf
	jmp start
c5:
	mov dx, OFFSET cipher
	push dx
	lea si, string
	add si,2
	lea di, outputs
	call encode
	jmp start
c6:	
	call encode
	jmp start
exit:
	mov ah,4ch
	int 21h

inputf proc                    ;открыть, прочиать, закрыть
	mov dx, OFFSET inFileName	; имя файла
	mov a,0
	CALL OpenFile 
	jc Error
	CALL ReadFile	
	jc Error			; проверить флаг
        Call CloseFile
        clfile
Error:	ret
inputf endp

outputf proc
	mov dx, OFFSET outFileName	; имя файла
	mov a,1
	CALL OpenFile 
	jc Er
	CALL WriteFile
	jc Er			; проверить флаг
        Call CloseFile
	clfile
Er:	ret
outputf endp

; encode
encode proc 
	pop dx
	mov bx,dx
	jmp m1
m2:	mov dx,bx
	jmp m3
m1:
	lodsb
m3:	cmp al,'$'
	je en
	xor al,cipher+[dx] ;27 c 0
	inc dx
	stosb
	cmp cipher+[dx],'$'
	je m2
	jmp m1

en:        ; code...
        ret
encode endp



OpenFile    PROC           ;открыть
     		mov ah,3dh
     		mov al,a				
		int 21h
		ret			
OpenFile    ENDP   

CloseFile    PROC              ;закрыть
     		mov ah,3eh
     		mov bx,[handle] 		
		int 21h
		ret			
CloseFile    ENDP

ReadFile PROC

	;mov ah,3fh		; функция чтения файла
	;mov cx,14h		; сколько читать
	;mov dx,OFFSET Buffer   	; буфер
	;int 21h			; выполнить
	mov [handle],ax 
	mov bx,ax               ;Дескриптор файла
    	mov ah,3Fh              ;Функция DOS 3Fh (чтение из файла)
    	mov dl,string           ;Адрес буфера для данных
    	mov cx,100               ;Максимальное кол-во читаемых байтов
    	int 21h                 ;Обращение к функции DOS
	ret
ReadFile endp

WriteFile proc 
        mov [handle],ax         ;Сохранение дескриптора файла
 	mov bx,ax               ;Дескриптор файла
    	mov ah,40h              ;Функция DOS 40h (запись в файл)
    	mov dl,string           ;Адрес буфера с данными
	xor ecx,ecx
    	mov cx,100         ;Размер данных
    	int 21h                 ;Обращение к функции DOS
        ret
WriteFile endp



clfile	macro
	jc Error
	jmp e
Error:
	mov dx,OFFSET ErrorStr 
e:
	ret
endm

end
