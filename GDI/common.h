#pragma once
#ifdef UNICODE
typedef std::wstring TSTRING;
#else
typedef std::string TSTRING;
#endif
#define null 0
#define NULL 0