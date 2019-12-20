/**
* @file  tool.c
* @brief  数据处理工具
* @author      lxf
* @date     2017-05-04
* @version  A002
* @copyright etslink.Ltd
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

//#include "Des_Encrypt.h"
//#include <des.h>


extern unsigned char const  auchCRCHi[];

extern unsigned char const auchCRCLo[];

const unsigned char  ShiftValue[16]={1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

const unsigned char  SBox1[64]=
{
    14,  4, 13,  1,  2,  15, 11,  8,  3,  10,  6,  12,  5,  9,  0,  7,
    0, 15,  7,  4,  14, 2,  13,  1,  10, 6 ,  12, 11,  9,  5,  3,  8,
    4,  1,  14,  8,  13, 6,  2,  11, 15,  12, 9,   7,  3,  10, 5,  0,
    15, 12, 8,   2,  4,  9,  1,   7,  5,  11,  3,  14, 10, 0,  6,  13
};

const unsigned char  SBox2[64]=
{
    15,  1,   8,  14,  6, 11,   3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3,  13,   4,   7, 15,  2,   8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0,  14,   7,  11, 10,  4,  13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8,  10,   1,  3, 15,   4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};
const unsigned char  SBox3[64]=
{
    10,  0,   9,  14,  6,  3,  15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,   0,   9,  3,  4,   6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,   4 ,  9,  8, 15,   3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10,  13,   0,  6,  9,   8,  7,  4, 15, 14,  3, 11,  5,  2, 12

};
const unsigned char  SBox4[64]=
{
    7, 13,  14,   3,  0,  6,   9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8,  11,   5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,   9,   0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,   0,   6, 10,  1,  13,  8,  9,  4,  5, 11, 12,  7,  2, 14

};
const unsigned char SBox5[64]=
{
    2, 12,  4,  1,  7, 10,  11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14, 2, 13,  6, 15,  0,  9, 10,  4,  5,  3

};
const unsigned char  SBox6[64]=
{

    12,  1, 10, 15, 9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2, 7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5, 2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12, 9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};
const unsigned char  SBox7[64]=
{
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12



};
const unsigned char  SBox8[64]=
{
    13,  2,  8, 4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13, 8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4, 1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14, 7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11

};


void GetTimes(unsigned char *timess);
void CurCalc_DES_Encrypt( unsigned char *Key,unsigned char *MsgIn,unsigned char *MsgOut);
void CurCalc_DES_Decrypt( unsigned char *Key,unsigned char *MsgIn,unsigned char *MsgOut);
void CurCalc_3DES_Decrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata );
void CurCalc_3DES_Encrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata );



void SysDelayMs(unsigned int ms)
{
    //Delayms(ms);
}

int PubDispData(const unsigned char * pcData,int nLen)
{
    int i = 0;
	  printf("\n");
    for(i = 0; i < nLen; i++)
    {
        printf("%02X ", *(pcData+i));
    }
    printf("\n");
    return 0;
}
void PubAllTrim(char *pszSrc)
{

}

int  PubAddSymbolToStr(char *pszString, int nLen, char ch, int nOption)
{

	return 0;
}

int  PubGetErrCode(void)
{

	return 0;
}
void PubGetCurrentDatetime(char *pDatetime)
{

}

// "62-----0826" 二磁道数据
int PubHexToAsc (const unsigned char* pszBcdBuf, int nLen, char cType, unsigned char* pszAsciiBuf)
{
    int i = 0;

    if (pszBcdBuf == NULL)
    {
        return APP_FAIL;
    }
    if (nLen & 0x01 && cType) /*判别是否为奇数以及往那边对齐*/
    {
        /*0左，1右*/
        i = 1;
        nLen ++;
    }
    else
    {
        i = 0;
    }
    for (; i < nLen; i ++, pszAsciiBuf ++)
    {
        if (i & 0x01)
        {
            *pszAsciiBuf = *pszBcdBuf ++ & 0x0f;
        }
        else
        {
            *pszAsciiBuf = *pszBcdBuf >> 4;
        }
        if (*pszAsciiBuf > 9)
        {
            *pszAsciiBuf += 'A' - 10;
        }
        else
        {
            *pszAsciiBuf += '0';
        }
    }
    *pszAsciiBuf = 0;
    return APP_SUCC;
}

/*****************************************************************
*Function :ReaderByteToBcd
* Params     nNum    ?data with IC card send to Terminal
*            ch       the length of data with IC card send to Terminal
*					 
*		
* Not: 0~99 hex to BCD
*******************************************************************/
int ReaderByteToBcd(int nNum, unsigned char *ch)
{
    if ((nNum < 0) || (nNum > 99))
    {
        return APP_FAIL;
    }
    *ch = ((nNum / 10) << 4) | (nNum % 10);
    return APP_SUCC;
}

//输入金额格式化4域
unsigned char AmountFormString(unsigned long value,unsigned char *Amountstr)
{
    unsigned char dbuf[10];
    unsigned char i;
    memcpy(Amountstr,"000000000000",12);//初始化

    dbuf[0]=(value/100000l)+'0';
    dbuf[1]=(value%100000l/10000l)+'0';
    dbuf[2]=(value%100000l%10000l/1000)+'0';
    dbuf[3]=(value%100000l%10000l%1000l/100)+'0';
    dbuf[4]=(value%100000l%10000l%1000l%100l/10)+'0';
    dbuf[5]=(value%100000l%10000l%1000l%100l%10)+'0';

    for(i=0;i<6;i++)Amountstr[i+6]= dbuf[i];
    return 0;
}
unsigned char CardSNFormSting(unsigned char SN,unsigned char *SNstr)
{
    unsigned char dbuf[4];
    unsigned char i;
    memcpy(SNstr,"000",3);//初始化

    dbuf[0]=(SN/10)+'0';
    dbuf[1]=(SN%10)+'0';
    // 	printf("CardSNFormSting\n");
    // 	printf("%.2x %.2x %.2x  \n",SN ,dbuf[0],dbuf[1]);
    SNstr[2]=dbuf[1];
    SNstr[1]=dbuf[0];
    //for(i=0;i<2;i++)SNstr[i+2]= dbuf[i];

    return 0;
}

//卡数据处理函数 主账户获取 通过磁道数据
int  GetPanFormTrace(unsigned char *szPan, unsigned char *panlen, unsigned char *expdata, const unsigned char *szTk2, const unsigned char *szTk3)
{
    int i;
    if (0 != szTk2[0])
    {
        for (i = 0; i < 37; i++)
        {
            if ((szTk2[i] == '=') || (szTk2[i] == 'D')) // d D 在上位机上导致的错误
            {
                break;
            }
        }
        if (i == 37)
        {
            return APP_FAIL;
        }
        if (i > 19)
        {
            memcpy(szPan, szTk2, 19);
            *panlen=19;
            memcpy(expdata,&szTk2[i+1],4);
            //	printf("panfrom\n");
            // PubDispData((const unsigned char*)szPan,19);
        }
        else
        {
            memcpy(szPan, szTk2, i);
            memcpy(expdata,&szTk2[i+1],4);
            //	printf("panfrom\n");
            //PubDispData((const unsigned char*)szPan,19);
            *panlen=i;
        }
        return APP_SUCC;
    }
    else if (0 != szTk3[0])
    {
        for (i = 0; i < 104; i++)
        {
            if (szTk3[i] == '=')
            {
                break;
            }
        }
        if (i == 104)
        {
            return APP_FAIL;
        }

        if (i > 19)
        {
            memcpy(szPan, szTk3, 19);
        }
        else
        {
            memcpy(szPan, szTk3, i);
        }
        return APP_SUCC;
    }
    return -1;
}

////////////////////////// add by lxf 0306
/*****************************************************************
*Function :ReaderGetData
* Params     gOutData    ?data with IC card send to Terminal
*          gOutDataLen   the length of data with IC card send to Terminal
*
*
* Not: 0~9999 hex to bcd
*******************************************************************/
int ReaderIntToBcd(unsigned char *psBcd, int pnBcdLen, int nNum)
{
    if ((nNum < 0) || (nNum > 9999) || (pnBcdLen < 2))
    {
        return APP_FAIL;
    }

    ReaderByteToBcd(nNum / 100, &psBcd[0]);
    ReaderByteToBcd(nNum % 100, &psBcd[1]);

    pnBcdLen = 2;
    return APP_SUCC;
}



void PubHexToBcd(unsigned char *hexbuf,unsigned char *bcdbuf,int len)
{
    unsigned char a,b;
    int i;
    for(i=0;i<len;i++)
    {
        a=hexbuf[i]/16;
        b=hexbuf[i]%16;
        bcdbuf[i]=10*a+b;
    }
}


void PubHexToTenBcd(unsigned char *hexbuf,unsigned char *bcdbuf,int len)
{
    unsigned char a,b;
    int i;
    for(i=0;i<len;i++)
    {
        a=hexbuf[i]/10;
        b=hexbuf[i]%10;
        bcdbuf[i]=a<<4|b;
    }
}

void PubAscToTenBcd(unsigned char *ascbuf,unsigned char *bcdbuf,int len)
{
    unsigned char hexbuf[300];
    unsigned char Tenbuf[300];
    PubAscToHex((unsigned char *)ascbuf,	len, 0, hexbuf);

    PubHexToBcd(hexbuf,Tenbuf,len/2);
    PubHexToTenBcd(Tenbuf,bcdbuf,len/2);
}


