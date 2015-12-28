#include <reg52.h>
#include <intrins.h>
sbit P32 = P3^2;
sbit P33 = P3^3;

//tag=0,not confirm
//tag=1,confirm
//tag=2,need check
unsigned char tag; 
unsigned char buf;    //�洢��Ҫ�����һ���ֽ�
unsigned char bitn;  //��¼��buf�ﻹδ����ȡ��λ��
char r_w;   //�Ƕ�����д,Ϊ2ʱ����ʾ���Ĺ���
unsigned char n;     //��¼������n���ֽ���
bit readbit;         //��EEPROM��ȡ������λ
unsigned char digital[10];
unsigned temp;
unsigned char MAX;   //����content����Ч����
unsigned char content[10];//�������д������

void filldigital(void);
void readinit(void);
void readinit2(void);


void main(void)
{
    r_w = 0; //1��0д
start:
    temp = 0;
    filldigital();
    P1 = 0x1;
    P2 = digital[0];
    bitn = 0;
    n = 0;
    content[0] = 0xa0;
	content[0] |= r_w;  //����дλ�����һ���ֽ���
    content[1] = 0xf0;
    content[2] = 0x04;
    content[3] = 0x05;
    content[4] = 0x07;
    MAX = 6;
    tag = 1;
    P32 = 1;
    P33 = 1;
	_nop_();
    P33 = 0;
    TH0 = 0xff;
    TL0 = 0xd2;
    TMOD |= 1;
    TR0 = 1;
    ET0 = 1;
    if(r_w)
        readinit();
    EA = 1;
    while(1)
    {
		if(r_w==-1)
		{
			r_w = 1;
			goto start;
		}
        if(n!=MAX)
            if(!bitn)
            {
                if(r_w==3)
                    content[n] = buf;
                else                     
					buf = content[n];
                    bitn = 8;
                    n++;
            }
    }
}

void readinit(void)
{
    n = 0;
    content[0] = 0xa0;
    content[1] = 0xf0;   //���潫Ҫ��ȡ��ַ
    MAX = 2;
}

void readinit2(void)
{
    n = 0;
    content[0] = 0xa1;
    MAX = 1;
}

void filldigital(void)
{
    digital[0] = 63; //index 0
    digital[1] = 6;
    digital[2] = 91;
    digital[3] = 79;
    digital[4] = 102;
    digital[5] = 109;
    digital[6] = 125;
    digital[7] = 7;
    digital[8] = 127;
    digital[9] = 111; //index 9
}

void Timer0(void) interrupt 1
{
    if(!P32&&!tag)
    {
        if(r_w==3)
        {
            P33 = 0;   //����ƽ��Ϊ0����ʾȷ���յ�
			P1 = 0x2;
			P2 = digital[buf];//��ʾ����������ֵ
			return;
        }
        else
        {
            P33 = 1;  //ǿ�ƽ���ƽ��Ϊ1
            tag = 2; //check the next signal
        }
        P32 = ~P32;
        return;
    }
    if(P32&&tag==2)
    {
        if(!P33)
        {
            tag = 1;
            if(n==MAX&&!bitn)//�յ�ȷ���źź�����Ѿ�д�꣬��STOP
            {
                if(r_w==1)//������
                {
					P32 = ~P32;
					_nop_();
					P33 = 1;
                	n = 20;
					while(n--);
                	P32 = ~P32;
					_nop_();
					P33 = 0;
                    readinit2();   //��ʼ�ĵڶ�������
                    r_w = 2;//��ʼ������
                    return;
                }
				if(r_w==2)//������
                {
                	P32 = ~P32;
                    r_w = 3;//��ʼ��ÿһλ
					n = 0;
                    MAX = 9;
                    return;
                }
                P32 = ~P32;
                n = 20;
				while(n--);
                P32 = ~P32;
				_nop_();
                P33 = 1;
                r_w = -1;
				return;//while(1);//д�����
            }
            temp++; //show show show
            P1 = 0x1;
            P2 = digital[temp];
        }
        P32 = ~P32;
        return;
    }
    if(!P32)
    {
        if(r_w==0||r_w==1||r_w==2)
        {
            P33 = 1;
            P33 &= (buf>>7);
            buf <<= 1;
			bitn--;
        }
    }
    if(P32)
    {
        if(r_w==3)
        {
            buf <<= 1;
            buf |= P33;
			bitn--;
        }        
    }
    if(!bitn)
    {
        tag = 0;
    }

    P32 = ~P32;
}