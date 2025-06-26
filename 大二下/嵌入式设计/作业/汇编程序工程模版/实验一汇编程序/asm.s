COUNT EQU 0x20000004	
	AREA Reset,DATA,READONLY  ;Reset为默认的入口地址
	DCD 0X12345678            ;程序从0x08000000开始运行，
							  ; 所选用的芯片 STM32F429IGT6
							  ; 包含 2M Flash，
							  ; 地址区间为 0x08000000~0x08100000。
		                      ;而系统将之后四个字节内容分给了堆栈指针
							  ;所以定义0x12345678方便观察
	DCD Reset_Handler         ;定义一个标号，作为后面的输出
	AREA CODE_SEGMENT,CODE,READONLY
Reset_Handler proc
	export Reset_Handler [weak]
Start
	ADR r2, a
	ADR r3, b
	LDR r0, [r2]
	LDR r1, [r3]
	ADD r1, r1, r0
	MUL r0, r0, r1
	ADR r2, x
	STR r0, [r2]
	
	
	ENDP
	END