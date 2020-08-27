#include "stm32f4xx_hal.h"
#include "user_main.h"
#include "bsp_rtc.h"
#include "gui.h"
#include "bsp_usartx_CC2541.h"
#include "bmi160.h"
uint16_t rawStep_show[1]= {0};


uint8_t set_time_number;//修改第几个时间
uint16_t foot_aim_number=123;
uint8_t set_foot_number;
uint8_t a1,a2,a3,a4,a5;
uint8_t c1,c2,c3,c4,c5;
uint16_t cal=1023;
uint8_t power_hearth=10;

void Time_set_page(void)
{

    set_time_number=1;
    //  /* 获取当前时间 */
    HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
    //* 获取当前日期 *//
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

    LCD_ShowPicture(0,0,135,240,2);
    Word23(3,17,RED,stimestructureget.Hours);
    Word23(49,17,WHITE,stimestructureget.Minutes);
    Word23(95,17,WHITE,stimestructureget.Seconds);
    Word48(20,178,WHITE,sdatestructureget.Month);
    Word48(78,178,WHITE,sdatestructureget.Date);
}
void Show_1(void)

{
    LCD_Fill(0,0,135,240,BLACK);
    Show_top(3,5,128,24,WHITE,BLACK,roll_data-1);

    LCD_Fill(10,35,125,39,RED);
    LCD_ShowPicture(0,133,27,35,0);
    LCD_ShowPicture(108,133,27,35,1);

    Show_roll(39,60,55,180,roll_data-1,1);
}
void Chose_time(void) {
    if (set_time_number==0) {
        Word48(78,178,WHITE,sdatestructureget.Date);

        Word23(3,17,RED,stimestructureget.Hours);
        set_time_number++;
    } else 	if (set_time_number==1) {
        Word23(3,17,WHITE,stimestructureget.Hours);

        Word23(49,17,RED,stimestructureget.Minutes);
        set_time_number++;

    } else 	if (set_time_number==2) {
        set_time_number++;
        Word23(49,17,WHITE,stimestructureget.Minutes);

        Word23(95,17,RED,stimestructureget.Seconds);

    } else 	if (set_time_number==3) {
        set_time_number++;
        Word23(95,17,WHITE,stimestructureget.Seconds);

        Word48(20,178,RED,sdatestructureget.Month);

    } else 	if (set_time_number==4) {
        set_time_number=0;
        Word48(20,178,WHITE,sdatestructureget.Month);

        Word48(78,178,RED,sdatestructureget.Date);

    }


}
void Change_time(void) {
    if(set_time_number==0) {
        Word48(78,178,BLACK,sdatestructureget.Date);
        if(sdatestructureget.Date==30) {
            sdatestructureget.Date=1;
        } else {
            sdatestructureget.Date++;
        }
        Word48(78,178,RED,sdatestructureget.Date);
    } else if(set_time_number==1) {

        Word23(3,17,BLACK,stimestructureget.Hours);
        if(stimestructureget.Hours==23) {
            stimestructureget.Hours=1;
        } else {
            stimestructureget.Hours++;
        }

        Word23(3,17,RED,stimestructureget.Hours);

    } else if(set_time_number==2) {
        Word23(49,17,BLACK,stimestructureget.Minutes);

        if(stimestructureget.Minutes==59) {
            stimestructureget.Minutes=1;
        } else {
            stimestructureget.Minutes++;
        }
        Word23(49,17,RED,stimestructureget.Minutes);
    } else if(set_time_number==3) {

        Word23(95,17,BLACK,stimestructureget.Seconds);

        if(stimestructureget.Seconds==59) {
            stimestructureget.Seconds=1;
        } else {
            stimestructureget.Seconds++;
        }
        Word23(95,17,RED,stimestructureget.Seconds);
    } else if(set_time_number==4) {
        Word48(20,178,BLACK,sdatestructureget.Month);

        if(sdatestructureget.Month==12) {
            sdatestructureget.Month=1;
        } else {
            sdatestructureget.Month++;
        }
        Word48(20,178,RED,sdatestructureget.Month);

    }

}
void Time_page_reten(void) {
//	RTC_DateTypeDef sdatestructureget_2;
//RTC_TimeTypeDef stimestructureget_2;
    sdatestructureget.Month=	get_number_c(sdatestructureget.Month,2)*16+(get_number_c(sdatestructureget.Month,1));
//		sdatestructureget.WeekDay=	get_number_c(sdatestructureget.WeekDay,2)*16+(get_number_c(sdatestructureget.WeekDay,1));
    sdatestructureget.Date=	get_number_c(sdatestructureget.Date,2)*16+(get_number_c(sdatestructureget.Date,1));


    stimestructureget.Hours=	get_number_c(stimestructureget.Hours,2)*16+(get_number_c(stimestructureget.Hours,1));
    stimestructureget.Minutes=	get_number_c(stimestructureget.Minutes,2)*16+(get_number_c(stimestructureget.Minutes,1));
    stimestructureget.Seconds=	get_number_c(stimestructureget.Seconds,2)*16+(get_number_c(stimestructureget.Seconds,1));
    HAL_RTC_SetTime(&hrtc, &stimestructureget, RTC_FORMAT_BCD);
    HAL_RTC_SetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BCD);
}
void Foot_page(void) {
//	uint8_t a
    set_foot_number=1;
    LCD_Fill(0,0,135,240,BLACK);
    LCD_ShowPicture(38,12,60,30,61);
    LCD_ShowPicture(46,52,48,23,62);
    LCD_ShowPicture(41,119,59,58,63);

//	for(int i;i<5,i++){
//		a=get_number_c(foot_aim_number,i+1);
//			Word23_sig(6+i*21,108,BLUE,a);
//	}
    a1=get_number_c(foot_aim_number,1);
    a2=get_number_c(foot_aim_number,2);
    a3=get_number_c(foot_aim_number,3);
    a4=get_number_c(foot_aim_number,4);
    a5=get_number_c(foot_aim_number,5);

    Word23_sig(17,85,BLUE,a5);
    Word23_sig(38,85,WHITE,a4);
    Word23_sig(59,85,WHITE,a3);
    Word23_sig(80,85,WHITE,a2);
    Word23_sig(101,85,WHITE,a1);

}
//选择修改的目标步数位置
void Chose_foot(void)
{

    if(set_foot_number==0) {
        set_foot_number++;
        Word23_sig(101,85,WHITE,a1);
        Word23_sig(17,85,BLUE,a5);
    } else if(set_foot_number==1) {
        set_foot_number++;

        Word23_sig(17,85,WHITE,a5);
        Word23_sig(38,85,BLUE,a4);

    } else if(set_foot_number==2) {
        set_foot_number++;

        Word23_sig(38,85,WHITE,a4);
        Word23_sig(59,85,BLUE,a3);

    } else if(set_foot_number==3) {
        set_foot_number++;

        Word23_sig(59,85,WHITE,a3);
        Word23_sig(80,85,BLUE,a2);

    } else if(set_foot_number==4) {

        Word23_sig(80,85,WHITE,a2);
        Word23_sig(101,85,BLUE,a1);
        set_foot_number=0;
    }

}
void Change_foot(void) {

    if (set_foot_number==0) {
        Word23_sig(101,85,BLACK,a1);
        if(!(a1==9)) {
            a1++;
        } else {
            a1=0;
        }
        Word23_sig(101,85,BLUE,a1);

    } else if (set_foot_number==1) {
        Word23_sig(17,85,BLACK,a5);

        if(!(a5==5)) {
            a5++;
        } else {
            a5=0;
        }
        Word23_sig(17,85,BLUE,a5);


    } else if (set_foot_number==2) {
        Word23_sig(38,85,BLACK,a4);

        if(!(a4==9)) {
            a4++;
        } else {
            a4=0;
        }
        Word23_sig(38,85,BLUE,a4);

    } else if (set_foot_number==3) {
        Word23_sig(59,85,BLACK,a3);

        if(!(a3==9)) {
            a3++;
        } else {
            a3=0;
        }
        Word23_sig(59,85,BLUE,a3);

    } else if (set_foot_number==4) {
        Word23_sig(80,85,BLACK,a2);

        if(!(a2==9)) {
            a2++;
        } else {
            a2=0;
        }
        Word23_sig(80,85,BLUE,a2);

    }






}
void Foot_page_reten(void) {
    foot_aim_number=a1+a2*10+a3*100+a4*1000+a5*10000;

}
void Cal_page(void)
{
    LCD_Fill(0,0,135,240,BLACK);
    LCD_ShowPicture(38,12,60,30,61);
    LCD_ShowPicture(40,49,56,29,65);
    c1=get_number_c(cal,1);
    c2=get_number_c(cal,2);
    c3=get_number_c(cal,3);
    c4=get_number_c(cal,4);
    c5=get_number_c(cal,5);
    Word23_sig(17,105,ORG,c5);
    Word23_sig(38,105,ORG,c4);
    Word23_sig(59,105,ORG,c3);
    Word23_sig(80,105,ORG,c2);
    Word23_sig(101,105,ORG,c1);
    LCD_ShowPicture(53,151,30,16,64);
}
void Tip_page(void)
{
						    LCD_ShowPicture(0,0,135,240,67);

//    LCD_Fill(0,0,135,240,BLACK);

//    LCD_ShowIntNum(0,0,1234,4,WHITE,BLACK,16);
//		LCD_ShowIntNum(0,0,1234,4,WHITE,BLACK,16);
//	LCD_ShowIntNum(0,0,1234,4,WHITE,BLACK,16);
//	LCD_ShowIntNum(0,0,1234,4,WHITE,BLACK,16);
}

