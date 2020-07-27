/*
 *  第八届初赛题 电子钟
 * 2020/7/27    by MRY
 */
#include <system.h>
#include <segment.h>
#include <ds1302.h>
#include <keyboard.h>
#include <intrins.h>

unsigned int SYSTICK;   //系统时间
unsigned int SYSTICK_tmp;
unsigned char SEG_CONTENT[] = {2, 3, 10, 5, 9, 10, 5, 0};   //初始值 23-59-50
unsigned char HOUR_RUN = 23;    //实时时钟数值
unsigned char MIN_RUN = 59;
unsigned char SEC_RUN = 50;
unsigned char HOUR_ALARM = 0;   //闹钟数值
unsigned char MIN_ALARM = 0;
unsigned char SEC_ALARM = 0;
unsigned char KEY_PRESSED = NONE_PRESSED;   //键盘扫描返回的按键值
unsigned char SYS_STATE;    //系统状态
unsigned char SETTING_MODE; //设定状态
bit BLINK = 0;    //闪烁状态 
unsigned char T;            //测量温度
unsigned char ALARM_COUNT = 0;  //闹钟次数
bit LED_FLAG = 1;         //LED闪烁FLAG
unsigned char ALARM_BREAK = 0;

void DS1302_WriteTime();
void DS1302_ReadTime();
void SegUpdate();
void NextState();
void SetBlink();
void Add_or_Sub(unsigned char mode);

/***********************
 ***********************/
void main()
{
    SysInit();
    SYSTICK = 0;
    DS1302_WriteTime();
    while(1){
        SYSTICK_tmp = SYSTICK;
        while(SYSTICK == SYSTICK_tmp) ;
        if(SYSTICK > 50000) SYSTICK = 0;    //系统时钟溢出设定 5s
        if(SYSTICK % 1100 == 0){     //110ms更新实时时钟
            SegUpdate(); 
            SetBlink();  
            if(HOUR_RUN == HOUR_ALARM && MIN_RUN == MIN_ALARM && SEC_RUN == SEC_ALARM && SYS_STATE != ALARM_RISING){ //80ms判断闹钟
                SYS_STATE = ALARM_RISING;
                ALARM_COUNT = 0;   
            }
        }
        if(SYSTICK % 600 == 0){     //60ms扫描键盘
            KEY_PRESSED = KeyScan();
            switch(KEY_PRESSED)
            {
            case NONE_PRESSED:
                break;
            case S7_PRESSED:    //按下S7实时设置
                if(SYS_STATE == IDLE)   SETTING_MODE = RUNTIME_SETTING;
                if(SETTING_MODE == RUNTIME_SETTING){
                    NextState();
                }
                if(SYS_STATE == ALARM_RISING){
                    SYS_STATE = IDLE; //中断闹钟
                    LatchCtrl(LED_ID, 0xFF);
                } 
                break;
            case S6_PRESSED:    //按下S6闹钟设置
                if(SYS_STATE == IDLE)   SETTING_MODE = ALARM_SETTING;
                if(SETTING_MODE == ALARM_SETTING){
                    NextState();
                }
                if(SYS_STATE == ALARM_RISING){
                    SYS_STATE = IDLE; //中断闹钟
                    LatchCtrl(LED_ID, 0xFF);
                } 
                break;
            case S5_PRESSED:    //按下S5加时
                Add_or_Sub(TIME_ADD);
                if(SYS_STATE == ALARM_RISING){
                    SYS_STATE = IDLE; //中断闹钟
                    LatchCtrl(LED_ID, 0xFF);
                } 
                break;
            case S4_PRESSED:    //按下S4减时
                Add_or_Sub(TIME_SUB);
                if(SYS_STATE == ALARM_RISING){
                    SYS_STATE = IDLE; //中断闹钟
                    LatchCtrl(LED_ID, 0xFF);
                } 
                break;
            default:
                break;
            }     
        }
    }
}


// 100us系统中断
void Timer0Routine() interrupt 1 
{
    SYSTICK ++;
    if(SYSTICK % 20 == 0){  //2ms刷新数码管
        SegFresh(SEG_CONTENT);
    }
    if(SYSTICK % 10000){    //1s闪烁判断
           BLINK = ~BLINK;
    }
    if(SYS_STATE == ALARM_RISING && SYSTICK % 2000 == 0){   //0.2sLED闹钟
        LatchCtrl(LED_ID, 0xFE + (unsigned char)LED_FLAG);
        LED_FLAG = ~ LED_FLAG;
        ALARM_COUNT ++;
        if(ALARM_COUNT >=25){           //5s
            LatchCtrl(LED_ID, 0xFF);
            SYS_STATE = IDLE;
            ALARM_COUNT = 0;
        }
    }
    
}


/*
 *  DS1302时钟写入
 * @param
 * hour min sec 写入的小时,分钟,秒
 */
void DS1302_WriteTime()
{
    Write_Ds1302(SEC_WRITE_ADDR,  ((SEC_RUN / 10) << 4) + (SEC_RUN % 10));  //写入秒
    Write_Ds1302(MIN_WRITE_ADDR,  ((MIN_RUN / 10) << 4) + (MIN_RUN % 10));  //写入分
    Write_Ds1302(HOUR_WRITE_ADDR, ((HOUR_RUN / 10) << 4) + (HOUR_RUN % 10)); //写入时
}


