#pragma once

//WARNING STRING
#ifdef _DEBUG
#define ASF_WARNING(ID) MyLog::warn("%s at %s(%d)FuncName:<%s>",ASF_WARNING##ID,__FILE__,__LINE__,__FUNCTION__)
#else
#define ASF_WARNING(ID)
#endif
#define ASF_WARNING1 "��������˹��ڸ߼���MyLog::print"
#define ASF_WARNING2 "���ݰ���ʽ����ȫ��ȷ"
#define ASF_WARNING3 "ͼƬ���ظ�������160*160��"
#define ASF_WARNING4 "λͼ������Ϊ0x00"
#define ASF_WARNING5 "���ڹرշ���ֵ����ERROR_SUCCESS"
#define ASF_WARNING__ ""
//ERROR STRING
#define ASF_ERROR(ID) 	MyLog::error("%s at %s(%d)FuncName:<%s>",ASF_ERROR##ID,__FILE__,__LINE__,__FUNCTION__)
#define ASF_ERROR1 "��ͼ�����ļ�ʱʧ��"
#define ASF_ERROR2 "оƬ���ʹ���"
#define ASF_ERROR3 "û������convert"
#define ASF_ERROR4 "ת��ʧ��"
#define ASF_ERROR5 "���������"
#define ASF_ERROR6 "��ǰЭ�鲻֧�ָò���"
#define ASF_ERROR_ ""
//CONST STRING
#define SYNO "Syno"
#define GD32 "GD32F30"

#define NEW_INFO  MyLog::info("new   at %s(%d)<%s>",__FILE__,__LINE__,__FUNCTION__)
#define DEL_INFO  MyLog::info("del   at %s(%d)<%s>",__FILE__,__LINE__,__FUNCTION__)
#define NEWA_INFO MyLog::info("new[] at %s(%d)<%s>",__FILE__,__LINE__,__FUNCTION__)
#define DELA_INFO MyLog::info("del[] at %s(%d)<%s>",__FILE__,__LINE__,__FUNCTION__)