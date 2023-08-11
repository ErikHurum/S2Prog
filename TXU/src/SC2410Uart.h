#ifndef SC2410UART_H
#define SC2410UART_H

class SC2410Uart:public TSNUart {
private:
	unsigned   BitSubRx,
	BitSubTx,
	BitSubErr;
	void    (*getRxChar) ();		 /* pointer to xmitr function */
	void    (*putTxChar) ();		/* pointer tp rcvr function */
	unsigned char *rRxReg,
	*rTxReg;
	unsigned *rLineControl,
	*rUartControl,
	*rFIFOControl,
	*rModemControl,
	*rTxRxStatus,
	*rRxErrorStatus,
	*rModemStatus,
	*rBaudRateDivisor,
	*rFIFOStatus;


public:

	SC2410Uart(int PortNum,unsigned BdRate,
						 unsigned WrdLength,unsigned StpBits,char Prty, unsigned BufSize, int Dev, int HWProt,int SWProt, bool IsMstr,int MaxTimeChar=0,bool Relax=false, int LogP=0, int LogE=0, int DelayP=0);
	void EnableInt(void);
	void EnableFIFO(int TxTrigger, int RxTrigger);
	bool Send(U8* Data, int Size,char EventMsk, bool Wait=true);
	void ActivateTx(void);
	void DeactivateTx(void);
	bool Receive(U8* Data, int Size, int TimeOut);
	void Transmit(void);
	void ReceiveInt(void);
	void ClearRxBuffer(void);
	void HandleInterrupt(void);
	bool HasMore(void);
};

#define TX_FIFO_FULL	0x100

#define ADDR_ULCON0     0x50000000 //UART 0 Line control
#define ADDR_UCON0      0x50000004 //UART 0 Control
#define ADDR_UFCON0     0x50000008 //UART 0 FIFO control
#define ADDR_UMCON0     0x5000000c //UART 0 Modem control
#define ADDR_UTRSTAT0   0x50000010 //UART 0 Tx/Rx status
#define ADDR_UERSTAT0   0x50000014 //UART 0 Rx error status
#define ADDR_UFSTAT0    0x50000018 //UART 0 FIFO status
#define ADDR_UMSTAT0    0x5000001c //UART 0 Modem status

#define ADDR_UTXH0 			0x50000020 //UART 0 Transmission Hold
#define ADDR_URXH0 			0x50000024 //UART 0 Receive buffer

#define ADDR_UBRDIV0    0x50000028 //UART 0 Baud rate divisor

#endif

