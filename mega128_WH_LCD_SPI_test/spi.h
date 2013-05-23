
#ifndef _SPI_H_
#define _SPI_H_ 1

//����������� ������ ���������� SPI
#define SPI_DDR		DDRB
#define SPI_CS_DDR	DDRB
#define SPI_CS_PORT PORTB

//����������� ����� ����������� SPI
#define CS1_PIN		0
//#define CS2	
//#define CS3	
#define MISO_PIN	3
#define MOSI_PIN	2
#define SCK_PIN		1
 
//����������� ������ SPI ����� UART
#define SPI_UART_DDR		DDRE
#define SPI_UART_CS_DDR		DDRE
#define SPI_UART_CS_PORT	PORTE

//����������� ����� SPI ����� UART
#define CS1_UART_PIN	7
//#define CS2	
//#define CS3	
#define MISO_UART_PIN	1
#define MOSI_UART_PIN	0
#define SCK_UART_PIN	2

#define SPI_CS1_LOW SPI_CS_PORT&=~_BV(CS1_PIN);
#define SPI_CS1_HIGH SPI_CS_PORT|=_BV(CS1_PIN);
   
// ������������� ����������� SPI � ������ Master
void SPI_Init_Master(void);
// ������������� ����������� SPI � ������ Slave
void SPI_Init_Slave(void);   
// �������� ����� �� SPI � ������ Master
void SPI_SendByte_Master(unsigned char data);  
// �������� ����� �� SPI � ������ Slave
void SPI_SendByte_Slave(unsigned char data);  
// ����� ����� �� SPI � ������ Master
unsigned char SPI_ReceiveByte_Master(void);  
// ����� ����� �� SPI � ������ Slave
unsigned char SPI_ReceiveByte_Slave(void);
// ����� ������� �� SPI � ������ Slave
unsigned char SPI_RotateByte_Slave(unsigned char data);

#endif /* _SPI_H */
