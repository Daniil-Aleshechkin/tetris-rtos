#include "stdlib.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#ifndef CLI
#define CLI

extern QueueHandle_t xCLIQueue;

#define mainCLI_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
void vCLITask(void* parameters);

#endif
