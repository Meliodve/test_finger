#include"stdafx.h"

// ��ȡ�������ظ�����,д�ɺ�
#define Merge(Dest,Src) Dest.insert(Dest.end(),Src.begin(),Src.end())
#define MergePtr(Dest,Src) Dest.insert(Dest.end(),Src->begin(),Src->end())

// �ض������ȡ��ǰ׺,д�����
typedef MainDialogCtrlValidity::vec vec;

// �������͵Ŀؼ�����
vec InitVec;
vec SynoVec;
vec WorkingVec;
vec WorkedVec;
vec GD32F30Vec;
vec Empty;

// ����Э������,����׼����������
vec* getWorkedVec(){
    if(getProtocol()==SYNO){
        return &SynoVec;
    } else if(getProtocol()==GD32){
        return &GD32F30Vec;
    } else{
        return &Empty;
    }
}

// ��ʼ���ؼ�
void MainDialogCtrlValidity::InitCtrl(){
    InitVec=vec{cmbBaud,cmbWay,btnConnect,editPassword};
    // Э���Ӧ��ť����������������,�����Vec������Ƕ�ӦЭ��Ϳ��Ե�
    SynoVec=vec{editFingerId,cmbProtocolType,btnConnect,btnAdvDbg,
        btnRawImage,btnContinueImage,btnEnroll,btnMatch,btnTest,
        btnViewEnrollIds,btnDeleteTemplate};
    GD32F30Vec=vec{cmbProtocolType,btnConnect,btnAdvDbg,btnTest,
        btnRawImage,btnTestImage,btnContinueImage,btnContinueBGImg,
        btnReadReg,btnWriteReg,btnDeviceInfo};
    WorkedVec=vec{editFingerId,cmbProtocolType,btnConnect,btnAdvDbg,
        btnRawImage,btnTestImage,btnContinueImage,btnContinueBGImg,
        btnReadReg,btnWriteReg,btnEnroll,btnMatch,btnTest,
        btnDeviceInfo,btnViewEnrollIds,btnDeleteTemplate};
    WorkingVec=vec{btnCancel};
    Empty=vec{};
    vec Disable,Enable;
    Merge(Disable,WorkedVec);
    Merge(Disable,WorkingVec);
    Merge(Disable,InitVec);
    update(Disable,Enable);
}

// ��ʼ״̬
void MainDialogCtrlValidity::Init(vec except){
    vec Disable,Enable;
    vec* GetWorkedVec=getWorkedVec();
    Merge(Disable,WorkedVec);
    MergePtr(Disable,GetWorkedVec);
    Merge(Disable,WorkingVec);
    Merge(Enable,InitVec);
    Merge(Enable,except);
    update(Disable,Enable);
}

// ������״̬
void MainDialogCtrlValidity::Connecting(vec except){
    vec Disable,Enable;
    vec* GetWorkedVec=getWorkedVec();
    Merge(Disable,WorkedVec);
    MergePtr(Disable,GetWorkedVec);
    Merge(Disable,WorkingVec);
    Merge(Disable,InitVec);
    Merge(Enable,except);
    update(Disable,Enable);
}

// ������֮ǰ��״̬
void MainDialogCtrlValidity::BeforeConnect(vec except){
    Init(except);
}

// ����֮���״̬
void MainDialogCtrlValidity::AfterConnect(vec except){
    Work(except);
}

// ׼��̬
void MainDialogCtrlValidity::Work(vec except){
    vec Disable,Enable;
    vec* GetWorkedVec=getWorkedVec();
    Merge(Disable,InitVec);
    Merge(Disable,WorkingVec);
    Merge(Disable,WorkedVec);
    MergePtr(Enable,GetWorkedVec);
    Merge(Enable,except);
    update(Disable,Enable);
}

// ����̬
void MainDialogCtrlValidity::Working(vec except){
    vec Disable,Enable;
    vec* GetWorkedVec=getWorkedVec();
    Merge(Disable,InitVec);
    Merge(Disable,WorkedVec);
    MergePtr(Disable,GetWorkedVec);
    Merge(Enable,WorkingVec);
    Merge(Enable,except);
    update(Disable,Enable);
}

// ���¿ؼ�������
inline void MainDialogCtrlValidity::update(vec& Disable,vec& Enable){
    for(auto it=Disable.begin();it!=Disable.end();it++){
        disable(*it);
    }
    for(auto it=Enable.begin();it!=Enable.end();it++){
        enable(*it);
    }
}

// ���ÿؼ�
inline void MainDialogCtrlValidity::disable(CWnd * pWnd){
    pWnd->EnableWindow(FALSE);
}

// ���ÿؼ�
inline void MainDialogCtrlValidity::enable(CWnd * pWnd){
    pWnd->EnableWindow(TRUE);
}
