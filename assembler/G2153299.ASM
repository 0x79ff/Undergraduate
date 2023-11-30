EXTRN	DISPBX: FAR		; 声明外部函数DISPBX; 此函数将在本模块中被调用
MYDATA SEGMENT
DATA DW 1234H,5678H,9D4CH,0D7H,0,-1,7D2AH,8A0EH,10F5H,645DH,8000H,8004H,1,7FFFH,8201H,9023H,2345H
N EQU ($-DATA)/2
MIN DW ?
MAX DW ?
Msg1 DB " is minimum even number",0DH,0AH,"$"
Msg2 DB " is maximum even number",0DH,0AH,"$"
MYDATA ENDS
CODE    SEGMENT
        ASSUME  CS:CODE,DS:MYDATA

START:  MOV     AX,MYDATA
        MOV     DS,AX
        MOV     CX,N-1
        MOV     BX,OFFSET DATA
        MOV     AX,[BX]
        MOV     DX,[BX]
AGAIN:  INC     BX
        INC     BX
        MOV     SI,[BX]
        TEST    SI,01H;验证是否为偶数
        JNZ     NEXT
STEP1:  CMP     AX,[BX];验证是否更小
        JLE     STEP2
        MOV     AX,[BX]
STEP2:  CMP     DX,[BX];验证是否更大
        JGE     NEXT
        MOV     DX,[BX]
NEXT:   LOOP    AGAIN
        ;先输出最小的偶数
        MOV     MIN,AX
        MOV     MAX,DX
        MOV     BX,MIN
        CALL    DISPBX;调用外部函数DISPBX，用BX传递参数
        MOV     AH,2
        MOV     DL,48H;输出'H'
        INT     21H
        MOV 	AH, 9
	    MOV 	DX, Offset Msg1
	    INT 	21H
        ;再输出最大的偶数
        MOV     BX,MAX
        CALL    DISPBX;调用外部函数DISPBX，用BX传递参数
        MOV     AH,2
        MOV     DL,48H;输出'H'
        INT     21H
        MOV 	AH, 9
	    MOV 	DX, Offset Msg2
	    INT 	21H
        ;
        MOV     AH,4CH
        INT     21H
CODE    ENDS
       	END	START
