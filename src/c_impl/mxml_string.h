#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_C_STRING_H__
#define __HDR_MYXML_C_STRING_H__

#include "../config.h"

typedef struct mxml_string_tag
{
	mxml_char_t * str;
	size_t len;
} mxml_string_t;

#define init_str( s ) do { (s)->str = NULL; (s)->len = 0; } while ( 0,0 )
#define alloc_str( s, n ) do { (s)->str = (mxml_char_t*)malloc( sizeof(mxml_char_t) * (n) ); (s)->len = (n - 1); } while(0,0)
#define free_str( s ) do { if ((s)->str) free( (s)->str ); (s)->len = 0; } while(0,0)
#define assign_str( dest, src ) \
	do { if ( (dest)->str && (dest)->len != (src)->len ) \
		free_str( (dest) ); \
	alloc_str( (dest), (src)->len + 1 );\
	xml_strcpy( (dest)->str, (src)->str ); } while ( 0,0 )

#define assign_cstr( dest, src ) \
	do { if ( (dest)->str && (dest)->len ) \
		free_str( (dest) ); \
	alloc_str( (dest), xml_strlen( (src) ) + 1 );\
	xml_strcpy( (dest)->str, (src) ); } while ( 0,0 )

#define assign_cstr_len( dest, src, src_len ) \
	do { if ( (dest)->str && (dest)->len != (src_len) ) \
		{ free_str( (dest) ); alloc_str( (dest), (src_len) + 1 ); }\
	else if ( !(dest)->str && !(dest)->len ) alloc_str( (dest), (src_len) + 1 ); \
	xml_strncpy( (dest)->str, (src), (src_len) ); \
	(dest)->str[(src_len)] = 0; } while ( 0,0 )

#define append_str( s, app, app_len ) \
	do { \
		mxml_string_t tmp; \
		init_str( &tmp ); \
		if ( (s) != NULL && (s)->len != 0 ) { \
			alloc_str( &tmp, (s)->len + app_len + 1 ); \
			xml_strcpy( tmp.str, (s)->str ); \
			xml_strcpy( &tmp.str[(s)->len], app ); \
			free_str( (s) ); } \
		else { alloc_str( &tmp, app_len + 1 ); xml_strcpy( tmp.str, app ); } \
		(s)->str = tmp.str; \
		(s)->len = tmp.len; \
	} while ( 0,0 )

#define eq_str( str1, str2 ) xml_strcmp( (str1)->str, (str2)->str )

void append_str_impl( mxml_string_t * s, const mxml_char_t * app, size_t app_len );

#endif /* __HDR_MYXML_C_STRING_H__ */
