#include "stdafx.h"

// ��ͼƬ�ļ��е���¼�
void MainDialog::OnBnClickedBtnOpenImage(){
    ShellExecuteA(NULL,"explore",MyFile::IMAGE_DIR,NULL,NULL,SW_NORMAL);
}

// �򿪱����ļ��е���¼�
void MainDialog::OnBnClickedBtnOpenBackgroundImage(){
    ShellExecuteA(NULL,"explore",MyFile::BACKGROUND_DIR,NULL,NULL,SW_NORMAL);
}

//ԭʼͼ��ĵ���¼�
void MainDialog::OnBnClickedBtnRawImage(){
    if(getProtocol()==SYNO){
        MyLog::user("��ʼ��ȡͼ��");
        // ��������
        flow.clear();
        // ���� 0:����<���ͼ��>����
        flow.add(0,[](int& result){
            MainDialogCtrlValidity::Working();
            comm.request(SII(GetRawImage));
            setProgress(100*flow.percent());
            flow.next();
            return false;
            });
        // ���� 1:���ȡ��ͼ,����<�ϴ�ͼ��>����
        // ���� 1:���ûȡ��ͼ,�ص���һ������
        flow.add(1,[](int& result){
            if(result==0x00){
                MainDialogCtrlValidity::Working();
                comm.request(SII(UpImage));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            } else{
                flow.prev();
                return true;
            }
            });
        // ���� 2:��ȡͼ�����,�ƺ���
        flow.add(2,[](int& result){
            setProgress(100*flow.percent());
            MyLog::user("��ȡͼ�����");
            flow.clear();
            MainDialogCtrlValidity::Work();
            return false;
            });
        // ��ʼִ������
        flow.start();
    }
    if(getProtocol()==GD32){
//#define NoHardWare
#ifdef NoHardWare
        test.testBegin(test.Comm,GD32);
        comm.disconnect();
        comm.connect(0,0);
        comm.request(SII(GetRawImage));
        while(!test.commTest.Comm_sendSize);
        uint8_t receiveData[]={0xEF,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,0x03,0x02,0x10,0x02,0x00,0x00};
        int k=0;

        uint8_t img[5][5];
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                img[i][j]=(i*5+j)*255/24;
            }
        }
        uint8_t* bigImg=new uint8_t[160*160];
        uint8_t* bigImg2=new uint8_t[160*160];
        imgSizeX2(5,5,(uint8_t*)img,bigImg);
        imgSizeX2(10,10,bigImg,bigImg2);
        imgSizeX2(20,20,bigImg2,bigImg);
        imgSizeX2(40,40,bigImg,bigImg2);
        imgSizeX2(80,80,bigImg2,bigImg);

        for(int i=0;i<25600;){
            uint16_t* len=(uint16_t*)(receiveData+15);
            if(25600-i<=528){
                *len=25600-i;
            }
            memcpy(test.commTest.Comm_receive+k,receiveData,sizeof receiveData);
            k+=sizeof receiveData;
            for(int j=0;j<528&&i<25600;j++){
                test.commTest.Comm_receive[k++]=bigImg[i++];
            }
            // TODO-When CRCVal be used
            test.commTest.Comm_receive[k++]=0;
            test.commTest.Comm_receive[k++]=0;
        }
        bool process=false;
        flow.clear();
        flow.add(0,
            [&](int& result)->bool{
                process=true;
                flow.clear();
                return false;
            }
        );
        flow.jump(0);
        test.commTest.Comm_receiveSize=k;

        test.testEnd();
#else
        MainDialogCtrlValidity::Working();
        // ����<��ȡԭʼͼ��>����
        comm.request(SII(GetRawImage));
        setProgress(30);
        MyLog::user("�����ָ");
#endif
    }
}

void MainDialog::OnBnClickedBtnBackgroundImage(){
    if(getProtocol()==GD32){
        MainDialogCtrlValidity::Working();
        setProgress(30);
        MyLog::debug("��ʼ�ɼ�����");
        comm.request(SII(GetTestImage));
        setProgress(60);
    }
}

void MainDialog::OnBnClickedBtnContinueBackgroundImage(){
    if(getProtocol()==GD32){
        // ���ݰ�ť�ϵ������жϵ�ǰ����״̬
        if(getText(btnContinueBGImg)=="������ȡ����"){
            MyLog::user("��ʼ������ȡ����");
            MainDialogCtrlValidity::Working(MainDialogCtrlValidity::vec{btnContinueBGImg});
            setText(btnContinueBGImg,"ֹͣ��ȡ����");
            sendMainDialogMessage(WM_GET_CON_BKI);
        } else{
            MyLog::user("ֹͣ������ȡ����");
            MainDialogCtrlValidity::Work();
            setText(btnContinueBGImg,"������ȡ����");
            sendMainDialogMessage(WM_STP_GET_BKI);
        }
    }
}

//������ȡͼ��ĵ���¼�
void MainDialog::OnBnClickedBtnContinueImage(){
    if(getProtocol()==SYNO){
        MyLog::user("��ʼ������ȡͼ��");
        // ��������
        flow.clear();
        // ���� 0:����<���ͼ��>����
        flow.add(0,[](int& result){
            MainDialogCtrlValidity::Working();
            comm.request(SII(GetRawImage));
            setProgress(100*flow.percent());
            flow.next();
            return false;
            });
        // ���� 1:���ȡͼ�ɹ�,����<�ϴ�ͼ��>����
        // ���� 1:���ȡͼʧ��,�ص���һ������
        flow.add(1,[](int& result){
            if(result==0x00){
                MainDialogCtrlValidity::Working();
                comm.request(SII(UpImage));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            } else{
                flow.prev();
                return true;
            }
            });
        // ���� 2:�ص����� 0
        flow.add(2,[](int& result){
            setProgress(100*flow.percent());
            flow.jump(0);
            return true;
            });
        // ���� 3:����ȡͼ����,�ƺ���
        flow.add(3,[](int& result){
            setProgress(100*flow.percent());
            MyLog::user("ֹͣ������ȡͼ��");
            flow.clear();
            MainDialogCtrlValidity::Work();
            return false;
            });
        flow.start();
    }
    if(getProtocol()==GD32){
        //���ݰ�ť�ϵ������жϵ�ǰ����״̬
        if(getText(btnContinueImage)=="������ȡͼ��"){
            MyLog::user("��ʼ������ȡͼ��");
            MainDialogCtrlValidity::Working(MainDialogCtrlValidity::vec{btnContinueImage});
            setText(btnContinueImage,"ֹͣ��ȡͼ��");
            sendMainDialogMessage(WM_GET_CON_IMAGE);
        } else{
            MyLog::user("ֹͣ������ȡͼ��");
            MainDialogCtrlValidity::Work();
            setText(btnContinueImage,"������ȡͼ��");
            sendMainDialogMessage(WM_STP_GET_IMAGE);
        }
    }
}
