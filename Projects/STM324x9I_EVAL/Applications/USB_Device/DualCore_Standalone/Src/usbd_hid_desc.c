/**
  ******************************************************************************
  * @file    USB_Device/DualCore_Standalone/Src/usbd_hid_desc.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    26-February-2014
  * @brief   This file provides the USBD HID descriptors and string formating method.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usbd_hid_desc.h"
#include "usbd_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USBD_HID_VID                      0x0483
#define USBD_HID_PID                      0x5710
#define USBD_HID_LANGID_STRING            0x409
#define USBD_HID_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_HID_PRODUCT_HS_STRING        "HID Joystick in HS Mode"
#define USBD_HID_SERIALNUMBER_HS_STRING   "00000000001A"
#define USBD_HID_PRODUCT_FS_STRING        "HID Joystick in FS Mode"
#define USBD_HID_SERIALNUMBER_FS_STRING   "00000000001B"
#define USBD_HID_CONFIGURATION_HS_STRING  "HID Config"
#define USBD_HID_INTERFACE_HS_STRING      "HID Interface"
#define USBD_HID_CONFIGURATION_FS_STRING  "HID Config"
#define USBD_HID_INTERFACE_FS_STRING      "HID Interface"

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t *USBD_HID_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_ManufacturerStrDescriptor (USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_ProductStrDescriptor (USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *USBD_HID_USRStringDesc (USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);  
#endif /* USB_SUPPORT_USER_STRING_DESC */  

/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef HID_Desc = {
  USBD_HID_DeviceDescriptor,
  USBD_HID_LangIDStrDescriptor, 
  USBD_HID_ManufacturerStrDescriptor,
  USBD_HID_ProductStrDescriptor,
  USBD_HID_SerialStrDescriptor,
  USBD_HID_ConfigStrDescriptor,
  USBD_HID_InterfaceStrDescriptor,
};

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t USBD_HID_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
  0x00,                       /* bcdUSB */
  0x02,
  0x00,                       /* bDeviceClass */
  0x00,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_HID_VID),           /* idVendor */
  HIBYTE(USBD_HID_VID),           /* idVendor */
  LOBYTE(USBD_HID_PID),           /* idVendor */
  HIBYTE(USBD_HID_PID),           /* idVendor */
  0x00,                       /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t USBD_HID_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
  USB_LEN_LANGID_STR_DESC,         
  USB_DESC_TYPE_STRING,       
  LOBYTE(USBD_HID_LANGID_STRING),
  HIBYTE(USBD_HID_LANGID_STRING), 
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t USBD_HID_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Returns the device descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  *length = sizeof(USBD_HID_DeviceDesc);
  return USBD_HID_DeviceDesc;
}

/**
  * @brief  Returns the LangID string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  *length = sizeof(USBD_HID_LangIDDesc);  
  return USBD_HID_LangIDDesc;
}

/**
  * @brief  Returns the product string descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == 0)
  {   
    USBD_GetString((uint8_t *)USBD_HID_PRODUCT_HS_STRING, USBD_HID_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_PRODUCT_FS_STRING, USBD_HID_StrDesc, length);    
  }
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the manufacturer string descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  USBD_GetString((uint8_t *)USBD_HID_MANUFACTURER_STRING, USBD_HID_StrDesc, length);
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the serial number string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {    
    USBD_GetString((uint8_t *)USBD_HID_SERIALNUMBER_HS_STRING, USBD_HID_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_SERIALNUMBER_FS_STRING, USBD_HID_StrDesc, length);    
  }
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the configuration string descriptor.    
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {  
    USBD_GetString((uint8_t *)USBD_HID_CONFIGURATION_HS_STRING, USBD_HID_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_CONFIGURATION_FS_STRING, USBD_HID_StrDesc, length); 
  }
  return USBD_HID_StrDesc;  
}

/**
  * @brief  Returns the interface string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == 0)
  {
    USBD_GetString((uint8_t *)USBD_HID_INTERFACE_HS_STRING, USBD_HID_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_INTERFACE_FS_STRING, USBD_HID_StrDesc, length);
  }
  return USBD_HID_StrDesc;  
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