void PubAscToBcd(unsigned char *ascbuf,unsigned char *bcdbuf,int len)
{
    unsigned char hexbuf[1024];

    PubAscToHex((unsigned char *)ascbuf,	len, 0, hexbuf);

    PubHexToBcd(hexbuf,bcdbuf,len/2);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数名称：GetRandom
//函数功能：取随机数
//入口参数：无
//出口参数：random:随机数  randomlen:随机数的长度
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void GetRandom(unsigned char *random,unsigned char randomlen)
{
    unsigned char i;
		unsigned char time[6];
		unsigned long data;
		//GetTimes(time);
		data=time[0]*365*24*60*60+time[1]*30*24*60*60+time[2]*24*60*60+time[3]*60*60+time[4]*60+time[5];
		srand(data);
		for(i = 0; i < randomlen;i++ )
		{
				random[i]=rand()%256;
		}
}
*/


#include "string.h"
#include "stdio.h"

#define bit1    (0x01<<7)//0x80
#define bit2    (0x01<<6)//0x40
#define bit3    (0x01<<5)//0x20
#define bit4    (0x01<<4)//0x10
#define bit5    (0x01<<3)//0x08
#define bit6    (0x01<<2)//0x04
#define bit7    (0x01<<1)//0x02
#define bit8    (0x01<<0)//0x01

#define ENCRY	0x00
#define DECRY	0x01

//unsigned char  Min[8];
//unsigned char  Mout[8];
//unsigned char  des_key[16];*
//unsigned char  des_key_temp[8];
//unsigned char  mac_data[4];
//unsigned char TripleMAC(unsigned char *initdata,unsigned char *insdata,unsigned char datalen,unsigned char *key);
//void TDES(unsigned char MsgIn[],unsigned char Key[], unsigned char Mode);
//void Des( unsigned char MsgIn[], unsigned char MsgOut[], unsigned char Key[], unsigned char Mode)
//{

//}

/****************************************************************
unsigned int crc16(unsigned char *puchMsg,unsigned int usDataLen)
{
    unsigned char  uchCRCHi = 0xFF ;  // high byte of CRC initialized
    unsigned char uchCRCLo = 0xFF ;  // low byte of CRC initialized
    unsigned short uIndex  ;          // will index into CRC lookup table
     while (usDataLen--)             // Pass through message buffer
           {
              uIndex = uchCRCHi ^ *puchMsg++ ; // calculate the CRC
              uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
              uchCRCLo = auchCRCLo[uIndex] ;
           }
     return (((unsigned short)(uchCRCLo) << 8) | uchCRCHi) ;
}	// puchMsg message to calculate CRC upon
*************************************************************/


//void TDES( unsigned char MsgIn[], unsigned char Key[], unsigned char Mode)//Mode=0:加密 Mode=1：解密
//{
//    int i;
//    if(Mode ==0)//加密
//    {
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i];
//            Min[i]=MsgIn[i];
//        }
//        Des(Min, Mout, des_key_temp,0);
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i+8];
//            Min[i]=Mout[i];
//        }
//        Des(Min, Mout, des_key_temp,1);
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i];
//            Min[i]=Mout[i];
//        }
//        Des(Min, Mout, des_key_temp,0);
//    }
//    else//解密
//    {
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i];
//            Min[i]=MsgIn[i];
//        }
//        Des(Min, Mout, des_key_temp,1);
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i+8];
//            Min[i]=Mout[i];
//        }
//        Des(Min, Mout, des_key_temp,0);
//        for (i=0;i<8;i++)
//        {
//            des_key_temp[i]=Key[i];
//            Min[i]=Mout[i];
//        }
//        Des(Min, Mout, des_key_temp,1);
//    }
//}
/**********************************************************************************
原型:  　unsigned char TripleMAC(unsigned char *initdata,unsigned char *insdata,
                    unsigned char datalen,unsigned char *mackey)
功能: 　１６字节密钥ＭＡＣ加密
参数:   initdata:初始化数据　insdata: 待加密数据　datalen: 待加密数据长度　mackey: 16字节密钥
结果:   送出４字节的ＭＡＣ码　data_out: MAC 码
***********************************************************************************/
//unsigned char TripleMAC(unsigned char *initdata,unsigned char *insdata,unsigned char datalen,unsigned char *mackey)
//{
//    unsigned char macdata0[8],macdata1[8];
//    unsigned char len;
//    unsigned char i,j;
//    unsigned char L[8],R[8];
//    for(i=0;i<8;i++)
//        macdata0[i]=initdata[i];
//    j=datalen%8;
//    if(j!=0) return 1;
//    for(i=0;i<8;i++)
//    {
//        L[i]=mackey[i];
//        R[i]=mackey[i+8];
//    }
//    len=datalen/8;
//    for(j=0;j<len;j++)
//    {
//        for(i=0;i<8;i++)
//            macdata0[i] ^= insdata[i+j*8];

//        Des(macdata0,macdata1,L,ENCRY);
//        memcpy(macdata0,macdata1,8);
//    }
//    Des(macdata0,macdata1,R,DECRY);
//    memcpy(macdata0,macdata1,8);
//    Des(macdata0,macdata1,L,ENCRY);
//    for(i=0;i<8;i++)
//        mac_data[i]=macdata1[i];
//    return len;
//}
/**********************************************************************************
原型:   unsigned char SIngleMAC(unsigned char *initdata,unsigned char *insdata,
                    unsigned char datalen,unsigned char *mackey)
功能:  ８字节密钥ＭＡＣ加密
参数:   initdata:初始化数据　insdata: 待加密数据　datalen: 待加密数据长度　mackey: 8位密钥
结果:   送出４字节的ＭＡＣ码
***********************************************************************************/
//unsigned char SIngleMAC(unsigned char *initdata,unsigned char *insdata,unsigned char datalen,unsigned char *mackey)
//{
//    unsigned char macdata0[8];
//    unsigned char macdata1[8];
//    unsigned char len;
//    unsigned char i,j;
//    for(i=0;i<8;i++)
//        macdata0[i]=initdata[i];
//    j=datalen%8;
//    if(j!=0)
//    {
//        printf("ddd\r\n");
//        return 1;
//    }

//    len=datalen/8;
//    for(j=0;j<len;j++)
//    {
//        for(i=0;i<8;i++)
//            macdata0[i] ^= insdata[i+j*8];
//        Des(macdata0,macdata1,mackey,ENCRY);
//        memcpy(macdata0,macdata1,8);
//    }
//    memcpy(mac_data,macdata0,4);
//    return len;
//}

