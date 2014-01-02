#include "../myxml.h"
#include "detail.h"
#include "parsing.h"
#include "print_out.h"

mxml_node * create_document( const mxml_char_t* value )
{
	mxml_node * n = create_node( value, NULL );

	if ( n != NULL )
	{
		mxml_document * doc = (mxml_document *)malloc( sizeof( mxml_document ) );

		if ( doc )
		{
			doc->error_code = 0;
			doc->error_desc = XML_T( "" );
			n->extend = doc;
		}
		n->type = type_document;
		n->document = n;
	}

	return n;
}

void destroy_document( mxml_document *doc )
{
	if ( doc != NULL )
		free( doc );
}

void print_out_document( mxml_node * n, FILE *file )
{
	if ( n != NULL )
	{
		mxml_node * child = n->first_child;

		while( child != NULL )
		{			
			node_print_out( child, file );
			xml_fprintf( file, XML_T("\n") );
			child = child->next;
		}
	}
}

static 
const mxml_char_t * s_document_set_error( mxml_node * doc, const mxml_char_t * desc, int err )
{
	if ( doc && doc->extend && doc->type == type_document ) 
	{
		mxml_document * docptr = (mxml_document *)doc->extend;

		docptr->error_code = err;
		docptr->error_desc = desc;
	}

	return NULL;
}

const mxml_char_t *document_set_error( mxml_node * doc, const mxml_char_t *str )
{
	return s_document_set_error( (mxml_node *)doc, str, -1 );
}

void document_clear_error( mxml_node * doc )
{
	if ( !doc )
		return;
	else
	{
		mxml_node * doc_node = /* (mxml_node *) */doc;
		if ( doc_node->extend && doc_node->type == type_document )
		{
			mxml_document * docptr = (mxml_document *)doc_node->extend;
			docptr->error_code = 0;
			docptr->error_desc = XML_T( "" );
		}
	}
}

const mxml_char_t * parse_document( mxml_node *doc, const mxml_char_t * str, parsing_context *ctx )
{
	if ( !doc )
		return NULL;

	if ( !str )
		return s_document_set_error( doc, XML_T("NULL pointer data !"), -4 );		

	while ( str && *str )
	{
		str = skip_space( str );
		if ( *str )
		{
			mxml_node * ident = node_identify( doc, str, ctx );

			if ( !ident || !( str = parse_node( ident, str, ctx ) ) )			
				return s_document_set_error( doc, XML_T("can't parse node data !"), -5 );

			append_child( doc, ident );
		}		
		else 
			break;
	}

	return str;
}

int document_load( mxml_node * doc )
{
	FILE * file = NULL;

	if ( !doc )
		return -1;

	document_clear_error( doc );

	if ( !doc->value.str || !doc->value.len )
	{
		s_document_set_error( doc, XML_T("empty file name !"), -8 );
		return -1;
	}

	file = xml_file_open( doc->value.str, XML_T("rt") );
	if ( file )
	{
		size_t beg = 0;
		const mxml_char_t * str = NULL;
		mxml_char_t * buffer = NULL;
		parsing_context ctx = { {0, 0}, 0, NULL };
		long length = 0;
		/*mxml_node * parse_node = doc;*/

		fseek( file, 0, SEEK_END );
		length = ftell( file );
		fseek( file, 0, SEEK_SET );
		if ( !length )
		{
			s_document_set_error( doc, XML_T("zero file length !"), -2 );
			fclose( file );
			return -1;
		}
		
		buffer = malloc( (length + 1) * sizeof(mxml_char_t) );
		if ( !buffer )
		{
			s_document_set_error( doc, XML_T("memory allocation failed !"), -2 );
			fclose( file );
			return -1;
		}

		while ( xml_file_gets( &buffer[beg], (int)(length - beg), file ) )
		{
			size_t len = xml_strlen( &buffer[beg] );

			beg += len;
		}
		
		str = parse_document( doc, &buffer[0], &ctx );

		/*while( 1 )
		{
			str = parse_document( parse_node, &buffer[0], &ctx );
			if ( str == NULL )
		}*/
		free( buffer );
		fclose( file );
		return ( str == NULL ? -1 : 0 );
	}

	s_document_set_error( doc, XML_T("can't open file !"), -1 );
	return -1;
}

int document_load_content( mxml_node * doc, const mxml_char_t * xml )
{
	parsing_context ctx = { {0, 0}, 0, NULL };

	if ( !doc )
		return -1;

	document_clear_error( doc );

	if ( !xml || !*xml )
	{
		s_document_set_error( doc, XML_T("empty xml content !"), -1 );
		return -1;
	}

	return ( parse_document( doc, xml, &ctx ) == NULL ? -1 : 0 );
}

int document_save( mxml_node *doc, const mxml_char_t * file_name )
{
	FILE *file = xml_file_open( file_name, XML_T("wt") );

	if ( file != NULL )
	{
		print_out_document( doc, file );
		fflush( file );
		fclose( file ); 

		return 0;
	}

	return -1;
}
