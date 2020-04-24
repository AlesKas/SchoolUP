.386
.model flat, stdcall
.code


	avg_int_masm PROC	a::DWORD, b::DWORD, c::DWORD
			
			mov eax, a
			add eax, b
			add eax, c
			mov ebx, 3
			mov edx, 0
			cdq
			div ebx
			ret

	avg_int_masm ENDP
end 