/************************************************************************************************************************
原型：void Des( unsigned char MsgIn[], unsigned char MsgOut[], unsigned char Key[], unsigned char Mode)
功能：对一个8字节的字符串进行单DES加解密计算
参数：MsgIn ：输入的明文（加密）或密文（解密） MsgOut ：输出的密文（加密）或明文（解密） Key:密钥　Mode:0(加密) 其它 (解密)
结果：无
************************************************************************************************************************/
void Des(unsigned char MsgIn[], unsigned char MsgOut[], unsigned char Key[], unsigned char Mode)
{
    unsigned char  i;
    unsigned char  temp1,temp2, temp3,temp4;
    unsigned char  C0[4], D0[4];
    unsigned char  Ki[8];
    //////////////////////////////////////////
    //	unsigned long int *p;
    //	char Msgtemp[8];
    //	char tempR[6];
    //	char C0[4], D0[4];
    //  char temp[8];
    //  处理64位数据块
    //  初始置换IP
    //  输出：L[0],R[0];
    //  L[0]从MsgOut[0]开始，R[0]从MsgOut[4]开始
    for(i=0; i<8; i++)
    {
        MsgOut[0]>>=1;
        MsgOut[1]>>=1;
        MsgOut[2]>>=1;
        MsgOut[3]>>=1;
        MsgOut[4]>>=1;
        MsgOut[5]>>=1;
        MsgOut[6]>>=1;
        MsgOut[7]>>=1;

        temp1=MsgIn[i];
        //	temp1=0x55;
        MsgOut[4] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[0] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[5] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[1] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[6] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[2] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[7] |= (temp1&0x80);
        temp1<<=1;
        MsgOut[3] |= (temp1&0x80);
    }
    //密钥处理
    //序列变换１（PC-1）
    //输出：C0, D0,各28bit
    for(i=0; i<8; i++)
    {
        C0[0]>>=1;
        C0[1]>>=1;
        C0[2]>>=1;
        C0[3]>>=1;
        D0[0]>>=1;
        D0[1]>>=1;
        D0[2]>>=1;

        temp1=Key[i];
        C0[0] |= (temp1&0x80);
        temp1<<=1;
        C0[1] |= (temp1&0x80);
        temp1<<=1;
        C0[2] |= (temp1&0x80);
        temp1<<=1;
        C0[3] |= (temp1&0x80);
        temp1<<=1;
        D0[2] |= (temp1&0x80);
        temp1<<=1;
        D0[1] |= (temp1&0x80);
        temp1<<=1;
        D0[0] |= (temp1&0x80);

    }

    D0[3]=(C0[3]&0x0f)|(D0[2]<<4);
    D0[2]=(D0[2]>>4)|(D0[1]<<4);
    D0[1]=(D0[1]>>4)|(D0[0]<<4);
    D0[0]=(D0[0]>>4)&0x0F;
    C0[3]&=0xf0;
    ////////////////////////////////////////

    for(i=0; i<16; i++)
    {
        //计算子密钥,输出Ki
        if(Mode == ENCRY)
        {
            for(temp1=0; temp1<ShiftValue[i]; temp1++)
            {

                if((C0[0]&bit1)!=0) C0[3]|=bit5;
                C0[0]<<=1;
                if((C0[1]&bit1)!=0) C0[0]|=bit8;
                C0[1]<<=1;
                if((C0[2]&bit1)!=0) C0[1]|=bit8;
                C0[2]<<=1;
                if((C0[3]&bit1)!=0) C0[2]|=bit8;
                C0[3]<<=1;

                //	D0
                D0[0]<<=1;
                if((D0[1]&bit1)!=0) D0[0]|=bit8;
                D0[1]<<=1;
                if((D0[2]&bit1)!=0) D0[1]|=bit8;
                D0[2]<<=1;
                if((D0[3]&bit1)!=0) D0[2]|=bit8;
                D0[3]<<=1;
                if((D0[0]&bit4)!=0)
                {
                    D0[3]|=bit8;
                    D0[0]&=0x0f;//(~bit4);
                }


            }
        }
        //把C[i]D[i]串联起来，变成Ki,共有56bit

        Ki[0]=C0[0];
        Ki[1]=C0[1];
        Ki[2]=C0[2];
        Ki[3]=C0[3]|D0[0];
        Ki[4]=D0[1];
        Ki[5]=D0[2];
        Ki[6]=D0[3];


        //序列变换２(PC-2)，变换后存入Ki中，共有48bit
        temp1=0;
        temp2=0;
        temp3=0;

        if((Ki[0]&bit1)!=0) temp1|=bit5;  //1
        if((Ki[0]&bit2)!=0) temp3|=bit8;  //2
        if((Ki[0]&bit3)!=0) temp1|=bit7;  //3
        if((Ki[0]&bit4)!=0) temp2|=bit8;  //4
        if((Ki[0]&bit5)!=0) temp1|=bit6;  //5
        if((Ki[0]&bit6)!=0) temp2|=bit2;  //6
        if((Ki[0]&bit7)!=0) temp3|=bit4;  //7
        if((Ki[0]&bit8)!=0) temp3|=bit2;  //8

        //		if((Ki[1]&bit1)!=0) temp1|=bit5;  // 9
        if((Ki[1]&bit2)!=0) temp2|=bit4;  //10
        if((Ki[1]&bit3)!=0) temp1|=bit3;  //11
        if((Ki[1]&bit4)!=0) temp2|=bit7;  //12
        if((Ki[1]&bit5)!=0) temp3|=bit7;  //13
        if((Ki[1]&bit6)!=0) temp1|=bit1;  //14
        if((Ki[1]&bit7)!=0) temp2|=bit1;  //15
        if((Ki[1]&bit8)!=0) temp3|=bit3;  //16
        //
        if((Ki[2]&bit1)!=0) temp1|=bit2;  //17
        //		if((Ki[2]&bit2)!=0) temp3|=bit8;  //18
        if((Ki[2]&bit3)!=0) temp2|=bit6;  //19
        if((Ki[2]&bit4)!=0) temp3|=bit6;  //20
        if((Ki[2]&bit5)!=0) temp2|=bit3;  //21
        //		if((Ki[2]&bit6)!=0) temp2|=bit2;  //22
        if((Ki[2]&bit7)!=0) temp2|=bit5;  //23
        if((Ki[2]&bit8)!=0) temp1|=bit4;  //24

        //		if((Ki[3]&bit1)!=0) temp1|=bit5;  //25
        if((Ki[3]&bit2)!=0) temp3|=bit1;  //26
        if((Ki[3]&bit3)!=0) temp3|=bit5;  //27
        if((Ki[3]&bit4)!=0) temp1|=bit8;  //28

        Ki[0]=temp1;
        Ki[1]=temp2;
        Ki[2]=temp3;

        temp1=0;
        temp2=0;
        temp3=0;

        if((Ki[3]&bit5)!=0) temp3|=bit7;
        if((Ki[3]&bit6)!=0) temp1|=bit7;
        if((Ki[3]&bit7)!=0) temp1|=bit3;
        if((Ki[3]&bit8)!=0) temp3|=bit8;

        if((Ki[4]&bit1)!=0) temp2|=bit3;
        if((Ki[4]&bit2)!=0) temp3|=bit1;
        //		if((Ki[4]&bit3)!=0) temp1|=bit7;
        if((Ki[4]&bit4)!=0) temp3|=bit6;
        if((Ki[4]&bit5)!=0) temp1|=bit4;
        //		if((Ki[4]&bit6)!=0) temp2|=bit2;
        if((Ki[4]&bit7)!=0) temp2|=bit7;
        if((Ki[4]&bit8)!=0) temp1|=bit8;

        if((Ki[5]&bit1)!=0) temp1|=bit1;
        if((Ki[5]&bit2)!=0) temp3|=bit4;
        //		if((Ki[5]&bit3)!=0) temp1|=bit7;
        if((Ki[5]&bit4)!=0) temp2|=bit5;
        if((Ki[5]&bit5)!=0) temp2|=bit2;
        if((Ki[5]&bit6)!=0) temp3|=bit3;
        if((Ki[5]&bit7)!=0) temp1|=bit5;
        if((Ki[5]&bit8)!=0) temp2|=bit4;


        if((Ki[6]&bit1)!=0) temp2|=bit6;
        if((Ki[6]&bit2)!=0) temp3|=bit5;
        if((Ki[6]&bit3)!=0) temp2|=bit1;
        if((Ki[6]&bit4)!=0) temp1|=bit2;
        if((Ki[6]&bit5)!=0) temp3|=bit2;
        //		if((Ki[6]&bit6)!=0) temp2|=bit2;
        if((Ki[6]&bit7)!=0) temp1|=bit6;
        if((Ki[6]&bit8)!=0) temp2|=bit8;

        Ki[3]=temp1;
        Ki[4]=temp2;
        Ki[5]=temp3;

        //此时已计算出Ki

        //把32位R扩展成48位,即把MsgOut[4]、MsgOut[５]、
        //MsgOut[６]、MsgOut[７]扩展,取得然后与Ki异或
        //

        //1
        temp1=((MsgOut[4]>>1)&0x7c);
        if((MsgOut[7]&bit8)!=0) temp1|=bit1;
        if((MsgOut[4]&bit4)!=0) temp1|=bit7;
        if((MsgOut[4]&bit5)!=0) temp1|=bit8;

        //扩展后R与Ki异或
        Ki[0]^=temp1;

        //2
        temp1=((MsgOut[4]<<5)&0xE0);
        if((MsgOut[5]&bit1)!=0) temp1|=bit4;
        if((MsgOut[4]&bit8)!=0) temp1|=bit5;
        temp1|=((MsgOut[5]>>5)&0x07);

        //扩展后R与Ki异或
        Ki[1]^=temp1;

        //3
        temp1=((MsgOut[5]<<3)&0xc0)|((MsgOut[5]<<1)&0x3e);
        if((MsgOut[6]&bit1)!=0) temp1|=bit8;
        Ki[2]^=temp1;

        //4
        temp1=((MsgOut[6]>>1)&0x7c);
        if((MsgOut[5]&bit8)!=0) temp1|=bit1;
        temp1|=((MsgOut[6]>>3)&0x03);

        Ki[3]^=temp1;

        //5
        temp1=((MsgOut[6]<<5)&0xE0);
        if((MsgOut[7]&bit1)!=0) temp1|=bit4;
        if((MsgOut[6]&bit8)!=0) temp1|=bit5;
        temp1|=((MsgOut[7]>>5)&0x07);

        Ki[4]^=temp1;

        //6
        temp1=((MsgOut[7]<<1)&0x3E);
        if((MsgOut[7]&bit4)!=0) temp1|=(bit1);
        if((MsgOut[7]&bit5)!=0) temp1|=(bit2);
        if((MsgOut[4]&bit1)!=0) temp1|=bit8;
        //扩展后R与Ki异或
        Ki[5]^=temp1;



        //	 	for(i=0; i<6; i++)
        //			Ki[i]^=tempR[i];

        //准备S盒的行列坐标
        /*		Ki[7]= Ki[5]&0x3F;
                Ki[6]= ((Ki[5]>>6))|((Ki[4]<<2)&0x3C);
                Ki[5]= (Ki[4]>>4)|((Ki[3]<<4)&0x30);
                Ki[4]= (Ki[3]>>2);
                Ki[3]= Ki[2]&0x3F;
                Ki[2]= ((Ki[2]>>6))|((Ki[1]<<2)&0x3C);
                Ki[1]= (Ki[1]>>4)|((Ki[0]<<4)&0x30);
                Ki[0]= (Ki[0]>>2);*/

        //选择SBox的值来替代，替代后的值存入Ki

        /*		i=((Ki[0]&0x20)>>4)|(Ki[0]&0x01);
                j=(Ki[0]&0x1E)>>1;
                Ki[0]=SBox1[i][j];

                i=((Ki[1]&0x20)>>4)|(Ki[1]&0x01);
                j=(Ki[1]&0x1E)>>1;
                Ki[1]=SBox2[i][j];

                i=((Ki[2]&0x20)>>4)|(Ki[2]&0x01);
                j=(Ki[2]&0x1E)>>1;
                Ki[2]=SBox3[i][j];

                i=((Ki[3]&0x20)>>4)|(Ki[3]&0x01);
                j=(Ki[3]&0x1E)>>1;
                Ki[3]=SBox4[i][j];



                i=((Ki[4]&0x20)>>4)|(Ki[4]&0x01);
                j=(Ki[4]&0x1E)>>1;
                Ki[4]=SBox5[i][j];

                i=((Ki[5]&0x20)>>4)|(Ki[5]&0x01);
                j=(Ki[5]&0x1E)>>1;
                Ki[5]=SBox6[i][j];

                i=((Ki[6]&0x20)>>4)|(Ki[6]&0x01);
                j=(Ki[6]&0x1E)>>1;
                Ki[6]=SBox7[i][j];

                i=((Ki[7]&0x20)>>4)|(Ki[7]&0x01);
                j=(Ki[7]&0x1E)>>1;
                Ki[7]=SBox8[i][j];*/

        temp1=0;

        if((Ki[5]&bit8)!=0) temp1|=bit4;
        if((Ki[5]&bit7)!=0) temp1|=bit8;
        if((Ki[5]&bit6)!=0) temp1|=bit7;
        if((Ki[5]&bit5)!=0) temp1|=bit6;
        if((Ki[5]&bit4)!=0) temp1|=bit5;
        if((Ki[5]&bit3)!=0) temp1|=bit3;
        Ki[7]=SBox8[temp1];

        temp1=0;
        if((Ki[5]&bit2)!=0) temp1|=bit4;
        if((Ki[5]&bit1)!=0) temp1|=bit8;
        if((Ki[4]&bit8)!=0) temp1|=bit7;
        if((Ki[4]&bit7)!=0) temp1|=bit6;
        if((Ki[4]&bit6)!=0) temp1|=bit5;
        if((Ki[4]&bit5)!=0) temp1|=bit3;
        Ki[6]=SBox7[temp1];

        temp1=0;
        if((Ki[4]&bit4)!=0) temp1|=bit4;
        if((Ki[4]&bit3)!=0) temp1|=bit8;
        if((Ki[4]&bit2)!=0) temp1|=bit7;
        if((Ki[4]&bit1)!=0) temp1|=bit6;
        if((Ki[3]&bit8)!=0) temp1|=bit5;
        if((Ki[3]&bit7)!=0) temp1|=bit3;
        Ki[5]=SBox6[temp1];

        temp1=0;
        if((Ki[3]&bit6)!=0) temp1|=bit4;
        if((Ki[3]&bit5)!=0) temp1|=bit8;
        if((Ki[3]&bit4)!=0) temp1|=bit7;
        if((Ki[3]&bit3)!=0) temp1|=bit6;
        if((Ki[3]&bit2)!=0) temp1|=bit5;
        if((Ki[3]&bit1)!=0) temp1|=bit3;
        Ki[4]=SBox5[temp1];

        temp1=0;
        if((Ki[2]&bit8)!=0) temp1|=bit4;
        if((Ki[2]&bit7)!=0) temp1|=bit8;
        if((Ki[2]&bit6)!=0) temp1|=bit7;
        if((Ki[2]&bit5)!=0) temp1|=bit6;
        if((Ki[2]&bit4)!=0) temp1|=bit5;
        if((Ki[2]&bit3)!=0) temp1|=bit3;
        Ki[3]=SBox4[temp1];

        temp1=0;
        if((Ki[2]&bit2)!=0) temp1|=bit4;
        if((Ki[2]&bit1)!=0) temp1|=bit8;
        if((Ki[1]&bit8)!=0) temp1|=bit7;
        if((Ki[1]&bit7)!=0) temp1|=bit6;
        if((Ki[1]&bit6)!=0) temp1|=bit5;
        if((Ki[1]&bit5)!=0) temp1|=bit3;
        Ki[2]=SBox3[temp1];

        temp1=0;
        if((Ki[1]&bit4)!=0) temp1|=bit4;
        if((Ki[1]&bit3)!=0) temp1|=bit8;
        if((Ki[1]&bit2)!=0) temp1|=bit7;
        if((Ki[1]&bit1)!=0) temp1|=bit6;
        if((Ki[0]&bit8)!=0) temp1|=bit5;
        if((Ki[0]&bit7)!=0) temp1|=bit3;
        Ki[1]=SBox2[temp1];

        temp1=0;
        if((Ki[0]&bit6)!=0) temp1|=bit4;
        if((Ki[0]&bit5)!=0) temp1|=bit8;
        if((Ki[0]&bit4)!=0) temp1|=bit7;
        if((Ki[0]&bit3)!=0) temp1|=bit6;
        if((Ki[0]&bit2)!=0) temp1|=bit5;
        if((Ki[0]&bit1)!=0) temp1|=bit3;
        Ki[0]=SBox1[temp1];

        //把上面的结果进行P置换
        temp1=0;
        temp2=0;
        temp3=0;
        temp4=0;

        if(Ki[0]&bit5)        //1
            temp2|=bit1;      //
        if(Ki[0]&bit6)        //2
            temp3|=bit1;      //
        if(Ki[0]&bit7)        //3
            temp3|=bit7;      //
        if(Ki[0]&bit8)        //4
            temp4|=bit7;      //
        //
        if(Ki[1]&bit5)        //5
            temp2|=bit5;      //
        if(Ki[1]&bit6)        //6
            temp4|=bit4;      //
        if(Ki[1]&bit7)        //7
            temp1|=bit2;      //
        if(Ki[1]&bit8)        //8
            temp3|=bit2;      //
        //
        if(Ki[2]&bit5)        //9
            temp3|=bit8;      //
        if(Ki[2]&bit6)        //10
            temp2|=bit8;      //
        if(Ki[2]&bit7)        //11
            temp4|=bit6;      //
        if(Ki[2]&bit8)        //12
            temp1|=bit6;      //
        //
        if(Ki[3]&bit5)        //13
            temp4|=bit2;      //
        if(Ki[3]&bit6)        //14
            temp3|=bit4;      //
        if(Ki[3]&bit7)        //15
            temp2|=bit2;      //
        if(Ki[3]&bit8)        //16
            temp1|=bit1;      //
        //
        if(Ki[4]&bit5)        //17
            temp1|=bit8;      //
        if(Ki[4]&bit6)        //18
            temp2|=bit6;      //
        if(Ki[4]&bit7)        //19
            temp4|=bit1;      //
        if(Ki[4]&bit8)        //20
            temp1|=bit3;      //
        //
        if(Ki[5]&bit5)        //21
            temp1|=bit4;      //
        if(Ki[5]&bit6)        //22
            temp4|=bit5;      //
        if(Ki[5]&bit7)        //23
            temp2|=bit3;      //
        if(Ki[5]&bit8)        //24
            temp3|=bit3;          //
        //
        if(Ki[6]&bit5)        //25
            temp4|=bit8;      //
        if(Ki[6]&bit6)        //26
            temp2|=bit4;      //
        if(Ki[6]&bit7)        //27
            temp3|=bit6;      //
        if(Ki[6]&bit8)        //28
            temp1|=bit7;      //
        //
        if(Ki[7]&bit5)        //29
            temp1|=bit5;      //
        if(Ki[7]&bit6)        //30
            temp4|=bit3;      //
        if(Ki[7]&bit7)        //31
            temp2|=bit7;      //
        if(Ki[7]&bit8)        //32
            temp3|=bit5;      //
        //
        //保存R               //
        Ki[0]=MsgOut[4];      //
        Ki[1]=MsgOut[5];      //
        Ki[2]=MsgOut[6];      //
        Ki[3]=MsgOut[7];      //

        //计算新的R
        MsgOut[4]=temp1^MsgOut[0];
        MsgOut[5]=temp2^MsgOut[1];
        MsgOut[6]=temp3^MsgOut[2];
        MsgOut[7]=temp4^MsgOut[3];
        //用上一次的R作为这一次的L

        MsgOut[0]=Ki[0];
        MsgOut[1]=Ki[1];
        MsgOut[2]=Ki[2];
        MsgOut[3]=Ki[3];

        if(Mode != ENCRY)
        {
            for(temp1=0; temp1<ShiftValue[15-i]; temp1++)
            {
                C0[3]>>=1;
                if((C0[2]&bit8)!=0) C0[3]|=bit1;
                C0[2]>>=1;
                if((C0[1]&bit8)!=0) C0[2]|=bit1;
                C0[1]>>=1;
                if((C0[0]&bit8)!=0) C0[1]|=bit1;
                C0[0]>>=1;
                if((C0[3]&bit5)!=0)
                {
                    C0[3]&=0xF0;//(~bit5);
                    C0[0]|=bit1;

                }
                if((D0[3]&bit8)!=0) D0[0]|=bit4;
                D0[3]>>=1;
                if((D0[2]&bit8)!=0) D0[3]|=bit1;
                D0[2]>>=1;
                if((D0[1]&bit8)!=0) D0[2]|=bit1;
                D0[1]>>=1;
                if((D0[0]&bit8)!=0) D0[1]|=bit1;
                D0[0]>>=1;
            }
        }
    }
    //对R[16]L[16]进行置换，Final Permutation (IP**-1)
    Ki[0]=MsgOut[0];
    Ki[1]=MsgOut[4];
    Ki[2]=MsgOut[1];
    Ki[3]=MsgOut[5];


    Ki[4]=MsgOut[2];
    Ki[5]=MsgOut[6];
    Ki[6]=MsgOut[3];
    Ki[7]=MsgOut[7];

    for(i=0; i<8; i++)
    {
        MsgOut[0]<<=1;
        MsgOut[1]<<=1;
        MsgOut[2]<<=1;
        MsgOut[3]<<=1;
        MsgOut[4]<<=1;
        MsgOut[5]<<=1;
        MsgOut[6]<<=1;
        MsgOut[7]<<=1;

        MsgOut[0] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[1] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[2] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[3] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[4] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[5] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[6] |= (Ki[i]&0x01);
        Ki[i]>>=1;
        MsgOut[7] |= (Ki[i]&0x01);
    }

    /*
        40 8 48 16 56 24 64 32
        39 7 47 15 55 23 63 31
        38 6 46 14 54 22 62 30
        37 5 45 13 53 21 61 29
        36 4 44 12 52 20 60 28
        35 3 43 11 51 19 59 27
        34 2 42 10 50 18 58 26
        33 1 41 9  49 17 57 25

        */
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//原型：　　void Diversify(unsigned char mk[16],unsigned char data[8], unsigned char dk[16])
//函数功能：密钥分散算法，将一个双长度的主密钥MK，对分散数据进行处理，推导出双长度密钥DK。对应4.3.1
//参数：mk: 16字节主密钥  data: 8字节分散因子    dk: 推导出的双长度密钥DK
///////////////////////////////////////////////////////////////////////////////////////////////////
//void Diversify(unsigned char mk[16],unsigned char indata[8], unsigned char dk[16])
//{
//    unsigned char i;
//    unsigned char temp[8];
//    TDES(indata,mk,ENCRY);
//    memcpy(dk,Mout,8);
//    for(i=0;i<8;i++)
//    {                  //data 取反作为右半密钥生成的输入因子
//        temp[i] = ~indata[i];
//    }
//    TDES(temp,mk,ENCRY);
//    memcpy(dk+8,Mout,8);
//}


#include "tool.h"
#include "string.h"

//???ù????×?BCD??
/********************************************
unsigned char HexToSerialBCD( unsigned char *hexSrc, unsigned char *BcdDes, unsigned int num ,unsigned char mode)
{
        unsigned int i=0,j;
        unsigned char dbuf[2];

        if(mode==0)//0--99 ??16???????? 1×???BCD??±í??  ?? 0x0E-->0x14 ; 0x11-->0x17
        {
                for(j=0;j<num;j++)
                {
                        //hexSrc[j]= hexSrc[j]
                        dbuf[0]=hexSrc[j]%100/10;
                        dbuf[1]=hexSrc[j]%100%10;
                        BcdDes[j]= (dbuf[0]<<4) | dbuf[1];
                }
        }
        else if(mode==1)////0--99 ??16???????? 2×???BCD??±í??  ?? 0x0E-->0x01 0x04   ; 0x11-->0x01 0x07
        {
                for(j=0;j<num;j++)
                {
                        //hexSrc[j]= hexSrc[j]
                        BcdDes[i]=   hexSrc[j]%100/10;
                        BcdDes[i+1]= hexSrc[j]%100%10;
                        i=i+2;
                }
        }
        return 0;
}
*//////////////////////////////////////



//算法数据处理工具

/************************************************************************************************
*
*  异或
*************************************************************************************************/
void DataXOR( unsigned char *source, unsigned char *dest, int size, unsigned char *out )
{
    int i;
    for( i = 0; i<size; i++ ) out[i] = dest[i] ^ source[i];
}

//秘钥算法接口

void CurCalc_DES_Encrypt( unsigned char *Key,unsigned char *MsgIn,unsigned char *MsgOut)
{
    Des(MsgIn,MsgOut,Key,0);//加密
}

void CurCalc_DES_Decrypt( unsigned char *Key,unsigned char *MsgIn,unsigned char *MsgOut)
{
    Des(MsgIn,MsgOut,Key,1);//解密
}

/**************************************************************************************************************
*
* 函数原型：void CurCalc_3DES_Encrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata )
*
* 函数功能：3DES加密
*
* 函数输入：inkey		16字节密码
*			indata		8字节需要加密的数据
*
* 函数输出：outdata		8字节加密结果输出
*
* 函数返回：无
****************************************************************************************************************/
void CurCalc_3DES_Encrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata )
{
    unsigned char LKey[8];
    unsigned char RKey[8];
    unsigned char TmpDest[8];

    memcpy( LKey, inkey,   8 );
    memcpy( RKey, inkey+8, 8 );

    CurCalc_DES_Encrypt( LKey, indata,  outdata );			//加
    CurCalc_DES_Decrypt( RKey, outdata, TmpDest );			//解
    CurCalc_DES_Encrypt( LKey, TmpDest, outdata );			//加
}

