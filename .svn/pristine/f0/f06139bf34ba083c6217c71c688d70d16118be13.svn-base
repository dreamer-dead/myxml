#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_PARSING_C_H__
#define __HDR_MYXML_PARSING_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../config.h"
#include "types.h"

const mxml_char_t * parse_node		( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_text		( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_unknown	( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_comment	( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_document	( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_attribute	( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_element	( mxml_node *, const mxml_char_t *, parsing_context * );
const mxml_char_t * parse_declaration( mxml_node *, const mxml_char_t *, parsing_context * );
mxml_node * node_identify( void *, const mxml_char_t *, parsing_context *);

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_PARSING_C_H__ */
