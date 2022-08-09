#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512

/* kservice optimization */

#define RT_DEBUG
#define RT_DEBUG_COLOR

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_MEMHEAP_AUTO_BINDING
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart3"
#define RT_VER_NUM 0x40100
#define ARCH_ARM
#define RT_USING_CPU_FFS
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M4

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 22
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 256
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_LFN_UNICODE_0
#define RT_DFS_ELM_LFN_UNICODE 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT
#define RT_DFS_ELM_MUTEX_TIMEOUT 3000
//#define RT_USING_FAL
//#define FAL_DEBUG_CONFIG
//#define FAL_DEBUG 1
//#define FAL_PART_HAS_TABLE_CFG
//#define FAL_USING_SFUD_PORT
//#define FAL_USING_NOR_FLASH_DEV_NAME "norflash0"

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 8192
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_RTC
#define RT_USING_SOFT_RTC
#define RT_USING_SDIO
#define RT_SDIO_STACK_SIZE 512
#define RT_SDIO_THREAD_PRIORITY 15
#define RT_MMCSD_STACK_SIZE 1024
#define RT_MMCSD_THREAD_PREORITY 22
#define RT_MMCSD_MAX_PARTITION 16
#define RT_USING_SPI
//#define RT_USING_QSPI
//#define RT_USING_SFUD
//#define RT_SFUD_USING_SFDP
//#define RT_SFUD_USING_FLASH_INFO_TABLE
//#define RT_SFUD_USING_QSPI
//#define RT_SFUD_SPI_MAX_HZ 50000000

/* Using USB */


/* C/C++ and POSIX layer */

#define RT_LIBC_DEFAULT_TIMEZONE 8

/* POSIX (Portable Operating System Interface) layer */

#define RT_USING_POSIX_FS

/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */


/* Network */

#define RT_USING_SAL
#define SAL_INTERNET_CHECK

/* protocol stack implement */

#define SAL_USING_AT
#define SAL_USING_POSIX
#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT
#define NETDEV_IPV4 1
#define NETDEV_IPV6 0
#define RT_USING_AT
#define AT_USING_CLIENT
#define AT_CLIENT_NUM_MAX 1
#define AT_USING_SOCKET
#define AT_USING_CLI
#define AT_CMD_MAX_LEN 512
#define AT_SW_VERSION_NUM 0x10301

/* Utilities */


/* RT-Thread Utestcases */


/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_WEBCLIENT
#define WEBCLIENT_USING_SAMPLES
#define WEBCLIENT_USING_FILE_DOWMLOAD
#define WEBCLIENT_NOT_USE_TLS
//#define WEBCLIENT_USING_SAL_TLS
//#define WEBCLIENT_USING_MBED_TLS
#define PKG_USING_WEBCLIENT_V220
#define PKG_WEBCLIENT_VER_NUM 0x20200

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

#define PKG_USING_NETUTILS
#define PKG_NETUTILS_NTP
#define NTP_USING_AUTO_SYNC
#define NTP_AUTO_SYNC_FIRST_DELAY 40
#define NTP_AUTO_SYNC_PERIOD 3600
#define NETUTILS_NTP_HOSTNAME "ntp6.aliyun.com"
#define NETUTILS_NTP_HOSTNAME2 "ntp.rt-thread.org"
#define NETUTILS_NTP_HOSTNAME3 "edu.ntp.org.cn"
#define PKG_USING_NETUTILS_LATEST_VERSION
#define PKG_NETUTILS_VER_NUM 0x99999
#define PKG_USING_AT_DEVICE
#define AT_DEVICE_USING_ESP32
#define AT_DEVICE_ESP32_INIT_ASYN
#define AT_DEVICE_ESP32_SOCKET
#define AT_DEVICE_ESP32_SAMPLE
#define ESP32_SAMPLE_WIFI_SSID "MI_dream-box"
#define ESP32_SAMPLE_WIFI_PASSWORD "1234567890"
#define ESP32_SAMPLE_CLIENT_NAME "uart6"
#define ESP32_SAMPLE_RECV_BUFF_LEN 10240
#define PKG_USING_AT_DEVICE_LATEST_VERSION
#define PKG_AT_DEVICE_VER_NUM 0x99999

///* IoT Cloud */

//#define PKG_USING_EZ_IOT_OS

///* ez-iot configuration */

