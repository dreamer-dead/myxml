#include <stdlib.h>
#include <memory.h>

#include "../myxml.h"
#include "./xpath/xpath_match.h"
#include "./xpath/xpath_parser.h"
#include "grammar.h"
#include "destroy.h"
#include "parsing.h"
#include "print_out.h"

#define UNUSED_ARG( x ) (void)x

const mxml_char_t * parse_node_impl( mxml_node *n, const mxml_char_t * str, parsing_context * ctx );
void node_print_out_impl( mxml_node *, FILE* );

typedef const mxml_char_t * (* parse_func)(mxml_node *, const mxml_char_t *, parsing_context * );
parse_func g_ext_parse_table[ type_unknown + 1 ] = 
{
	&parse_node_impl,	 /* type_node,			*/
	&parse_document,	 /* type_document		*/
	&parse_element,		 /* type_element		*/
	&parse_comment,		 /* type_comment		*/
	&parse_attribute,	 /* type_attribute		*/
	&parse_text,		 /* type_text			*/
	&parse_declaration,  /* type_declaration	*/
	&parse_unknown		 /* type_unknown		*/
};					  

void (* g_ext_printout_table[ type_unknown + 1 ])( mxml_node *, FILE* ) =
{
	&node_print_out_impl,	 /* type_node,			*/
	&print_out_document,	 /* type_document		*/
	&print_out_element,		 /* type_element		*/
	&print_out_comment,		 /* type_comment		*/
	&print_out_attribute,	 /* type_attribute		*/
	&print_out_text,		 /* type_text			*/
	&print_out_declaration,  /* type_declaration	*/
	&print_out_unknown		 /* type_unknown		*/
};

mxml_node * create_node( const mxml_char_t* value, mxml_node * parent )
{
	mxml_node * n = (mxml_node *)malloc( sizeof(mxml_node) );

	if ( n != NULL )
	{
		init_str( &n->value );
		assign_cstr( (&n->value), value );
		n->parent = parent;
		if ( parent != NULL )
			n->document = parent->document;
		else
			n->document = NULL;

		n->type = type_node;
		n->extend = NULL;

		n->next = n->prev = n->first_child = n->last_child = NULL;
	}
	return n;
}

void node_destroy( mxml_node * n )
{
	if ( n != NULL )
	{
		mxml_node * temp = NULL;
		mxml_node * child = n->first_child;

		while ( child )
		{
			temp = child->next;
			node_destroy( child );
			child = temp;
		}

		if ( n->extend != NULL && n->type != type_node )
		{
			switch( n->type )
			{
			case type_element		: destroy_element	 ( (mxml_element *)n->extend ); break;
			case type_attribute		: destroy_attribute	 ( (mxml_attribute *)n->extend ); break;
			case type_declaration	: destroy_declaration( (mxml_declaration *)n->extend ); break;
			case type_document		: destroy_document	 ( (mxml_document *)n->extend ); break;
			}
		}
		free_str( &n->value );
		free( n );
	}
}

const mxml_char_t * parse_node_impl( mxml_node *n, const mxml_char_t * str, parsing_context * ctx )
{
	UNUSED_ARG(n);
	UNUSED_ARG(str);
	UNUSED_ARG(ctx);

	return NULL;
}

void node_print_out_impl( mxml_node *n, FILE *file )
{
	UNUSED_ARG(n);
	UNUSED_ARG(file);

	return;
}

const mxml_char_t * parse_node( mxml_node *n, const mxml_char_t * str, parsing_context * ctx )
{
	if ( n != NULL )
	{
		return g_ext_parse_table[ (int)n->type ]( n, str, ctx );
	}

	return NULL;
}

void node_print_out( mxml_node *n, FILE *file )
{
	if ( n != NULL )
	{
		g_ext_printout_table[ (int)n->type ]( n, file );
	}
}

void append_child( mxml_node * to, mxml_node * n )
{
	if ( !n )
		return;
	else
	{
		mxml_node * nparent = n->parent;

		if ( nparent )
		{
			remove_child( nparent, n );
		}

		if ( !to->last_child && !to->first_child )
		{
			to->first_child = n;
			to->last_child = n;
			n->prev = NULL;
		}
		else if ( to->last_child )
		{
			to->last_child->next = n;
			n->prev = to->last_child;
			to->last_child = n;
		}

		n->parent = to;
		n->next = NULL;
		if ( !n->document )
			n->document = to->document;
	}		
}

void append_before_child( mxml_node * parent, mxml_node * n, mxml_node * before )
{
	if ( before == NULL )
	{
		if ( !parent->last_child && !parent->first_child )
		{
			append_child( parent, n );
			return;
		}
		else
		{
			if ( parent->first_child )
				parent->first_child->prev = n;

			n->next = parent->first_child;
			parent->first_child = n;
		}
	}
	else
	{
		if ( before->parent == parent )
		{
			mxml_node * aprev = before->prev;
			mxml_node * nparent = n->parent;

			if ( nparent )
			{
				remove_child( nparent, n );
			}

			before->prev = n;
			n->prev = aprev;
			if ( aprev )
			{					
				aprev->next = n;
			}
			n->next = before;		

			if ( before == parent->first_child )
				parent->first_child = n;
		}
		else // logic error !	
			return; 		
	}

	n->parent = parent;
	if ( !n->document)
		n->document = parent->document;
}

