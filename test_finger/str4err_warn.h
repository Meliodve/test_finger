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
#define ASF_WARNING(ID) \
	log(LOGW,"%s at %s(%d)FuncName:<%s>",ASF_WARNING##ID,__FILE__,__LINE__,__FUNCTION__)
#endif

//WARNING STRING
#ifdef ASF_WARNING01
#error macro is repeated!
#else
#define ASF_WARNING01 \
"~��������˹��ڸ߼���log"
#endif

#ifdef ASF_WARNING02
#error macro is repeated!
#else
#define ASF_WARNING02 \
"~���ݰ���ʽ����ȫ��ȷ"
#endif

#ifdef ASF_WARNING03
#error macro is repeated!
#else
#define ASF_WARNING03 \
"~ͼƬ���ظ�������160*160��"
#endif

#ifdef ASF_WARNING04
#error macro is repeated!
#else
#define ASF_WARNING04 \
"!λͼ������Ϊ0x00"
#endif

#ifdef ASF_WARNING05
#error macro is repeated!
#else
#define ASF_WARNING05 \
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

#ifdef ASF_ERROR01
#error macro is repeated!
#else
#define ASF_ERROR01 \
"!��ͼ�����ļ�ʱʧ��"
#endif

#ifdef ASF_ERROR__
#error macro is repeated!
#else
#define ASF_ERROR__ \
""
#endif