#include "CommFunc.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef WIN32
#include <Windows.h>
#endif

namespace CommFunc
{
	string strExecFileDir;
	void SetAppFileDir(const string &strDir) { strExecFileDir = strDir; };
	const string& GetAppFileDir() { return strExecFileDir; };

	void test_trace(const char *psFormat, ...)
	{
		if (psFormat == nullptr) {
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

