#include "mxml_string.h"

void append_str_impl( mxml_string_t * s, const mxml_char_t * app, size_t app_len )
{
	mxml_string_t tmp;
	init_str( &tmp );
	if ( (s) != NULL && (s)->len != 0 ) {
		alloc_str( &tmp, (s)->len + app_len + 1 );
		xml_strcpy( tmp.str, (s)->str );
		xml_strcpy( &tmp.str[(s)->len], app );
		free_str( (s) ); }
	else { xml_strcpy( tmp.str, app ); }
	(s)->str = tmp.str;
	(s)->len = tmp.len;
}
