/**
* \file config.h
* Основные макро-определения проекта
*/

#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_CONFIG_H__
#define __HDR_MYXML_CONFIG_H__

#include <stdlib.h>

#if !defined XML_UNICODE
#	include <string.h>
#	define XML_CHAR_TYPE char
#	define XML_T(x) x
#	define xml_strcpy strcpy
#	define xml_strncpy strncpy
#	define xml_strcmp strcmp
#	define xml_strcmp_n strncmp
#	define xml_strcmp_i _stricmp
#	define xml_strcmp_i_n _strnicmp
#	define xml_strchr strchr
#	define xml_strtol strtol
#	define xml_strlen strlen
#	define xml_strtok strtok
#	define xml_file_open fopen
#	define xml_file_gets fgets
#	define xml_fprintf	 fprintf
#else
#	include <wchar.h>
#	define XML_CHAR_TYPE wchar_t
#	define XML_T(x) L ## x
#	define xml_strcpy wcscpy
#	define xml_strncpy wcsncpy
#	define xml_strcmp wcscmp
#	define xml_strcmp_n wcsncmp
#	define xml_strcmp_i _wcsicmp
#	define xml_strcmp_i_n _wcsnicmp
#	define xml_strchr wcschr
#	define xml_strtol wcstol
#	define xml_strlen wcslen
#	define xml_strtok wcstok
#	define xml_file_open _wfopen
#	define xml_file_gets fgetws
#	define xml_fprintf	 fwprintf
#endif

/**
* Основной символьный тип проекта.
*/
typedef XML_CHAR_TYPE mxml_char_t;

#endif /* __HDR_MYXML_CONFIG_H__ */
