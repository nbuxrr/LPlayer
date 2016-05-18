#include "CommFunc.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef WIN32
#include <Windows.h>
#endif

namespace CommFunc
{
	string strExecFileDir;
	void SetExecDir(const string &strDir) { strExecFileDir = strDir; };
	const char* GetExecDir() { return strExecFileDir.c_str(); };

	/**
	* @Parameters
	* @Return Values
	* @Remarks
	��VS IDE�ڵ���ģʽʱ���ڵ���������ڴ�ӡ������Ϣ��������windows���޶ϵ���ԡ�
	ģ��TRACE�������޶�ֻ�����������255���ȵ��ַ���!!
	* @Example
	for (int it = 0; it < 512; it++)	// ����һ����������ַ�������
	{
	static string stra;
	stra += "1";
	test_trace("%d\n", stra.length() + 1);
	test_trace("%s\n", stra.c_str());	// i == 256ʱ '\n'�޷������
	}
	* @Author xurr 2014-12-21 0:02:22
	*/
	void test_trace(const char *psFormat, ...)
	{
		if (psFormat == nullptr)
		{
			return;
		}

#ifdef WIN32
		va_list arglist;
		va_start(arglist, psFormat);
		char stmp[1024] = {0};
		_vsnprintf(stmp, 1023, psFormat, arglist);	// �趨һ�δ�ӡ����ַ������Ȳ�����255
		va_end(arglist);

		OutputDebugStringA(stmp);
#endif
	}
}

