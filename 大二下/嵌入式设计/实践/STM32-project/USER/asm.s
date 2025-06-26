	AREA Reset, DATA, READONLY
	DCD 0X12345678
		
		
	DCD Reset_Handler
	AREP CORD_SEGMENT, CODE, READONLY
Reset_Handler proc
	export Reset_Handler [weak]
Start
	MOV R1, #1
	MOV R2, #2
	ADD R3, R1, R2
	ENDP
	END