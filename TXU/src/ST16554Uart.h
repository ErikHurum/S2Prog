#ifndef ST165540UART_H
#define ST165540UART_H
typedef enum {
	Unknown, FIFOPresent, FIFONotPresent
} FIFOStatus;

class ST165540Uart:public TSNUart {
private:
	FIFOStatus  FIFOInstalled;
	U8 *UartBase;
	int LastTxTime;
public:
	ST165540Uart(int PortNum,unsigned BdRate,
							 unsigned WrdLength,unsigned StpBits,char Prty, unsigned BufSize, int Dev, int HWProt,int SWProt, bool IsMstr,int MaxTimeChar=0,bool Relax=false, int LogP=0, int LogE=0, int DelayP=0);

	FIFOStatus PhysicalHasFIFO(void);
	bool HasFIFO(void);
	void EnableFIFO(int Trigger);
	bool Send(U8* Data, int Size,char EventMsk, bool Wait=true);
	void ActivateTx(void);
	void DeactivateTx(void);
	bool Receive(U8* Data, int Size, int TimeOut);
	void Transmit(void);
	void ReceiveInt(void);
	void ClearRxBuffer(void);
	void EnableInt(void);
	void HandleInterrupt(void);
	bool HasMore(void);

};

/* UART port offsets */
#define RXB  0x00
#define TXB  0x00
#define IER  0x01
#define IIR  0x02
#define FCR  0x02
#define LCR  0x03
#define MCR  0x04
#define LSR  0x05
#define MSR  0x06
#define SCR  0x07
#define DLL  0x00
#define DLM  0x01
#define DEFAULT_TRIGGER_LEVEL 8 /* for 16550 UARTs          */

/* register definitions */

#define UART_THR        0x00	/* Transmitter holding reg. */
#define UART_RDR        0x00	/* Receiver data reg.       */
#define UART_BRDL       0x00	/* Baud rate divisor (LSB)  */
#define UART_BRDH       0x01	/* Baud rate divisor (MSB)  */
#define UART_IER        0x01	/* Interrupt enable reg.    */
#define UART_IID        0x02	/* Interrupt ID reg.        */
#define UART_LCR        0x03	/* Line control reg.        */
#define UART_MDC        0x04	/* Modem control reg.       */
#define UART_LST        0x05	/* Line status reg.         */
#define UART_MSR        0x06	/* Modem status reg.        */

/* equates for interrupt enable register */

#define IER_RXRDY	0x01	/* receiver data ready */
#define IER_TBE	0x02	/* transmit bit enable */
#define IER_LST	0x04	/* line status interrupts */
#define IER_MSI	0x08	/* modem status interrupts */

/* equates for interrupt identification register */

#define IIR_IP	    0x01	/* interrupt pending bit */
#define IIR_MASK	0x0F	/* interrupt id bits mask */
#define IIR_MSTAT   0x00	/* modem status interrupt */
#define IIR_THRE	0X02	/* transmit holding register empty */
#define IIR_RBRF	0x04	/* receiver buffer register full */
#define IIR_SEOB	0x06	/* serialization error or break */
#define IIR_TOUT    0x0c	/* char receive timeout */

/* equates for line control register */

#define LCR_CS5		0x00	/* 5 bits data size */
#define LCR_CS6		0x01	/* 6 bits data size */
#define LCR_CS7		0x02	/* 7 bits data size */
#define LCR_CS8		0x03	/* 8 bits data size */
#define LCR_2_STB  	0x04	/* 2 stop bits */
#define LCR_1_STB	0x00	/* 1 stop bit */
#define LCR_PEN		0x08	/* parity enable */
#define LCR_PDIS   	0x00	/* parity disable */
#define LCR_EPS		0x10	/* even parity slect */
#define LCR_SP		0x20	/* stick parity select */
#define LCR_SBRK	0x40	/* break control bit */
#define LCR_DLAB	0x80	/* divisor latch access enable */

/* equates for the modem control register */

#define MCR_DTR		0x01	/* dtr output */
#define MCR_RTS		0x02	/* rts output */
#define MCR_OUT1	0x04	/* output #1 */
#define MCR_OUT2	0x08	/* output #2 */
#define MCR_LOOP	0x10	/* loop back */

/* equates for line status register */

#define LSR_RXRDY	0x01	/* receiver data available */
#define LSR_OE		0x02	/* overrun error */
#define LSR_PE		0x04	/* parity error */
#define LSR_FE		0x08	/* framing error */
#define LSR_BI		0x10	/* break interrupt */
#define LSR_THRE	0x20	/* transmit holding register empty */
#define LSR_TEMT	0x40	/* transmitter empty */

/* equates for modem status register */

#define MSR_DCTS	0x01	/* cts change */
#define MSR_DDSR	0x02	/* dsr change */
#define MSR_DRI		0x04	/* ring change */
#define MSR_DDCD	0x08	/* data carrier change */
#define MSR_CTS		0x10	/* complement of cts */
#define MSR_DSR		0x20	/* complement of dsr */
#define MSR_RI		0x40	/* complement of ring signal */
#define MSR_DCD		0x80	/* complement of dcd */

/* FIFO Control Register */

#define FCR_EN			0x01	/* enable xmit and rcvr */
#define FIFO_ENABLE		FCR_EN
#define FCR_RXCLR		0x02	/* clears rcvr fifo */
#define RxCLEAR			FCR_RXCLR
#define FCR_TXCLR  		0x04	/* clears xmit fifo */
#define TxCLEAR			FCR_TXCLR
#define FCR_RXTRIG_L	0x40	/* rcvr fifo trigger lvl low */
#define FCR_RXTRIG_H	0x80	/* rcvr fifo trigger lvl high */


#define rEXT_UART0 ((U8*)0x08000000)
#define rEXT_UART1 ((U8*)0x10000000)
#define rEXT_UART2 ((U8*)0x18000000)
#define rEXT_UART3 ((U8*)0x20000000)

#define XTAL_UART     3686400L     // Frequency of UART Xtal


#define EVENT_TXBUF_EMPTY   1

#endif


