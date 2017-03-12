#include "stdafx.h"
#include "Multimeter.h"

CMultimeter::CMultimeter(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CMultimeter::~CMultimeter(void)
{
}


int CMultimeter::MultiQueryResult(char* model, char* serialNum)
{
	int ret=1;
	char querycode[]="ABCD0300111400";         //��ѯָ��
	BYTE buffer[255];
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	DWORD numBytes;
	m_CHidUart.DeviceWriteString(m_deviceName,querycode);                    //д��ָ��
	Sleep(100);                                //��ʱ200ms
	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)     //��ȡ
	{
		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x72 && buffer[i+5]==0x11)    //֡�����Ƿ�Ϊ��ѯ�����ͣ�֡�����Ƿ�Ϊ��ѯ����
					{
						ret=0;
						numBytes=buffer[i+3]*(0x100)+buffer[i+2]-3;   //��������
						memcpy(model,buffer+i+6,12);                    //��ȡ�ͺ�
						//AfxMessageBox(model);
						memcpy(serialNum,buffer+i+17,numBytes-11);      //��ȡ���к�
						//AfxMessageBox(serialNum);
					}				
				}
			}	
		}
		else
		{
			ret=1;
			//AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;
}

int CMultimeter::MultiNumbers(char* hidnumber,char* multinumber)
{
	char temp[10];
	char a[10];
	char multiModel[255];
	char multiSN[255];
	int ret=1;

	DWORD numDevices=0;
	DWORD hidNumbers=0;
	DWORD multiNumbers=0;
	HID_UART_DEVICE_STR deviceString;
	
	if(m_CHidUart.DevicesGetNum(m_deviceName,&numDevices)==0)
	{
		//���HID�豸����
		for(DWORD i=0;i<numDevices;i++)
		{			
			if(m_CHidUart.DeviceGetString(m_deviceName,i,deviceString)==0)
			{
				if(strlen(deviceString)>5)
				{
					m_CHidUart.DeviceOpen(m_deviceName,i);
					m_CHidUart.DeviceConnect(m_deviceName);
				
				//AfxMessageBox(deviceString);
				//������ñ�����
					ret=MultiQueryResult(multiModel, multiSN);
					m_CHidUart.DeviceClose(m_deviceName);
					if(ret==0)
					{
					
						m_COperate.WriteStatusCache_M(itoa(hidNumbers,a,10),deviceString,itoa(i,a,10));
						sequense[multiNumbers]=i;
						multiNumbers++;
					}
					else
					{
						m_COperate.WriteStatusCache_M(itoa(hidNumbers,a,10),"0",itoa(i,a,10));
					}

					hidNumbers++;
				}
			}
		}
	}
	sprintf(temp,"%d",hidNumbers);
	memcpy(hidnumber,temp,(strlen(temp)+1));

	sprintf(temp,"%d",multiNumbers);
	memcpy(multinumber,temp,(strlen(temp)+1));

	return ret;
}

int CMultimeter::MultiConnect(char* number)
{

	int ret=1;
	char deviceStr[255];
	char numberStr[255];
	DWORD numDevices=0;
	DWORD deviceNum=0;
	
	HID_UART_DEVICE_STR deviceString;

	if(m_COperate.ReadStatusCache_M(number,deviceStr,numberStr)!=0)
	{
		if(strcmp(deviceStr,"0")!=0)
		{
			if(m_CHidUart.DevicesGetNum(m_deviceName,&numDevices)==0)
			{
				//���HID�豸����
				for(DWORD i=0;i<numDevices;i++)
				{			
					if(m_CHidUart.DeviceGetString(m_deviceName,i,deviceString)==0)
					{
						if(strcmp(deviceStr,deviceString)==0)
						{
							ret=m_CHidUart.DeviceOpen(m_deviceName,i);
							break;
						}
					}
				}
			}
			if(ret==0)
			{
				ret=m_CHidUart.DeviceConnect(m_deviceName);
			}
			else
			{
				m_CHidUart.DeviceClose(m_deviceName);
			}
		}
	}

	return ret;
}

int CMultimeter::MultiDisconnect(char* number)
{
	int ret=1;
	ret=m_CHidUart.DeviceClose(m_deviceName);
	return ret;
}

int CMultimeter::MultiRangeSet(char* range)
{	
	int ret=1;
	BYTE rangecode[]={0xAB,0xCD,0x04,0x00,0x02,0x00,0x06,0x00} ;  //ABCD040002000600 �Զ�ģʽ
	rangecode[5]=rangecode[5]+atoi(range);                       //��������
	rangecode[6]=rangecode[6]+atoi(range);                       //����У���
	DWORD numBytesToWrite=sizeof(rangecode);
	BYTE buffer[255];
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	DWORD numBytes;
	char statusReturn[3]="";
    m_CHidUart.DeviceWrite(m_deviceName,rangecode,numBytesToWrite);      //д��ָ��
	Sleep(200);                                                          //��ʱ200ms
	                    
	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)                    //��ȡ
	{
		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x01)    //֡�����Ƿ�ΪӦ����
					{
						memcpy(statusReturn,buffer+i+5,2);                    //��ȡ����״̬
						//AfxMessageBox(statusReturn);
						if(statusReturn[0]=='O' && statusReturn[1]=='K')
							ret=0;
					}				
				}
			}	
		}
		else
		{
			ret=1;
			//AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;

}

