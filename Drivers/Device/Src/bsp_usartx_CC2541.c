/**
  ******************************************************************************
  * 文件名程: bsp_usartx.c
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2015-10-04
  * 功    能: 串口屏通讯
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F1Pro使用。
  *
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
#include "bsp_usartx_CC2541.h"
#include "usart.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/

/* 扩展变量 ------------------------------------------------------------------*/
extern uint8_t aRxBuffer;
extern uint8_t aRxBuffer2;



/**
  * 函数功能: 串口发送一个字节数据
  * 输入参数: ch：待发送字符
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendByte(uint8_t ch )
{
    while(__HAL_UART_GET_FLAG(&husartx,UART_FLAG_TXE)==0); //循环发送,直到发送完毕
    /* 发送一个字节数据到USART2 */
    HAL_UART_Transmit(&husartx,(uint8_t *)&ch,1,0xffff);

}

/**
  * 函数功能: 串口发送指定长度的字符串
  * 输入参数: str：待发送字符串缓冲器
  *           strlen:指定字符串长度
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendStr_length(uint8_t *str,uint32_t strlen )
{
    unsigned int k=0;
    do
    {
        Usart_SendByte( *(str + k) );
        k++;
    } while(k < strlen);
}

/**
  * 函数功能: 串口发送字符串，直到遇到字符串结束符
  * 输入参数: str：待发送字符串缓冲器
  * 返 回 值: 无
  * 说    明：无
  */
void Usart_SendString(uint8_t *str)
{
    unsigned int k=0;
    do
    {
        Usart_SendByte(*(str + k) );
        k++;
    } while(*(str + k)!='\0');
}

//中断缓存串口数据
#define UART_BUFF_SIZE      100
__IO  uint16_t uart_p = 0;
__IO  uint16_t uart_p2 = 0;
uint8_t   uart_buff[UART_BUFF_SIZE];
uint8_t   uart_buff2[UART_BUFF_SIZE];
//uint8_t   uart_buff3[100000];

/**
  * 函数功能: 接收中断回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
//	printf()
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

    if(UartHandle==&huart2) {
        if(uart_p<UART_BUFF_SIZE)
        {
            uart_buff[uart_p] =aRxBuffer;
            uart_p++;
            HAL_UART_Receive_IT(UartHandle,&aRxBuffer,1);

        }
        else
        {
            clean_rebuff(1);
        }
    }
    else {
        if(uart_p2<UART_BUFF_SIZE)
        {
            uart_buff2[uart_p2] =aRxBuffer2;
            uart_p2++;
            HAL_UART_Receive_IT(UartHandle,&aRxBuffer2,1);


        }
        else
        {
            clean_rebuff(2);
        }
    }
}

/**
  * 函数功能: 获取接收到的数据和长度
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
char *get_rebuff(uint16_t *len)
{
    *len = uart_p;
    return (char *)&uart_buff;
}
char *get_rebuff2(uint16_t *len2)
{
    *len2 = uart_p2;
    return (char *)&uart_buff2;
}

/**
  * 函数功能: 清空缓冲区
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void clean_rebuff(int a)
{

    uint16_t i=UART_BUFF_SIZE;

    if(a==1) {


        uart_p = 0;
        while(i)
            uart_buff[--i]=0;
    }
    else {

        uart_p2 = 0;
        while(i)
            uart_buff2[--i]=0;
    }
}

uint8_t CC2541_Send_CMD(char* cmd)
{
    uint16_t len;
    char * redata;
    uint8_t retry=2;
    uint8_t i;
    while(retry--)
    {
        clean_rebuff(1);
        delay_ms(10);
        Usart_SendString((uint8_t*)cmd);
        delay_ms(100);
        for(i=0; i<20; i++)
        {
            redata=get_rebuff(&len);
            if(len>0)
            {
//                if(strstr(redata,"CS"))
//                {
                    return 1;
//                }

            }
            delay_ms(200);
        }
    }
    clean_rebuff(1);
    return 0 ;
}
uint8_t CC2541_Send_CMD_blue(char* cmd)
{
    uint16_t len;
    char * redata;
    uint8_t retry=2;
    uint8_t i;
    while(retry--)
    {
        clean_rebuff(1);
        delay_ms(10);
        Usart_SendString((uint8_t*)cmd);
        delay_ms(100);

        for(i=0; i<4; i++)
        {
            redata=get_rebuff(&len);
            if(len>0)
            {
                if(strstr(redata,"N"))
                {


                    clean_rebuff(1);
                    return 0;
                }
            }
            else {

                delay_ms(100);
            }
        }
    }
    clean_rebuff(1);
    return 1 ;
}
uint8_t CC2541_Send_CMD_power(char* cmd)
{
    uint16_t len;
    char * redata;
    uint8_t retry=2;
    uint8_t i;
    while(retry--)
    {
        clean_rebuff(1);
        delay_ms(10);
        Usart_SendString((uint8_t*)cmd);
        delay_ms(100);

//        for(i=0; i<1; i++)
//        {
        redata=get_rebuff(&len);
        if(len>0)
        {
            if(strstr(redata,"ADC"))
            {
                return 1;
            }
        }
    }
//        }

    clean_rebuff(1);
    return 0 ;
}
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
