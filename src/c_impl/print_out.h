#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_PRINTOUT_C_H__
#define __HDR_MYXML_PRINTOUT_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

void print_out_text			( mxml_node *, FILE* );
void print_out_unknown		( mxml_node *, FILE* );
void print_out_comment		( mxml_node *, FILE* );
void print_out_document		( mxml_node *, FILE* );
void print_out_attribute	( mxml_node *, FILE* );
void print_out_element		( mxml_node *, FILE* );
void print_out_declaration	( mxml_node *, FILE* );

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_PRINTOUT_C_H__ */
