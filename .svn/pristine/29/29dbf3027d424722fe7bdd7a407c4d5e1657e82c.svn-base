#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_GRAMMAR_HPP__
#define __HDR_MYXML_GRAMMAR_HPP__

#include "../myxml.hpp"
#include "detail.hpp"

namespace myxml 
{	
	namespace detail 
	{
		bool is_element_impl( const char_t *& str );
	}	

	struct grammar
	{
		struct tag 
		{
			const char_t *value;
			size_t length;
		};

	protected :		

		static const tag header_tag;
		static const tag comment_tag;
		static const tag comment_end_tag;
		static const tag dtd_tag;		

	public :

		static const char_t underscore	= char_t( '_' );
		static const char_t less		= char_t( '<' );
		static const char_t greater		= char_t( '>' );
		static const char_t ampersand	= char_t( '&' );
		static const char_t dies		= char_t( '#' );
		static const char_t smX			= char_t( 'x' );
		static const char_t grX			= char_t( 'X' );
		static const char_t colon		= char_t( ';' );
		static const char_t equal		= char_t( '=' );
		static const char_t single_quote= char_t( '\'' );
		static const char_t dbl_quote	= char_t( '\"' );
		static const char_t slash		= char_t( '/' );
		static const char_t minus		= char_t( '-' );

		template < typename T >
		static inline bool is( const char_t * str, size_t& len ) { return false; }		

		template < typename T >
		static inline bool is( const char_t * str )
		{
			size_t length = 0;
			return is< T >( str, length );
		}		

		static inline bool is_end_comment( const char_t * str, size_t& len ) 
		{ 
			return ( 
				detail::string_n_compare<false>( str, grammar::comment_end_tag.value, grammar::comment_end_tag.length ) 
				&& (len = grammar::comment_end_tag.length) > 0 );
		}
	};

	template <> 
	inline bool grammar::is< element >( const char_t * str ) 
	{
		return ( 
			detail::is_element_impl( str )
			); 
	}	

	template <> 
	inline bool grammar::is< comment >( const char_t * str, size_t& len ) 
	{
		return ( 
			detail::string_n_compare<false>( str, comment_tag.value, comment_tag.length ) 
			&& (len = comment_tag.length) > 0 ); 
	}

	template <> 
	inline bool grammar::is< declaration >( const char_t * str, size_t& len ) 
	{
		return ( 
			detail::string_n_compare<true>( str, header_tag.value, header_tag.length ) 
			&& (len = header_tag.length) > 0 ); 
	}

	template <> 
	inline bool grammar::is< unknown >( const char_t * str, size_t& len ) 
	{
		return ( 
			detail::string_n_compare<false>( str, dtd_tag.value, dtd_tag.length ) 
			&& (len = dtd_tag.length) > 0 ); 
	}

	template <> 
	inline bool grammar::is< text >( const char_t * str, size_t& len ) 
	{
		len = 0;
		return ( 
			*str && (detail::is_space(*str) || detail::is_symbol(*str))
			); 
	}

	template <> 
	inline bool grammar::is< element >( const char_t * str, size_t& len ) 
	{
		const char_t * begin = str;

		//if ( grammar::is< element >( str ) )
		if ( detail::is_element_impl( str ) )
		{
			len = static_cast< size_t >( str - begin );
			while ( *str && !detail::is_space( *str++ ) )
				++len;

			return true;
		}

		return false;
	}
}

#endif /* __HDR_MYXML_GRAMMAR_HPP__ */