int CMultimeter::MultiReadResult(char* value, char* unit,char* funcSet,char* range)
{
	int ret=1;
	
	char readRealTimecode[]="ABCD040005000900";         //��ȡʵʱ��������ģʽָ��
	BYTE buffer[255]="";
	char resultbuffer[5]="";
	char unitbuffer[9]="";
	char a[2]="";
	char b[2]="";
	char c[2]="";
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	float resultvalue=0;
	m_CHidUart.DeviceWriteString(m_deviceName,readRealTimecode);                //д��ָ��
	Sleep(100);                                                                 //��ʱ200ms
	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)                        //��ȡ
	{

		/*CString hexb;
		char a[2]="";
		for(DWORD i=0;i<numBytesRead;i++)
		{
			sprintf(a,"%2x",buffer[i]);
			hexb=hexb+a;
		}
		AfxMessageBox(_T(hexb));*/


		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x02)    //֡�����Ƿ�Ϊʵʱ��
					{
						ret=0;

						memcpy(resultbuffer,buffer+i+10,4);           
						resultvalue=*(float *)resultbuffer;           //��ȡ���Խ��
						sprintf(value,"%f",resultvalue);
						//AfxMessageBox(value);
						     //��ȡ��λ
						if(buffer[i+15]==0xB0)
						{
							strcpy(unitbuffer,"deg");;
						}
						else if(buffer[i+15]==0x7E)
						{
							strcpy(unitbuffer,"ohm");
						}
						else if(buffer[i+16]==0x7E)
						{
							unitbuffer[0]=buffer[i+15];
							strcat(unitbuffer,"ohm");
						}
						else if(buffer[i+15]==0x25)
						{
							strcpy(unitbuffer,"per");
						}
						else
						{
							memcpy(unitbuffer,buffer+i+15,8); 
						}
						strcpy(unit,unitbuffer);

						sprintf(a,"%2x",buffer[i+8]);
						sprintf(b,"%2x",buffer[i+7]);						
						strcat(a,b);						
						strcpy(funcSet,a);                  //����SW|SL|MN|FX����

						sprintf(c,"%2x",buffer[i+9]);
						strcpy(range,c);                    //������������
					}				
				}
			}	
		}
		else
		{
			ret=1;
			AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;
}

int CMultimeter::MultiMeasFuncSet(char* sW, char* sL, char* mN, char* fX)
{
	int ret=1;
	int x1=atoi(sW);
	int x2=atoi(sL);
	int x3=atoi(mN);
	int x4=atoi(fX);
	if(strcmp(sW,"A")==0)
		x1=0xA;
	BYTE func1= SW( x1 )| SL( x2 );
	BYTE func2= MN( x3 )| FX( x4 );
	BYTE codesum={0x0000};
	BYTE functionCode[]={0xAB,0xCD,0x05,0x00,0x01,0x00,0x00,0x00,0x00} ;  //ABCD05000100000600 �Զ�ģʽ
	functionCode[5]=functionCode[5]+func2;                       //����menu��F��
	functionCode[6]=functionCode[6]+func1;                       //���õ��̺�F��
	codesum=functionCode[2]+functionCode[3]+functionCode[4]+functionCode[5]+functionCode[6];  //����У���
	functionCode[7]=codesum & 0xFF;
	functionCode[8]=(codesum & 0xFF00)>>8;

	DWORD numBytesToWrite=sizeof(functionCode);
	BYTE buffer[255];
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	char statusReturn[3]="";

    m_CHidUart.DeviceWrite(m_deviceName,functionCode,numBytesToWrite);      //д��ָ��
	Sleep(100);                                                          //��ʱ200ms

	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)                    //��ȡ
	{
		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x01)                           //֡�����Ƿ�ΪӦ����
					{
						memcpy(statusReturn,buffer+i+5,2);                    //��ȡ����״̬
						//AfxMessageBox(statusReturn);
						if(statusReturn[0]=='O' && statusReturn[1]=='K')
							ret=0;
					}				
				}
			}	
		}
		else
		{
			ret=1;
			//AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;

}

