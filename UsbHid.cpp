// UsbHid.cpp: implementation of the UsbHid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "UsbHidStr.h"
#include "UsbHid.h"

extern "C" {
#include "setupapi.h"
#include "hidsdi.h"
}

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define		REPORT_COUNT	64		//�˵㳤��
#define		USBD_VID        0x1183 
#define		USBD_PID        0x5711 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsbHid::CUsbHid()
{
	hWriteHandle=hReadHandle=INVALID_HANDLE_VALUE;
}

CUsbHid::~CUsbHid()
{

}

bool CUsbHid::OpenHid(USHORT Vid, USHORT Pid)
{
	//���������豸�Ƿ��Ѿ��ҵ�
	BOOL DevFound=FALSE;
	//���������ҵ����豸·��
	CString DevPathName="";
	//����һ��GUID�Ľṹ��HidGuid������HID�豸�Ľӿ���GUID��
	GUID HidGuid;
	//����һ��DEVINFO�ľ��hDevInfoSet�������ȡ�����豸��Ϣ���Ͼ����
	HDEVINFO hDevInfoSet;
	//����MemberIndex����ʾ��ǰ�������ڼ����豸��0��ʾ��һ���豸��
	DWORD MemberIndex;
	//DevInterfaceData�����������豸�������ӿ���Ϣ
	SP_DEVICE_INTERFACE_DATA DevInterfaceData;
	//����һ��BOOL���������溯�������Ƿ񷵻سɹ�
	BOOL Result;
	//����һ��RequiredSize�ı���������������Ҫ������ϸ��Ϣ�Ļ��峤�ȡ�
	DWORD RequiredSize;
	//����һ��ָ���豸��ϸ��Ϣ�Ľṹ��ָ�롣
	PSP_DEVICE_INTERFACE_DETAIL_DATA	pDevDetailData;
	//����һ������������豸�ľ����
	HANDLE hDevHandle;
	//����һ��HIDD_ATTRIBUTES�Ľṹ������������豸�����ԡ�
	HIDD_ATTRIBUTES DevAttributes;

	//��DevInterfaceData�ṹ���cbSize��ʼ��Ϊ�ṹ���С
	DevInterfaceData.cbSize=sizeof(DevInterfaceData);
	//��DevAttributes�ṹ���Size��ʼ��Ϊ�ṹ���С
	DevAttributes.Size=sizeof(DevAttributes);

	//����HidD_GetHidGuid������ȡHID�豸��GUID����������HidGuid�С�
	HidD_GetHidGuid(&HidGuid);

	//����HidGuid����ȡ�豸��Ϣ���ϡ�����Flags��������Ϊ
	//DIGCF_DEVICEINTERFACE|DIGCF_PRESENT��ǰ�߱�ʾʹ�õ�GUIDΪ
	//�ӿ���GUID�����߱�ʾֻ�о�����ʹ�õ��豸����Ϊ��������ֻ
	//�����Ѿ������ϵ��豸�����صľ��������hDevinfo�С�ע���豸
	//��Ϣ������ʹ����Ϻ�Ҫʹ�ú���SetupDiDestroyDeviceInfoList
	//���٣���Ȼ������ڴ�й©��
	hDevInfoSet=SetupDiGetClassDevs(&HidGuid,
		                            NULL,
							       	NULL,
						            DIGCF_DEVICEINTERFACE|DIGCF_PRESENT);

	//MessageBox(NULL,"��ʼ�����豸!",NULL,MB_OK);

	//Ȼ����豸������ÿ���豸�����о٣�����Ƿ�������Ҫ�ҵ��豸
	//���ҵ�����ָ�����豸�������豸�Ѿ��������ʱ�����˳����ҡ�
	//����ָ���һ���豸������MemberIndex��Ϊ0��
	MemberIndex=0;
	while(1)
	{
		//����SetupDiEnumDeviceInterfaces���豸��Ϣ�����л�ȡ���Ϊ
		//MemberIndex���豸��Ϣ��
		Result=SetupDiEnumDeviceInterfaces(hDevInfoSet,
											NULL,
											&HidGuid,
											MemberIndex,
											&DevInterfaceData);

		//�����ȡ��Ϣʧ�ܣ���˵���豸�Ѿ�������ϣ��˳�ѭ����
		if(Result==FALSE) break;

		//��MemberIndexָ����һ���豸
		MemberIndex++;

		//�����ȡ��Ϣ�ɹ����������ȡ���豸����ϸ��Ϣ���ڻ�ȡ�豸
		//��ϸ��Ϣʱ����Ҫ��֪��������ϸ��Ϣ��Ҫ���Ļ���������ͨ��
		//��һ�ε��ú���SetupDiGetDeviceInterfaceDetail����ȡ����ʱ
		//�ṩ�������ͳ��ȶ�ΪNULL�Ĳ��������ṩһ������������Ҫ���
		//�������ı���RequiredSize��
		Result=SetupDiGetDeviceInterfaceDetail(hDevInfoSet,
												&DevInterfaceData,
												NULL,
												NULL,
												&RequiredSize,
												NULL);

		//Ȼ�󣬷���һ����СΪRequiredSize�����������������豸��ϸ��Ϣ��
		pDevDetailData=(PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(RequiredSize);
		if(pDevDetailData==NULL) //����ڴ治�㣬��ֱ�ӷ��ء�
		{
			MessageBox(NULL,"�ڴ治��!",NULL,MB_OK);
			SetupDiDestroyDeviceInfoList(hDevInfoSet);
			return false;
		}

		//������pDevDetailData��cbSizeΪ�ṹ��Ĵ�С��ע��ֻ�ǽṹ���С��
		//���������滺��������
		pDevDetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		//Ȼ���ٴε���SetupDiGetDeviceInterfaceDetail��������ȡ�豸��
		//��ϸ��Ϣ����ε�������ʹ�õĻ������Լ���������С��
		Result=SetupDiGetDeviceInterfaceDetail(hDevInfoSet,
												&DevInterfaceData,
												pDevDetailData,
												RequiredSize,
												NULL,
												NULL);

		//���豸·�����Ƴ�����Ȼ�����ٸո�������ڴ档
		DevPathName=pDevDetailData->DevicePath;
		free(pDevDetailData);

		//�������ʧ�ܣ��������һ���豸��
		if(Result==FALSE) continue;

		//������óɹ�����ʹ�ò�����д���ʵ�CreateFile����
		//����ȡ�豸�����ԣ�����VID��PID���汾�ŵȡ�
		//����һЩ��ռ�豸������USB���̣���ʹ�ö����ʷ�ʽ���޷��򿪵ģ�
		//��ʹ�ò�����д���ʵĸ�ʽ�ſ��Դ���Щ�豸���Ӷ���ȡ�豸�����ԡ�
		hDevHandle=CreateFile(DevPathName, 
								NULL,
								FILE_SHARE_READ|FILE_SHARE_WRITE, 
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);

		//����򿪳ɹ������ȡ�豸���ԡ�
		if(hDevHandle!=INVALID_HANDLE_VALUE)
		{
			//��ȡ�豸�����Բ�������DevAttributes�ṹ����
			Result=HidD_GetAttributes(hDevHandle,
										&DevAttributes);

			//�رոոմ򿪵��豸
			CloseHandle(hDevHandle);

			//��ȡʧ�ܣ�������һ��
			if(Result==FALSE) continue;

			//�����ȡ�ɹ����������е�VID��PID�Լ��豸�汾����������Ҫ��
			//���бȽϣ������һ�µĻ�����˵������������Ҫ�ҵ��豸��
			if(DevAttributes.VendorID==Vid) //���VID���
				if(DevAttributes.ProductID==Pid) //����PID���
					//if(DevAttributes.VersionNumber==MyPvn) //�����豸�汾�����
						{
							DevFound=TRUE; //�����豸�Ѿ��ҵ�
							//MessageBox(NULL,"�豸�Ѿ��ҵ�!",NULL,MB_OK);

							//��ô��������Ҫ�ҵ��豸���ֱ�ʹ�ö�д��ʽ��֮������������
							//����ѡ��Ϊ�첽���ʷ�ʽ��
							//����ʽ���豸
							hReadHandle=CreateFile(DevPathName, 
													GENERIC_READ,
													FILE_SHARE_READ|FILE_SHARE_WRITE, 
													NULL,
													OPEN_EXISTING,
													FILE_ATTRIBUTE_NORMAL,//|FILE_FLAG_OVERLAPPED,
													NULL);

							if(hReadHandle!=INVALID_HANDLE_VALUE)
							{
								//MessageBox(NULL,"�����ʴ��豸�ɹ�!",NULL,MB_OK);
							}
							else 
								MessageBox(NULL,"�����ʴ��豸ʧ��!",NULL,MB_OK);

							//д��ʽ���豸
							hWriteHandle=CreateFile(DevPathName, 
													GENERIC_WRITE,
													FILE_SHARE_READ|FILE_SHARE_WRITE, 
													NULL,
													OPEN_EXISTING,
													FILE_ATTRIBUTE_NORMAL,//|FILE_FLAG_OVERLAPPED,
													NULL);
							if(hWriteHandle!=INVALID_HANDLE_VALUE)
							{
								//MessageBox(NULL,"д���ʴ��豸�ɹ�!",NULL,MB_OK);
							}
							else 
								MessageBox(NULL,"д���ʴ��豸ʧ��!",NULL,MB_OK);

							break;
						}
		}
		//�����ʧ�ܣ��������һ���豸
		else continue;
	}

	//����SetupDiDestroyDeviceInfoList���������豸��Ϣ����
	SetupDiDestroyDeviceInfoList(hDevInfoSet);

	//����豸�Ѿ��ҵ�����ôӦ��ʹ�ܸ�������ť����ͬʱ��ֹ���豸��ť
	if(DevFound)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void CUsbHid::CloseHid()
{
	//��������ݵľ��������Ч�������ر�֮
	if(hReadHandle!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hReadHandle);
		hReadHandle=INVALID_HANDLE_VALUE;
	}
	if(hWriteHandle!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hWriteHandle);
		hWriteHandle=INVALID_HANDLE_VALUE;
	}
}

