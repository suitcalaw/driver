#ifndef _RTC_H_
#define _RTC_H_
 
//add the head file what you need here               /* user must write */
//#include "system/includes.h"
//#include "gpio.h"
/************************************************************************
//DS1302 �Ĵ�����
+----+-----+-----+----+-----+-------+----+----+----+----+---------+
|read|write|bit7 |bit6|bit5 |bit4   |bit3|bit2|bit1|bit0|  range  |
+----+-----+-----+------------------+-------------------+---------+
|81h | 80h |  CH |    10Seconds     |       Seconds     |  00-59  |
+----+-----+-----+------------------+-------------------+---------+
|83h | 82h |     |    10Minutes     |       Minutes     |  00-59  |
+----+-----+-----+------------------+-------------------+---------+
|85h | 84h |12/24| 0  |AM/PM|  Hour |        Hour       |1-12/0-23|
+----+-----+-----+----+-------------+-------------------+---------+
|87h | 86h |  0  | 0  |  10Date     |        Date       |  1-31   |
+----+-----+-----+----+-------------+-------------------+---------+
|89h | 88h |  0  | 0  |  0  |10Month|        Month      |  1-12   |
+----+-----+-----+----+-----+-------+-------------------+---------+
|8Bh | 8Ah |  0  | 0  |  0  |   0   |  0 |      Day     |  1-7    |
+----+-----+------------------------+-------------------+---------+
|8Dh | 8Ch |        10Year          |        Year       |  00-99  |
+----+-----+------------------------+-------------------+---------+
|8Fh | 8Eh |  WP | 0  |  0  |   0   | 0  | 0  | 0  | 0  |    -    |
+----+-----+-----+----+-----+-------+----+----+----+----+---------+
|91h | 90h | TCS |TCS | TCS |  TCS  | DS | DS | DS | DS |    -    |
+----+-----+-----+----+-----+-------+----+----+----+----+---------+
ע����Ĵ���bit7��1 ʱ��ֹͣ��ʱ��0 DS1302��������
    Сʱ�Ĵ���bit7�� 1 12Сʱ�ƣ�0 24Сʱ��
             bit5�� 1 PM     �� 0 AM
    д�����Ĵ���bit7�� WP=1 ���ܶ�DS1302����д����  WP=0 ������ȡ����
    ͻ��ģʽbit6��ָ��ʱ�ӻ�ram   bit0 ָ������д

 ʱ��ͻ��ģʽ�Ĵ���  CLOCK BURST  ����BFh  д��BEh
 RAMͻ��ģʽ�Ĵ���   RAM CURST    ����FFh  д��FEh
************************************************************************/

//�Ĵ�����ַ
#define DS1302_SECOND_WRITE  0x80               // ��
#define DS1302_SECOND_READ   0x81

#define DS1302_MINUTES_WRITE 0x82               // ��
#define DS1302_MINUTES_READ  0x83

#define DS1302_HOUR_WRITE    0x84               // ʱ
#define DS1302_HOUR_READ     0x85

#define DS1302_DATE_WRITE    0x86               // ��
#define DS1302_DATE_READ     0x87

#define DS1302_MONTH_WRITE   0x88               // ��
#define DS1302_MOMTH_READ    0x89

#define DS1302_DAY_WRITE     0x8A               // ����
#define DS1302_DAY_READ      0x8B

#define DS1302_YEAR_WRITE    0x8C               // ��
#define DS1302_YEAR_READ     0x8D

#define DS1302_PROTECT_WRITE 0x8E               // д�����Ĵ���
#define DS1302_PROTECT_READ  0x8F

//δ֪ 
#define DS1302_X_WRITE 0x90                     // ���ģʽ�Ĵ���
#define DS1302_X_READ  0x91

#define DS1302_CLOCK_BURST_WRITE 0x8E           // ʱ��ͻ��ģʽ�Ĵ���
#define DS1302_CLOCK_BURST_READ  0x8F

#define DS1302_RAM_BURST_WRITE   0x8E           // ramͻ��ģʽ�Ĵ���
#define DS1302_RAM_BURST_READ    0x8F

#define DS1302_SDA_OUT() \
    do { \
                    //the SDAportOutPut_config  /* user must write */
    } while(0)

#define DS1302_SDA_IN() \
    do { \
                    //the SDAportInPut_config   /* user must write */
    } while(0)


#define RSTs_H      //config RST = 1            /* user must write */
#define RSTs_L      //config RST = 0            /* user must write */

#define SDA_H       //config SDA = 1            /* user must write */
#define SDA_L       //config SDA = 0            /* user must write */


#define SDA         //SDA_Read config           /* user must write */

#define SCLK_H      //config SCLK = 1           /* user must write */
#define SCLK_L      //config SCLK = 0           /* user must write */

void DS302PortInit();
u8   DS1302Read(u8 addr);
void DS1302Write(u8 addr,u8 dat);

void DS1302ReadClock(u8 *dat);
void DS1302WriteClock(u8 *dat);
#endif                                          // _RTC_H_