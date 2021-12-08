/****************************************************************
 * Copyright (C) 2016, XinLi, all right reserved.
 * File name:    delay.c
 * Date:         2016.03.22
 * Description:  Delay Driver
*****************************************************************/
 
/****************************************************************
 *                        Header include
*****************************************************************/
#include "delay.h"
 
/****************************************************************
 *                       Global variables
*****************************************************************/
 
 
/****************************************************************
 *                     Function declaration
*****************************************************************/
static void delay_Init(void);
 
/****************************************************************
 *                     Function definition
*****************************************************************/
 
/****************************************************************
 * Function:    delay_Init
 * Description: Delay Configuration.
 * Input:
 * Output:
 * Return:
*****************************************************************/
static void delay_Init(void)
{
  static uint8_t first = 0;
  
  if(first == 0)
  {
    first = 1;
    
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disability SysTick counter */
  }
}
 
/****************************************************************
 * Function:    delay_us
 * Description: Microsecond delay.
 * Input:       nus
 * Output:
 * Return:
*****************************************************************/
void delay_us(uint64_t nus)
{
  uint32_t temp = 0;
  uint64_t nms = 0;
  
  delay_Init();
  
  if(nus == 0)
  {
    return;
  }
  
  nms = nus / 1000;
  nus = nus % 1000;
  
  if(nms > 0)
  {
    delay_ms(nms);
  }
 
  if(nus > 0)
  {
    SysTick->LOAD = SystemCoreClock / 8000000 * nus;  /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                          /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;         /* Start the countdown */
 
    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */
 
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
  }
}
 
/****************************************************************
 * Function:    delay_ms
 * Description: Millisecond delay.
 * Input:       nms
 * Output:
 * Return:
*****************************************************************/
void delay_ms(uint64_t nms)
{
  uint32_t temp = 0;
  
  delay_Init();
  
  if(nms == 0)
  {
    return;
  }
  
  while(nms > 500)
  {
    SysTick->LOAD = SystemCoreClock / 8000 * 500; /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                      /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */
 
    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */
 
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
    
    nms -= 500;
  }
  
  SysTick->LOAD = SystemCoreClock / 8000 * nms; /* Time load (SysTick-> LOAD is 24bit) */
  SysTick->VAL = 0x000000;                      /* Empty counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */
 
  do
  {
    temp = SysTick->CTRL;
  }
  while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */
 
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
  SysTick->VAL = 0x000000;                    /* Empty counter */
}
 
/****************************************************************
 * Function:    Delay_s
 * Description: Second delay.
 * Input:       ns
 * Output:
 * Return:
*****************************************************************/
void delay_s(uint64_t ns)
{
  while(ns > 0)
  {
    delay_ms(1000);
    ns--;
  }
}
