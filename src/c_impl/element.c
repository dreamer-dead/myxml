#include <stdlib.h>
#include <assert.h>
#include "../myxml.h"
#include "grammar.h"
#include "detail.h"
#include "parsing.h"
#include "print_out.h"

mxml_node * create_element( const mxml_char_t* value, mxml_node * parent )
{
	mxml_node * n = create_node( value, parent );

	if ( n != NULL )
	{
		mxml_element * elem = (mxml_element *)malloc( sizeof( mxml_element ) );

		if ( elem )
		{
			elem->first_attribute = NULL;
			elem->text = NULL;
			n->extend = elem;
		}		
		n->type = type_element;
	}

	return n;
}

void destroy_element( mxml_element * elem )
{
	if ( elem != NULL )
	{
		mxml_node * attr = elem->first_attribute;
		/* 
		if ( elem->text )
			node_destroy( elem->text );
		*/

		while( attr != NULL )
		{
			mxml_node * temp = attr->next;

			node_destroy( attr );
			attr = temp;
		}

		free( elem );
	}
}

void print_out_element( mxml_node *n, FILE *file )
{
	if ( n != NULL && n->value.str != NULL && n->value.len != 0 )
	{
		xml_fprintf( file, XML_T("<%s"), n->value.str );

		if ( n->extend != NULL )
		{
			mxml_element * elem = (mxml_element *)n->extend;
			mxml_node * attr = elem->first_attribute;

			while( attr != NULL )
			{
				print_out_attribute( attr, file );
				attr = attr->next;
			}

			if ( n->first_child != NULL )
			{
				mxml_node * txt = elem->text;
				mxml_node * child = n->first_child;

				xml_fprintf( file, XML_T("%s"), XML_T(" >\n\t") );
				if ( txt != NULL )
				{
					print_out_text( txt, file );
					xml_fprintf( file, XML_T("\n\t") );
				}
				
				while( child != NULL )
				{
					if ( child != txt )
					{
						node_print_out( child, file );
						xml_fprintf( file, XML_T("%s"), XML_T("\n\t") );
					}
					child = child->next;
				}

				xml_fprintf( file, XML_T("</%s>"), n->value.str );
			}		
			else
			{
				xml_fprintf( file, XML_T("%s"), XML_T(" />") );
			}
		}		
	}
}

static 
const mxml_char_t * read_tag( mxml_node *n, const mxml_char_t * str, int* closed )
{	
	*closed = 0;
	str = skip_space( str );
	if ( str && *str )
	{
		const mxml_char_t * beg = str;

		while ( 
			*str 
			&& *str != greater 
			&& *str != slash 
			&& !detail_isspace(*str) 
			)
			++str;

		if ( beg < str )
		{
			assign_cstr_len( &n->value, beg, (size_t)(str - beg) );		
			if ( *str == slash ) 
			{
				++str;
				if ( *str++ != greater )
					*closed = 1;
				else 
					return NULL;
			}
			return str;
		}
	}

	return NULL;
}

static 
const mxml_char_t * read_attributes( mxml_node *n, const mxml_char_t * str, parsing_context* ctx, int* closed )
{
	*closed = 0;
	// read attributes of tha elemend
	while( *str )
	{
		mxml_node *att = NULL;

		str = skip_space( str );
		if ( !*str )
			return document_set_error( n->document, XML_T("error while parsing element tag !") );

		if ( *str == greater )
		{
			++str;
			break;
		}

		if ( *str == slash )
		{
			++str;
			if ( *str++ == greater )
				return ( *closed = 1, str );
			else
				return document_set_error( n->document, XML_T("find incorrect symbol after '/' while parsing element tag !") );
		}

		att = create_attribute( XML_T(""), n );
		if ( att )
		{
			str = parse_attribute( att, str, ctx );

			if ( !str )
				return document_set_error( n->document, XML_T("error while parsing element tag !") );
		}

		element_add_attribute( n, att );
	}
	return str;
}

static 
void append_text( mxml_node* n, mxml_node * text_node )
{
	mxml_node * child = NULL;
	
	if ( n == NULL || text_node == NULL )
		return;

	child = n->last_child;
	if ( child )
	{
		while( child && child->type != type_text )
			child = child->prev;
		/*
		if ( child->type != type_text )
			child = child->prev;
		*/

		if ( child && child->type == type_text )
		{
			append_str( &child->value, text_node->value.str, text_node->value.len );
			return;
		}
	}

	((mxml_element *)n->extend)->text = text_node;
	append_child( n, text_node );
}

