// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MOUSEHOOKLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MOUSEHOOKLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MOUSEHOOKLL_EXPORTS
#define MOUSEHOOKLL_API __declspec(dllexport)
#else
#define MOUSEHOOKLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class MOUSEHOOKLL_API CMouseHookLL {
public:
	CMouseHookLL(void);
	// TODO: add your methods here.
};

extern MOUSEHOOKLL_API int nMouseHookLL;

MOUSEHOOKLL_API int fnMouseHookLL(void);