/*
 *  读取DS1302的时分秒
 */
void DS1302_ReadTime()
{
    unsigned char read_data, shi, ge;
    read_data = Read_Ds1302(SEC_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    SEC_RUN = shi * 10 + ge;
    read_data = Read_Ds1302(MIN_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    MIN_RUN = shi * 10 + ge;
    read_data = Read_Ds1302(HOUR_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    HOUR_RUN = shi * 10 + ge;
}


/*
 *  更新数码管的显示内容
 */
void SegUpdate()
{
    if(SYS_STATE == IDLE){  //正常显示状态
        DS1302_ReadTime();
        SEG_CONTENT[0] = HOUR_RUN / 10;
        SEG_CONTENT[1] = HOUR_RUN % 10;
        SEG_CONTENT[3] = MIN_RUN / 10;
        SEG_CONTENT[4] = MIN_RUN % 10;
        SEG_CONTENT[6] = SEC_RUN / 10;
        SEG_CONTENT[7] = SEC_RUN % 10;
    } 
}


/*
 *  时间设置时的闪烁
 */
void SetBlink()
{
    if(SETTING_MODE == RUNTIME_SETTING){
        SEG_CONTENT[0] = (BLINK && SYS_STATE == HOUR_SETTING)? 12 : HOUR_RUN / 10;
        SEG_CONTENT[1] = (BLINK && SYS_STATE == HOUR_SETTING)? 12 : HOUR_RUN % 10;
        SEG_CONTENT[3] = (BLINK && SYS_STATE == MIN_SETTING)? 12 : MIN_RUN / 10;
        SEG_CONTENT[4] = (BLINK && SYS_STATE == MIN_SETTING)? 12 : MIN_RUN % 10;
        SEG_CONTENT[6] = (BLINK && SYS_STATE == SEC_SETTING)? 12 : SEC_RUN / 10;
        SEG_CONTENT[7] = (BLINK && SYS_STATE == SEC_SETTING)? 12 : SEC_RUN % 10;
    }
    else if(SETTING_MODE == ALARM_SETTING){
        SEG_CONTENT[0] = (BLINK && SYS_STATE == HOUR_SETTING)? 12 : HOUR_ALARM / 10;
        SEG_CONTENT[1] = (BLINK && SYS_STATE == HOUR_SETTING)? 12 : HOUR_ALARM % 10;
        SEG_CONTENT[3] = (BLINK && SYS_STATE == MIN_SETTING)? 12 : MIN_ALARM / 10;
        SEG_CONTENT[4] = (BLINK && SYS_STATE == MIN_SETTING)? 12 : MIN_ALARM % 10;
        SEG_CONTENT[6] = (BLINK && SYS_STATE == SEC_SETTING)? 12 : SEC_ALARM / 10;
        SEG_CONTENT[7] = (BLINK && SYS_STATE == SEC_SETTING)? 12 : SEC_ALARM % 10;
    }
}

/*
 *  状态转换
 */
void NextState()
{
    if(SYS_STATE == IDLE)   SYS_STATE = HOUR_SETTING;
    else if(SYS_STATE == HOUR_SETTING) SYS_STATE = MIN_SETTING;
    else if(SYS_STATE == MIN_SETTING) SYS_STATE = SEC_SETTING;
    else if(SYS_STATE == SEC_SETTING){
        if(SETTING_MODE == RUNTIME_SETTING) DS1302_WriteTime(); //写入改后的时间
        SYS_STATE = IDLE;
        SETTING_MODE = NONE_SETTING;
    }
    else    SYS_STATE = IDLE;
}


/*
 *  加减时间处理    0~23h 0~59min 0~59s
 *  @param
 *  mode 加/减模式
 */
void Add_or_Sub(unsigned char mode)
{
    if(mode == TIME_ADD){
        switch (SYS_STATE)
        {
        case HOUR_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && HOUR_RUN < 23)    HOUR_RUN ++;
            else if(SETTING_MODE == ALARM_SETTING && HOUR_ALARM < 23)   HOUR_ALARM ++;
            break;
        case MIN_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && MIN_RUN < 59)    MIN_RUN ++;
            else if(SETTING_MODE == ALARM_SETTING && MIN_ALARM < 59)   MIN_ALARM ++;
            break;
        case SEC_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && SEC_RUN < 59)    SEC_RUN ++;
            else if(SETTING_MODE == ALARM_SETTING && SEC_ALARM < 59)   SEC_ALARM ++;
            break;
        default:
            break;
        }
    }
    else if(mode == TIME_SUB){
        switch (SYS_STATE)
        {
        case HOUR_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && HOUR_RUN > 0)    HOUR_RUN --;
            else if(SETTING_MODE == ALARM_SETTING && HOUR_ALARM >0)   HOUR_ALARM --;
            break;
        case MIN_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && MIN_RUN > 0)    MIN_RUN --;
            else if(SETTING_MODE == ALARM_SETTING && MIN_ALARM > 0)   MIN_ALARM --;
            break;
        case SEC_SETTING:
            if(SETTING_MODE == RUNTIME_SETTING && SEC_RUN > 0)    SEC_RUN --;
            else if(SETTING_MODE == ALARM_SETTING && SEC_ALARM > 0)   SEC_ALARM --;
            break;
        default:
            break;
        }
    }
}


