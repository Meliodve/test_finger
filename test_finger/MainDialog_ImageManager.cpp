#include "stdafx.h"

void MainDialog::OnBnClickedBtnopenimage(){
    if(access("collectedImage",0)){
        MyLog::user("ͼƬ�ļ��в�����,���Ȳ�һ��ͼƬ");
    } else{
        ShellExecuteA(NULL,"explore","collectedImage",NULL,NULL,SW_NORMAL);
    }
}

void MainDialog::OnBnClickedBtnopenbackgroundimage(){
    if(access("collectedBGI",0)){
        MyLog::user("�����ļ��в�����,���Ȳ�һ�ű���");
    } else{
        ShellExecuteA(NULL,"explore","collectedBGI",NULL,NULL,SW_NORMAL);
    }
}

//ԭʼͼ��ĵ���¼�
void MainDialog::OnBnClickedBtnrawimage(){
    if(getText(cmbProtocolType)==SYNO){
        MyLog::user("��ʼ��ȡͼ��");
        Flow.clear();
        Flow.push_back(FlowFunction(0)(int& result){
            MainDialogCtrlValidity::Working();
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        });
        Flow.push_back(FlowFunction(1)(int& result){
            if(result==0x00){
                MainDialogCtrlValidity::Working();
                comm.request(SII(UpImage));
                progress->SetPos(100*++FlowID/Flow.size());
                return false;
            } else{
                FlowID--;
                return true;
            }
        });
        Flow.push_back(FlowFunction(2)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            Flow.clear();
            MyLog::user("��ȡͼ�����");
            MainDialogCtrlValidity::Work();
            return false;
        });
        ExecStart();
        return;
    }
    MainDialogCtrlValidity::Working();
    comm.request(SII(GetRawImage));
    progress->SetPos(30);
    MyLog::user("�����ָ");
}

void MainDialog::OnBnClickedBtnbackgroundimage(){
    if(getText(cmbProtocolType)==SYNO){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    MainDialogCtrlValidity::Working();
    progress->SetPos(30);
    MyLog::debug("��ʼ�ɼ�����");
    comm.request(SII(GetTestImage));
    progress->SetPos(60);
}

void MainDialog::OnBnClickedBtncontinuebackgroundimage(){
    if(getText(cmbProtocolType)==SYNO){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueBGImg)=="������ȡ����"){
        MyLog::user("��ʼ������ȡ����");
        MainDialogCtrlValidity::Working(MainDialogCtrlValidity::vec{btnContinueBGImg});
        setText(btnContinueBGImg,"ֹͣ��ȡ����");
        SendMessage(WM_GET_CON_BKI,WM_GET_CON_BKI,0);
    } else{
        MyLog::user("ֹͣ������ȡ����");
        MainDialogCtrlValidity::Work();
        setText(btnContinueBGImg,"������ȡ����");
        SendMessage(WM_STP_GET_BKI,WM_STP_GET_BKI,0);
    }
}

//������ȡͼ��ĵ���¼�
void MainDialog::OnBnClickedBtncontinueimage(){
    if(getText(cmbProtocolType)==SYNO){
        MyLog::user("��ʼ������ȡͼ��");
        Flow.clear();
        Flow.push_back(FlowFunction(0)(int& result){
            MainDialogCtrlValidity::Working();
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        });
        Flow.push_back(FlowFunction(1)(int& result){
            if(result==0x00){
                MainDialogCtrlValidity::Working();
                comm.request(SII(UpImage));
                progress->SetPos(100*++FlowID/Flow.size());
                return false;
            } else{
                FlowID--;
                return true;
            }
        });
        Flow.push_back(FlowFunction(2)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            return true;
        });
        Flow.push_back(FlowFunction(3)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            Flow.clear();
            MyLog::user("ֹͣ������ȡͼ��");
            MainDialogCtrlValidity::Work();
            return false;
        });
        ExecStart();
        return;
    }
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueImage)=="������ȡͼ��"){
        MyLog::user("��ʼ������ȡͼ��");
        MainDialogCtrlValidity::Working(MainDialogCtrlValidity::vec{btnContinueImage});
        setText(btnContinueImage,"ֹͣ��ȡͼ��");
        SendMessage(WM_GET_CON_IMAGE,WM_GET_CON_IMAGE,0);
    } else{
        MyLog::user("ֹͣ������ȡͼ��");
        MainDialogCtrlValidity::Work();
        setText(btnContinueImage,"������ȡͼ��");
        SendMessage(WM_STP_GET_IMAGE,WM_STP_GET_IMAGE,0);
    }
}
