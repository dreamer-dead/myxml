#include <stdlib.h>
#include "../myxml.h"
#include "grammar.h"
#include "detail.h"

#define UNUSED_ARG( x ) (void)x

mxml_node * create_comment( mxml_node * parent )
{
	mxml_node * n = create_node( XML_T(""), parent );
	if ( n )
	{
		n->type = type_comment;
	}

	return n;
}

void print_out_comment( mxml_node *n, FILE *file )
{
	if ( n == NULL )
		return;
	else 
	{
		//xml_fprintf( file, XML_T("%s"), XML_T( "<!-- " ) );
		//file_write_content( &n->value, file );
		//xml_fprintf( file, XML_T("%s"), XML_T( " -->" ) );		
		xml_fprintf( file, XML_T("<!-- %s -->"), n->value.str );		
	}
}

const mxml_char_t * parse_comment( mxml_node *n, const mxml_char_t * str, parsing_context * ctx )
{
	const mxml_char_t * end_tag = NULL;
	size_t len = 0;
	UNUSED_ARG(ctx);

	if ( !is_comment_len( str, len ) )
		return document_set_error( n->document, XML_T("incorrect open tag while parsing comment element !") );

	str += len;
	end_tag = str;		
	while (
		*end_tag 
		&& !is_end_comment_len( end_tag, len ) 
		)
	{
		const mxml_char_t * end_tag_old = end_tag;
		end_tag = xml_strchr( end_tag_old, minus );
		if ( !end_tag )
			return document_set_error( n->document, XML_T("can't find closing '-->' while parsing comment element !") );

		else if ( (void*)end_tag_old == (void*)end_tag ) // repeating '-'
		{
			++end_tag;
		}
	}

	if ( !end_tag || !*end_tag )
		return document_set_error( n->document, XML_T("can't find closing '-->' while parsing comment element !") );

	assign_cstr_len( &n->value, str, (size_t)(end_tag - str) );
	return end_tag + len;
}
