_DATA   SEGMENT 'DATA'
Msg 	DB  	13, 10, "Please input a number: ", 13, 10, "$"
s1  	DB  	9, "Monday", 13, 10, '$'
s2  	DB  	9, "Tuesday", 13, 10, '$'
s3  	DB  	9, "Wednesday", 13, 10, '$'
s4  	DB	9, "Thursday", 13, 10, '$'
s5  	DB  	9, "Friday", 13, 10, '$'
s6  	DB  	9, "Saturday", 13, 10, '$'
s7  	DB  	9, "Sunday", 13, 10, '$'
err 	DB  	9, "Error!", 13, 10, '$'
CaseTab DW  	Case0, Case1, Case2, Case3, Case4, Case5, Case6, Case7, Default
_DATA   ENDS
_TEXT   SEGMENT 'CODE'
	ASSUME 	CS: _TEXT, DS: _DATA
Start:  MOV 	AX, _DATA
	MOV 	DS, AX
Again:  MOV 	AH, 9
	MOV 	DX, Offset Msg
	INT 	21H
	MOV 	AH, 1
	INT 	21H
	SUB 	AL, '0'
	JL  	Error   ; 输入字符小于'0'的情况
	CMP 	AL, 7
	JLE 	Loc1
Error:  MOV 	AL, 8
Loc1:   MOV 	AH, 0
	ADD 	AX, AX  ;AX×2
	MOV 	BX, AX
	JMP 	Word Ptr DS: CaseTab [BX]
Default:MOV 	DX, Offset err
	JMP 	EndSwitch
Case1:  MOV 	DX, Offset s1
	JMP 	EndSwitch
Case2:  MOV 	DX, Offset s2
	JMP 	EndSwitch
Case3:  MOV 	DX, Offset s3
	JMP 	EndSwitch
Case4:  MOV 	DX, Offset s4
	JMP 	EndSwitch
Case5:  MOV 	DX, Offset s5
	JMP 	EndSwitch
Case6:  MOV 	DX, Offset s6
	JMP 	EndSwitch
Case7:  MOV 	DX, Offset s7
	JMP 	EndSwitch
Case0:  MOV 	AX, 4C00H
	INT 	21H
EndSwitch:  MOV AH, 9
	INT 	21H
	JMP 	Again
_TEXT   ENDS
	END 	Start