///*
//************************************************************************************************

//**************
//*
//* 函数原型：void CurCalc_3DES_Decrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata )
//*
//* 函数功能：3DES解密
//*
//* 函数输入：inkey		8字节密码
//*			indata		8字节需要解密的数据
//*
//* 函数输出：outdata		8字节解密结果输出
//*
//* 函数返回：无
//*
//***************************************************************************************************************/
void CurCalc_3DES_Decrypt( unsigned char *inkey, unsigned char *indata, unsigned char *outdata )
{
    unsigned char LKey[8];
    unsigned char RKey[8];
    unsigned char TmpDest[8];

    memcpy( LKey, inkey,   8 );
    memcpy( RKey, inkey+8, 8 );

    CurCalc_DES_Decrypt( LKey, indata,  outdata );			//解
    CurCalc_DES_Encrypt( RKey, outdata, TmpDest );			//加
    CurCalc_DES_Decrypt( LKey, TmpDest, outdata );			//解
}


/*******************************************************
* 名称:获取报文MAC值
* 功能:报文MAC算法
* 入口:
* *buf ,要计算的数据缓冲区;buf_size,计算数据的长度
* *key ,密钥(8B)
* 出口:mac_buf,计算出来的MAC值(8B)
ansi x9.9 MAC算法
********************************************************/
void Ansi99X_Get_MAC(unsigned char *initdata, unsigned char *buf, int buf_size, unsigned char *key, unsigned char *mac_buf )
{
    unsigned char val[8],dxor[8];
    unsigned char block[512];
    unsigned short x,n;
    unsigned short i,j=0;

    memcpy( block, buf, buf_size );  //将输入数据赋值给临时变量block
    x = buf_size / 8;                //计算有多少个完整的块
    n = buf_size % 8;                //计算最后一个块有几个字节
    if( n != 0 )	                   //y非0,则在其后补上0x00...
    {
        memset(&block[x*8+n],0x00,8-n);
        x += 1;
    }
    memcpy( val, initdata, 8 );
    for( i = 0;i<x;i++ )
    {
        DataXOR(val,&block[j],8,dxor);
        CurCalc_DES_Encrypt(key,dxor,val);//DES加密
        j += 8;
    }
    memcpy(mac_buf,val, 8 );
}

extern unsigned char  mac_data[4];
/**************************************************
** PBOC-DES MAC计算
**************************************************/
void PBOC_DES_MAC( unsigned char *initdata,unsigned char *inputbuf, int buf_size, unsigned char *key, unsigned char *mac_buf)
{
    unsigned char val[8],dxor[8];
    unsigned char block[512];
    unsigned short x,n;
    unsigned short i,j=0;

    memcpy( block, inputbuf, buf_size ); //将输入数据赋值给临时变量block
    x = buf_size / 8;                    //计算有多少个完整的块
    n = buf_size % 8;                    //计算最后一个块有几个字节
    if( n != 0 )	                       //y非0,则在其后补上0x00...
    {
        memset(&block[x*8+n],0x00, 8-n);
        block[x*8+n]=0x80;
    }
    else
    {
        memset(&block[x*8], 0x00, 8 );   //如果最后一块长度是8个字节，则最后加80 00。
        block[x*8]=0x80;
    }
    memcpy( val, initdata, 8 );
    for( i = 0;i<x+1;i++ )	               //有多少块循环多少次
    {
        DataXOR(val,&block[j],8,dxor);
        CurCalc_DES_Encrypt(key,dxor,val); //DES加密
        j += 8;	                           //用于取下一块的数据
    }
    memcpy(mac_buf,val,8);
}

