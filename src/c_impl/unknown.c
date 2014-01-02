#include "../myxml.h"
#include "detail.h"
#include "grammar.h"

#define UNUSED_ARG( x ) (void)x

mxml_node * create_unknown( mxml_node * parent )
{
	mxml_node * n = create_node( XML_T(""), parent );
	if ( n )
	{
		n->type = type_unknown;
	}

	return n;
}

void print_out_unknown( mxml_node *n, FILE *file )
{
	if ( n != NULL && n->value.len != 0 && n->value.str != NULL )
	{
		//xml_fprintf( file, XML_T("< %s >"), n->value.str );
		xml_fprintf( file, XML_T("%s"), n->value.str );
	}
}

const mxml_char_t * parse_unknown( mxml_node * n, const mxml_char_t * str, parsing_context * ctx )
{
	UNUSED_ARG(ctx);

	str = skip_space( str );
	if ( *str != less )
		return document_set_error( n->document, XML_T("unexpected character while parsing unknown tag !") );
	else
	{
		const mxml_char_t * end_tag = xml_strchr( str, greater );
		if ( !end_tag )
			return document_set_error( n->document, XML_T("can't find closing '>' while parsing unknown tag !") );
		
		assign_cstr_len( &n->value, str, (size_t)( end_tag - str + 1) );
		return end_tag + 1;
	}

	/* unreachable code */
	/*
		return NULL;
	//*/
}
