#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_TYPES_C_H__
#define __HDR_MYXML_XPATH_TYPES_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../types.h"
#include "../mxml_string.h"

#define LIST_PUSH_BACK( l, el ) list_add( l, el )
#define LIST_TYPE list_type *

typedef enum
{
	x_unknown,
	x_child,
	x_parent,
	x_attribute
} x_type;

typedef struct predicate_tag
{
	int single;
	x_type type;
	mxml_string_t value;
	int cond;
	mxml_string_t cond_value;
} predicate;

typedef struct match_tag
{
	x_type type;
	mxml_string_t value;
	int use_pred;
	predicate pred;
} match;


#ifdef __cplusplus
}
/* END extern "C" { */
#endif

#endif /* __HDR_MYXML_XPATH_TYPES_C_H__ */
