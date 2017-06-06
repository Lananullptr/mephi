SEL macro ; выбор пункта меню 
    mov ah,09h          ;\
    lea dx,select       ; > Вывод строки 'Select>'
    int 21h             ;/
 
    mov ah,01h          ;Функция DOS 01h - ввод символа
    int 21h             ;Введённый символ помещается в AL
 	mov item,al
 	mov ah, 2		;вывод на дисплей
	mov dx, 13		;символ на вывод из текстовой строки
	int 21h
	mov dx, 10		;символ на вывод из текстовой строки
	int 21h
	ret
ENDM

PRNT macro
	lea dx, string[2]
	call, print_line
	ret
ENDM

end
