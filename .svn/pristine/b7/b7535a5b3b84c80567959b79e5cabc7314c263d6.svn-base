#include <stdlib.h>
#include "../myxml.h"
#include "grammar.h"
#include "detail.h"
#include "parsing.h"

const mxml_string_t 
	atrribute_version = { XML_T("version"), 7 }, 
	attribute_encoding = { XML_T("encoding"), 8 },
	attribute_standalone = { XML_T("standalone"), 10 };

mxml_node * create_declaration( mxml_node * parent )
{
	mxml_node * n = create_node( XML_T("?xml"), parent );

	if ( n != NULL )
	{
		mxml_declaration * decl = (mxml_declaration *)malloc( sizeof( mxml_declaration ) );

		if ( decl )
		{
			init_str( (&decl->version) );
			init_str( (&decl->standalone) );
			init_str( (&decl->encoding) );
			n->extend = decl;
		}
		n->type = type_declaration;
	}

	return n;
}

void destroy_declaration( mxml_declaration * decl )
{
	if ( decl )
	{
		free_str( &decl->encoding );
		free_str( &decl->standalone );
		free_str( &decl->version );

		free( decl );
	}
}
void print_out_declaration( mxml_node *n, FILE *file )
{
	if ( n != NULL )
	{
		mxml_declaration * decl = (mxml_declaration *)n->extend;

		if ( decl != NULL )
		{
			xml_fprintf( file, XML_T( "%s" ), XML_T( "<?xml" ) );

			if ( decl->version.len != 0 && decl->version.str != NULL )
				xml_fprintf( file, XML_T( " version=\"%s\"" ), decl->version.str );

			if ( decl->encoding.len != 0 && decl->encoding.str != NULL )
				xml_fprintf( file, XML_T( " encoding=\"%s\"" ), decl->encoding.str );

			if ( decl->standalone.len != 0 && decl->standalone.str != NULL )
				xml_fprintf( file, XML_T( " standalone=\"%s\"" ), decl->standalone.str );

			xml_fprintf( file, XML_T( "%s" ), XML_T( " ?>" ) );
		}
	}
}


const mxml_char_t * parse_declaration( mxml_node *n, const mxml_char_t *str, parsing_context * ctx )
{
	size_t len = 0;
	mxml_declaration * decl = NULL;

	if ( !n || !n->extend )
		return document_set_error( n->document, XML_T("NULL declaraton object") );

	decl = (mxml_declaration *)n->extend;
	str = skip_space( str );
	if ( *str != less )
		return document_set_error( n->document, XML_T("unexpected character while parsing declaration tag !") );

	if ( !is_declaration_len( str, len ) )
		return document_set_error( n->document, XML_T("incorrect tag while parsing declaration tag !") );

	assign_cstr_len( &n->value, (str + 1), (len - 1) );
	str += len;

	while ( *str && *str != greater )
	{
		mxml_string_t * attr_value_ptr = NULL;
		str = skip_space( str );		

		if ( xml_strcmp_i_n( str, atrribute_version.str, atrribute_version.len ) == 0 )
			attr_value_ptr = &decl->version;
		else if ( xml_strcmp_i_n( str, attribute_encoding.str, attribute_encoding.len ) == 0 )
			attr_value_ptr = &decl->encoding;
		else if ( xml_strcmp_i_n( str, attribute_standalone.str, attribute_standalone.len ) == 0 )
			attr_value_ptr = &decl->standalone;

		if ( attr_value_ptr )
		{
			mxml_node temp;
			mxml_attribute attr;

			init_str( &attr.value );			
			temp.type = type_attribute;
			temp.extend = &attr;
			init_str( &temp.value );

			str = parse_attribute( &temp, str, ctx );
			if ( str )
			{
				/* assign_str( attr_value_ptr, &temp.value ); */
				assign_str( attr_value_ptr, &attr.value );
				free_str( &temp.value );
				free_str( &attr.value );
			}
			else 
			{
				free_str( &temp.value );
				free_str( &attr.value );
				return document_set_error( n->document, XML_T("can't parse attribute while parsing declaration tag !") );
			}
		}
		else 
		{
			while ( *str && !detail_isspace(*str) && *str != greater )
				++str;
		}
	}

	if ( decl->standalone.str && decl->standalone.len )
	{
		/*
			http://www.w3.org/TR/2004/REC-xml-20040204/#NT-SDDecl
		*/
		if ( 
			xml_strcmp_i( decl->standalone.str, XML_T("yes") ) != 0
			&& xml_strcmp_i( decl->standalone.str, XML_T("no") ) != 0 
			)
			return document_set_error( n->document, XML_T("declaration's tag attribute 'standalone' has invalid value !") );		
	}

	return str + 1;
}