/**************************************************
* PBOC-3DES MAC计算
**************************************************/
void PBOC_3DES_MAC( unsigned char *initdata,unsigned char *inputbuf, int buf_size, unsigned char *key, unsigned char *mac_buf )
{
    unsigned char val[8],dxor[8];
    unsigned char keyL[8],keyR[8];
    unsigned char block[512];
    unsigned short x,n;
    unsigned short i;
    memcpy(keyL,key,8);
    memcpy(keyR,&key[8],8);
    memcpy(block,inputbuf,buf_size);   //将输入数据赋值给临时变量block
    x = buf_size / 8;                  //计算有多少个完整的块
    n = buf_size % 8;                  //计算最后一个块有几个字节
    if( n != 0 )	                     //y非0,则在其后补上0x00...
    {
        memset(&block[x*8+n],0x00, 8-n);
        block[x*8+n]=0x80;
    }
    else
    {
        memset(&block[x*8], 0x00, 8 );      //如果最后一块长度是8个字节，则最后加80 00。
        block[x*8]=0x80;
    }
    memcpy( val, initdata, 8 );           //初始向量
    DataXOR(val,&block[0], 8,dxor);
    for( i = 1; i<x+1; i++ )	            //有多少块循环多少次
    {
        CurCalc_DES_Encrypt(keyL,dxor,val); //DES加密
        DataXOR(val,&block[i*8], 8,dxor);
    }
    CurCalc_DES_Encrypt(keyL,dxor,val);
    CurCalc_DES_Decrypt(keyR,val,dxor);
    CurCalc_DES_Encrypt(keyL,dxor,val);
    memcpy(mac_buf,val, 8 );
}

///////////////////////////////////////////////// 数据MAC计算                                                                             //单倍长 双倍
void Data_MAC( unsigned char *initdata,unsigned char *inputbuf, int buf_size, unsigned char *key, unsigned char *mac_buf,unsigned char Keytype)
{
    switch(Keytype)
    {
    case x99:
        Ansi99X_Get_MAC(initdata, inputbuf,  buf_size, key,mac_buf);
        break;
    case PBOC_Des_Mac:
        PBOC_DES_MAC(initdata,inputbuf,buf_size,key,mac_buf);
        break;
    case PBOC_3Des_Mac:
        PBOC_3DES_MAC(initdata,inputbuf,buf_size,key,mac_buf );
        break;
    }
}

/**********************************************************************
DES -3DES加密 对任意长度数据加密
inputlen :原始数据长度
inputbuf :原始数据
outdLen  :返回的数据长度
outData  :返回的数据
key      :加密 秘钥
Algortype:0-des 1-3des
***********************************************************************/
unsigned char Data_Encryption(unsigned char inputlen, /*原始数据*/
                              unsigned char *inputbuf,
                              unsigned char *outdLen, // 返回的数据
                              unsigned char *outData,
                              unsigned char *key,  // 加密 秘钥
                              AlgorIdent Algortype) // 8-16-des 3des
{
    //首先补0 ,计算出目标长度
    //分块计算加密
    unsigned char tempIn[8];
    unsigned char block[512];
    unsigned char val[10];

    unsigned short x,n;
    unsigned short i;
    //     if((Algortype!=0)|(Algortype!=1)) return PARAMERR;  //参数错误
    //     if(inputbuf==NULL)                return PARAMERR;   //数据指针错误
    memcpy(block,inputbuf,inputlen);                    //将输入数据赋值给临时变量block
    x = inputlen / 8;                                   //计算有多少个完整的块
    n = inputlen% 8;                                    //计算最后一个块有几个字节
    if( n != 0 )	                                      //y非0,则在其后补上0x80.00..
    {
        memset(&block[x*8+n],0x00, 8-n);
        block[x*8+n]=0x80;
        x+=1;
        *outdLen=inputlen+(8-n);
        //printf("len=%.2x ",*outdLen);
    }
    else
    {
        *outdLen=inputlen;
        //printf("len=%.2x ",*outdLen);
    }
    for( i = 0; i<x; i++ )	    //有多少块循环多少次
    {
        if(Algortype==DES_ENCY) //des
        {
            CurCalc_DES_Encrypt(key,&block[8*i],val);
            memcpy(&outData[i*8], val, 8);
        }
        else    //3des
        {
            CurCalc_3DES_Encrypt( key,&block[8*i],val);
            memcpy(&outData[i*8], val, 8);
        }
    }
    return 0;
}


/**************************************************************************************
soft-mac测试
//由于要计算过程密钥，所以输入是两组数据
//首先算过程密钥用3DES
//用过程密钥计算MAC1，调用signleMAC
//矣捎?AC2计算要使用过程密钥所以过程密钥要甩出去（默认是8字节的长度）//
***************************************************************************************/
unsigned char Calculate_MAC1(unsigned char *InputData_MAC,
                             unsigned char InputData_MAC_Len,
                             unsigned char *InputData_Senkey,
                             unsigned char InputData_Senkey_Len,
                             unsigned char *key,
                             unsigned char *Senkey)
{
    unsigned char Senkeylen[1];
    CalcMAC_Data *Data_MAC1;

    //EncryptionData_2(InputData_Senkey_Len, InputData_Senkey,Senkeylen,Senkey,key, 16);
    memcpy(Data_MAC1->initData,"\x00\x00\x00\x00\x00\x00\x00\x00",8);
    memcpy(Data_MAC1->sourceData,InputData_MAC,InputData_MAC_Len);
    Data_MAC1->sourceLen = InputData_MAC_Len;
    //    CalculateMAC_Data(Data_MAC1, Senkey, 8);  //计算出来的MAC1在Data_MAC1结构体中
}

/******************************************************************************
//用过程密钥计算MAC2，调用signleMAC
//传进来的数据是消费金额过程密钥和MAC1的过程密钥是相同的
*******************************************************************************/


unsigned char Calculate_MAC2(unsigned char *InputData_MAC,
                             unsigned char InputData_MAC_Len,
                             unsigned char *Senkey,
                             unsigned char *MAC2
                             )
{
    CalcMAC_Data *Data_MAC2;
    memcpy(Data_MAC2->sourceData,InputData_MAC,InputData_MAC_Len);
    Data_MAC2->sourceLen = InputData_MAC_Len;
    memcpy(Data_MAC2->initData,"\x00\x00\x00\x00\x00\x00\x00\x00",8);
    //    CalculateMAC_Data(Data_MAC2, Senkey, 8);
    if(!memcmp(Data_MAC2->MACData,MAC2,4))
    {
        return  MAC2_RIGHT;
    }
    return   MAC2_ERR;
}

#if 1
int PubAscToHex (const unsigned char* pszAsciiBuf, int nLen, char cType, unsigned char* pszBcdBuf)
{
    int i = 0;
    char cTmp, cTmp1;

    if (pszAsciiBuf == NULL)
    {
        return APP_FAIL;
    }

    if (nLen & 0x01 && cType) /* 判别是否为奇数以及往那边对齐 */
    {
        cTmp1 = 0 ;
    }
    else
    {
        cTmp1 = 0x55 ;
    }

    for (i = 0; i < nLen; pszAsciiBuf ++, i ++)
    {
        if ( *pszAsciiBuf >= 'a' )
        {
            cTmp = *pszAsciiBuf - 'a' + 10 ;
        }
        else if ( *pszAsciiBuf >= 'A' )
        {
            cTmp = *pszAsciiBuf - 'A' + 10 ;
        }
        else if ( *pszAsciiBuf >= '0' )
        {
            cTmp = *pszAsciiBuf - '0' ;
        }
        else
        {
            cTmp = *pszAsciiBuf;
            cTmp&=0x0f;
        }

        if ( cTmp1 == 0x55 )
        {
            cTmp1 = cTmp;
        }
        else
        {
            *pszBcdBuf ++ = cTmp1 << 4 | cTmp;
            cTmp1 = 0x55;
        }
    }
    if (cTmp1 != 0x55)
    {
        *pszBcdBuf = cTmp1 << 4;
    }

    return APP_SUCC;
}

