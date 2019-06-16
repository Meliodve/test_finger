#include "stdafx.h"

// 1~8С��ť�ĵ���¼�
void MainDialog::OnBnClickedBtn(){
    // ����ָ�ƺŵ��ı�
    setText(editFingerId,getText(GetFocus()));
}

// ע�ᰴť�¼�
void MainDialog::OnBnClickedBtnEnroll(){
    if(getText(cmbProtocolType)==SYNO){
        // �пռ��
        if(getText(editFingerId)==""){
            MyLog::user("��Ų���Ϊ��");
            return;
        }
        // static ��ֹ���ͷ�
        static uint8_t BufferID=1;
        // ���ָ�ƺ�
        uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
        static const int EnrollCount=3;
        // ��������
        flow.clear();
        // ���� 0:����<��ȡע��ͼ��>����
        flow.add(0,
            [](int& result)->bool{
                MainDialogCtrlValidity::Working();
                comm.request(SII(GetEnrollImage));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            }
        );
        // ���� 1:���ȡ��ͼ��,����<�ϴ�ͼ��>����
        // ���� 1:���ûȡ��ͼ��,�ص����� 0
        flow.add(1,
            [](int& result)->bool{
                if(result==0x00){
                    // ȡ��ͼ��
                    MyLog::debug("ȡ��ָ��ͼ��(%d/%d)",BufferID,EnrollCount);
                    comm.request(SII(UpImage));//�ϴ�ͼ��
                    setProgress(100*flow.percent());
                    flow.next();
                    return false;
                } else{//ûȡ��ͼ��
                    flow.prev();
                    return true;
                }
            }
        );
        // ���� 2:����ϴ�ͼ��ɹ�,����<��������>����
        // ���� 2:����ϴ�ͼ��ʧ��,��ע��ʧ����
        flow.add(2,
            [](int& result)->bool{
                if(result==0x00){
                    // �ϴ�ͼ��ɹ�
                    comm.request(SII(GenChar),DataPacket(&BufferID,1));
                    setProgress(100*flow.percent());
                    flow.next();
                    return false;
                } else{
                    // �ϴ�ͼ��ʧ��
                    MyLog::debug("�ϴ�ͼ��ʧ��");
                    MyLog::user("ע��ʧ��");
                    flow.terminate();
                    return false;
                }
            }
        );
        // ���� 3:������������ɹ�,����<����ָ��>����
        // ���� 3:�����������ʧ��,��ͷ��ʼ��ָ��
        flow.add(3,
            [](int& result)->bool{
                if(result==0x00){
                    // ���������ɹ�
                    MyLog::debug("���������ɹ�(%d/%d)",BufferID,EnrollCount);

                    uint8_t x[]={BufferID,0,0,0,0x87};
                    comm.request(SII(Search),DataPacket(x,sizeof x));
                    setProgress(100*flow.percent());
                    flow.next();
                    return false;
                } else{
                    // ��������ʧ��
                    flow.jump(0);
                    return true;
                }
            }
        );
        // ���� 4:���û��������ָ��,����<���ָ��>����
        // ���� 4:�����������ָ��,�����Ѿ�ע�����,��ע��ʧ����
        flow.add(4,
            [](int& result)->bool{
                if(result==0x09||result==0x17){
                    // û�ѵ�ָ��
                    MyLog::debug("�ȴ���ָ�ƿ�");
                    comm.request(SII(GetRawImage));
                    setProgress(100*flow.percent());
                    flow.next();
                    return false;
                } else{
                    // �ѵ�ָ��
                    MyLog::user("��ָ��ע�����,ע��ʧ��");
                    flow.terminate();
                    return true;
                }
            }
        );
        // ���� 5:���û����ָ,ִ����һ������
        // ���� 5:�������ָ,����result=0x09�ķ�ʽִ����һ������
        //        ���ڵȴ���ָ�ƿ�
        flow.add(5,
            [](int& result)->bool{
                if(result==0x02){
                    // ûָ��
                    flow.next();
                } else{
                    // ��ָ��
                    result=0x09;
                    flow.prev();
                }
                return true;
            }
        );
        // ���� 6:����ﵽ¼�����,ִ����һ������
        // ���� 6:���û�ﵽ¼�����,¼�����+1,������0¼��ָ��
        flow.add(6,
            [](int& result)->bool{
                if(BufferID>=EnrollCount){
                    // �ﵽ¼�����
                    flow.next();
                } else{
                    // û�ﵽ¼�����
                    BufferID++;
                    flow.jump(0);
                }
                return true;
            }
        );
        // ���� 7:����<�ϲ�����>����
        flow.add(7,
            [](int& result)->bool{
                comm.request(SII(RegModel));//�ϲ�����
                setProgress(100*flow.percent());
                flow.next();
                return false;
            }
        );
        // ���� 8:����ϲ������ɹ�,����<�洢ģ��>����
        // ���� 8:����ϲ�����ʧ��,��ע��ʧ����
        flow.add(8,
            [FingerID](int& result)->bool{
                if(result==0x00){
                    // �ϲ������ɹ�
                    MyLog::debug("�ϲ������ɹ�");

                    uint8_t data[]={1,0,FingerID};
                    comm.request(SII(StoreChar),DataPacket(data,sizeof data));//�洢ģ��
                    setProgress(100*flow.percent());
                    flow.next();
                    return false;
                } else{
                    // �ϲ�ʧ��
                    MyLog::user("ע��ʧ��");
                    flow.terminate();
                }
                return true;
            }
        );
        // ���� 9:����洢ģ��ɹ�,�ͱ���һ��
        // ���� 9:����洢ģ��ʧ��,��ע��ʧ����
        flow.add(9,
            [](int& result)->bool{
                if(result==0x00){
                    // �洢ģ��ɹ�
                    flow.next();
                    MyLog::debug("�洢ģ��ɹ�");
                } else{
                    // �洢ʧ��
                    MyLog::user("ע��ʧ��");
                    flow.terminate();
                }
                return true;
            }
        );
        // ����10:ע�����,�ƺ���
        flow.add(10,
            [](int& result)->bool{
                BufferID=1;
                setProgress(100*flow.percent());
                MyLog::user("ע�����");
                flow.clear();
                MainDialogCtrlValidity::Work();
                return false;
            }
        );
        // ��ʼִ������
        flow.start();
    }
}

