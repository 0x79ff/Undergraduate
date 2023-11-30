;计算机科学与技术 2153299 杨非凡
DATA SEGMENT
    FILENAME  DB   'mystu.txt',0 ;文件名字
    HANDLE    DW    0          ;保存文件句柄用
    NUM       DW    0          ;文件中学生的个数
    LOOP_NUM  DW    0          ;打印学号时需要忽略的前面的字的个数
    SEVEN     DW    7          ;学号的长度
    ERROR_MSG1  DB  'error1: fail to open mystu.txt$'
    ERROR_MSG2  DB  'error2: fail to read mystu.txt$'
    ERROR_MSG3  DB  'error3: mystu.txt is empty$'
    BUF  DB  256 DUP(0)      ;缓冲区，用来存储从文件中读取的内容
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
MAIN PROC FAR
    MOV	AX, DATA
    MOV	DS, AX
    
    CALL COUNT                ;统计学号的个数
    CALL GET_RANDOM_NUM       ;生成随机数
    
    CALL SET_CLS

	MOV DH, 4
	MOV DL, 35
    CALL SET_XY
    CALL PRINT_NUM            ;打印幸运数字

	MOV DH, 8
	MOV DL, 33
    CALL SET_XY
    CALL PRINT_STU_NO         ;打印中奖的学号

	MOV DH, 10
	MOV DL, 1
    CALL SET_XY
MAIN_RETURN:
    MOV AX, 4C00H
    INT 21H
MAIN ENDP

;*************************CONUT*****************************
COUNT PROC NEAR ;统计mystu.txt中的学号的个数
    MOV AL,0             ;1.打开文件mystu.txt
    MOV AH,3DH
    MOV DX,OFFSET FILENAME
    INT 21H         
    CALL ERROR1          ;ERROR1判断文件是否打开成功
    MOV HANDLE,AX        ;HANDLE用来存储文件句柄
    MOV BX,AX

COUNT_LOOP:
    MOV CX,1             ;2.读文件，每次读一个字
    MOV DX,OFFSET BUF    
    MOV AH,3FH           
    INT 21H              
    CALL ERROR2          ;ERROR2判断读取文件是否成功
    CMP AX,1             ;进行比较：AX为1说明没有结束
    JNE COUNT_END         
    INC NUM              
    JMP COUNT_LOOP        

COUNT_END:
    MOV BX,HANDLE        ;3.关闭文件
    MOV AH,3EH      
    INT 21H
    MOV AX, NUM          
    CMP AX, 0            
    CALL ERROR3          ;ERROR3判断文件是否为空文件
    DEC AX
    MOV BL, 9
    DIV BL               
    INC AL
    MOV BL, AL           ;结果存到BL上，下面AX还有其它用
    RET
COUNT ENDP
;************************************************************

;*********************PRINT_ONE_CH**************************
;按照指定颜色输出一个字符
PRINT_ONE_CH PROC NEAR
    PUSH CX
    PUSH DX
    MOV AH,09H          ;按照指定的颜色输出一个字符
    INT 10H
                    
    MOV AH,03H          ;移动鼠标光标
    INT 10H
    INC DL
    MOV AH,02H
    INT 10H              

    POP DX
    POP CX
    RET
PRINT_ONE_CH ENDP
;***********************************************************

;***********************PRINT_NUM****************************
PRINT_NUM PROC NEAR 
    INC AX
    PUSH AX
    MOV BX, 10
    MOV CX, 0       
    AND AX, 00FFH
PUSH_LOOP:               ;通过循环模10，把结果压入栈中
    MOV DX, 0       
    DIV BX          
    PUSH DX        
    INC CX
    CMP AX, 0
    JNE PUSH_LOOP    
POP_LOOP:                ;这个循环负责把栈中的数字弹出并且打印
    POP DX
    ADD DL,'0'           ;数字转换成字符打印
    MOV AL,DL
    MOV BL,02H
    MOV BH,0
    CALL PRINT_ONE_CH    ;按照规定颜色打印单个字符
    DEC CX          
    JNE POP_LOOP
    POP AX
    RET
PRINT_NUM ENDP
;***********************************************************

