#include "grammar.h"

const mxml_char_t underscore	= (mxml_char_t)( '_' );
const mxml_char_t less			= (mxml_char_t)( '<' );
const mxml_char_t greater		= (mxml_char_t)( '>' );
const mxml_char_t ampersand		= (mxml_char_t)( '&' );
const mxml_char_t dies			= (mxml_char_t)( '#' );
const mxml_char_t smX			= (mxml_char_t)( 'x' );
const mxml_char_t grX			= (mxml_char_t)( 'X' );
const mxml_char_t colon			= (mxml_char_t)( ';' );
const mxml_char_t equal			= (mxml_char_t)( '=' );
const mxml_char_t single_quote	= (mxml_char_t)( '\'' );
const mxml_char_t dbl_quote		= (mxml_char_t)( '\"' );
const mxml_char_t slash			= (mxml_char_t)( '/' );
const mxml_char_t minus			= (mxml_char_t)( '-' );

const grammar_tag header_tag		= { XML_T("<?xml"), 5 };
const grammar_tag comment_tag		= { XML_T("<!--"), 4 };
const grammar_tag comment_end_tag	= { XML_T("-->"), 3 };
const grammar_tag dtd_tag			= { XML_T("<!"), 2 };

int is_element_len_impl( const mxml_char_t * str, size_t *len )
{
	if ( is_element( str ) )
	{
		len = 0;
		while ( *str && !detail_isspace( *str++ ) )
			++len;

		return 1;
	}

	return 0;
}
