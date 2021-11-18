//
//
#define LP			0x00
#define MC			0x01
#define FT6			0x02
#define IMU_VV_IO	0x03

//*****************************************************************************
//
//  SPI pins for PDI EtherCAT interface
//
//*****************************************************************************
#if HW_TYPE == LP

	#define ECAT_SSI_BASE                   SSI2_BASE
	#define ECAT_SSI_SYSCTL_PERIPH   		SYSCTL_PERIPH_SSI2

	#define ECAT_SSI_GPIO_PORTBASE         	GPIO_PORTB_BASE
	#define ECAT_SSI_GPIO_SYSCTL_PERIPH  	SYSCTL_PERIPH_GPIOB

	#define ECAT_SSI_CLK                	GPIO_PIN_4
	#define ECAT_SSI_CS                 	GPIO_PIN_5
	#define ECAT_SSI_RX_MISO               	GPIO_PIN_6
	#define ECAT_SSI_TX_MOSI               	GPIO_PIN_7

	#define ECAT_GPIO_PORTBASE              GPIO_PORTB_BASE
	#define ECAT_GPIO_SYSCTL_PERIPH  		SYSCTL_PERIPH_GPIOB

	#define ECAT_IRQ                		GPIO_PIN_0
	#define ECAT_EEPROM_LOADED      		GPIO_PIN_1

	#define LED_BASE      					GPIO_PORTF_BASE
	#define LED_PERIPH      				SYSCTL_PERIPH_GPIOF
	#define LED_PIN							GPIO_PIN_1

    #define SWITCH_BASE                     GPIO_PORTF_BASE
    #define SW1_PIN                         GPIO_PIN_4
    #define SW2_PIN                         GPIO_PIN_0


#elif HW_TYPE == MC

	#define ECAT_SSI_BASE                   SSI0_BASE
	#define ECAT_SSI_SYSCTL_PERIPH   		SYSCTL_PERIPH_SSI0

	#define ECAT_SSI_GPIO_PORTBASE         	GPIO_PORTA_BASE
	#define ECAT_SSI_GPIO_SYSCTL_PERIPH  	SYSCTL_PERIPH_GPIOA

	#define ECAT_SSI_CLK                	GPIO_PIN_2
	#define ECAT_SSI_CS                 	GPIO_PIN_3
	#define ECAT_SSI_RX_MISO               	GPIO_PIN_4
	#define ECAT_SSI_TX_MOSI               	GPIO_PIN_5

	#define ECAT_GPIO_PORTBASE              GPIO_PORTA_BASE
	#define ECAT_GPIO_SYSCTL_PERIPH  		SYSCTL_PERIPH_GPIOA

	#define ECAT_IRQ                		GPIO_PIN_7
	#define ECAT_EEPROM_LOADED      		GPIO_PIN_6

	#define LED_BASE            			GPIO_PORTE_BASE
	#define LED_PERIPH      				SYSCTL_PERIPH_GPIOE
	#define LED_PIN          				GPIO_PIN_4

#elif HW_TYPE == FT6

#elif HW_TYPE == IMU_VV_IO

	#define ECAT_SSI_BASE                   SSI0_BASE
	#define ECAT_SSI_SYSCTL_PERIPH   		SYSCTL_PERIPH_SSI0

	#define ECAT_SSI_GPIO_PORTBASE         	GPIO_PORTA_BASE
	#define ECAT_SSI_GPIO_SYSCTL_PERIPH  	SYSCTL_PERIPH_GPIOA

	#define ECAT_SSI_CLK                	GPIO_PIN_2
	#define ECAT_SSI_CS                 	GPIO_PIN_3
	#define ECAT_SSI_RX_MISO               	GPIO_PIN_4
	#define ECAT_SSI_TX_MOSI               	GPIO_PIN_5

	#define ECAT_GPIO_PORTBASE              GPIO_PORTA_BASE
	#define ECAT_GPIO_SYSCTL_PERIPH  		SYSCTL_PERIPH_GPIOA

	#define ECAT_IRQ                		GPIO_PIN_7
	#define ECAT_EEPROM_LOADED      		GPIO_PIN_6

	#define LED_BASE      					GPIO_PORTC_BASE
	#define LED_PERIPH      				SYSCTL_PERIPH_GPIOC
	#define LED_PIN							GPIO_PIN_7

#else
	#error "Unknown HW_TYPE"
#endif

#define ECAT_SSI_PINS            		(ECAT_SSI_RX_MISO | ECAT_SSI_TX_MOSI | ECAT_SSI_CLK)
