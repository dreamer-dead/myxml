#include "../myxml.hpp"
#include "detail.hpp"

namespace myxml
{
	void text::print_out( FILE * file )
	{
		xml_fprintf( file, XML_T("%s"), this->value().c_str() );
	}

	const char_t * text::parse( const char_t * str, parsing_context& ctx )
	{
		document * doc = this->get_document();
		if ( doc )
		{
			if ( !*str || !(detail::is_space(*str) || detail::is_symbol(*str)) )
				return node::document_set_error( XML_T("") );

			detail::parsing_context_state< bool, &parsing_context::skip_whitespace > state( ctx );
			ctx.skip_whitespace = false;
			str = detail::read_content( str, XML_T("<"), ctx, this->value_ );
			if ( str )
				--str;
			
			return str;
		}
		return NULL;
	}
}