// �ȶ԰�ť����¼�
void MainDialog::OnBnClickedBtnMatch(){
    if(getText(cmbProtocolType)==SYNO){
        // �пռ��
        if(getText(editFingerId)==""){
            MyLog::user("��Ų���Ϊ��");
            return;
        }
        // ���ָ�ƺ�
        uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
        // ��������
        flow.clear();
        // ���� 0:����<��������>����
        flow.add(0,[FingerID](int& result)->bool{
            MainDialogCtrlValidity::Working();
            uint8_t data[]={02,00,FingerID};
            comm.request(SII(LoadChar),DataPacket(data,sizeof data));
            flow.next();
            MyLog::user("����ָ��ģ����...");
            return false;
            });
        // ���� 1:������������ɹ�,����<��ȡͼ��>����
        // ���� 1:�����������ʧ��,�ͱȶ�ʧ����
        flow.add(1,[](int& result)->bool{
            if(result==0x00){
                comm.request(SII(GetRawImage));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            } else{
                flow.terminate();
                return true;
            }
            });
        // ���� 2:���ȡͼ�ɹ�,����<��������>����
        // ���� 2:���ȡͼʧ��,������һ������
        flow.add(2,[](int& result)->bool{
            if(result==0x00){
                MyLog::user("ȡָ��ͼ�ɹ�");
                uint8_t data[]={02};
                comm.request(SII(GenChar),DataPacket(data,sizeof data));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            } else{
                result=0x00;
                flow.prev();
                return true;
            }
            });
        // ���� 3:������������ɹ�,����<ƥ��>����
        // ���� 3:�����������ʧ��,�ص����� 1,����ȡͼ
        flow.add(3,[](int& result)->bool{
            if(result==0x00){
                MyLog::user("ָ�����������ɹ�");
                comm.request(SII(Match));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            } else{
                MyLog::user("ָ����������ʧ��");
                result=0x00;
                flow.jump(1);
                return true;
            }
            });
        // ���� 4:���ƥ����
        flow.add(4,[](int& result)->bool{
            if(result==0x00){
                MyLog::user("ָ��ƥ��ɹ�");
            } else{
                MyLog::user("ָ�Ʋ�ƥ��");
            }
            flow.next();
            return true;
            });
        // ���� 5:�ȶԽ���,�ƺ���
        flow.add(5,[](int& result)->bool{
            setProgress(100*flow.percent());
            MyLog::user("�ȶԽ���");
            flow.clear();
            MainDialogCtrlValidity::Work();
            return false;
            });
        // ��ʼִ������
        flow.start();
    }
}

// �鿴����ע��ָ�Ƶ�ID�İ�ť����¼�
void MainDialog::OnBnClickedBtnViewEnrollIDs(){
    if(getText(cmbProtocolType)==SYNO){
        // ��������
        flow.clear();
        // ���� 0:����<��ȡ������>����
        flow.add(0,[](int& result)->bool{
            MainDialogCtrlValidity::Working();
            uint8_t data[]={0};
            comm.request(SII(ReadIndexTable),DataPacket(data,sizeof data));
            setProgress(100*flow.percent());
            flow.next();
            return false;
            });
        // ���� 1:��ȡ���������,�ƺ���
        flow.add(1,[](int& result)->bool{
            setProgress(100*flow.percent());
            flow.clear();
            MainDialogCtrlValidity::Work();
            return false;
            });
        // ��ʼִ������
        flow.start();
    }
}

// ɾ��ģ��İ�ť����¼�
void MainDialog::OnBnClickedBtnDeleteTemplate(){
    if(getText(cmbProtocolType)==SYNO){
        // �пռ��
        if(getText(editFingerId)==""){
            MyLog::user("��Ų���Ϊ��");
            return;
        }
        // ���ָ�ƺ�
        uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
        // ��������
        flow.clear();
        // ���� 0:����<ɾ��ģ��>����
        flow.add(0,[FingerID](int& result)->bool{
            MainDialogCtrlValidity::Working();
            uint8_t data[]={0,FingerID,0,1};
            comm.request(SII(DeleteChar),DataPacket(data,sizeof data));
            setProgress(100*flow.percent());
            flow.next();
            return false;
            });
        // ���� 1:ɾ��ģ�����,�ƺ���
        flow.add(1,[FingerID](int& result)->bool{
            if(result==0x00){
                MyLog::user("ɾ��ָ��%d�ɹ�",FingerID);
            }
            // ���ʧ����,�ڼ��������������ԭ��
            setProgress(100*flow.percent());
            flow.clear();
            MainDialogCtrlValidity::Work();
            return false;
            });
        // ��ʼִ������
        flow.start();
    }
}
