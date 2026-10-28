#include "port.h"
typedef enum {
    MODBUS_ROLE_SLAVE,
    MODBUS_ROLE_MASTER
} ModbusRole;

static volatile ModbusRole modbus_role = MODBUS_ROLE_SLAVE;

extern void MB_MasterTxReadyIRQ(void);
extern void MB_MasterRxReadyIRQ(void);
extern void MB_MasterTimerIRQ(void);

extern void MB_SlaveTxReadyIRQ(void);
extern void MB_SlaveRxReadyIRQ(void);
extern void MB_SlaveTimerIRQ(void);


void UX_USART_IRQ_HANDLER(void)
{
    if (__HAL_UART_GET_FLAG(&UX_UART, UART_FLAG_TXE) != RESET) {
        if (modbus_role == MODBUS_ROLE_MASTER) {
            MB_MasterTxReadyIRQ();
        } else {
            MB_SlaveTxReadyIRQ();
        }
    }

    if (__HAL_UART_GET_FLAG(&UX_UART, UART_FLAG_RXNE) != RESET) {
        if (modbus_role == MODBUS_ROLE_MASTER) {
            MB_MasterRxReadyIRQ();
        } else {
            MB_SlaveRxReadyIRQ();
        }
    }
}

void UX_TIM_IRQ_HANDLER(void)
{
    if(__HAL_TIM_GET_FLAG(&UX_TIM, TIM_FLAG_UPDATE) != RESET){
        __HAL_TIM_CLEAR_FLAG(&UX_TIM, TIM_FLAG_UPDATE);
        if(modbus_role == MODBUS_ROLE_MASTER){
            MB_MasterTimerIRQ();
        } else {
            MB_SlaveTimerIRQ();
        }
    }
}
