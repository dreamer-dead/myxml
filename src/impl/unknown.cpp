#include "../myxml.hpp"
#include "grammar.hpp"

namespace myxml
{		
	void unknown::print_out( FILE * file )
	{
		//xml_fprintf( file, XML_T("< %s >"), this->value().c_str() );
		xml_fprintf( file, XML_T("%s"), this->value().c_str() );
	}

	const char_t * unknown::parse( const char_t * str, parsing_context& )
	{
		str = detail::skip_space( str );
		if ( *str != grammar::less )
			return node::document_set_error( XML_T("unexpected character while parsing unknown tag !") );

		const char_t * end_tag = xml_strchr( str, grammar::greater );
		if ( !end_tag )
			return node::document_set_error( XML_T("can't find closing '>' while parsing unknown tag !") );

		this->value_.assign( str, end_tag + 1 );
		return end_tag + 1;
	}
}
