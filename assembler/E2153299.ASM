MYDATA SEGMENT
DATA DW 1234H,5678H,9D4CH,0D7H,0,-1,7D2AH,8A0EH,10F5H,645DH,8000H,8004H,1,7FFFH,8201H,9023H,2345H
N EQU ($-DATA)/2
MIN DW ?
MYDATA ENDS

CODE    SEGMENT
        ASSUME  CS:CODE,DS:MYDATA

MYPRINT PROC NEAR
        MOV     CH,4
        MOV     CL,4   
ROTATE: ROL     BX,CL;循环移位4位
        MOV     AX,BX
        AND     AX,0FH
        ADD     AX,30H
        CMP     AX,3AH
        JL      PRINTIT
        ADD     AX,7
PRINTIT:MOV     DL,AL
        MOV     AH,2
        INT     21H
        DEC     CH
        JNZ     ROTATE
        MOV     AH,2
        MOV     DL,48H;输出'H'
        INT     21H
        RET
MYPRINT ENDP

MAIN PROC FAR
        PUSH    DX
        MOV     AX,0
        PUSH    AX
        MOV     AX,MYDATA
        MOV     DS,AX
        MOV     CX,N-1
        MOV     BX,OFFSET DATA
        MOV     AX,[BX]
AGAIN:  INC     BX
        INC     BX
        MOV     SI,[BX]
        TEST    SI, 01H;验证是否为偶数
        JNZ     NEXT
        CMP     AX,[BX];验证是否更小
        JLE     NEXT
        MOV     AX,[BX]
NEXT:   LOOP    AGAIN
        MOV     MIN,AX
        MOV     BX,MIN
        CALL    MYPRINT
        RET
MAIN ENDP

CODE    ENDS
       	END MAIN
