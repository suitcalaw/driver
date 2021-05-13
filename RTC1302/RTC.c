#include "RTC.h"
//#include "user.h"
/*************************************************
DS1302控制字
bit 7  6   5   4   3   2   1   0
--------------------------------------
bit7:写操作时候必须为1
bit6：1：存取日历时钟数据；0：存取ram数据
bit5-bit1：寄存器地址
bit0：0：写操作；1：读操作

*************************************************/
/*----------------------------------------------------
函数名称：void DS1302WriteByte(u8 dat)
dat：要写入的数据
返回值：NONE
-----------------------------------------------------*/
void DS1302WriteByte(u8 dat)
{
    u8 i=0;
	
    DS1302_SDA_OUT();
    // user_delay_us(2)          /* user must write */
    // DS1302_Write(DS1302_PROTECT_WRITE,0x00);              // 关写保护
    SCLK_L;
    // user_delay_us(2)          /* user must write */
    for(i=0;i<8;i++)
    {
        //SDA=dat&0x01;
        if(dat&0x01)
            SDA_H;
        else
            SDA_L;
        // user_delay_us(2)      /* user must write */
        SCLK_H;
        // user_delay_us(2)      /* user must write */
        SCLK_L;
        dat>>=1;
    }
   // user_delay_us(2);
   // DS1302Write(DS1302_PROTECT_WRITE,0x80);                 // 开写保护
}
/*----------------------------------------------------
函数名称：u8 DS1302ReadByte()
返回值：读出的数据
-----------------------------------------------------*/
u8 DS1302ReadByte()
{
    u8 i=0,dat=0;

    DS1302_SDA_IN();
    // user_delay_us(2)          /* user must write */
    for(i=0;i<8;i++)
    {
        dat>>=1;
        if(SDA==1)
		{
			dat|=0x80;
		}
        SCLK_H;
       // user_delay_us(2)       /* user must write */
        SCLK_L;
       // user_delay_us(2)       /* user must write */

    }
    return dat;
}
/*----------------------------------------------------
函数名称：u8 DS1302Read(u8 addr)
addr:要读的寄存器地址
返回值：寄存器的值
-----------------------------------------------------*/
u8 DS1302Read(u8 addr)
{
   u8 dat=0;

   RSTs_L;
   SCLK_L;
   RSTs_H;
   DS1302WriteByte(addr);
   dat=DS1302ReadByte();
   SCLK_H;
   RSTs_L;
   return dat;
}
/*----------------------------------------------------
函数名称：void DS1302Write(u8 addr,u8 dat)
addr:要写的寄存器地址
dat：要写入的数据
返回值：NONE
-----------------------------------------------------*/
void DS1302Write(u8 addr,u8 dat)
{
   RSTs_L;
   SCLK_L;
   RSTs_H;
   DS1302WriteByte(addr);
   DS1302WriteByte(dat);
   SCLK_H;
   RSTs_L;
}
/*----------------------------------------------------
函数名称：u8 DS1302_burstRead(u8 addr,u8 *dat)
addr：要读出的地址
* dat：读出的数据 31byte
返回值：NONE
-----------------------------------------------------*/
void DS1302_burstRead(u8 addr,u8 *dat)
{
    u8 i=0;
	
    RSTs_L;
    SCLK_L;
    RSTs_H;
    DS1302WriteByte(addr);
    for(i=0;i<31;i++)
    {
        *dat=DS1302ReadByte(addr);
        dat++;
    }
    RSTs_L;
    SCLK_H;
}
/*----------------------------------------------------
函数名称：u8 DS1302_burstWrite(u8 addr,u8 *dat)
addr：要写入的地址
*dat：要写入的数据  31byte
返回值：NONE
-----------------------------------------------------*/
void DS1302_burstWrite(u8 addr,u8 *dat)
{
    u8 i=0,*ptr;
	
    ptr=dat;
    DS1302Write(DS1302_PROTECT_WRITE,0x00);                     // 关写保护
    RSTs_L;
    SCLK_L;
    RSTs_H;
    DS1302WriteByte(addr);
    for(i=0;i<31;i++)
    {
        DS1302WriteByte(*ptr);
        ptr++;
    }
    RSTs_L;
    SCLK_H;
    DS1302Write(DS1302_PROTECT_WRITE,0x80);                      // 开写保护
}

/*----------------------------------------------------
函数名称：void DS1302PortInit()
RST  单向输出
SDA  注意双向，写的时候配置为输出，读的时候配置为输入
SCLK 单向输出
返回值：NONE
-----------------------------------------------------*/
void DS302PortInit()
{
    //RST port output config   /* user must write */
   
    //SDA port output config   /* user must write */
    
    //SCLK port output config  /* user must write */


   DS1302Write(DS1302_PROTECT_WRITE,0x00);                        // 关写保护
   DS1302Write(DS1302_X_WRITE,0x00);                              // 关闭充电
   DS1302Write(DS1302_PROTECT_WRITE,0x80);                        // 开写保护
}
/*----------------------------------------------------
函数名称：void DS1302WriteClock(u8 *dat)
* dat:存进去的时间数据 7byte
顺序是：秒、分、时、日、月、星期、年
每个数据占用1个byte
返回值：NONE
-----------------------------------------------------*/
void DS1302WriteClock(u8 *dat)
{
    u8 i,dat_buf=0;

    DS1302Write(DS1302_PROTECT_WRITE,0x00);                       // 关写保护
    for(i=0;i<7;i++)
	{
        dat_buf=(((dat[i]/10)<<4)+(dat[i]%10));                   // HEX2BCD
        DS1302Write(DS1302_SECOND_WRITE+2*i,dat_buf);
    }
    DS1302Write(DS1302_PROTECT_WRITE,0x80);                       // 开写保护
}
/*----------------------------------------------------
函数名称：void DS1302ReadClock(u8 *dat)
* dat:读出来的时间数据 7byte
顺序是：秒、分、时、日、月、星期、年
每个数据占用1个byte
返回值：NONE
-----------------------------------------------------*/
void DS1302ReadClock(u8 *dat)
{
    u8 i,dat_buf=0;
	
    for(i=0;i<7;i++)
	{
        dat_buf=DS1302Read(DS1302_SECOND_READ+2*i);
        dat[i]=((dat_buf>>4)*10+(dat_buf&0x0f));                   // BCD2HEX
    }
}

