#include "../myxml.h"
#include "detail.h"

mxml_node * create_text( mxml_node * parent )
{
	mxml_node * n = create_node( XML_T(""), parent );
	if ( n )
	{
		n->type = type_text;
	}

	return n;
}

void print_out_text( mxml_node *n, FILE *file )
{
	if ( n != NULL && n->value.len != 0 && n->value.str != NULL )
	{
		//xml_fprintf( file, XML_T("%s"), n->value.str );
		file_write_content( &n->value, file );
	}
}

const mxml_char_t * parse_text( mxml_node *n, const mxml_char_t * str, parsing_context * ctx )
{	
	void * doc = n->document;
	if ( doc )
	{
		int old_skip_ws = ctx->skip_whitespace;

		if ( !*str || !(detail_isspace(*str) || detail_issymbol(*str)) )
			return document_set_error( doc, XML_T("error while parsing text!") );
		
		ctx->skip_whitespace = 0;
		str = read_content( str, XML_T("<"), 1, ctx, &n->value );
		if ( str )
			--str;

		ctx->skip_whitespace = old_skip_ws;
		return str;
	}
	return NULL;
}