static
const mxml_char_t * read_inner( mxml_node *n, const mxml_char_t * str, parsing_context* ctx )
{
	void * doc = n->document;
	assert( doc );

	while ( *str )
	{
		mxml_node *ident = NULL;

		str = skip_space( str );
		if ( xml_strcmp_n( str, XML_T("</"), 2 ) == 0 )
			break;

		ident = node_identify( doc, str, ctx );
		if ( !ident || !(str = parse_node( ident, str, ctx )) )
			return document_set_error( n->document, XML_T("can't read inner data while parsing element !") );

		if ( ident->type != type_text )
			append_child( n, ident );
		else 
			append_text( n, ident );
	}

	return str;
}

const mxml_char_t * parse_element( mxml_node *n, const mxml_char_t *str, parsing_context *ctx )
{
	int closed = 0;

	if ( !n )
		return NULL;

	str = skip_space( str );
	if ( *str != less )
		return document_set_error( n->document, XML_T("unexpected character while parsing element tag !") );

	str = read_tag( n, str + 1, &closed );
	if ( !str )
		return document_set_error( n->document, XML_T("can't read tag name while parsing element tag !") );

	if ( !closed )
	{
		str = read_attributes( n, str, ctx, &closed );
		if ( !str ) 
			return document_set_error( n->document, XML_T("can't read attributes while parsing element tag !") );

		if ( !closed )
		{
			str = read_inner( n, str, ctx );
			if ( !str )
				return document_set_error( n->document, XML_T("error while parsing element tag !") );
			else // end tag ?
			{
				const mxml_char_t * end = NULL;

				if ( xml_strcmp_n( str, XML_T("</"), 2 ) != 0 )
					return document_set_error( n->document, XML_T("not found '</' while parsing element tag !") );

				/* 
					исправления по замечаниям WinterMute на RSDN - http://rsdn.ru/Forum/Message.aspx?mid=2400256&only=1 
					пробелы в тексте вида <node>...</ node > не обрабатывались корректно

					15:07 12.03.2007 
					Dreamer
				*/
				/*					
				str += 2;
				const char_t * end = xml_strchr( str, greater );
				//*/

				str = skip_space( str + 2 );
				if ( !str )
					return document_set_error( n->document, XML_T("error while parsing element tag !") );

				end = str;
				while ( *end && (*end != greater && !detail_isspace( *end )) )
					++end;

				if ( /* !end || */ !*end )
					return document_set_error( n->document, XML_T("not found closing '>' while parsing element tag !") );

				if ( xml_strcmp_n( n->value.str, str, (size_t)( end - str ) ) )
					return document_set_error( n->document, XML_T("end tag not match with open tag while parsing element tag !") );

				str = end + 1;
			}
		}
	}

	return str;
}

mxml_node * element_add_attribute( mxml_node * n, mxml_node * attr )
{
	if ( n == NULL )
		return NULL;

	if ( n->extend == NULL )
		return NULL;
	else
	{
		mxml_element * elem = (mxml_element *)(n->extend);

		if ( elem->first_attribute == NULL )
		{
			elem->first_attribute = attr;
			attr->parent = n;
			attr->prev = NULL;
			attr->next = NULL;
		}
		else
		{
			mxml_node * last = elem->first_attribute;
			while ( last != NULL && last->next != NULL )
				last = last->next;

			//append_child( next, attr );
			last->next = attr;
			attr->parent = n;
			attr->prev = last;
			attr->next = NULL;
		}
	}

	return attr;
}

mxml_node * element_first_attribute( mxml_node * n )
{
	if ( n == NULL )
		return NULL;

	if ( n->extend != NULL )
	{
		mxml_element * elem = (mxml_element *)(n->extend);

		return elem->first_attribute;
	}

	return NULL;
}

mxml_node * element_find_attribute( mxml_node * n, const mxml_char_t * value )
{
	mxml_node * attr = element_first_attribute( n );

	while ( attr )	
	{
		if ( xml_strcmp( attr->value.str, value ) == 0 )
			return attr;

		attr = attr->next;
	}

	return NULL;
}

mxml_node * element_get_text( mxml_node *n )
{
	if ( n != NULL && n->extend != NULL && n->type == type_element )
	{
		mxml_element * elem = (mxml_element *)n->extend;
		if ( elem->text != NULL )
			return elem->text;
		else
		{
			mxml_node * txt = n->first_child;

			while ( txt != NULL )
			{
				if ( txt->type == type_text )
				{
					elem->text = txt;
					return txt;
				}

				txt = txt->next;
			}
		}
	}

	return NULL;
}
