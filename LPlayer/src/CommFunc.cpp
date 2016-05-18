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
	当VS IDE在调试模式时，在调试输出窗口打印调试信息，方便在windows上无断点调试。
	模仿TRACE，本处限定只会输出不超过255长度的字符串!!
	* @Example
	for (int it = 0; it < 512; it++)	// 测试一次最多可输出字符串长度
	{
	static string stra;
	stra += "1";
	test_trace("%d\n", stra.length() + 1);
	test_trace("%s\n", stra.c_str());	// i == 256时 '\n'无法被输出
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
		_vsnprintf(stmp, 1023, psFormat, arglist);	// 设定一次打印输出字符串长度不超过255
		va_end(arglist);

		OutputDebugStringA(stmp);
#endif
	}
}

