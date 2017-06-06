.model small
.stack 100h
.data
.386
	cipher  db 'Itisjustthetopofcryptography$'
	string db 'pashadurak hahahahaha blin blimn blin blin$'
.code
mov ax, @data
mov ds, ax
mov es, ax
	lea si, string
	lods string
	lods string
	lods string
	mov ah,4ch
	int 21h
end
