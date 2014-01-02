#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_GRAMMAR_C_H__
#define __HDR_MYXML_GRAMMAR_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../config.h"
#include "detail.h"

extern const mxml_char_t underscore;
extern const mxml_char_t less;
extern const mxml_char_t greater;
extern const mxml_char_t ampersand;
extern const mxml_char_t dies;
extern const mxml_char_t grX;
extern const mxml_char_t smX;
extern const mxml_char_t colon;
extern const mxml_char_t equal;
extern const mxml_char_t single_quote;
extern const mxml_char_t dbl_quote;
extern const mxml_char_t slash;
extern const mxml_char_t minus;

typedef struct grammar_tag_tag
{
	const mxml_char_t *value;
	size_t length;
} grammar_tag;

extern const grammar_tag header_tag;
extern const grammar_tag comment_tag;
extern const grammar_tag comment_end_tag;
extern const grammar_tag dtd_tag;

#define is_comment( str ) ( xml_strcmp_n( (str), comment_tag.value, comment_tag.length ) == 0 )
#define is_comment_len( str, l ) \
	(( xml_strcmp_n( (str), comment_tag.value, comment_tag.length ) == 0 ) && ( (l = comment_tag.length) > 0 ))

#define is_declaration( str ) ( xml_strcmp_n( (str), header_tag.value, header_tag.length ) == 0 )
#define is_declaration_len( str, l ) \
	( ( xml_strcmp_n( (str), header_tag.value, header_tag.length ) == 0 ) && ( l = header_tag.length) > 0 )

#define is_text( str ) ( *(str) && (detail_isspace(*(str)) || detail_issymbol(*(str))) )
#define is_text_len( str, l ) \
	( (*(str) && ((l = 0) == 0)) && (detail_isspace(*(str)) || detail_issymbol(*(str))) )

#define is_element( str ) ( *(str) == less && (detail_isalpha( *((str)+1) ) || *(str+1) == underscore || detail_isspace(*(str+1)) )  )
#define is_element_len( str, l ) ( is_element_len_impl( (str), (&l) ) && ( (str) + l ) != NULL )

#define is_unknown( str ) ( xml_strcmp_n( (str), dtd_tag.value, dtd_tag.length ) == 0 )
#define is_unknown_len( str, l ) \
	( xml_strcmp_n( (str), dtd_tag.value, dtd_tag.length ) == 0 ) && ( l = dtd_tag.length) > 0 )

#define is_end_comment( str ) ( xml_strcmp_n( (str), comment_end_tag.value, comment_end_tag.length ) == 0 )
#define is_end_comment_len( str, l ) \
	(( xml_strcmp_n( (str), comment_end_tag.value, comment_end_tag.length ) == 0 ) && ( (l = comment_end_tag.length) > 0 ))

int is_element_len_impl( const mxml_char_t * str, size_t *len );

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_GRAMMAR_C_H__ */
