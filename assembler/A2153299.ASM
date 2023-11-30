DATA    SEGMENT
X   DW      32, 100, 128, 1025
Y   DW      4 DUP (-1)
DATA    ENDS
CODE    SEGMENT
	ASSUME  CS: CODE, DS: DATA
START:  MOV     AX, DATA
	MOV DS, AX
        MOV AX, X+2     ;取出X数组第2个元素
	MOV Y+2, AX     ;送入Y数组第2个元素中
	MOV AX, X+6     ;取出X数组第3个元素
	MOV Y+6, AX     ;送入Y数组第3个元素中
        MOV X+2,0 ;将X数组中的第二字清零
        MOV X+6,0 ;将X数组中的第四字清零
	MOV AX, 4C00H
	INT     21H
CODE    ENDS
	END START
