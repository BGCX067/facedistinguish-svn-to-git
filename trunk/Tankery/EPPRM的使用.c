#include <reg52.h>
#include <intrins.h>
sbit P32 = P3^2;
sbit P33 = P3^3;

//tag=0,not confirm
//tag=1,confirm
//tag=2,need check
unsigned char tag; 
unsigned char buf;    //存储将要传输的一个字节
unsigned char bitn;  //记录了buf里还未被读取的位数
char r_w;   //是读还是写,为2时，表示读的过程
unsigned char n;     //记录读到第n个字节了
bit readbit;         //从EEPROM读取出来的位
unsigned char digital[10];
unsigned temp;
unsigned char MAX;   //设置content的有效长度
unsigned char content[10];//保存读与写的内容

void filldigital(void);
void readinit(void);
void readinit2(void);


void main(void)
{
    r_w = 0; //1读0写
start:
    temp = 0;
    filldigital();
    P1 = 0x1;
    P2 = digital[0];
    bitn = 0;
    n = 0;
    content[0] = 0xa0;
	content[0] |= r_w;  //将读写位置入第一个字节中
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
    content[1] = 0xf0;   //保存将要读取地址
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
            P33 = 0;   //将电平拉为0，表示确认收到
			P1 = 0x2;
			P2 = digital[buf];//显示读出来的数值
			return;
        }
        else
        {
            P33 = 1;  //强制将电平拉为1
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
            if(n==MAX&&!bitn)//收到确认信号后，如果已经写完，则STOP
            {
                if(r_w==1)//读操作
                {
					P32 = ~P32;
					_nop_();
					P33 = 1;
                	n = 20;
					while(n--);
                	P32 = ~P32;
					_nop_();
					P33 = 0;
                    readinit2();   //开始的第二次启动
                    r_w = 2;//开始读操作
                    return;
                }
				if(r_w==2)//读操作
                {
                	P32 = ~P32;
                    r_w = 3;//开始读每一位
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
				return;//while(1);//写完成了
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