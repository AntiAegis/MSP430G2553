/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
//#define	USE_CHIP01


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER01.h"


#ifdef	USE_CHIP01
/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
void main (void)
{
	//-WDT-//
	wdtSetup(WDT_OFF, WDT_TIME_8MS);
	//=============================================================================================
	//-CLK-//
	clkSetup(CLK_DCO_1MHZ);
	//=============================================================================================
	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);
	//=============================================================================================
	//-UART-//
	uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_ON);
	//---------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
//		if(sRegisterStatus01.bRespToMst == 1)
//		{
//			cmn01MakeFrame(eSlv01SendToMst_Btn1);
//			txdStr(arrUART01);
//			sRegisterStatus01.bRespToMst = 0;
//		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* UART RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	/* Read RXD */
	varUART01 = rxdChar();
	gpioHigh(PORT1, LED_RED);

	/* Process data */
	switch (varUART01)
	{
		/* Header */
		case STARTING:
			sRegisterStatus01.bIsMst = 1;
			break;
		//=========================================================================================
		/* Ending */
		case FRAME_ENDING:
			sRegisterStatus01.bIsMst = 0;
			break;
		//=========================================================================================
		/* Data */
		default:
			if(sRegisterStatus01.bIsMst == 1)
				if(varUART01 == ADDR_SLV_01) sRegisterStatus01.bRespToMst = 1;
			break;
	}
	gpioLow(PORT1, LED_RED);
}


/**************************************************************************************************
 *	END OF MAIN01.c
 *************************************************************************************************/
#endif	/* USE_CHIP01 */
