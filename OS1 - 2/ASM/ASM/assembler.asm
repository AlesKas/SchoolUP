.486
.model flat, c

.const
cislo dword 42
pozdrav byte "Hello World!", 0
format byte "cislo: %i, pozdrav: %s", 13, 10, 0

.code
extern printf: proc
public testuj
testuj:
	push offset pozdrav
	push dword ptr cislo
	push offset format
	call printf
	add esp, 12
	ret

public ReturnOne
ReturnOne:
	mov eax, 1
	ret

end