void append_after_child( mxml_node * parent, mxml_node * n, mxml_node * after )
{
	if ( after == NULL )
	{
		append_child( parent, n );
		return;
	}
	else
	{
		if ( after->parent == parent )
		{
			mxml_node * anext = after->next;
			mxml_node * nparent = n->parent;

			if ( nparent )
			{
				remove_child( nparent, n );
			}				

			after->next = n;
			n->next = anext;
			if ( anext )
			{					
				anext->prev = n;
			}
			n->prev = after;	

			if ( after == parent->last_child )
				parent->last_child = n;
		}
		else // logic error !		
			return; 	
	}

	n->parent = parent;
	if ( !n->document)
		n->document = parent->document;
}

void remove_child( mxml_node * parent, mxml_node * n )
{
	if ( n != NULL && n->parent == parent )
	{
		mxml_node * nnext = n->next;
		mxml_node * nprev = n->prev;

		if ( nnext )
		{
			nnext->prev = nprev;

			if ( n == parent->first_child )
				parent->first_child = nnext;
		}

		if( nprev )
		{
			nprev->next = nnext;

			if ( n == parent->last_child )
				parent->last_child = nprev;
		}

		n->parent = NULL;
	}
	else // logic error !		
		return;
}

mxml_node * node_identify( void * doc, const mxml_char_t * str, parsing_context *ctx )
{	
	mxml_node * doc_node = (mxml_node *)doc;
	mxml_node * ident_node = NULL;

	UNUSED_ARG( ctx );

	if ( !doc_node )
		return NULL;
	
	if ( is_declaration ( str ) )
		ident_node = create_declaration( doc_node );
	else if ( is_comment( str ) )
		ident_node = create_comment( doc_node );
	else if ( is_unknown( str ) )
		ident_node = create_unknown( doc_node );
	else if ( is_element( str ) )
		ident_node = create_element( XML_T(""), doc_node );
	else if ( is_text( str ) )
		ident_node = create_text( doc_node );
	else 
		ident_node = create_unknown( doc_node );

	return ident_node;
}

static 
int match_nodes( const mxml_char_t * path, size_t *path_len, mxml_node *n, LIST_TYPE lst )
{
#define XPATH_MAX_LEN 128
	mxml_char_t buffer [XPATH_MAX_LEN];
	const mxml_char_t * slash_ptr = xml_strchr( path, (mxml_char_t)('/') );
	const size_t length = slash_ptr ? (size_t)(slash_ptr - path) : 0;
	match m;

	if ( length >= XPATH_MAX_LEN )
		return -1;

	memset( buffer, 0, XPATH_MAX_LEN * sizeof( mxml_char_t ) );

	//*
	if ( length )
		xml_strncpy( buffer, path, length );
	else 
		xml_strcpy( buffer, path );

	init_str( &m.value );
	init_str( &m.pred.cond_value );
	init_str( &m.pred.value );

	if ( 0 == identify_match( buffer, &m ) )
	{
		if ( 0 != xpath_match( lst, n, &m ) )
			return -1;
		else
		{
			*path_len = length;

			return 0;
		}
	}
	//*/

	return -1;

#undef XPATH_MAX_LEN
}

static
int node_find_impl( mxml_node *n, const mxml_char_t * path, LIST_TYPE lst )
{
#define TMP_LIST_INIT_SIZE 32
	size_t length = 0;
	list_type tmp_list;

	list_init( &tmp_list, TMP_LIST_INIT_SIZE );
#undef TMP_LIST_INIT_SIZE

	if ( match_nodes( path, &length, n, &tmp_list ) == 0 )
	{
		size_t ii = 0;
		if ( length != 0 )
		{
			for ( ii = 0; ii < tmp_list.count; ++ii )
			{
				node_find( tmp_list.items[ ii ], path + length + 1, lst );
			}

			list_free( &tmp_list );
			return 0;
		}
		else
		{
			for ( ii = 0; ii < tmp_list.count; ++ii )
				lst->items[ lst->count + ii ] = tmp_list.items[ ii ];

			lst->count += tmp_list.count;

			list_free( &tmp_list );
			return 0;
		}		
	}
	
	list_free( &tmp_list );
	return -1;
}

mxml_node * node_find_single( mxml_node *n, const mxml_char_t * path )
{
	mxml_node * fnode = NULL;
	list_type lst;
	list_init( &lst, 16 );

	if ( 0 != node_find_impl( n, path, &lst ) )
		return NULL;

	fnode = ( lst.count ? lst.items[0] : NULL );
	list_free( &lst );
	return fnode;
}

int node_find( mxml_node *n, const mxml_char_t * path, LIST_TYPE lst )
{
	return node_find_impl( n, path, lst );
}