int CMultimeter::MultiInit(char* isReset)
{
	int ret=1;
	char status[10];
	m_COperate.ReadHandles("MultiMeter","DeviceStatus",status);  
	string temp_s(status);
	if(temp_s!="Open")
	{
		ret=0;
		int isWrite=m_COperate.WriteHandles("MultiMeter","DeviceStatus","Open"); 
		if(isWrite==0)
		{
			throw string("״̬д��ʧ��");
		}
	}
	else if(temp_s=="Open")
	{
		ret=2;
	}
	return ret;
}

int CMultimeter::MultiClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	char status[10];
	m_COperate.ReadHandles("MultiMeter","DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s=="Close")
		return 0;	
	m_COperate.WriteHandles("MultiMeter","DeviceStatus","Close"); //д���豸״̬

	return ret;
}

int CMultimeter::MultiDeviceNumbers(std::vector<CString> & deviceList)
{
	char multiModel[255];
	char multiSN[255];
	int ret=1;
	CString deviceStr="";

	DWORD numDevices=0;
	DWORD hidNumbers=0;
	DWORD multiNumbers=0;
	HID_UART_DEVICE_STR hidString;
	
	if(m_CHidUart.DevicesGetNum(m_deviceName,&numDevices)==0)
	{
		//���HID�豸����
		for(DWORD i=0;i<numDevices;i++)
		{			
			if(m_CHidUart.DeviceGetString(m_deviceName,i,hidString)==0)
			{
				if(strlen(hidString)>5)
				{
					m_CHidUart.DeviceOpen(m_deviceName,i);
					m_CHidUart.DeviceConnect(m_deviceName);
					hidNumbers++;
					//AfxMessageBox(deviceString);
					//������ñ�����
					ret=MultiQueryResult(multiModel, multiSN);
					m_CHidUart.DeviceClose(m_deviceName);
					if(ret==0)
					{
						deviceStr.Format(_T("%d"),i);
						deviceStr=deviceStr + _T("_") + _T(hidString)+ _T("_") + _T(multiSN);
						deviceList.push_back(deviceStr);
						AfxMessageBox(deviceStr);
					}
					else
					{
						deviceStr.Format(_T("%d"),i);
						deviceStr=deviceStr + _T("_") + _T(hidString)+ _T("_") + _T("--");
						deviceList.push_back(deviceStr);
						AfxMessageBox(deviceStr);
					}
				}
			}
		}
	}
	return ret;
}


int CMultimeter::MultiReadResultData(float& resultvalue)
{
	int ret=1;	
	char readRealTimecode[]="ABCD040005000900";         //��ȡʵʱ��������ģʽָ��
	BYTE buffer[255]="";
	char resultbuffer[5]="";
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	m_CHidUart.DeviceWriteString(m_deviceName,readRealTimecode);                //д��ָ��
	Sleep(100);                                                                 //��ʱ200ms
	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)                        //��ȡ
	{
		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x02)    //֡�����Ƿ�Ϊʵʱ��
					{
						ret=0;
						memcpy(resultbuffer,buffer+i+10,4);           
						resultvalue=*(float *)resultbuffer;           //��ȡ���Խ��
					}				
				}
			}	
		}
		else
		{
			ret=1;
			AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;
}
int CMultimeter::MultiReadSampleResult(char* count, char* intervalTime, char* limitValue, char* result)
{
	int ret=1;
	float dataTemp=0;
	float dataDelta=10000;
	float deltaTemp=10000;
	float resultValue=0;
	//char strResult[255];

	for(int i=0;i<atoi(count);i++)
	{
		Sleep(atoi(intervalTime));
		MultiReadResultData(resultValue);
		dataDelta=abs(resultValue-dataTemp);
		if(dataDelta<atof(limitValue) && deltaTemp<atof(limitValue))
		{
			break;
		}
		dataTemp=resultValue;
		deltaTemp=dataDelta;
	}
	ret=MultiReadResultData(resultValue);
	sprintf(result,"%f",resultValue);
	return ret;
}