;********************GET_RANDOM_NUM*************************
;得到一个1到N范围内的随机数
GET_RANDOM_NUM PROC NEAR 
    MOV AH, 0
    INT 1AH             ;只取DX来生成随机数
    MOV AX, DX
    AND AX, 00FFH
    DIV BL              ;除以学生的个数，获得一定区间的随机数
    MOV AL, AH          ;余数在AH中，把AH的值给AX
    AND AX, 00FFH
    
    PUSH AX             ;保存AX,BX的值
    PUSH BX
    MOV BX, 9
    MUL BX
    MOV LOOP_NUM, AX    ;得到学号在文件的相对位置
    POP BX              ;弹出BX，AX的值
    POP AX
    RET
GET_RANDOM_NUM ENDP;
;***********************************************************

;*********************PRINT_STU_NO**************************
;打开文件并且找到学号的相对位置，打印学号
PRINT_STU_NO PROC NEAR
    MOV AL,0             ;1.打开文件
    MOV AH,3DH
    MOV DX,OFFSET FILENAME 
    INT 21H         
    CALL  ERROR1         ;ERROR1判断文件是否打开成功
    MOV HANDLE,AX        ;HANDLE用来存储文件句柄
    MOV BX,AX

SKIP_LOOP:
    CMP LOOP_NUM, 0  
    JE PRINT_LOOP
    MOV AH,3FH           ;2.读文件，循环来一个字一个字的读
    MOV CX,1        
    MOV DX,OFFSET BUF      
    INT 21H         
    CALL ERROR2          ;ERROR2判断读取文件是否成功
    DEC LOOP_NUM     
    JMP SKIP_LOOP   
PRINT_LOOP:
    MOV AH,3FH           ;3.读文件（读到了需要打印的学号）
    MOV BX,HANDLE   
    MOV CX,1             ;还是一个字一个字的读
    MOV DX,OFFSET BUF   
    INT 21H         
    CALL  ERROR2         ;ERROR2判断读取文件是否成功
    MOV AL,BUF[0]   
    MOV BL,04H
    MOV BH,0
    CALL PRINT_ONE_CH

    DEC SEVEN            ;学号一共7位，需要输出7次
    CMP SEVEN,0      
    JE PRINT_END    
    JMP PRINT_LOOP
    
PRINT_END:
    MOV AH,3EH           ;4.关闭文件
    MOV BX,HANDLE   
    INT 21H         
    RET
PRINT_STU_NO ENDP
;***********************************************************

;*************************SET_XY****************************
;入口参数寄存器为DL DH
;作用为把光标移动到DH行DL列
SET_XY PROC NEAR
    PUSH AX
    PUSH BX
    MOV  AH, 2
	MOV  BH, 0
	INT  10H  
    POP  BX
    POP  AX
    RET
SET_XY ENDP
;***********************************************************

;************************SET_CLS****************************
;作用如同命令行界面的CLS：清屏
SET_CLS PROC NEAR
    PUSH AX
    MOV  AH,15
    INT  10H
    MOV  AH,0
    INT  10H         
    POP  AX
SET_CLS ENDP
;***********************************************************

;*******************ERROR1 ERROR2 ERROR3********************
;用于判断是否出现各种错误并且给出相应提示
ERROR1 PROC NEAR
    JNC ERROR1_RETURN
    MOV AL, 0
    MOV AH, 09H
    MOV DX, OFFSET ERROR_MSG1
    INT 21H
    JMP FAR PTR MAIN_RETURN
ERROR1_RETURN:
    RET
ERROR1 ENDP

ERROR2 PROC NEAR
    JNC ERROR2_RETURN
    MOV AL, 0
    MOV AH, 09H
    MOV DX, OFFSET ERROR_MSG2
    INT 21H
    JMP FAR PTR MAIN_RETURN
ERROR2_RETURN:
    RET
ERROR2 ENDP

ERROR3 PROC NEAR
    JNE ERROR3_RETURN
    MOV AL, 0
    MOV AH, 09H
    MOV DX, OFFSET ERROR_MSG3
    INT 21H
    JMP FAR PTR MAIN_RETURN
ERROR3_RETURN:
    RET
ERROR3 ENDP
;***********************************************************

CODE ENDS
     END MAIN