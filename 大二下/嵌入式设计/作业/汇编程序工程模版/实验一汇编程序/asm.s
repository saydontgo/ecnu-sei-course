COUNT EQU 0x20000004	
	AREA Reset,DATA,READONLY  ;ResetΪĬ�ϵ���ڵ�ַ
	DCD 0X12345678            ;�����0x08000000��ʼ���У�
							  ; ��ѡ�õ�оƬ STM32F429IGT6
							  ; ���� 2M Flash��
							  ; ��ַ����Ϊ 0x08000000~0x08100000��
		                      ;��ϵͳ��֮���ĸ��ֽ����ݷָ��˶�ջָ��
							  ;���Զ���0x12345678����۲�
	DCD Reset_Handler         ;����һ����ţ���Ϊ��������
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