int CMultimeter::MultiReadSampleResult_M(char* numbers,char* count, char* intervalTime, char* limitValue, char* result)
{
	int ret1=1;
	int ret2=1;
	int k=0;
	char a[5];
	//char strResult[255];
	float resultValue=0;
	std::vector<float> dataTemp(atoi(numbers),0);
	std::vector<float> dataDelta(atoi(numbers),10000);
	std::vector<float> deltaTemp(atoi(numbers),10000);
	//std::vector<std::vector<float>> resultList;
	//resultList.reserve(atoi(count)*(atoi(numbers)+1));
	std::bitset<100> isPass;
	//CString s;

	for(int i=0;i<atoi(count);i++)
	{
		Sleep(atoi(intervalTime));
		for(int j=0;j<atoi(numbers);j++)
		{			
			ret2=MultiConnect(itoa(j,a,10));
			if(ret2==0)
			{
				MultiReadResultData(resultValue);
				MultiDisconnect(itoa(j,a,10));
				dataDelta[j]=abs(resultValue-dataTemp[j]);
				dataTemp[j]=resultValue;
				if(dataDelta[j]<atof(limitValue) && deltaTemp[j]<atof(limitValue))
				{
					isPass.set(j,false);	//ͨ����Ϊ0
				}
				else
				{
					isPass.set(j,true);		//��ͨ����Ϊ1
				}
				deltaTemp[j]=dataDelta[j];
			}
		}
		if(isPass.none())	//�Ƿ����н����Ϊ0������ǽ���ѭ��
		{
			/*s.Format("%d",i);
			AfxMessageBox(s);*/
			ret1=0;
			break;
		}
	}
	for(int j=0;j<atoi(numbers);j++)
		{			
			ret2=MultiConnect(itoa(j,a,10));
			if(ret2==0)
			{
				MultiReadResultData(resultValue);
				MultiDisconnect(itoa(j,a,10));
				if(k==0)
				{
					sprintf(result,"%f",resultValue);
				}
				else
				{
					sprintf(result,"%s,%f",result,resultValue);
				}
				k++;
			}
			else
			{
				if(k==0)
				{
					sprintf(result,"%s","--");
				}
				else
				{
					sprintf(result,"%s,%s",result,"--");
				}
				k++;
			}
		}
	return ret1;
}


int CMultimeter::MultiInvalidValue(char* numbers,char* result)
{
	int ret=0;
	int k=0;
	char a[5];
	for(int i=0;i<atoi(numbers);i++)
	{			
		ret=MultiConnect(itoa(i,a,10));
		if(ret==0)
		{
			//MultiReadResultData(resultValue);
			MultiDisconnect(itoa(i,a,10));
			if(i==0)
			{
				sprintf(result,"%s","Invalid");
			}
			else
			{
				sprintf(result,"%s,%s",result,"Invalid");
			}
			
		}
		else
		{
			if(i==0)
			{
				sprintf(result,"%s","--");
			}
			else
			{
				sprintf(result,"%s,%s",result,"--");
			}
			
		}
	}

	return ret;
}

//int CMultimeter::MultiMeasureSet(char* numbers, char* funcSet, char* rangeSet)
//{
//	int ret=0;
//	char result[100];
//	char unit[50];
//	char func[50];
//	char range[50];
//	char a[5];
//	for(int i=0;i<atoi(numbers);i++)
//	{
//		ret=MultiConnect(itoa(i,a,10));
//		if(ret==0)
//		{
//			MultiMeasFuncSet(funcSet[0],funcSet[1],funcSet[2],funcSet[3]);
//			MultiRangeSet(rangeSet);
//			//��鵵λ�Ƿ���ȷ
//			MultiReadResult(result,unit,func,range);
//			if(func[0]=='a' && func[1]=='1')
//			{
//				m_COperate.ShowMessage("�뽫��λת����������A��");
//				do
//				{
//					MultiMeasFuncSet(funcSet[0],funcSet[1],funcSet[2],funcSet[3]);
//					MultiRangeSet(rangeSet);
//					Sleep(1000);
//					MultiReadResult(result,unit,func,range);
//				}
//				while(func[0]=='a' && func[1]=='1');
//			}
//			MultiDisconnect(itoa(i,a,10));
//		}
//	}
//	return 0;
//}

int CMultimeter::MultiRemoveMisuse()
{
	int ret=1;
	BYTE rangecode[]={0xAB,0xCD,0x07,0x00,0xFD,0x10,0x81,0x89,0x20,0x3E,0x02} ;  //ABCD040002000600 �Զ�ģʽ

	DWORD numBytesToWrite=sizeof(rangecode);
	BYTE buffer[255];
	DWORD numBytesRead=0;
	DWORD* p=&numBytesRead;
	DWORD numBytes;
	char statusReturn[3]="";
    m_CHidUart.DeviceWrite(m_deviceName,rangecode,numBytesToWrite);      //д��ָ��
	Sleep(200);                                                          //��ʱ200ms
	                    
	if (m_CHidUart.DeviceRead(m_deviceName,buffer,p)==0)                    //��ȡ
	{
		if(numBytesRead>0)
		{
			for(DWORD i=0;i<numBytesRead;i++)
			{
				if(buffer[i]==0xAB && buffer[i+1]==0xCD)          //��ѯ֡��ͷ
				{
					if(buffer[i+4]==0x01)    //֡�����Ƿ�ΪӦ����
					{
						memcpy(statusReturn,buffer+i+5,2);                    //��ȡ����״̬
						//AfxMessageBox(statusReturn);
						if(statusReturn[0]=='O' && statusReturn[1]=='K')
							ret=0;
					}				
				}
			}	
		}
		else
		{
			ret=1;
			//AfxMessageBox("�����Ƿ������豸");
		}
	}
	return ret;
}