bool CUsbHid::WriteHid(BYTE *str, DWORD *len, DWORD *err)
{
	BOOL Result;
	UINT LastError;
	UINT i;
	DWORD strlen=0;
	UCHAR WriteReportBuffer[REPORT_COUNT+1]={0};

	//��������Ч����˵�����豸ʧ��
	if(hWriteHandle==INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"��Ч��д������!",NULL,MB_OK);
		if(err!=NULL)
			*err=(DWORD)INVALID_HANDLE_VALUE;
		if(len!=NULL)
			*len=0;
		return false;
	}

	if(len==NULL)
		strlen=REPORT_COUNT+1;
	else
		strlen=*len;

	//����Ҫ���ͱ��������
	WriteReportBuffer[0]=0x00;   //����IDΪ0
	for(i=0;(i<REPORT_COUNT)&&(i<strlen);i++)
		WriteReportBuffer[i+1]=str[i];

	//����WriteFile������������
	Result=WriteFile(hWriteHandle,
					WriteReportBuffer, 
					REPORT_COUNT+1,
					&strlen,
					NULL);
	if(len!=NULL)
		*len=strlen;

	//�����������ʧ�ܣ�����������ʧ�ܣ�Ҳ������IO������
	if(Result==FALSE)
	{
		//��ȡ���������
		LastError=GetLastError();
		if(err!=NULL)
			*err=LastError;

		//���Ƿ������IO����
		if((LastError==ERROR_IO_PENDING)||(LastError==ERROR_SUCCESS))
		{
			return true;
		}
		//�����Ǻ�������ʱ����������ʾ�������
		else
		{
			CString cs;
			cs.Format("����ʧ�ܣ�������룺%d",LastError);
			MessageBox(NULL,cs,NULL,MB_OK);
			//���������Ϊ1��˵�����豸��֧�ָú�����
			if(LastError==1)
			{
				MessageBox(NULL,"���豸��֧��WriteFile������",NULL,MB_OK);
			}
			return false;
		}
	}
	//���򣬺������سɹ�
	else
	{
		return true;
	}	
}

bool CUsbHid::ReadHid(BYTE *str, DWORD *len, DWORD *err)
{
	BOOL Result;
	UINT i;
	DWORD strlen=0;
	UCHAR ReadReportBuffer[REPORT_COUNT+1]={0};

	if(hReadHandle==INVALID_HANDLE_VALUE) //����������Ч
	{
		MessageBox(NULL,"��Ч�Ķ�������!",NULL,MB_OK);
		if(err!=NULL)
			*err=(DWORD)INVALID_HANDLE_VALUE;
		if(len!=NULL)
			*len=0;
		return false;
	}

	//�����ReadFile��������9�ֽڵı�������
	Result=ReadFile(hReadHandle,
			ReadReportBuffer,
			REPORT_COUNT+1,
			&strlen,
			NULL);

	if(len!=NULL)
		*len=strlen;

	if(Result==FALSE)
	{
		if(err!=NULL)
			*err=GetLastError();
		if(len!=NULL)
			*len=0;
		return false;	
	}
	else
	{
		for(i=0;i<REPORT_COUNT;i++)
			str[i]=ReadReportBuffer[i+1];

		return true;
	}
}
