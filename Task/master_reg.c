#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

//Master mode:DiscreteInputs variables

//Master mode:InputRegister variables
#define M_REG_INPUT_START             0
#define M_REG_INPUT_NREGS             100
USHORT   usMRegInStart                              = M_REG_INPUT_START;
USHORT   usMRegInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_INPUT_NREGS];
//Master mode:HoldingRegister variables


eMBErrorCode eMBMasterRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          REG_INPUT_START = M_REG_INPUT_START;
    USHORT          REG_INPUT_NREGS = M_REG_INPUT_NREGS;
    USHORT          iRegIndex;
    USHORT *        pusRegInputBuf;
    USHORT          usRegInStart;

    // 从站为1时，二维数组指向usMRegInBuf[0]，其他从站对应其他行
    pusRegInputBuf = usMRegInBuf[ucMBMasterGetDestAddress() - 1];
    usRegInStart = usMRegInStart;

    /* it already plus one in modbus function method. */
    usAddress--;

    if ((usAddress >= REG_INPUT_START)
            && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
    {
        iRegIndex = usAddress - usRegInStart;
        while (usNRegs > 0)
        {
            pusRegInputBuf[iRegIndex] = *pucRegBuffer++ << 8;
            pusRegInputBuf[iRegIndex] |= *pucRegBuffer++;
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
