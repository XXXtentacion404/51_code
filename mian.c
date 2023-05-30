#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define GPIO P1
#define count 50000			   //����ֵ��ԼΪ0.05s
#define TH	(65536-count)/256  //��ʱ����ʼ������
#define TL	(65536-count)%256
sbit LSA=P2^2;				   //�����λѡ����
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit bee=P2^5;
sbit LED=P2^0;
sbit KEY1=P3^1;
int key=0;					   //������̰�����־
int password[4];			   //������������
int right[4]={6,6,6,6};	   //��ȷ��������
int temporary[4];			   //��ʱ��������
uchar code DSY[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	 //�������ʾ��������


void delay(int n)			   //��ʱ����
{	int t;
	while(n--)
	{	for(t=0;t<12;t++);
	}
}
void main()
{
	int flag=1;
  int sign=0;				   //��������λ��
	int mark01=0;			   //���������һ�飨ԭ���룩��־
	int mark02=0;			   //��������ڶ��飨ԭ�����ظ�����־
	int mark03=0;			   //������������飨�����룩��־
	int mark04=0;			   //����������ı飨�������ظ�����־
	int mistake=0;			   //�������
	int temp=0;				   //��ȷλ��
	int N=0;				   //����λ��
	int i=0;				   //����
	int a=0;				   //����
	bee=0;
	TMOD&=0X0F;				   //��ʱ����ʼ������
	TMOD|=0X01;
	P2=0X03;
	while(1)
	{
	while(1)				   //����ѭ��
		{
			GPIO=0x0f;
			if(GPIO!=0x0f)		   //�жϰ���
			{
				delay(100);
				if(GPIO!=0x0f)	   //�����жϰ���
				{
					switch(N)      //λѡ   
		            {
		                case(0):
		                        LSA=1;LSB=1;LSC=1; break;
		                case(1):
		                        LSA=0;LSB=1;LSC=1; break;
		                case(2):
		                        LSA=1;LSB=0;LSC=1; break;
		                case(3):
		                        LSA=0;LSB=0;LSC=1; break;
//		                case(4):
//		                        LSA=1;LSB=1;LSC=0; break;
//		                case(5):
//		                        LSA=0;LSB=1;LSC=0; break;
					}
					GPIO=0X0F;						//������
						switch(GPIO)
						{
							case(0x07):key=0;break;
							case(0x0b):key=1;break;
							case(0x0d):key=2;break;
							case(0x0e):key=3;break;
						}						   //������
					GPIO=0XF0;
					switch(GPIO)
						{
							case(0x70):key=key;break;
							case(0xb0):key=key+4;break;
							case(0xd0):key=key+8;break;
							case(0xe0):key=key+12;break;
						}
					
//					P0=DSY[key];				  //������̰������������ܲ���ʾ
					password[N]=key;			  //���水������
					if(mark04==1)				  //���ı������־����ʱ����������������������ı���������ȶ�
					{
						if(key==temporary[N])
						sign++;
					}
					if(mark03==1)				  //�����������־����ʱ�������������뱣�浽��ʱ����������
					{
						temporary[N]=key;
					}
					if(key==right[N])			  //�ж���һλ�����Ƿ���ȷ������
					   temp++;
					if(key ==13){
					
					temporary[N]=key;				//�����������뱣�浽��ʱ����������
					
					
}
				if (key == 14) 
			{
					while (1) 
									{
					LSA = 1; LSB = 1; LSC = 1;
					P0 = 0x40; // ��ʾ��һλ
					LSA = 0; LSB = 1; LSC = 1;
					P0 = 0x40; // ��ʾ�ڶ�λ
					LSA = 1; LSB = 0; LSC = 1;
					P0 = 0x40; // ��ʾ����λ
					LSA = 0; LSB = 0; LSC = 1;
					P0 = 0x40; // ��ʾ����λ
									}
				}

					if(key==15)					  //�����������빦��
					  {N=0;
					   if(mark01==1)			  //������ȷ�����S16��������ڶ�������
					   {mark02=1;				  //�ڶ��������־����
					    mark01=0;
					}
					   break;
					  }
					while((GPIO!=0xf0)&&(i<500))  //��������
					{	delay(100);
						i++;
					}
					i=0; 
					while(1)					  //������ʾѭ��
						{	while(1)
							{
							 LSA=1;LSB=1;LSC=1;	  //��ʾ��һλ
							 key=password[0];
							 P0=0x40;
							 delay(15); 
							 if(N==0)			  
							 break;
							 LSA=0;LSB=1;LSC=1;	  //��ʾ�ڶ�λ
							 key=password[1];
							 P0=0x40;
							 delay(15);
							 if(N==1)
							 break;
							 LSA=1;LSB=0;LSC=1;	 //��ʾ����λ
							 key=password[2];
							 P0=0x40;
							 delay(15);
							 if(N==2)
							 break;
							 LSA=0;LSB=0;LSC=1;	 //��ʾ����λ
							 key=password[3];
							 P0=0x40;
							 delay(15);
							 if(N==3)
							 break;
//							 LSA=1;LSB=1;LSC=0;	 //��ʾ����λ
//							 key=password[4];
//							 P0=DSY[key];
//							 delay(15);
//							 if(N==4)
//				             break;
//							 LSA=0;LSB=1;LSC=0;	 //��ʾ����λ
//						 	 key=password[5];
//							 P0=DSY[key];
//							 delay(15);
//							 if(N==5)
//				             break;
							}
							if(GPIO!=0xf0)		 //�����ٴΰ����˳�ѭ��
							{	delay(100);
								if(GPIO!=0xf0)
								break;
							}
						}
					 
				N++;	 
				}
		        
			}
			if(N==4)							//��λ�����������
			{	if(mark03==1)					//�����������־��������������λ������󣬿ɽ��е��ı���������
				{mark04=1;
				 mark03=0;
				}
				if(temp!=4)						//������󣬼�����һ
				mistake++;
				while((GPIO!=0xf0)&&(i<500))	//��������
					{	
						delay(100);
						i++;
					}
					i=0; 
				if(sign==4)						//��������������ı�������ͬʱ��������������Ϊ������
				{
					delay(15);
				  right[0]=temporary[0];
					right[1]=temporary[1];
					right[2]=temporary[2];
					right[3]=temporary[3];
					right[4]=temporary[4];
					right[5]=temporary[5];
					sign=0;
					mark04=0;
					mistake=0;
					for(flag=1;flag<100;flag++)	//�����޸���ȷ��������
					{ bee=~bee;
					  delay(15);
					}
				}
				while(1)						//������ʾѭ��
				{
//							LSA=1;LSB=1;LSC=1;		 //��һλ��ʾ
//							LSA=0;LSB=1;LSC=1;	  //��ʾ�ڶ�λ
//							LSA=1;LSB=0;LSC=1;	 //��ʾ����λ
//							LSA=0;LSB=0;LSC=1;	 //��ʾ����λ
//							P0=DSY[10];
//							delay(200000);
					while(1)
					{
							LSA=1;LSB=1;LSC=1;		 //��һλ��ʾ
							LSA=0;LSB=1;LSC=1;	  //��ʾ�ڶ�λ
							LSA=1;LSB=0;LSC=1;	 //��ʾ����λ
							LSA=0;LSB=0;LSC=1;	 //��ʾ����λ
				    	if(temp==4)				//������ȷ��ʾ8888
						{
						 mistake=0;
						 P0=DSY[8];
						 mark01=1;				//����������ȷʱ����һ�������־����
						 if(mark02==1)			//�ڶ��������־�������ڶ�������������ȷʱ�������������־����
						 {mark03=1;
						  mark02=0;
						 }
						}
						 else					//���������ʾ0
						{
							P0=0x00;
							LSA=1;LSB=1;LSC=1;		 //��һλ��ʾ
							LSA=0;LSB=1;LSC=1;	  //��ʾ�ڶ�λ
							LSA=1;LSB=0;LSC=1;	 //��ʾ����λ
							LSA=0;LSB=0;LSC=1;	 //��ʾ����λ
							P0=0x76;
						 if(mistake==3)			//�������Ϊ3ʱ
						 {LED=0;
						  for(a=0;a<100;a++)
						 	{	
								TH0=TH;
								TL0=TL;
								TR0=1;
								bee=~bee;					  	//��������
								LSA=1;LSB=1;LSC=1;	//�����ѭ����ʾ
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
						 mistake=0; 				//�����������
						 LED=1;
						 }
						 
						}
						break;
					}
					if(GPIO!=0xf0)			 //�����ٴΰ����˳�ѭ��
					{	delay(100);
						if(GPIO!=0xf0)
						break;
					}
				}
				N=0;					   //����λ������
				temp=0;
			}	
		}
	
	}
}
