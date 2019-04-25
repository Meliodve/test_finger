//#pragma once
#include"stdafx.h"
//#include<vector>
//#include<map>
//#define foreach(TYPE,IT,CONTAINER) \
//	for(TYPE::iterator IT=CONTAINER.begin();IT!=CONTAINER.end();IT++)
////Ӧ���˹۲���ģʽ
//
////�۲��߱�����еĽӿ�:���ƿؼ������ԵĽӿ�
//interface IUpdateCtrl{
//public:
//	void Update(action a);
//};
//
////�۲��߷ֳɲ�ͬ��ɫ
//template <typename T>
//class UpdateRole : public IUpdateCtrl
//{
//public:
//	void Update(action a){
//		if(m.count(a)){
//			bool b=m[a];
//			foreach(Ctrls,it,v){
//				(*it)->EnableWindow(b);
//			}
//			foreach(Ctrls,it,rev){
//				(*it)->EnableWindow(!b);
//			}
//		}
//	}
//	void Register(CWnd* ctrl,bool rev=false){
//		if(rev){
//			revVector.push_back(ctrl);
//		}else{
//			Vector.push_back(ctrl);
//		}
//	}
//protected:
//	std::map<action,bool> m;
//	typedef std::vector<CWnd*> Ctrls;
//	Ctrls Vector,revVector;
//public:
//	static T* GetInstance(){
//		if (s_instance.get()==NULL){
//			static HANDLE mutex=CreateMutex(NULL,FALSE,NULL);
//			WaitForSingleObject(mutex,INFINITE);
//			if (s_instance.get()==NULL){
//				s_instance.reset(new T());
//			}
//			ReleaseMutex(mutex);
//		}
//		return s_instance;
//	}
//protected:
//	UpdateRole(){}
//	~UpdateRole(){}
//	static std::auto_ptr<T> s_instance;
//private:
//	UpdateRole(const UpdateRole&);
//	UpdateRole& operator =(const UpdateRole&);
//};
//template <typename T>std::auto_ptr<T> UpdateRole<T>::s_instance;
//
//#define ObserverDefineBegin(name)		\
//class name : public UpdateRole<name>{	\
//private:								\
//	~name(){}							\
//	friend UpdateRole<name>;			\
//	friend std::auto_ptr<name>;			\
//	name(const name&);					\
//	name& operator =(const name&);		\
//	name()
//
//ObserverDefineBegin(InitialObserver){
//	//2.ÿһ���ɫ����Ժ���action������Ӧ
//	m[actInit]=true;
//	CWnd* Array[]={cmbBaud,cmbWay,0};
//	CWnd* revArray[]={editAddress,editPassword,editAddressSet,editPasswordSet,
//		editLightTime,editSensitivity,cmbBaudSet,cmbChipType,btnRawImage,btnTestImage,
//		btnContinueImage,btnContinueBackGroundImage,btnSetCmos,btnSetBaud,btnSetPassword,
//		btnSetAddress,btnReadReg,btnWriteReg,chkTimeoutContinue,0};
//	for(CWnd**i=Array;*i;i++){
//		Register(*i);
//	}
//	for(CWnd**i=revArray;*i;i++){
//		Register(*i,true);
//	}
//}};
//
//ObserverDefineBegin(ConnectObserver){
//	//2.ÿһ���ɫ����Ժ���action������Ӧ
//}};
//	
//#undef ObserverDefineBegin(name)
//
////���۲�����
//class UpdateBroadcast{
//public:
//	//�Թ۲��߹㲥����
//	void Update(action a){
//		foreach(IUpdater,it,v){
//			(*it)->Update(a);
//		}
//	}
//	static UpdateBroadcast* getIns(){
//		if(!instance){
//			instance=new UpdateBroadcast();
//		}
//		return instance;
//	}
//private:
//	typedef std::vector<IUpdateCtrl*> IUpdater;
//	IUpdater v;
//	static UpdateBroadcast* instance;
//	UpdateBroadcast(){
//		//1.�㲥�����ע��
//		Register(InitialObserver::GetInstance());
//		Register(ConnectObserver::GetInstance());
//	}
//	UpdateBroadcast(const UpdateBroadcast&){}
//	UpdateBroadcast& operator=(const UpdateBroadcast&){}
//	void Register(IUpdateCtrl* iUpdateCtrl){
//		v.push_back(iUpdateCtrl);
//	}
//};
