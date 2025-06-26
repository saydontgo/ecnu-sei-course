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
	ADR r3, b
    LDR r0, [r3]
    ADR r3, c 
    LDR r1, [r3]
    OR r0, r1, r0 
    ADR r3, a 
    LDR r1, [r3]
    AND r1, r0, r1
    ADR r3, y
    STR r1, [r3]
	
	ENDP
	END