void Upset_time(void)


{

    /* 获取当前时间 */
    HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
    /* 获取当前日期 */
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
    static uint8_t M=0,D=0,h=0,m=0;
    if(sdatestructureget.Month!=M) {
        M=sdatestructureget.Month;
        Refresh(0);
        Word23(23,57,WHITE,sdatestructureget.Month);
    }
    if(sdatestructureget.Date!=D) {
        D=sdatestructureget.Date;
        Refresh(1);
        Word23(73,57,WHITE,sdatestructureget.Date);
    }
    if(stimestructureget.Hours!=h) {
        h=stimestructureget.Hours;
        Refresh(2);
        Word48(21,111,WHITE,stimestructureget.Hours);
    }
    if(stimestructureget.Minutes!=m) {
        m=stimestructureget.Minutes;
        Refresh(3);
        Word48(72,111,WHITE,stimestructureget.Minutes);
    }




}
void Set_host_time(void)


{
    /* 获取当前时间 */
    HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
    /* 获取当前日期 */
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
    Word23(23,57,WHITE,sdatestructureget.Month);
    Word23(73,57,WHITE,sdatestructureget.Date);
    Word48(21,111,WHITE,stimestructureget.Hours);
    Word48(72,111,WHITE,stimestructureget.Minutes);

}
void Show_aim_set() {
    uint8_t a=0;
    uint8_t b=38;
    for (uint8_t j=1; j<6; j++) {
        a=get_number_c(rawStep_show[0],j);
        if(!a) {
            b=b+6*j;
            break;
        }
    }
    if (rawStep_show[0]>=foot_aim_number) {
        LCD_ShowIntNum(b,205,rawStep_show[0],5,RED,WHITE,16);
    } else {
        LCD_ShowIntNum(b,205,rawStep_show[0],5,BLACK,WHITE,16);
    }
}
void Show_power_hearth() {
    uint16_t len3;
    char * redata3;
	if(    CC2541_Send_CMD_power("AT:ADC5\r\n")
){
    redata3=get_rebuff(&len3);
//    for(int i=0; i<21; i++) {
//        printf("%c",redata3[i]);
//    }
//		printf("%c",redata3[16]);
//	printf("%c",redata3[18]);
//	printf("%c",redata3[20]);
	uint16_t gg=100*(redata3[17]-48)+(redata3[19]-48)*10+(redata3[20]-48);
	if (gg>210){
	power_hearth=6;}
		else if(gg>200){power_hearth=7;}
		else if(gg>190){power_hearth=8;}
		else if(gg>180){power_hearth=9;}
		else{power_hearth=10;}

//		printf("%c",redata3[21]);
//	printf("%c",redata3[22]);
//	printf("%c",redata3[23]);
	}
            clean_rebuff(1);

}
void Host_page()
{
    bmi160_getStep(rawStep_show);
    LCD_ShowPicture(0,0,135,240,3);
    Set_host_time();
    LCD_ShowIntNum(17,205,foot_aim_number,5,BLACK,WHITE,16);
    Show_aim_set();
//Show_power_hearth();
	Show_power_hearth();
	    Show_top(98,8,32,14,BLACK,0X2995,power_hearth);

									                if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0){
														Show_top(83,6,8,15,BLACK,0X2995,5);
													}//振动+显示+提醒
//
}
void Heart_page(void)
{
    LCD_Fill(0,0,135,240,BLACK);
    LCD_ShowPicture(49,26,43,39,4);

}
