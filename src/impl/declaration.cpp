#include "../myxml.hpp"
#include "grammar.hpp"

namespace myxml
{		
	const string_t 
		atrribute_version = XML_T("version"), 
		attribute_encoding = XML_T("encoding"), 
		attribute_standalone = XML_T("standalone");

	const char_t * declaration::parse( const char_t * str, parsing_context& ctx )
	{
		str = detail::skip_space( str );
		if ( *str != grammar::less )
			return node::document_set_error( XML_T("unexpected character while parsing declaration tag !") );

		size_t len = 0;
		if ( !grammar::is< declaration>( str, len ) )
			return node::document_set_error( XML_T("incorrect tag while parsing declaration tag !") );

		this->value_.assign( str + 1, len - 1 );
		str += len;

		while ( *str && *str != grammar::greater )
		{
			str = detail::skip_space( str );
			string_t * attr_value_ptr = NULL;

			if ( detail::string_n_compare<true>( str, atrribute_version.c_str(), atrribute_version.length() ) )
				attr_value_ptr = &this->version_;
			else if ( detail::string_n_compare<true>( str, attribute_encoding.c_str(), attribute_encoding.length() ) )
				attr_value_ptr = &this->encoding_;
			else if ( detail::string_n_compare<true>( str, attribute_standalone.c_str(), attribute_standalone.length() ) )
				attr_value_ptr = &this->standalone_;

			if ( attr_value_ptr )
			{
				attribute attr( this->get_document() );
				str = attr.parse( str, ctx );
				if ( str )
					*attr_value_ptr = attr.value();
				else 
					return node::document_set_error( XML_T("can't parse attribute while parsing declaration tag !") );
			}
			else 
			{
				while ( *str && !detail::is_space(*str) && *str != grammar::greater )
					++str;
			}
		}

		if ( !this->standalone_.empty() )
		{
			/*
				http://www.w3.org/TR/2004/REC-xml-20040204/#NT-SDDecl
			//*/
			if ( this->standalone_ != string_t( XML_T("yes") ) && this->standalone_ != string_t( XML_T("no") ) )
				return node::document_set_error( XML_T("declaration's tag attribute 'standalone' has invalid value !") );
		}
	
		return str + 1;
	}

	void declaration::print_out( FILE * file )
	{
		string_t line = XML_T( "<?xml" );

		if ( !this->version_.empty() )
			line += XML_T(" version=\"") + this->version_ + static_cast<char_t>('\"');

		if ( !this->encoding_.empty() )
			line += XML_T(" encoding=\"") + this->encoding_ + static_cast<char_t>('\"');

		if ( !this->standalone_.empty() )
			line += XML_T(" standalone=\"") + this->standalone_ + static_cast<char_t>('\"');
		line += XML_T( "?>" );

		xml_fprintf( file, XML_T("%s"), line.c_str() );
	}
}
