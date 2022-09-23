/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_filex.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ittia/os/threadx/filex_file.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEFAULT_STACK_SIZE               (2 * 1024)
/* Thread_0 priority */
#define DEFAULT_THREAD_PRIO              10
/* Thread_0 preemption priority */
#define DEFAULT_PREEMPTION_THRESHOLD     DEFAULT_THREAD_PRIO

/* fx media buffer of size equals a one sector */
#define DEFAULT_MEDIA_BUF_LENGTH         512
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* Buffer for FileX FX_MEDIA sector cache. */
ULONG media_memory[DEFAULT_MEDIA_BUF_LENGTH/sizeof(ULONG)];
/* Define FileX global data structures.  */
FX_MEDIA        nor_flash_disk;
FX_FILE         fx_file;
/* Define ThreadX global data structures.  */
TX_THREAD       fx_thread;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void fx_thread_entry(ULONG thread_input);
void Error_Handler(void);
/* USER CODE END PFP */

/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_FileX_Init(VOID *memory_ptr)
{
  UINT ret = FX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_FileX_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END App_FileX_MEM_POOL */

  /* USER CODE BEGIN MX_FileX_Init */

  CHAR *pointer;

  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer, DEFAULT_STACK_SIZE, TX_NO_WAIT);

  /* Check DEFAULT_STACK_SIZE allocation*/
  if (ret != FX_SUCCESS)
  {
    /* Failed at allocating memory */
    Error_Handler();
  }

  /* Create the main thread.  */
  ret = tx_thread_create(&fx_thread, "thread 0", fx_thread_entry, 0, pointer, DEFAULT_STACK_SIZE,
                          DEFAULT_THREAD_PRIO, DEFAULT_PREEMPTION_THRESHOLD, TX_NO_TIME_SLICE, TX_AUTO_START);

  /* Check main thread creation */
  if (ret != FX_SUCCESS)
  {
    /* Failed at allocating memory */
    Error_Handler();
  }

  /* Initialize FileX.  */
  fx_system_initialize();

  /* USER CODE END MX_FileX_Init */

  return ret;
}

/* USER CODE BEGIN 1 */
void fx_thread_entry(ULONG thread_input)
{

  UINT status;
  ULONG available_space_pre;

  printf("FileX/LevelX NOR OCTO-SPI Application Start.\n");

  /* Print the absolute size of the NOR chip*/
  printf("Total NOR Flash Chip size is: %lu bytes.\n",(ULONG)LX_STM32_OSPI_FLASH_SIZE);

#if 1
  /* Format the NOR flash as FAT */
  status =  fx_media_format(&nor_flash_disk,
                            fx_stm32_levelx_nor_driver,   // Driver entry
                            (VOID*)LX_NOR_OSPI_DRIVER_ID,    // Device info pointer
                            (UCHAR *) media_memory,       // Media buffer pointer
                            DEFAULT_MEDIA_BUF_LENGTH,     // Media buffer size
                            "NOR_FLASH_DISK",             // Volume Name
                            1,                            // Number of FATs
                            32,                           // Directory Entries
                            0,                            // Hidden sectors
                            LX_STM32_OSPI_FLASH_SIZE / 512,    // Total sectors
                            512,                          // Sector size
                            8,                            // Sectors per cluster
                            1,                            // Heads
                            1);                           // Sectors per track

  /* Check if the format status */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }
#endif

  /* Open the OCTO-SPI NOR Flash disk driver.  */
  status =  fx_media_open(&nor_flash_disk, "FX_LX_NOR_DISK", fx_stm32_levelx_nor_driver,(VOID*)LX_NOR_OSPI_DRIVER_ID , (VOID *) media_memory, DEFAULT_MEDIA_BUF_LENGTH);

  /* Check the media open status.  */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  /* Get the available usable space */
  status =  fx_media_space_available(&nor_flash_disk, &available_space_pre);

  /* Check the get available state request status.  */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  printf("User available NOR Flash disk space size before database is written: %lu bytes.\n", available_space_pre);

  /* Enable ITTIA DB to access the FileX media. */
  /* The media must remain open until all databases are closed. */
  db_set_filex_media(&nor_flash_disk);

  while(1)
  {
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND / 2);
  }

}
/* USER CODE END 1 */
