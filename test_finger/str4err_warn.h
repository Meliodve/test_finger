#pragma once
#include"stdafx.h"

/*
��������ǰ�������:
~:���Ź��̵Ľ���,������Ҫ�����仯
!:���Ź��̵Ľ���,��̫���ܷ����仯
�� û����ŵľ���ʹ���(ģ��)
���Ը���һ���µ�,Ȼ���ٸ���һ��
*/

#ifdef ASF_WARNING
#error macro is repeated!
#else
#ifndef NDEBUG
#define ASF_WARNING(ID) \
	log(LOGW,"%s at %s(%d)FuncName:<%s>",ASF_WARNING##ID,__FILE__,__LINE__,__FUNCTION__)
#else
#define ASF_WARNING(ID)
#endif
#endif

//WARNING STRING
#ifdef ASF_WARNING1
#error macro is repeated!
#else
#define ASF_WARNING1 \
"~��������˹��ڸ߼���log"
#endif

#ifdef ASF_WARNING2
#error macro is repeated!
#else
#define ASF_WARNING2 \
"~���ݰ���ʽ����ȫ��ȷ"
#endif

#ifdef ASF_WARNING3
#error macro is repeated!
#else
#define ASF_WARNING3 \
"~ͼƬ���ظ�������160*160��"
#endif

#ifdef ASF_WARNING4
#error macro is repeated!
#else
#define ASF_WARNING4 \
"!λͼ������Ϊ0x00"
#endif

#ifdef ASF_WARNING5
#error macro is repeated!
#else
#define ASF_WARNING5 \
"!���ڹرշ���ֵ����ERROR_SUCCESS"
#endif

#ifdef ASF_WARNING__
#error macro is repeated!
#else
#define ASF_WARNING__ \
""
#endif

#ifdef ASF_ERROR
#error macro is repeated!
#else
#define ASF_ERROR(ID) \
	log(LOGE,"%s at %s(%d)FuncName:<%s>",ASF_ERROR##ID,__FILE__,__LINE__,__FUNCTION__)
#endif

#ifdef ASF_ERROR1
#error macro is repeated!
#else
#define ASF_ERROR1 \
"!��ͼ�����ļ�ʱʧ��"
#endif

#ifdef ASF_ERROR2
#error macro is repeated!
#else
#define ASF_ERROR2 \
"!оƬ���ʹ���"
#endif

#ifdef ASF_ERROR__
#error macro is repeated!
#else
#define ASF_ERROR__ \
""
#endif