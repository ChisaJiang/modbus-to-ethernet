#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

TaskHandle_t xMasterTaskHandle = NULL;
void MasterTask(void *pvParameters);


void MasterTaskCreate(void)
{
    BaseType_t status = xTaskCreate(MasterTask, 
                                    "MasterTask", 
                                    512, 
                                    NULL, 
                                    5, 
                                    &xMasterTaskHandle);

    if(status != pdPASS)
        printf("MasterTaskCreate failed\r\n");
}

void MasterTask(void *pvParameters)
{
    eMBErrorCode    eStatus;
    eStatus = eMBMasterInit(MB_RTU, 2, 115200, MB_PAR_NONE);
    eStatus = eMBMasterEnable(  );
	if(eStatus != MB_ENOERR)
    {
        printf("Modbus Master Init Is Failed\r\n");
        vTaskDelete(NULL);
    }
    while(1)
    {
        eMBMasterPoll(  );
		//vTaskDelay(pdMS_TO_TICKS(10));  
    }
}
