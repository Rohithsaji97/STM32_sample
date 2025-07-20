//LED Port - E
//LED Pin - 8-15
//LED BUS - AHB2
//USER PIN - PA0
#include<stdint.h>

//Address Setting
#define PERIPH_BASE 			(0x40000000UL)
#define AHB2PERIPH_OFFSET 		(0x08000000UL)
#define ABH2PERIPH_BASE 		(PERIPH_BASE + AHB2PERIPH_OFFSET)

#define GPIOE_OFFSET			(0x1000UL)
#define GPIOE_BASE				(ABH2PERIPH_BASE + GPIOE_OFFSET)

#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define RCC_OFFSET				(0x1000UL)

#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x14UL)
#define RCC_AHB1EN_R			(* (volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOE_MODE_R			(* (volatile unsigned int *)(GPIOE_BASE + MODE_R_OFFSET))

#define GPIOEEN					(1U << 21)  //0b 0000 0000 0010 0000 0000 0000 0000 0000 for GPIO E port

#define OD_R_OFFSET				(0x14UL)
#define GPIOE_OD_R				(* (volatile unsigned int *)(GPIOE_BASE + OD_R_OFFSET))

#define PIN8					(1U<<8)
#define LED_PIN					PIN8
/*
(1U << 16) //set mode register bit 16 to 1
&= ~(1U << 17) // set mode register bit 17 to 1
 */

typedef struct
{
  volatile uint32_t DUMMY[5];
  volatile uint32_t APB1ENR;      /*!< RCC APB1 peripheral clock enable register,                   Offset: 0x1C */
} RCC_TypeDef;


typedef struct
{
	//Although we don't need to mention unwanted GPIO registers memory alignment changes so its good to mention all (Each takes 4 bytes each)
	//Alternatively we can create dummy array to maintain the alignment and then delete unwanted
  volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00 */
  volatile uint32_t DUMMY[4];
  volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14 */
} GPIO_TypeDef;

#define RCC						((RCC_TypeDef *)RCC_BASE)
#define GPIOE					((GPIO_TypeDef *)GPIOE_BASE)


int main(void){
	//1. Enable clock access to GPIOE
	//RCC_AHB1EN_R |= GPIOEEN; // OR operator is used because other register bits may have other function and we should not disrupt it
	RCC->APB1ENR |= GPIOEEN;

	//2. Set PIN 8 as output pin
//	GPIOE_MODE_R |= (1U << 16); //set bit 16 to 1
//	GPIOE_MODE_R &=~(1U << 17); //set bit 17 to 0
	GPIOE->MODER |= (1U << 16);
	GPIOE->MODER &=~(1U << 17);


	while(1){
		/*3. Set PE8 high
		GPIOE_OD_R |= LED_PIN;
		*/
		//4. Toggle LED
		//GPIOE_OD_R ^= LED_PIN;
		GPIOE->ODR ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}
}
