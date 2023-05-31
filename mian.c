#include<reg52.h>
#include<intrins.h>
#include<stdio.h>


#define uchar unsigned char
#define uint unsigned int
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
#define GPIO P1
#define count 50000			   //计数值，约为0.05s
#define TH	(65536-count)/256  //定时器初始化设置
#define TL	(65536-count)%256

sbit LSA=P2^2;				   //数码管位选设置
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit bee=P2^5;						//蜂鸣器	
sbit LED=P2^0;						//LED灯
sbit KEY1=P3^1;							//初始化K1
int key=0;					   //矩阵键盘按键标志
int password[4];			   //输入数字数组
int right[4]={6,6,6,6};	   //正确密码数组
int temporary[4];			   //零时密码数组
uchar code DSY[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	 //数码管显示数字数组

void delay(int n)			   //延时函数
{	int t;
	while(n--)
	{	for(t=0;t<12;t++);
	}
}

void uart_init(void);//串行口初始化
void main()
{
	int flag=1;
  int sign=0;				   //重置密码位数
	int mark01=0;			   //重置密码第一遍（原密码）标志
	int mark02=0;			   //重置密码第二遍（原密码重复）标志
	int mark03=0;			   //重置密码第三遍（新密码）标志
	int mark04=0;			   //重置密码第四遍（新密码重复）标志
	int mistake=0;			 //错误次数
	int temp=0;				   //正确位数用来判断密码是否正确
	int N=0;				   //输入位数		用来循环４次
	int i=0;				   //计数
	int a=0;				   //计数
	bee=0;							//初始化蜂鸣器
	TMOD&=0X0F;				   //定时器初始化设置
	TMOD|=0X01;
	P2=0X03;
	uart_init();					//初始化串口
	while(1)
	{
		while(1)				   //进入循环
		{
			GPIO=0x0f;
			if(GPIO!=0x0f)		   //判断按下
			{
				delay(100);
				if(GPIO!=0x0f)	   //重新判断按下
				{
					switch(N)      //位选   
		            {
		                case(0):
		                        LSA=1;LSB=1;LSC=1; break;
		                case(1):
		                        LSA=0;LSB=1;LSC=1; break;
		                case(2):
		                        LSA=1;LSB=0;LSC=1; break;
		                case(3):
		                        LSA=0;LSB=0;LSC=1; break;
					}
					GPIO=0X0F;						//测试列
						switch(GPIO)
						{
							case(0x07):key=0;break;
							case(0x0b):key=1;break;
							case(0x0d):key=2;break;
							case(0x0e):key=3;break;
						}					   //测试行
					GPIO=0XF0;
					switch(GPIO)
						{
							case(0x70):key=key;break;
							case(0xb0):key=key+4;break;
							case(0xd0):key=key+8;break;
							case(0xe0):key=key+12;break;
						}
					password[N]=key;			  //保存按键输入
					if(mark03==1)				  	//第三遍密码标志开启时，将输入新密码保存到临时密码数组中
					{
						temporary[N]=key;
					}
					if(key==right[N])			  //判断这一位密码是否正确并计数
					   temp++;
					if(key == 12&&mark01==1){
						sign=4;
						break;
					}
					if(key ==13){
					LSA = 1; LSB = 1; LSC = 1;
					P0 = 0x00; // 显示第一位
					LSA = 0; LSB = 1; LSC = 1;
					P0 = 0x00; // 显示第二位
					LSA = 1; LSB = 0; LSC = 1;
					P0 = 0x00; // 显示第三位
					LSA = 0; LSB = 0; LSC = 1;
					P0 = 0x00; // 显示第四位		
					mark03=1;
						pirntf("")
						break;
}
				if (key == 14) 
			{
					while (1) 
									{
					LSA = 1; LSB = 1; LSC = 1;
					P0 = 0x40; // 显示第一位
					LSA = 0; LSB = 1; LSC = 1;
					P0 = 0x40; // 显示第二位
					LSA = 1; LSB = 0; LSC = 1;
					P0 = 0x40; // 显示第三位
					LSA = 0; LSB = 0; LSC = 1;
					P0 = 0x40; // 显示第四位
									}
									N=0;
				}

					if(key==15)					  //重新输入密码功能
					  {
							N=0;
					   if(mark01==1)			  //输入正确密码后按S16，可输入第二遍密码
					   {
							 mark02=1;				  //第二遍密码标志开启
							 mark01=0;
							}
					   break;
					  }
					while((GPIO!=0xf0)&&(i<500))  //按键弹起
					{
						delay(100);
						i++;
					}
					i=0;
					while(1)					  //进入显示循环
						{
							while(1)
							{
							 LSA=1;LSB=1;LSC=1;	  //显示第一位
							 key=password[0];
							 P0=0x40;
							 delay(15);  
							 if(N==0)			  
							 break;
							 LSA=0;LSB=1;LSC=1;	  //显示第二位
							 key=password[1];
							 P0=0x40;
							 delay(15);
							 if(N==1)
							 break;
							 LSA=1;LSB=0;LSC=1;	 //显示第三位
							 key=password[2];
							 P0=0x40;
							 delay(15);
							 if(N==2)
							 break;
							 LSA=0;LSB=0;LSC=1;	 //显示第四位
							 key=password[3];
							 P0=0x40;
							 delay(15);
							 if(N==3)
							 break;
							}
							if(GPIO!=0xf0)		 //按键再次按下退出循环
							{	delay(100);
								if(GPIO!=0xf0)
								break;
							}
						}
				N++;	 
				}
			}
			if(N==4)									//四位密码输入完成
			{
				if(mark03==1)					  //第三遍密码标志开启并输入完四位新密码后，可进行第四遍密码输入
				{
				 mark04=1;
				 mark03=0;
				}
				if(temp!=4)						//输入错误，计数加一
				mistake++;
				while((GPIO!=0xf0)&&(i<500))	//按键弹起
					{	
						delay(100);
						i++;
					}
					i=0;
				if(sign==4)						//第三遍密码与第四遍密码相同时，将此密码设置为新密码
				{
					delay(15);
				  right[0]=temporary[0];
					right[1]=temporary[1];
					right[2]=temporary[2];
					right[3]=temporary[3];
					printf("right[i]=");
					for(i=0;i<4;i++){
					printf("%d",right[i]);
					}
					printf("\n");
					sign=0;
					mark04=0;
					mistake=0;
					for(flag=1;flag<100;flag++)	//密码修改正确蜂鸣器响
					{
						bee=~bee;
					  delay(15);
					}
				}


				while(1)						//进入显示循环
				{
					while(1)
					{
							LSA=1;LSB=1;LSC=1;		 //第一位显示
							LSA=0;LSB=1;LSC=1;	  //显示第二位
							LSA=1;LSB=0;LSC=1;	 //显示第三位
							LSA=0;LSB=0;LSC=1;	 //显示第四位
				    	if(temp==4)				//密码正确显示8888
						{
										for(flag=1;flag<10;flag++)	//密码修改正确蜂鸣器响
											{
										bee=~bee;
										delay(15);
											}
						 mistake=0;
						 P0=DSY[8];
						 mark01=1;				//密码输入正确时，第一遍密码标志开启
						 if(mark02==1)			//第二遍密码标志开启并第二遍输入密码正确时，第三遍密码标志开启
						 {
							 mark03=1;
							 mark02=0;
						 }
						}
						 else					//密码错误显示0
						{
							P0=0x00;
							LSA=1;LSB=1;LSC=1;		 //第一位显示
							LSA=0;LSB=1;LSC=1;	  //显示第二位
							LSA=1;LSB=0;LSC=1;	 //显示第三位
							LSA=0;LSB=0;LSC=1;	 //显示第四位
							P0=0x76;
						 if(mistake==3)			//错误次数为3时
						 {LED=0;
						  for(a=0;a<10;a++)
						 	{	
								TH0=TH;
								TL0=TL;
								TR0=1;
								bee=~bee;					  	//蜂鸣器响
								LSA=1;LSB=1;LSC=1;	//数码管循环显示
								P0=DSY[8];
								delay(50); 
								LSA=0;LSB=1;LSC=1;
								P0=DSY[8];
								delay(50);
								LSA=1;LSB=0;LSC=1;
								P0=DSY[8];
								delay(50);
								LSA=0;LSB=0;LSC=1;
								P0=DSY[8];
								delay(50);
								LSA=1;LSB=1;LSC=0;
								P0=DSY[8];
								delay(50);
								LSA=0;LSB=1;LSC=0;
							 	P0=DSY[8];
								delay(50);
								LSA=1;LSB=0;LSC=0;
							 	P0=DSY[8];
								delay(50);
								LSA=0;LSB=0;LSC=0;
							 	P0=DSY[8];
								delay(50);
							}
						 mistake=0; 				//错误次数重置
						 LED=1;
						 }
						 
						}
						break;
					}
					if(GPIO!=0xf0)			 //按键再次按下退出循环
					{	delay(100);
						if(GPIO!=0xf0)
						break;
					}
				}
				N=0;					   //密码位数重置
				temp=0;
			}	
		}
	
	}
}
void uart_init(void)
{
	TMOD=0x20;//即0010 0000,定时器/计数器1,工作方式2
	TH1=0xfd;//设置波特率为9600
	TL1=0xfd;
	TR1=1;//启动定时器/计数器1
	
	SCON=0x50; //0101 0000.串口工作方式1，允许串行控制
	PCON=0x00;//设置SMOD=0
	IE=0x90; //CPU允许中断，串行允许中断
	
	TI=1;//直接使用printf必须加入此句才能实现发送
}
 
