#include "stdafx.h"

// ��ͼƬ�ļ��е���¼�
void MainDialog::OnBnClickedBtnOpenImage(){
    if(access("collectedImage",0)){
        MyLog::user("ͼƬ�ļ��в�����,���Ȳ�һ��ͼƬ");
    } else{
        ShellExecuteA(NULL,"explore","collectedImage",NULL,NULL,SW_NORMAL);
    }
}

// �򿪱����ļ��е���¼�
void MainDialog::OnBnClickedBtnOpenBackgroundImage(){
    if(access("collectedBGI",0)){
        MyLog::user("�����ļ��в�����,���Ȳ�һ�ű���");
    } else{
        ShellExecuteA(NULL,"explore","collectedBGI",NULL,NULL,SW_NORMAL);
    }
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
        MainDialogCtrlValidity::Working();
        // ����<��ȡԭʼͼ��>����
        comm.request(SII(GetRawImage));
        setProgress(30);
        MyLog::user("�����ָ");
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