#if 0
int GetMD5Code(char *pszInBuf, int nLen, char *pszOutBuf)
{
    unsigned int x[16];
    char szData[64+1];
    char szOutBuf[32+1]="";
    unsigned int A, B, C, D, a, b, c, d;
    A=0x67452301;
    B=0xefcdab89;
    C=0x98badcfe;
    D=0x10325476;
    a=A; b=B; c=C; d=D;
    memset(&x, 0, 64);
    memset(szData, 0, sizeof(szData));
    if( nLen>=64-8-4 )
    {
        return APP_FAIL;
    }
    else
    {
        memcpy(szData, pszInBuf, nLen);
        szData[nLen] = 128;
        memcpy(&x, szData, nLen+1);
        x[14] = nLen%256*8;
        x[15] = nLen/256;
    } /**/
    /* Round 1 */
    FF (a, b, c, d, x[ 0],  7, 0xd76aa478); /**/
    /* 1 */
    FF (d, a, b, c, x[ 1], 12, 0xe8c7b756); /**/
    /* 2 */
    FF (c, d, a, b, x[ 2], 17, 0x242070db); /**/
    /* 3 */
    FF (b, c, d, a, x[ 3], 22, 0xc1bdceee); /**/
    /* 4 */
    FF (a, b, c, d, x[ 4],  7, 0xf57c0faf); /**/
    /* 5 */
    FF (d, a, b, c, x[ 5], 12, 0x4787c62a); /**/
    /* 6 */
    FF (c, d, a, b, x[ 6], 17, 0xa8304613); /**/
    /* 7 */
    FF (b, c, d, a, x[ 7], 22, 0xfd469501); /**/
    /* 8 */
    FF (a, b, c, d, x[ 8],  7, 0x698098d8); /**/
    /* 9 */
    FF (d, a, b, c, x[ 9], 12, 0x8b44f7af); /**/
    /* 10 */
    FF (c, d, a, b, x[10], 17, 0xffff5bb1); /**//* 11 */
    FF (b, c, d, a, x[11], 22, 0x895cd7be); /**//* 12 */
    FF (a, b, c, d, x[12],  7, 0x6b901122); /**//* 13 */
    FF (d, a, b, c, x[13], 12, 0xfd987193); /**//* 14 */
    FF (c, d, a, b, x[14], 17, 0xa679438e); /**//* 15 */
    FF (b, c, d, a, x[15], 22, 0x49b40821); /**//* 16 */ /**//* Round 2 */
    GG (a, b, c, d, x[ 1],  5, 0xf61e2562); /**//* 17 */
    GG (d, a, b, c, x[ 6],  9, 0xc040b340); /**//* 18 */
    GG (c, d, a, b, x[11], 14, 0x265e5a51); /**//* 19 */
    GG (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /**//* 20 */
    GG (a, b, c, d, x[ 5],  5, 0xd62f105d); /**//* 21 */
    GG (d, a, b, c, x[10],  9, 0x02441453); /**//* 22 */
    GG (c, d, a, b, x[15], 14, 0xd8a1e681); /**//* 23 */
    GG (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /**//* 24 */
    GG (a, b, c, d, x[ 9],  5, 0x21e1cde6); /**//* 25 */
    GG (d, a, b, c, x[14],  9, 0xc33707d6); /**//* 26 */
    GG (c, d, a, b, x[ 3], 14, 0xf4d50d87); /**//* 27 */
    GG (b, c, d, a, x[ 8], 20, 0x455a14ed); /**//* 28 */
    GG (a, b, c, d, x[13],  5, 0xa9e3e905); /**//* 29 */
    GG (d, a, b, c, x[ 2],  9, 0xfcefa3f8); /**//* 30 */
    GG (c, d, a, b, x[ 7], 14, 0x676f02d9); /**//* 31 */
    GG (b, c, d, a, x[12], 20, 0x8d2a4c8a); /**//* 32 */ /**//* Round 3 */
    HH (a, b, c, d, x[ 5],  4, 0xfffa3942); /**//* 33 */
    HH (d, a, b, c, x[ 8], 11, 0x8771f681); /**//* 34 */
    HH (c, d, a, b, x[11], 16, 0x6d9d6122); /**//* 35 */
    HH (b, c, d, a, x[14], 23, 0xfde5380c); /**//* 36 */
    HH (a, b, c, d, x[ 1],  4, 0xa4beea44); /**//* 37 */
    HH (d, a, b, c, x[ 4], 11, 0x4bdecfa9); /**//* 38 */
    HH (c, d, a, b, x[ 7], 16, 0xf6bb4b60); /**//* 39 */
    HH (b, c, d, a, x[10], 23, 0xbebfbc70); /**//* 40 */
    HH (a, b, c, d, x[13],  4, 0x289b7ec6); /**//* 41 */
    HH (d, a, b, c, x[ 0], 11, 0xeaa127fa); /**//* 42 */
    HH (c, d, a, b, x[ 3], 16, 0xd4ef3085); /**//* 43 */
    HH (b, c, d, a, x[ 6], 23, 0x04881d05); /**//* 44 */
    HH (a, b, c, d, x[ 9],  4, 0xd9d4d039); /**//* 45 */
    HH (d, a, b, c, x[12], 11, 0xe6db99e5); /**//* 46 */
    HH (c, d, a, b, x[15], 16, 0x1fa27cf8); /**//* 47 */
    HH (b, c, d, a, x[ 2], 23, 0xc4ac5665); /**//* 48 */ /**//* Round 4 */
    II (a, b, c, d, x[ 0],  6, 0xf4292244); /**//* 49 */
    II (d, a, b, c, x[ 7], 10, 0x432aff97); /**//* 50 */
    II (c, d, a, b, x[14], 15, 0xab9423a7); /**//* 51 */
    II (b, c, d, a, x[ 5], 21, 0xfc93a039); /**//* 52 */
    II (a, b, c, d, x[12],  6, 0x655b59c3); /**//* 53 */
    II (d, a, b, c, x[ 3], 10, 0x8f0ccc92); /**//* 54 */
    II (c, d, a, b, x[10], 15, 0xffeff47d); /**//* 55 */
    II (b, c, d, a, x[ 1], 21, 0x85845dd1); /**//* 56 */
    II (a, b, c, d, x[ 8],  6, 0x6fa87e4f); /**//* 57 */
    II (d, a, b, c, x[15], 10, 0xfe2ce6e0); /**//* 58 */
    II (c, d, a, b, x[ 6], 15, 0xa3014314); /**//* 59 */
    II (b, c, d, a, x[13], 21, 0x4e0811a1); /**//* 60 */
    II (a, b, c, d, x[ 4],  6, 0xf7537e82); /**//* 61 */
    II (d, a, b, c, x[11], 10, 0xbd3af235); /**//* 62 */
    II (c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /**//* 63 */
    II (b, c, d, a, x[ 9], 21, 0xeb86d391); /**//* 64 */
    sprintf(szOutBuf, "%08x", PP(a+A));
    sprintf(szOutBuf+8, "%08x", PP(b+B));
    sprintf(szOutBuf+16, "%08x", PP(c+C));
    sprintf(szOutBuf+24, "%08x", PP(d+D));

    PubAscToHex((const unsigned char *)szOutBuf, 32, 0,(unsigned char *)pszOutBuf);
    return APP_SUCC;
}
#endif
#endif


int qdes(unsigned char *source,unsigned char * dest,unsigned char * inkey, int flg)
{
    unsigned char bufout[64+20]="",
    kwork[56+20]="", worka[48+20]="", kn[48+20]="", buffer[64+20]="", key[64+20]="",
    nbrofshift, temp1, temp2;
    int valindex;
    int i, j, k, iter;
    /* INITIALIZE THE TABLES */
    /* Table - s1 */
    static unsigned char s1[4][16] =
    {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    };
    /* Table - s2 */
    static unsigned char s2[4][16] =
    {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    };
    /* Table - s3 */
    static unsigned char s3[4][16] =
    {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    };
    /* Table - s4 */
    static unsigned char s4[4][16] =
    {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    };
    /* Table - s5 */
    static unsigned char s5[4][16] =
    {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    };
    /* Table - s6 */
    static unsigned char s6[4][16] =
    {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    };
    /* Table - s7 */
    static unsigned char s7[4][16] =
    {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    };
    /* Table - s8 */
    static unsigned char s8[4][16] =
    {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    };

    /* Table - Shift */
    static unsigned char shift[16] =
    {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
            };

    /* Table - Binary */
    static unsigned char binary[64] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1,
        1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
        1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1
    };
    /* MAIN PROCESS */
    /* Convert from 64-bit key into 64-byte key */
    for (i = 0; i < 8; i++)
    {
        key[8*i] = ((j = *(inkey + i)) / 128) % 2;
        key[8*i+1] = (j / 64) % 2;
        key[8*i+2] = (j / 32) % 2;
        key[8*i+3] = (j / 16) % 2;
        key[8*i+4] = (j / 8) % 2;
        key[8*i+5] = (j / 4) % 2;
        key[8*i+6] = (j / 2) % 2;
        key[8*i+7] = j % 2;
    }
    /* Convert from 64-bit data into 64-byte data */
    for (i = 0; i < 8; i++)
    {
        buffer[8*i] = ((j = *(source + i)) / 128) % 2;
        buffer[8*i+1] = (j / 64) % 2;
        buffer[8*i+2] = (j / 32) % 2;
        buffer[8*i+3] = (j / 16) % 2;
        buffer[8*i+4] = (j / 8) % 2;
        buffer[8*i+5] = (j / 4) % 2;
        buffer[8*i+6] = (j / 2) % 2;
        buffer[8*i+7] = j % 2;
    }
    /* Initial Permutation of Data */
    bufout[ 0] = buffer[57];
    bufout[ 1] = buffer[49];
    bufout[ 2] = buffer[41];
    bufout[ 3] = buffer[33];
    bufout[ 4] = buffer[25];
    bufout[ 5] = buffer[17];
    bufout[ 6] = buffer[ 9];
    bufout[ 7] = buffer[ 1];
    bufout[ 8] = buffer[59];
    bufout[ 9] = buffer[51];
    bufout[10] = buffer[43];
    bufout[11] = buffer[35];
    bufout[12] = buffer[27];
    bufout[13] = buffer[19];
    bufout[14] = buffer[11];
    bufout[15] = buffer[ 3];
    bufout[16] = buffer[61];
    bufout[17] = buffer[53];
    bufout[18] = buffer[45];
    bufout[19] = buffer[37];
    bufout[20] = buffer[29];
    bufout[21] = buffer[21];
    bufout[22] = buffer[13];
    bufout[23] = buffer[ 5];
    bufout[24] = buffer[63];
    bufout[25] = buffer[55];
    bufout[26] = buffer[47];
    bufout[27] = buffer[39];
    bufout[28] = buffer[31];
    bufout[29] = buffer[23];
    bufout[30] = buffer[15];
    bufout[31] = buffer[ 7];
    bufout[32] = buffer[56];
    bufout[33] = buffer[48];
    bufout[34] = buffer[40];
    bufout[35] = buffer[32];
    bufout[36] = buffer[24];
    bufout[37] = buffer[16];
    bufout[38] = buffer[ 8];
    bufout[39] = buffer[ 0];
    bufout[40] = buffer[58];
    bufout[41] = buffer[50];
    bufout[42] = buffer[42];
    bufout[43] = buffer[34];
    bufout[44] = buffer[26];
    bufout[45] = buffer[18];
    bufout[46] = buffer[10];
    bufout[47] = buffer[ 2];
    bufout[48] = buffer[60];
    bufout[49] = buffer[52];
    bufout[50] = buffer[44];
    bufout[51] = buffer[36];
    bufout[52] = buffer[28];
    bufout[53] = buffer[20];
    bufout[54] = buffer[12];
    bufout[55] = buffer[ 4];
    bufout[56] = buffer[62];
    bufout[57] = buffer[54];
    bufout[58] = buffer[46];
    bufout[59] = buffer[38];
    bufout[60] = buffer[30];
    bufout[61] = buffer[22];
    bufout[62] = buffer[14];
    bufout[63] = buffer[ 6];
    /* Initial Permutation of Key */
    kwork[ 0] = key[56];
    kwork[ 1] = key[48];
    kwork[ 2] = key[40];
    kwork[ 3] = key[32];
    kwork[ 4] = key[24];
    kwork[ 5] = key[16];
    kwork[ 6] = key[ 8];
    kwork[ 7] = key[ 0];
    kwork[ 8] = key[57];
    kwork[ 9] = key[49];
    kwork[10] = key[41];
    kwork[11] = key[33];
    kwork[12] = key[25];
    kwork[13] = key[17];
    kwork[14] = key[ 9];
    kwork[15] = key[ 1];
    kwork[16] = key[58];
    kwork[17] = key[50];
    kwork[18] = key[42];
    kwork[19] = key[34];
    kwork[20] = key[26];
    kwork[21] = key[18];
    kwork[22] = key[10];
    kwork[23] = key[ 2];
    kwork[24] = key[59];
    kwork[25] = key[51];
    kwork[26] = key[43];
    kwork[27] = key[35];
    kwork[28] = key[62];
    kwork[29] = key[54];
    kwork[30] = key[46];
    kwork[31] = key[38];
    kwork[32] = key[30];
    kwork[33] = key[22];
    kwork[34] = key[14];
    kwork[35] = key[ 6];
    kwork[36] = key[61];
    kwork[37] = key[53];
    kwork[38] = key[45];
    kwork[39] = key[37];
    kwork[40] = key[29];
    kwork[41] = key[21];
    kwork[42] = key[13];
    kwork[43] = key[ 5];
    kwork[44] = key[60];
    kwork[45] = key[52];
    kwork[46] = key[44];
    kwork[47] = key[36];
    kwork[48] = key[28];
    kwork[49] = key[20];
    kwork[50] = key[12];
    kwork[51] = key[ 4];
    kwork[52] = key[27];
    kwork[53] = key[19];
    kwork[54] = key[11];
    kwork[55] = key[ 3];
    /* 16 Iterations */
    for (iter = 1; iter < 17; iter++)
    {
        for (i = 0; i < 32; i++)
        {
            buffer[i] = bufout[32+i];
        }
        /* Calculation of F(R, K) */
        /* Permute - E */
        worka[ 0] = buffer[31];
        worka[ 1] = buffer[ 0];
        worka[ 2] = buffer[ 1];
        worka[ 3] = buffer[ 2];
        worka[ 4] = buffer[ 3];
        worka[ 5] = buffer[ 4];
        worka[ 6] = buffer[ 3];
        worka[ 7] = buffer[ 4];
        worka[ 8] = buffer[ 5];
        worka[ 9] = buffer[ 6];
        worka[10] = buffer[ 7];
        worka[11] = buffer[ 8];
        worka[12] = buffer[ 7];
        worka[13] = buffer[ 8];
        worka[14] = buffer[ 9];
        worka[15] = buffer[10];
        worka[16] = buffer[11];
        worka[17] = buffer[12];
        worka[18] = buffer[11];
        worka[19] = buffer[12];
        worka[20] = buffer[13];
        worka[21] = buffer[14];
        worka[22] = buffer[15];
        worka[23] = buffer[16];
        worka[24] = buffer[15];
        worka[25] = buffer[16];
        worka[26] = buffer[17];
        worka[27] = buffer[18];
        worka[28] = buffer[19];
        worka[29] = buffer[20];
        worka[30] = buffer[19];
        worka[31] = buffer[20];
        worka[32] = buffer[21];
        worka[33] = buffer[22];
        worka[34] = buffer[23];
        worka[35] = buffer[24];
        worka[36] = buffer[23];
        worka[37] = buffer[24];
        worka[38] = buffer[25];
        worka[39] = buffer[26];
        worka[40] = buffer[27];
        worka[41] = buffer[28];
        worka[42] = buffer[27];
        worka[43] = buffer[28];
        worka[44] = buffer[29];
        worka[45] = buffer[30];
        worka[46] = buffer[31];
        worka[47] = buffer[ 0];
        /* KS Function Begin */
        if (flg)
        {
            nbrofshift = shift[iter-1];
            for (i = 0; i < (int) nbrofshift; i++)
            {
                temp1 = kwork[0];
                temp2 = kwork[28];
                for (j = 0; j < 27; j++)
                {
                    kwork[j] = kwork[j+1];
                    kwork[j+28] = kwork[j+29];
                }
                kwork[27] = temp1;
                kwork[55] = temp2;
            }
        }
        else if (iter > 1)
        {
            nbrofshift = shift[17-iter];
            for (i = 0; i < (int) nbrofshift; i++)
            {
                temp1 = kwork[27];
                temp2 = kwork[55];
                for (j = 27; j > 0; j--)
                {
                    kwork[j] = kwork[j-1];
                    kwork[j+28] = kwork[j+27];
                }
                kwork[0] = temp1;
                kwork[28] = temp2;
            }
        }
        /* Permute kwork - PC2 */
        kn[ 0] = kwork[13];
        kn[ 1] = kwork[16];
        kn[ 2] = kwork[10];
        kn[ 3] = kwork[23];
        kn[ 4] = kwork[ 0];
        kn[ 5] = kwork[ 4];
        kn[ 6] = kwork[ 2];
        kn[ 7] = kwork[27];
        kn[ 8] = kwork[14];
        kn[ 9] = kwork[ 5];
        kn[10] = kwork[20];
        kn[11] = kwork[ 9];
        kn[12] = kwork[22];
        kn[13] = kwork[18];
        kn[14] = kwork[11];
        kn[15] = kwork[ 3];
        kn[16] = kwork[25];
        kn[17] = kwork[ 7];
        kn[18] = kwork[15];
        kn[19] = kwork[ 6];
        kn[20] = kwork[26];
        kn[21] = kwork[19];
        kn[22] = kwork[12];
        kn[23] = kwork[ 1];
        kn[24] = kwork[40];
        kn[25] = kwork[51];
        kn[26] = kwork[30];
        kn[27] = kwork[36];
        kn[28] = kwork[46];
        kn[29] = kwork[54];
        kn[30] = kwork[29];
        kn[31] = kwork[39];
        kn[32] = kwork[50];
        kn[33] = kwork[44];
        kn[34] = kwork[32];
        kn[35] = kwork[47];
        kn[36] = kwork[43];
        kn[37] = kwork[48];
        kn[38] = kwork[38];
        kn[39] = kwork[55];
        kn[40] = kwork[33];
        kn[41] = kwork[52];
        kn[42] = kwork[45];
        kn[43] = kwork[41];
        kn[44] = kwork[49];
        kn[45] = kwork[35];
        kn[46] = kwork[28];
        kn[47] = kwork[31];
        /* KS Function End */
        /* worka XOR kn */
        for (i = 0; i < 48; i++)
            worka[i] = worka[i] ^ kn[i];
        /* 8 s-functions */
        valindex = s1[2*worka[ 0]+worka[ 5]]
                   [2*(2*(2*worka[ 1]+worka[ 2])+
                       worka[ 3])+worka[ 4]];
        valindex = valindex * 4;
        kn[ 0] = binary[0+valindex];
        kn[ 1] = binary[1+valindex];
        kn[ 2] = binary[2+valindex];
        kn[ 3] = binary[3+valindex];
        valindex = s2[2*worka[ 6]+worka[11]]
                   [2*(2*(2*worka[ 7]+worka[ 8])+
                       worka[ 9])+worka[10]];
        valindex = valindex * 4;
        kn[ 4] = binary[0+valindex];
        kn[ 5] = binary[1+valindex];
        kn[ 6] = binary[2+valindex];
        kn[ 7] = binary[3+valindex];
        valindex = s3[2*worka[12]+worka[17]]
                   [2*(2*(2*worka[13]+worka[14])+
                       worka[15])+worka[16]];
        valindex = valindex * 4;
        kn[ 8] = binary[0+valindex];
        kn[ 9] = binary[1+valindex];
        kn[10] = binary[2+valindex];
        kn[11] = binary[3+valindex];
        valindex = s4[2*worka[18]+worka[23]]
                   [2*(2*(2*worka[19]+worka[20])+
                       worka[21])+worka[22]];
        valindex = valindex * 4;
        kn[12] = binary[0+valindex];
        kn[13] = binary[1+valindex];
        kn[14] = binary[2+valindex];
        kn[15] = binary[3+valindex];
        valindex = s5[2*worka[24]+worka[29]]
                   [2*(2*(2*worka[25]+worka[26])+
                       worka[27])+worka[28]];
        valindex = valindex * 4;
        kn[16] = binary[0+valindex];
        kn[17] = binary[1+valindex];
        kn[18] = binary[2+valindex];
        kn[19] = binary[3+valindex];
        valindex = s6[2*worka[30]+worka[35]]
                   [2*(2*(2*worka[31]+worka[32])+
                       worka[33])+worka[34]];
        valindex = valindex * 4;
        kn[20] = binary[0+valindex];
        kn[21] = binary[1+valindex];
        kn[22] = binary[2+valindex];
        kn[23] = binary[3+valindex];
        valindex = s7[2*worka[36]+worka[41]]
                   [2*(2*(2*worka[37]+worka[38])+
                       worka[39])+worka[40]];
        valindex = valindex * 4;
        kn[24] = binary[0+valindex];
        kn[25] = binary[1+valindex];
        kn[26] = binary[2+valindex];
        kn[27] = binary[3+valindex];
        valindex = s8[2*worka[42]+worka[47]]
                   [2*(2*(2*worka[43]+worka[44])+
                       worka[45])+worka[46]];
        valindex = valindex * 4;
        kn[28] = binary[0+valindex];
        kn[29] = binary[1+valindex];
        kn[30] = binary[2+valindex];
        kn[31] = binary[3+valindex];
        /* Permute - P */
        worka[ 0] = kn[15];
        worka[ 1] = kn[ 6];
        worka[ 2] = kn[19];
        worka[ 3] = kn[20];
        worka[ 4] = kn[28];
        worka[ 5] = kn[11];
        worka[ 6] = kn[27];
        worka[ 7] = kn[16];
        worka[ 8] = kn[ 0];
        worka[ 9] = kn[14];
        worka[10] = kn[22];
        worka[11] = kn[25];
        worka[12] = kn[ 4];
        worka[13] = kn[17];
        worka[14] = kn[30];
        worka[15] = kn[ 9];
        worka[16] = kn[ 1];
        worka[17] = kn[ 7];
        worka[18] = kn[23];
        worka[19] = kn[13];
        worka[20] = kn[31];
        worka[21] = kn[26];
        worka[22] = kn[ 2];
        worka[23] = kn[ 8];
        worka[24] = kn[18];
        worka[25] = kn[12];
        worka[26] = kn[29];
        worka[27] = kn[ 5];
        worka[28] = kn[21];
        worka[29] = kn[10];
        worka[30] = kn[ 3];
        worka[31] = kn[24];
        /* bufout XOR worka */
        for (i = 0; i < 32; i++)
        {
            bufout[i+32] = bufout[i] ^ worka[i];
            bufout[i] = buffer[i];
        }
    } /* End of Iter */
    /* Prepare Output */
    for (i = 0; i < 32; i++)
    {
        j = bufout[i];
        bufout[i] = bufout[32+i];
        bufout[32+i] = j;
    }
    /* Inverse Initial Permutation */
    buffer[ 0] = bufout[39];
    buffer[ 1] = bufout[ 7];
    buffer[ 2] = bufout[47];
    buffer[ 3] = bufout[15];
    buffer[ 4] = bufout[55];
    buffer[ 5] = bufout[23];
    buffer[ 6] = bufout[63];
    buffer[ 7] = bufout[31];
    buffer[ 8] = bufout[38];
    buffer[ 9] = bufout[ 6];
    buffer[10] = bufout[46];
    buffer[11] = bufout[14];
    buffer[12] = bufout[54];
    buffer[13] = bufout[22];
    buffer[14] = bufout[62];
    buffer[15] = bufout[30];
    buffer[16] = bufout[37];
    buffer[17] = bufout[ 5];
    buffer[18] = bufout[45];
    buffer[19] = bufout[13];
    buffer[20] = bufout[53];
    buffer[21] = bufout[21];
    buffer[22] = bufout[61];
    buffer[23] = bufout[29];
    buffer[24] = bufout[36];
    buffer[25] = bufout[ 4];
    buffer[26] = bufout[44];
    buffer[27] = bufout[12];
    buffer[28] = bufout[52];
    buffer[29] = bufout[20];
    buffer[30] = bufout[60];
    buffer[31] = bufout[28];
    buffer[32] = bufout[35];
    buffer[33] = bufout[ 3];
    buffer[34] = bufout[43];
    buffer[35] = bufout[11];
    buffer[36] = bufout[51];
    buffer[37] = bufout[19];
    buffer[38] = bufout[59];
    buffer[39] = bufout[27];
    buffer[40] = bufout[34];
    buffer[41] = bufout[ 2];
    buffer[42] = bufout[42];
    buffer[43] = bufout[10];
    buffer[44] = bufout[50];
    buffer[45] = bufout[18];
    buffer[46] = bufout[58];
    buffer[47] = bufout[26];
    buffer[48] = bufout[33];
    buffer[49] = bufout[ 1];
    buffer[50] = bufout[41];
    buffer[51] = bufout[ 9];
    buffer[52] = bufout[49];
    buffer[53] = bufout[17];
    buffer[54] = bufout[57];
    buffer[55] = bufout[25];
    buffer[56] = bufout[32];
    buffer[57] = bufout[ 0];
    buffer[58] = bufout[40];
    buffer[59] = bufout[ 8];
    buffer[60] = bufout[48];
    buffer[61] = bufout[16];
    buffer[62] = bufout[56];
    buffer[63] = bufout[24];
    j = 0;
    for (i = 0; i < 8; i++)
    {
        *(dest + i) = 0x00;
        for (k = 0; k < 7; k++)
            *(dest + i) = ((*(dest + i)) + buffer[j+k]) * 2;
        *(dest + i) = *(dest + i) + buffer[j+7];
        j += 8;
    }
    return 0;
}

int qdes3(unsigned char *source,unsigned char * dest,unsigned char * inkey, int flg)
{
    unsigned char tmpbuf[8];
    if(flg == ENCRYPT)/**3DES加密 */
    {
        qdes(source, dest, inkey, ENCRYPT);
        qdes(dest, tmpbuf, inkey+8, DECRYPT);
        qdes(tmpbuf, dest, inkey, ENCRYPT);
    }
    else if(flg == DECRYPT)  /**3DES解密 */
    {
        qdes(source, dest, inkey, DECRYPT);
        qdes(dest, tmpbuf, inkey+8, ENCRYPT);
        qdes(tmpbuf, dest, inkey, DECRYPT);
    }
    return 0;
}
/******************************************************************************
*	函数名称：PubIntToC4
*	函数介绍：整型转换为4字节字符串（高位在前）
*	函数描述：
*	入口参数：nNum		---- 需要转换的整型数
*	出口参数：pszBuf	---- 转换输出的字符串
*	返 回 值：无
*	修 改 者：陈丹莹
*	修改日期：2006-09-11
*******************************************************************************/
void PubIntToC4 (unsigned char* pszBuf, const unsigned int nNum )
{

    int nTmp = 0;

    nTmp = nNum;
    if (nNum <= 0x0FFFFFFF)
    {
        *( pszBuf ) = nNum >> 24;
        *( pszBuf + 1 ) = (nNum >> 16) ;
        *( pszBuf + 2 ) = (nNum >> 8) ;
        *( pszBuf + 3 ) = nNum %256;
    }
}

/******************************************************************************
*	函数名称：PubIntToC2
*	函数介绍：整型转换为2字节字符串（高位在前）
*	函数描述：
*	入口参数：nNum		---- 需要转换的整型数
*	出口参数：pszBuf	---- 转换输出的字符串
*	返 回 值：无
*	修 改 者：陈丹莹
*	修改日期：2006-09-11
*******************************************************************************/
void PubIntToC2 (unsigned char* pszBuf, const unsigned int nNum )
{
    int nTmp = nNum;
    if (nNum <= 65535)
    {
        *(pszBuf + 1) = nNum % 256;
        *pszBuf = nTmp >>8;
    }
    return ;
}

/******************************************************************************
*	函数名称：PubC4ToInt
*	函数介绍：4字节字符串转换为整型（高位在前）
*	函数描述：
*	入口参数：pszBuf		---- 需要转换的字符串
*	出口参数：nNum			---- 转换输出的整型数
*	返 回 值：APP_SUCC 0 成功; APP_FAIL -1 失败
*	修 改 者：陈丹莹
*	修改日期：2006-09-11
*******************************************************************************/
void PubC4ToInt (unsigned int* nNum, unsigned char* pszBuf )
{
    *nNum = ((*pszBuf) << 24) + (*(pszBuf+1) << 16) + (*(pszBuf+2) << 8) + (*(pszBuf + 3));
}

/******************************************************************************
*	函数名称：PubC2ToInt
*	函数介绍：2字节字符串转换为整型（高位在前）
*	函数描述：pszBuf长度要>=2
*	入口参数：pszBuf  ---- 需要转换的字符串
*	出口参数：nNum    ---- 转换输出的整型数
*	返回值  ：无
*	修改者  ：薛震
*	修改日期：2006-09-04
*******************************************************************************/
void PubC2ToInt(unsigned int *nNum, unsigned char *pszBuf)
{
    *nNum = ((*pszBuf) << 8) + (*(pszBuf + 1));
}


/******************************************************************************
*	函数名称：PubByteToBcd
*	函数介绍：整数(0-99)转换为一字节BCD
*	函数描述：
*	入口参数：nNum  ---- 需要转换的整型数(0-99)
*	出口参数：ch    ---- 转换输出的一个BCD字符
*	返回值  ：APP_SUCC 0     计算成功;
*             APP_FAIL -1    输入的数据不合法
*	修改者  ：薛震
*	修改日期：2006-09-04
*******************************************************************************/

int PubByteToBcd(int nNum, unsigned char *ch)
{
    if ((nNum < 0) || (nNum > 99))
    {
        return APP_FAIL;
    }
    *ch = ((nNum / 10) << 4) | (nNum % 10);
    return APP_SUCC;
}

/******************************************************************************
*	函数名称：PubBcdToByte
*	函数介绍： 一字节BCD转换为整数(0-99)
*	函数描述：
*	入口参数：ch      ---- 需要转换的BCD字符
*	出口参数：pnNum   ---- 转换输出的整数值(0-99)
*	返回值  ：APP_SUCC         0 计算成功;
*             APP_FAIL        -1 输入的数据不合法
*	修改者  : 薛震
*	修改日期: 2006-09-04
*******************************************************************************/
int PubBcdToByte(unsigned char ch, int *pnNum)
{
    if (((ch & 0x0F) > 9) || ((ch >> 4) > 9))
    {
        return APP_FAIL;
    }

    *pnNum = (ch >> 4) * 10 + (ch & 0x0f);
    return APP_SUCC;
}


/******************************************************************************
*	函数名称：PubIntToBcd
*	函数介绍：整数(0-9999)转换为二字节BCD
*	函数描述：
*	入口参数：nNum      ---- 需要转换的整型数(0-9999)
*             pnBcdLen  ---- 输出缓冲区的大小
*	出口参数：psBcd     ---- 转换输出的两字节BCD
*             pnBcdLen  ---- 转换后的BCD长度，如果成功此值，固定返回值为2
*	返回值  ：APP_SUCC 0         计算成功;
*             APP_FAIL -1        输入的数据不合法
*	修改者  ：薛震
*	修改日期：2006-09-04
*******************************************************************************/
int PubIntToBcd(unsigned char *psBcd, int *pnBcdLen, int nNum)
{
    if ((nNum < 0) || (nNum > 9999) || (*pnBcdLen < 2))
    {
        return APP_FAIL;
    }

    PubByteToBcd(nNum / 100, &psBcd[0]);
    PubByteToBcd(nNum % 100, &psBcd[1]);

    *pnBcdLen = 2;
    return APP_SUCC;
}

/******************************************************************************
*	函数名称：PubBcdToInt
*	函数介绍：二字节BCD转换为整数(0-9999)
*	函数描述：psBcd长度应等于2
*	入口参数：psBcd     ---- 需要转换的两字节BCD
*	出口参数：nNum达    ---- 转换后的整数(0-9999)
*	返回值  ：APP_SUCC  0 计算成功;
*             APP_FAIL -1 输入的数据不合法
*	修改者  ：薛震
*	修改日期：2006-09-04
*******************************************************************************/
int PubBcdToInt(const char * psBcd, int *nNum)
{
    int nNum1, nNum2, ret;

    if (psBcd == NULL)
    {
        return APP_FAIL;
    }

    ret = PubBcdToByte(psBcd[0], &nNum1);
    if (ret == APP_FAIL)
    {
        return APP_FAIL;
    }
    ret = PubBcdToByte(psBcd[1], &nNum2);
    if (ret == APP_FAIL)
    {
        return APP_FAIL;
    }
    *nNum = nNum1 * 100 + nNum2;
    return APP_SUCC;
}

/******************************************************************************
*	函数名称：PubCalcLRC
*	函数介绍：计算LRC
*	函数描述：psbuf缓冲的长度>nLen
*	入口参数：psBuf   ---- 需要计算LRC的字符串
*             nLen    ---- 需要计算LRC的字符串的长度
*	出口参数：chLRC   ---- 计算得出的LRC
*	返回值  ：APP_SUCC 0       计算成功;
*             APP_FAIL -1      源串为空串,或者非法
*	修改者  ：薛震
*	修改日期：2016-06-22
*******************************************************************************/
int PubCalcLRC(const char *psBuf, int nLen, char *chLRC)
{
    int	i;
    if (psBuf == NULL)
    {
        return APP_FAIL;
    }

    *chLRC = 0x00;
    for (i = 0; i < nLen; i++)
    {
        *chLRC ^= psBuf[i];
    }
    return APP_SUCC;
}


// 10 09 0E 0D 38 0E 00  ---> 16 09 14 13 38 14 00
//int-->hex
//2位数转为2位数hex 16--0x16
int PubInt2hex(const char *intBuf, int nLen, char *hexbuf)
{
    unsigned char a,b;
    unsigned char i;
    for(i=0;i<nLen;i++)
    {
        a=intBuf[i]/10;
        b=intBuf[i]%10;
        hexbuf[i]=a*16+b;
    }
    return APP_SUCC;
}

unsigned char Data_Decryption(unsigned char inputlen, /*原始数据*/
                              unsigned char *inputbuf,
                              unsigned char *outdLen, // 返回的数据
                              unsigned char *outData,
                              unsigned char *key,  // 加密 秘钥
                              AlgorIdent Algortype) // 8-16-des 3des
{
    //首先补0 ,计算出目标长度
    //分块计算加密
    unsigned char tempIn[8];
    unsigned char block[512];
    unsigned char val[10];

    unsigned short x,n;
    unsigned short i;
    //     if((Algortype!=0)|(Algortype!=1)) return PARAMERR;  //参数错误
    //     if(inputbuf==NULL)                return PARAMERR;   //数据指针错误
    memcpy(block,inputbuf,inputlen);                    //将输入数据赋值给临时变量block
    x = inputlen / 8;                                   //计算有多少个完整的块
    n = inputlen% 8;                                    //计算最后一个块有几个字节
    if( n != 0 )	                                      //y非0,则在其后补上0x80.00..
    {
        memset(&block[x*8+n],0x00, 8-n);
        block[x*8+n]=0x80;
        x+=1;
        *outdLen=inputlen+(8-n);
    }
    else
    {
        *outdLen=inputlen;
    }
    for( i = 0; i<x; i++ )	    //有多少块循环多少次
    {
        if(Algortype==DES_ENCY) //des
        {
            CurCalc_3DES_Decrypt(key,&block[8*i],val);
            memcpy(&outData[i*8], val, 8);
        }
        else    //3des
        {
            CurCalc_3DES_Decrypt( key,&block[8*i],val);
            memcpy(&outData[i*8], val, 8);
        }
    }
    return 0;
}

/******************************************************************************
*	CRC16
*	函数介绍：计算CRC
*******************************************************************************/
unsigned char const  auchCRCHi[] = {
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
        0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40
} ;

/* Table of CRC values for low-order byte    */
unsigned char const auchCRCLo[] = {
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
        0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
        0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
        0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
        0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
        0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
        0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
        0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
        0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
        0x40
} ;

unsigned int crc16(unsigned char *puchMsg,unsigned int usDataLen)
// puchMsg message to calculate CRC upon
{		                                   // usDataLen quantity of bytes in message
    unsigned char  uchCRCHi = 0xFF ;  // high byte of CRC initialized
    unsigned char  uchCRCLo = 0xFF ;  // low byte of CRC initialized
    unsigned int   uIndex  ;          // will index into CRC lookup table
    while (usDataLen--)             // Pass through message buffer
    {
        uIndex = uchCRCHi ^ *puchMsg++ ; // calculate the CRC
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (((unsigned int)(uchCRCLo) << 8) | uchCRCHi) ;
}


/******************************************************************************
*	intToByte
*	函数介绍：Change Int to QByteArray
*******************************************************************************/
/**
 * @brief intToByte
 * @param number
 * @return
 */
QByteArray  intToByte(int number)
{
    QByteArray abyte0;
    abyte0.resize(1);
    abyte0[0] = (uchar)  (0x000000ff & number);
    //abyte0[1] = (uchar) ((0x0000ff00 & number) >> 8);
    //abyte0[2] = (uchar) ((0x00ff0000 & number) >> 16);
    //abyte0[3] = (uchar) ((0xff000000 & number) >> 24);
    return abyte0;
}

