#include "../myxml.hpp"
#include "detail.hpp"
#include "grammar.hpp"

namespace myxml
{
	void comment::print_out( FILE * file )
	{
		xml_fprintf( file, XML_T("<!-- %s -->"), this->value().c_str() );
	}

	const char_t * comment::parse( const char_t * str, parsing_context& )
	{
		size_t len = 0;
		if ( !grammar::is< comment >( str, len ) )
			return node::document_set_error( XML_T("incorrect open tag while parsing comment element !") );

		str += len;
		const char_t * end_tag = str;		
		while (
			*end_tag 
			&& !grammar::is_end_comment( end_tag, len ) 
			)
		{
			const char_t * end_tag_old = end_tag;
			end_tag = xml_strchr( end_tag_old, grammar::minus );
			if ( !end_tag )
				return node::document_set_error( XML_T("can't find closing '-->' while parsing comment element !") );
			else if ( (void*)end_tag_old == (void*)end_tag ) // repeating '-'
			{
				++end_tag;
			}
		}

		if ( !end_tag || !*end_tag )
			return node::document_set_error( XML_T("can't find closing '-->' while parsing comment element !") );

		this->value_.assign( str, end_tag );
		return end_tag + len;
	}
}
