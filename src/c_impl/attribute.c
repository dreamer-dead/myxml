#include <stdlib.h>
#include "../myxml.h"
#include "grammar.h"
#include "detail.h"

mxml_node * create_attribute( const mxml_char_t* name, mxml_node * parent )
{
	mxml_node * n = create_node( name, parent );

	if ( n != NULL )
	{
		mxml_attribute * attr = (mxml_attribute *)malloc( sizeof( mxml_attribute ) );

		if ( attr )
		{
			init_str( (&attr->value) );
			n->extend = attr;
		}
		n->type = type_attribute;
	}

	return n;
}

void destroy_attribute( mxml_attribute * attr )
{
	if ( attr != NULL )
	{
		free_str( (&attr->value) );
		free( attr );
	}
}

void print_out_attribute( mxml_node * n, FILE * file )
{
	if ( n == NULL )
		return;
	else
	{
		mxml_attribute * attr = (mxml_attribute *)n->extend;

		if ( attr && attr->value.len != 0 && n->value.len != 0 )
		{
			xml_fprintf( file, XML_T(" %s=\""), n->value.str );
			file_write_content( &attr->value, file );
			xml_fprintf( file, XML_T("\"") );
		}
	}	
}

const mxml_char_t * parse_attribute( mxml_node *n, const mxml_char_t * str, parsing_context * ctx )
{
	str = skip_space( str );

	if ( str )
	{
		const mxml_char_t * beg = str;

		while( *str && *str != equal && !detail_isspace( *str ) )
			++str;

		assign_cstr_len( &n->value, beg, (size_t)(str - beg) );
		
		if ( *str != equal )
			str = skip_space( str );

		if ( *str++ != equal )
			return document_set_error( n->document, XML_T("unexpected symbol( expect '=' ) while parsing attribute !") );

		str = skip_space( str );

		if ( *str != single_quote && *str != dbl_quote )
			return document_set_error( n->document, XML_T("unexpected symbol( expect opening quote ) while parsing attribute !") );
		else
		{
			mxml_attribute * attr = (mxml_attribute *)n->extend;
			mxml_char_t quote[2] = { (mxml_char_t)('\0'), (mxml_char_t)('\0') };
			quote[0] = *str++;

			if ( !attr )
				return NULL;

			return read_content( str, quote, 1, ctx, &attr->value );
		}
	}

	return document_set_error( n->document, XML_T( "error while parsing attribute !" ) );
}
