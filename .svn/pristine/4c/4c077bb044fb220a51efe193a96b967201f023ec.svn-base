/**
* \file attribute.cpp
* desc
*/

#include "../myxml.hpp"
#include "detail.hpp"
#include "grammar.hpp"

namespace myxml
{
	void attribute::print_out( FILE * file )
	{
		if ( !this->value().empty() )
			xml_fprintf( file, XML_T(" %s=\"%s\""), this->name_.c_str(), this->value().c_str() );
	}

	const char_t * attribute::parse( const char_t * str, parsing_context& ctx )
	{
		str = detail::skip_space( str );
		const char_t * beg = str;

		while( *str && *str != grammar::equal && !detail::is_space( *str ) )
			++str;

		this->name_.assign( beg, str );
		if ( *str != grammar::equal )
			str = detail::skip_space( str );
		
		if ( *str++ != grammar::equal )
			return node::document_set_error( XML_T("unexpected symbol( expect '=' ) while parsing attribute !") );

		str = detail::skip_space( str );

		if ( *str != grammar::single_quote && *str != grammar::dbl_quote )
			return node::document_set_error( XML_T("unexpected symbol( expect opening quote ) while parsing attribute !") );

		//const char_t quote[] = { *str++, char_t('\0') };

		/*
		beg = str;
		str = _tcschr( str, quote );
		if ( !str )
			return node::document_set_error( XML_T("can't find closing quote while parsing attribute !") );

		this->value_.assign( beg, str );
		return str + 1;
		//*/

		//return detail::read_content( str, quote, ctx, this->value_ );
		const char_t quote = *str++;
		return detail::read_content_fast( str, quote, ctx, this->value_ );
	}
}
