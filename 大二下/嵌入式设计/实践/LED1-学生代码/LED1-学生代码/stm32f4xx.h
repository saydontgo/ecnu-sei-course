
/*Ƭ���������ַ  */
#define PERIPH_BASE           ((unsigned int)0x40000000)                          

/*���߻���ַ */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)	

/*GPIO�������ַ*/
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00)


/* GPIOH�Ĵ�����ַ,ǿ��ת����ָ�� */
#define GPIOH_MODER				*(unsigned int*)(GPIOH_BASE+0x00)
#define GPIOH_OTYPER			*(unsigned int*)(GPIOH_BASE+0x04)
#define GPIOH_OSPEEDR			*(unsigned int*)(GPIOH_BASE+0x08)
#define GPIOH_PUPDR				*(unsigned int*)(GPIOH_BASE+0x0C)
#define GPIOH_IDR					*(unsigned int*)(GPIOH_BASE+0x10)
#define GPIOH_ODR					*(unsigned int*)(GPIOH_BASE+0x14)
#define GPIOH_BSRR					*(unsigned int*)(GPIOH_BASE+0x18)
#define GPIOH_LCKR					*(unsigned int*)(GPIOH_BASE+0x1C)
#define GPIOH_AFRL					*(unsigned int*)(GPIOH_BASE+0x20)
#define GPIOH_AFRH					*(unsigned int*)(GPIOH_BASE+0x24)

/*RCC�������ַ*/
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)

/*RCC��AHB1ʱ��ʹ�ܼĴ�����ַ,ǿ��ת����ָ��*/
#define RCC_AHB1ENR				*(unsigned int*)(RCC_BASE+0x30)
	

