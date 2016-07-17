#ifndef _COMMFUNC_H_
#define _COMMFUNC_H_

#include <string>
using namespace std;

namespace CommFunc
{
	void SetAppFileDir(const string &strDir);
	const string& GetAppFileDir();

	void test_trace(const char *psFormat, ...);				// ʵ������afx��TRACE�Ĺ���	2014-12-21 9:32:47 xurr
};

#define LINUX_TRACE 1	// Linux�³����Ƿ��ӡQTRACE׷����Ϣ

#ifndef QTRACE
#ifdef WIN32	// �������׷��	2014-12-21 9:41:51 xurr
#ifdef _DEBUG
#define QTRACE(format,...) CommFunc::test_trace(format, ##__VA_ARGS__)
#else
#define QTRACE(format,...)
#endif
#else
#if LINUX_TRACE
#define QTRACE(format,...) printf(format, ##__VA_ARGS__)
#else
#define QTRACE(format,...)
#endif
#endif
#endif

#endif // _COMMFUNC_H_
