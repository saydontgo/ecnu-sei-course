COUNT EQU 0x20000004	
	AREA Reset,DATA,READONLY  ;ResetÎªÄ¬ÈÏµÄÈë¿ÚµØÖ·
	DCD 0X12345678            ;³ÌÐò´Ó0x08000000¿ªÊ¼ÔËÐÐ£¬
							  ; ËùÑ¡ÓÃµÄÐ¾Æ¬ STM32F429IGT6
							  ; °üº¬ 2M Flash£¬
							  ; µØÖ·Çø¼äÎª 0x08000000~0x08100000¡£
		                      ;¶øÏµÍ³½«Ö®ºóËÄ¸ö×Ö½ÚÄÚÈÝ·Ö¸øÁË¶ÑÕ»Ö¸Õë
							  ;ËùÒÔ¶¨Òå0x12345678·½±ã¹Û²ì
	DCD Reset_Handler         ;¶¨ÒåÒ»¸ö±êºÅ£¬×÷ÎªºóÃæµÄÊä³ö
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