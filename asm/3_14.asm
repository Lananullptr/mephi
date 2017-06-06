.model small
.data
	m equ 4         ;число строк
	n equ 4         ;длина строки

	a db 0, 0, 1, 4 ;исходная матрица
	  db 10, 1, 2, 3
	  db 1, 0, 3, -9
	  db 1,-1, 4, 3
	mt db m * n dup(0)  ; результат


.code
.486
	mov ax,@data
	mov ds,ax

	xor edi, edi
	mov ecx, m*n             
cp: mov al, a[edi]           
	mov mt[edi], al          
	inc edi            
	loop cp

	mov ebx, n * m              
ml: sub ebx, n           
	mov ecx, n         
	lp: mov edx, n             
		sub edx, ecx                
		lea edi, [ebx][edx]      
		mov al, mt[edi]      

		llp:mov ah, mt[ebx][edx]      
			cmp ah, al               
			jl skp           
			mov al, ah            
			lea edi, [ebx][edx]   
		skp:inc edx                  
			cmp edx, n            
			jne llp

		mov ebp, n
		sub ebp, ecx
		mov ah, mt[ebx][ebp]      
		mov mt[ebx][ebp], al
		mov mt[edi], ah


		loop lp
	cmp ebx, 0 
	jne ml


	mov ah, 4ch
	int 21h
end