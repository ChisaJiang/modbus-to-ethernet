#include "mb.h"
#include "mbport.h"

#define S_REG_INPUT_START 0
#define S_REG_INPUT_NREGS 10
static USHORT   usRegInputStart = S_REG_INPUT_START;
static USHORT   usRegInputBuf[S_REG_INPUT_NREGS] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
	USHORT          REG_INPUT_START = S_REG_INPUT_START;
	USHORT          REG_INPUT_NREGS = S_REG_INPUT_NREGS;
    int             iRegIndex;

    usAddress--;
    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
