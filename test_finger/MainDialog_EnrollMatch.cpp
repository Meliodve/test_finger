#include "stdafx.h"

void MainDialog::OnBnClickedBtn(){
    setText(editFingerId,getText(GetFocus()));
}

void MainDialog::OnBnClickedBtnenroll(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    static uint8_t BufferID;
    BufferID=1;
    static const int EnrollCount=3;
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        MainDialogCtrlValidity::Working();
        comm.request(SII(GetEnrollImage));//��ȡͼ��
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){//ȡ��ͼ��
            MyLog::debug("ȡ��ָ��ͼ��(%d/%d)",BufferID,EnrollCount);
            comm.request(SII(UpImage));//�ϴ�ͼ��
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//ûȡ��ͼ��
            FlowID--;
            return true;
        }
    });
    Flow.push_back(FlowFunction(2)(int& result){
        if(result==0x00){//�ϴ�ͼ��ɹ�
            comm.request(SII(GenChar),&BufferID,1);//��������
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//�ϴ�ͼ��ʧ��
            MyLog::debug("�ϴ�ͼ��ʧ��");
            FlowID=11;
            MyLog::user("ע��ʧ��");
            return true;
        }
    });
    Flow.push_back(FlowFunction(3)(int& result){
        if(result==0x00){//���������ɹ�
            FlowID++;
            MyLog::debug("���������ɹ�(%d/%d)",BufferID,EnrollCount);

            uint8_t x[]={BufferID,0,0,0,0x87};
            comm.request(SII(Search),x,sizeof x);//����ָ��
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//��������ʧ��
            FlowID=0;
            return true;
        }
    });
    Flow.push_back(FlowFunction(4)(int& result){
        if(result==0x09){//û�ѵ�ָ��
            MyLog::debug("�ȴ���ָ�ƿ�");
            comm.request(SII(GetRawImage));//�ȴ�����ָ�ƿ�
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//�ѵ�ָ��
            MyLog::debug("����ָ��");
            FlowID=11;
            MyLog::user("ע��ʧ��");
            return true;
        }
    });
    Flow.push_back(FlowFunction(5)(int& result){
        if(result==0x02){//ûָ��
            FlowID++;
        } else{//��ָ��
            result=0x09;
            FlowID--;
        }
        return true;
    });
    Flow.push_back(FlowFunction(6)(int& result){
        if(BufferID>=EnrollCount){//�ﵽ¼�����
            FlowID++;
        } else{//û�ﵽ¼�����
            BufferID++;
            FlowID=0;
        }
        return true;
    });
    Flow.push_back(FlowFunction(7)(int& result){
        comm.request(SII(RegModel));//�ϲ�����
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(8)(int& result){
        if(result==0x00){//�ϲ������ɹ�
            FlowID++;
            MyLog::debug("�ϲ������ɹ�");
        } else{//�ϲ�ʧ��
            FlowID=11;
            MyLog::user("ע��ʧ��");
        }
        return true;
    });
    Flow.push_back(FlowFunction(9)(int& result){
        uint8_t data[]={1,0,FingerID};
        comm.request(SII(StoreChar),data,sizeof data);//�洢ģ��
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(10)(int& result){
        if(result==0x00){//�洢ģ��ɹ�
            FlowID++;
            MyLog::debug("�洢ģ��ɹ�");
        } else{//�洢ʧ��
            FlowID=11;
            MyLog::user("ע��ʧ��");
        }
        return true;
    });
    Flow.push_back(FlowFunction(11)(int& result){//ע�����
        progress->SetPos(100*++FlowID/Flow.size());
        FlowID=0;
        BufferID=1;
        MyLog::user("ע�����");
        Flow.clear();
        MainDialogCtrlValidity::Work();
        return false;
    });
    ExecStart();
}

void MainDialog::OnBnClickedBtnmatch(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        MainDialogCtrlValidity::Working();
        uint8_t data[]={02,00,FingerID};
        comm.request(SII(LoadChar),data,sizeof data);
        FlowID++;
        MyLog::user("����ָ��ģ����...");
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            FlowID=5;
            return true;
        }
    });
    Flow.push_back(FlowFunction(2)(int& result){
        if(result==0x00){
            MyLog::user("ȡָ��ͼ�ɹ�");
            uint8_t data[]={02};
            comm.request(SII(GenChar),data,sizeof data);
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            result=0x00;
            FlowID--;
            return true;
        }
    });
    Flow.push_back(FlowFunction(3)(int& result){
        if(result==0x00){
            MyLog::user("ָ�����������ɹ�");
            comm.request(SII(Match));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            MyLog::user("ָ����������ʧ��");
            result=0x00;
            FlowID--;//��������
            FlowID--;//��������
            return true;
        }
    });
    Flow.push_back(FlowFunction(4)(int& result){
        if(result==0x00){
            MyLog::user("ָ��ƥ��ɹ�");
            FlowID++;
            return true;
        } else{
            MyLog::user("ָ�Ʋ�ƥ��");
            FlowID++;
            return true;
        }
    });
    Flow.push_back(FlowFunction(5)(int& result){
        progress->SetPos(100*++FlowID/Flow.size());
        MainDialogCtrlValidity::Work();
        MyLog::user("�ȶԽ���");
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}

void MainDialog::OnBnClickedBtnviewenrollids(){
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        MainDialogCtrlValidity::Working();
        uint8_t data[]={0};
        comm.request(SII(ReadIndexTable),data,sizeof data);
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        progress->SetPos(100*++FlowID/Flow.size());
        MainDialogCtrlValidity::Work();
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}

void MainDialog::OnBnClickedBtndeletetemplate(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        MainDialogCtrlValidity::Working();
        uint8_t data[]={0,FingerID,0,1};
        comm.request(SII(DeleteChar),data,sizeof data);
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){
            MyLog::user("ɾ��ָ��%d�ɹ�",FingerID);
        }
        progress->SetPos(100*++FlowID/Flow.size());
        MainDialogCtrlValidity::Work();
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}
