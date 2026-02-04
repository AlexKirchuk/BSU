.code

; RCX RDX R8 R9
; return EAX

ten DD 10

sum proc
mov eax, ecx
add eax, edx
ret
sum endp

kaprekar proc
mov edi, 1
mov ebx, ecx
imul ebx, ebx
mov esi, ebx
beg_:
cmp esi, 0
je end_
imul edi, ten
mov eax, ebx
cdq
idiv edi
cmp edx, 0
je beg_
add eax, edx
cmp eax, ecx
je a1
mov eax, esi
cdq
idiv ten
mov esi, eax
jmp beg_
a1:
mov eax, 1
jmp end__
end_:
xor eax, eax
end__:
ret
kaprekar endp

isArithmetic proc
dec ecx
mov edi, [rdx + 4]
sub edi, [rdx]
for_:
mov ebx, [rdx + 4]
sub ebx, [rdx]
cmp ebx, edi
jne end_
add rdx, 4
loop for_
mov eax, 1
ret
end_:
xor eax, eax
ret
isArithmetic endp

isGeometric proc
mov rsi, rdx
dec ecx
mov eax, [rsi + 4]
mov ebx, [rsi]
cdq
idiv ebx
mov edi, eax
for_:
mov eax, [rsi + 4]
mov ebx, [rsi]
cdq
idiv ebx
cmp eax, edi
jne end_
add rsi, 4
loop for_
mov eax, 1
ret
end_:
xor eax, eax
ret
isGeometric endp

removeZeros proc
mov eax, ecx
mov ecx, 1
mov edi, 2
a1:
cmp eax, 0
je end_
cdq
idiv edi
cmp edx, 0
je a1
imul ecx, edi
jmp a1
end_:
sub ecx, 1
mov eax, ecx
ret
removeZeros endp

twoToN proc
mov eax, 1
for_:
imul eax, 2
loop for_
ret
twoToN endp

end