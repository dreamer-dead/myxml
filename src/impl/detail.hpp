#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_DETAIL_HPP__
#define __HDR_MYXML_DETAIL_HPP__

#include "../myxml.hpp"
#include <locale>

namespace myxml 
{
	namespace detail 
	{
		struct replacement_t
		{
			const char_t * value;
			size_t len;
			char_t to_what;
		};

		const replacement_t replacements[] = 
		{
			{ XML_T( "&amp;" ),  5, char_t('&') },
			{ XML_T( "&lt;" ),   4, char_t('<') },
			{ XML_T( "&gt;" ),   4, char_t('>') },
			{ XML_T( "&quot;" ), 6, char_t('\"') },
			{ XML_T( "&apos;" ), 6, char_t('\'') }
		};

		extern std::locale xml_locale__;

		inline bool is_alpha( char_t ch )
		{
			return std::isalpha( ch, xml_locale__ );
		}
	
		inline bool is_alphanum( char_t ch )
		{
			return std::isalnum( ch, xml_locale__ );
		}

		inline bool is_symbol( char_t ch )
		{
			return ( 
				is_alphanum( ch )
				|| ( ch != char_t( '<' ) && ch != char_t( '>' ) )
				);
		}

		inline char_t to_lower( char_t ch )
		{
			return std::tolower( ch, xml_locale__ );
		}

		inline char_t to_upper( char_t ch )
		{
			return std::toupper( ch, xml_locale__ );
		}

		inline char_t is_space( char_t ch )
		{
			return ( 
				std::isspace( ch, xml_locale__ )
				|| ch == char_t( '\r' )
				);
		}

		template < bool ignore_case >
		inline bool string_compare( const char_t * src, const char_t * dst )
		{
			return xml_strcmp( src, dst ) == 0;
		} 

		template <>
		inline bool string_compare< true >( const char_t * src, const char_t * dst )
		{
			return xml_strcmp_i( src, dst ) == 0;
		} 

		template < bool ignore_case >
		inline bool string_n_compare( const char_t * src, const char_t * dst, size_t len )
		{
			return xml_strcmp_n( src, dst, len ) == 0;
		} 

		template <>
		inline bool string_n_compare< true >( const char_t * src, const char_t * dst, size_t len )
		{
			return xml_strcmp_i_n( src, dst, len ) == 0;
		}

		const replacement_t * get_replacment( const char_t * str );
		const char_t * get_char( const char_t * src, char_t * dst, size_t& len );
		const char_t * skip_space( const char_t * str );
		const char_t * read_content( const char_t * str, const string_t& end, parsing_context& ctx, string_t& dest ); 
		const char_t * read_content_fast( const char_t * str, const char_t end, 
			parsing_context& ctx, string_t& dest );

		template < typename T, T parsing_context::* memb >
		struct parsing_context_state
		{
			parsing_context& ctx_;
			T tmp_;

			explicit parsing_context_state( parsing_context& ctx ) : ctx_(ctx), tmp_( ctx.*memb ) {}
			~parsing_context_state() { ctx_.*memb = tmp_; }

		protected :
			const parsing_context_state& operator = ( const parsing_context_state& );
		};
	}
}

#endif /* __HDR_MYXML_DETAIL_HPP__ */
