/**
 * @file cli.h
 * @brief Command Line Interface (CLI) for Tetris game running on FreeRTOS.
 *
 * This header file defines the interfaces for a Command Line Interface (CLI)
 * that allows users to interact with the Tetris game and controls the settings
 * via a serial terminal. It includes definitions for initializing the CLI,
 * processing user input, and executing commands.
 */


#include "stdlib.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#ifndef CLI
#define CLI

/**
 * @brief Queue handle for CLI commands.
 *
 * This queue is used to communicate between the user input task
 * that receives serial data and the CLI task that processes the commands.
 */
extern QueueHandle_t xCLIQueue;

#define mainCLI_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

/**
 * @brief Initialize and run the CLI task.
 *
 * This function initializes the CLI environment and starts the CLI task for
 * processing user commands. It should be called during the system initialization
 * phase.
 *
 * @param parameters Pointer to parameters passed to the task if any (usually NULL).
 */
void vCLITask(void* parameters);

/**
 * @brief Clear the CLI screen.
 *
 * This function sends ANSI escape codes to clear the serial terminal screen and
 * reset the cursor position. It's used to refresh the CLI interface.
 */
void clearScrean();
#endif
