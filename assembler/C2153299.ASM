DATA SEGMENT
      IN1 DB 'Please enter a string of characters:','$'
      OUT1 DB 0DH,0AH,'Number of capital letters:','$'
      OUT2 DB 0DH,0AH,'Number of small letters:','$'
      OUT3 DB 0DH,0AH,'Number of numbers:','$'
      OUT4 DB 0DH,0AH,'Number of others:','$'
      BUFFER DB 80, ?, 80 DUP(?) 	;输入缓冲区
      RESULT DW	4 DUP(0)
      C10 DB 10
DATA ENDS
CODE    SEGMENT
	ASSUME  CS:CODE,DS:DATA   
START:  MOV     AX, DATA
	MOV DS, AX 
        LEA	DX, IN1;输入提示
        MOV	AH, 9
	INT	21H
        LEA	DX, BUFFER;输入字符串
	MOV	AH, 0AH
	INT	21H
        MOV	CL, BUFFER+1;循环次数
	MOV	CH, 0
	LEA	BX, BUFFER+2;装载字符存放区首地址
JUDGE:	MOV	AL, [BX]	;取出一S个字符
        CMP     AL,48;和'0'比较
        JB      CASE4
        CMP     AL,57;和'9'比较
        JBE     CASE3
        CMP     AL,65;和'A'比较
        JB      CASE4
        CMP     AL,90;和'Z'比较
        JBE     CASE1
        CMP     AL,97;和'a'比较
        JB      CASE4
        CMP     AL,122;和'z'比较
        JBE     CASE2
        JMP     CASE4
CASE1:  MOV AX,RESULT
        INC AX
        MOV RESULT,AX 
        JMP NEXT
CASE2:  MOV AX,RESULT+2
        INC AX
        MOV RESULT+2,AX 
        JMP NEXT
CASE3:  MOV AX,RESULT+4
        INC AX
        MOV RESULT+4,AX 
        JMP NEXT
CASE4:  MOV AX,RESULT+6
        INC AX
        MOV RESULT+6,AX 
        JMP NEXT
NEXT: 
        INC	BX		;修改指针
	LOOP	JUDGE		;计数与循环
        LEA	DX, OUT1
        MOV	AH, 9
	INT	21H
        MOV     AX,RESULT
        DIV     C10
        MOV     DH,AH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        MOV     AL,DH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        LEA	DX, OUT2
        MOV	AH, 9
	INT	21H
        MOV AX,RESULT+2
        DIV C10
        MOV DH,AH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        MOV AL,DH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        LEA	DX, OUT3
        MOV	AH, 9
	INT	21H
        MOV AX,RESULT+4
        DIV C10
        MOV DH,AH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        MOV AL,DH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        LEA	DX, OUT4
        MOV	AH, 9
	INT	21H
        MOV AX,RESULT+6
        DIV C10
        MOV DH,AH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
        MOV AL,DH
        OR  	AL, 30H	;转换成数字的ASCII代码
        MOV     DL,AL
	MOV  	AH, 2
	INT  	21H     ;向显示器输出一个字符
	MOV AX, 4C00H
	INT     21H
CODE    ENDS
	END START
       
