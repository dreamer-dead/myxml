#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_MATCH_C_H__
#define __HDR_MYXML_XPATH_MATCH_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../types.h"
#include "xpath_types.h"

int xpath_match( LIST_TYPE dst, mxml_node *n, match *m );

#ifdef __cplusplus
}
/* END extern "C" { */
#endif

#endif /* __HDR_MYXML_XPATH_MATCH_C_H__ */
