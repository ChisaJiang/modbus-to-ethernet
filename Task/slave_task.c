#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include "mb.h"
#include "mbport.h"

TaskHandle_t xSlaveTaskHandle = NULL;
void SlaveTask(void *pvParameters);


void SlaveTaskCreate(void)
{
    BaseType_t status = xTaskCreate(SlaveTask, 
                                    "SlaveTask", 
                                    256, 
                                    NULL, 
                                    5, 
                                    &xSlaveTaskHandle);

    if(status != pdPASS)
        printf("SlaveTaskCreate failed\r\n");
}

void SlaveTask(void *pvParameters)
{
    eMBErrorCode eStatus;
    eStatus = eMBInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE, 0);
    eStatus = eMBEnable();
    if(eStatus != MB_ENOERR){
        printf("eMBEnable failed\r\n");
        vTaskDelete(NULL);
    }
        
    while(1)
    {
        eMBPoll();
    }
}