//#define EZIOT_CORE_ENABLE
//#define EZIOT_CORE_MULTI_TASK
//#define EZIOT_CORE_ACEESS_TASK_STACK_SIZE 16384
//#define EZIOT_CORE_ACEESS_TASK_PRIORITY 5
//#define EZIOT_CORE_USER_TASK_STACK_SIZE 16384
//#define EZIOT_CORE_USER_TASK_PRIORITY 5
//#define EZIOT_CORE_MESSAGE_SIZE_MAX 16384
//#define EZIOT_CORE_MESSAGE_NUMBER_MAX 64
//#define EZIOT_CORE_EXTEND_COUNT 8
//#define EZIOT_CORE_RISK_CONTROL_CMD_MAX 16
//#define EZIOT_CORE_DEFAULT_PUBLISH_RETRY 2
//#define EZIOT_BASE_ENABLE
//#define EZIOT_HUB_ENABLE
//#define EZIOT_MODEL_ENABLE
//#define EZIOT_OTA_ENABLE
//#define EZIOT_OTA_TASK_STACK_SIZE 16384
//#define EZIOT_OTA_TASK_PRIORITY 10
//#define EZIOT_SHADOW_ENABLE
//#define EZIOT_SHADOW_TASK_PRIORITY 2
//#define EZIOT_SHADOW_STACK_SIZE 16384
//#define EZIOT_SHADOW_FULL_SYNC_RETRY_MAX 3
//#define EZIOT_SHADOW_FULL_SYNC_RETRY_INTERVAL 30
//#define EZIOT_SHADOW_FORCE_FULL_SYNC_INTERVAL 86400
//#define EZIOT_TSL_ENABLE
//#define EZIOT_TSL_SHADOW_SUPPORT
//#define EZIOT_TSL_LEGALITY_CHECK_WEAK
//#define EZIOT_TSL_DOWNLOAD_TASK_PRIORITY 5
//#define EZIOT_TSL_DOWNLOAD_STACK_SIZE 16384
//#define EZIOT_TSL_PROFILE_MAP_SIZE 4096
//#define EZIOT_TSL_PROFILE_SIZE 8192

///* os/bsp configuration */

//#define EZIOT_OS_KV_ENABLE
//#define EZIOT_OS_LIBC_ENABLE
//#define EZIOT_OS_MEM_ENABLE
//#define EZIOT_OS_SOCKET_ENABLE
//#define EZIOT_OS_SYSTEM_ENABLE
//#define EZIOT_OS_THREAD_ENABLE
//#define EZIOT_OS_TIME_ENABLE

/* components configuration */

#define EZIOT_COMPONENT_CJSON_ENABLE

/* unit-test configuration */


/* examples configuration */

//#define PKG_USING_EZ_IOT_OS_V20000

/* security packages */
//#define PKG_USING_MBEDTLS
/* Select Root Certificate */

//#define MBEDTLS_AES_ROM_TABLES
//#define MBEDTLS_ECP_WINDOW_SIZE 2
//#define MBEDTLS_SSL_MAX_CONTENT_LEN 3584
//#define PKG_USING_MBEDTLS_V27101


/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */


/* XML: Extensible Markup Language */


/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */

#define PKG_USING_LVGL
#define PKG_LVGL_THREAD_PRIO 20
#define PKG_LVGL_THREAD_STACK_SIZE 8192
#define PKG_LVGL_DISP_REFR_PERIOD 5
#define PKG_LVGL_VER_NUM 0x08020
//#define PKG_USING_LV_MUSIC_DEMO

/* u8g2: a monochrome graphic library */


/* PainterEngine: A cross-platform graphics application framework written in C language */


/* tools packages */


/* system packages */

/* enhanced kernel services */


/* acceleration: Assembly language or algorithmic acceleration packages */


/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */


/* Micrium: Micrium software products porting for RT-Thread */


/* peripheral libraries and drivers */

#define SDIO_MAX_FREQ 24000000

/* AI packages */


/* miscellaneous packages */

/* project laboratory */

/* samples: kernel and components samples */

#define PKG_USING_NETWORK_SAMPLES
#define PKG_USING_NETWORK_SAMPLES_LATEST_VERSION
#define NETWORK_SAMPLES_USING_HTTP_CLIENT

/* entertainment: terminal games and other interesting software packages */

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F4

/* Hardware Drivers Config */

#define SOC_STM32F469NI

/* Onboard Peripheral Drivers */

#define BSP_USING_SDRAM
#define BSP_USING_LCD_MIPI
#define BSP_USING_LCD_OTM8009A
#define BSP_USING_LVGL
//#define BSP_USING_QSPI_FLASH
#define BSP_USING_SDCARD
#define BSP_USING_TOUCH
#define BSP_TOUCH_INT_PIN 149
#define BSP_I2C_NAME "i2c1"

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART3
#define BSP_USING_UART6
#define BSP_USING_I2C1

/* Notice: PB8 --> 24; PB9 --> 25 */

#define BSP_I2C1_SCL_PIN 24
#define BSP_I2C1_SDA_PIN 25
#define BSP_USING_QSPI
#define BSP_USING_FMC
#define BSP_USING_SDIO
#define BSP_USING_LTDC

/* Board extended module Drivers */


#endif
