#include "../myxml.hpp"
#include "grammar.hpp"

namespace myxml
{
	namespace detail
	{
		std::locale xml_locale__;

		const replacement_t * get_replacment( const char_t * str )
		{
			static const size_t size = sizeof( replacements ) / sizeof( replacements[0] );
			for ( size_t ii = 0; ii < size; ++ii )
			{
				if ( string_n_compare<true>( str, replacements[ii].value, replacements[ii].len ) )
					return &replacements[ii];
			}

			return NULL;
		}

		const char_t * get_char( const char_t * src, char_t * dst, size_t& len )
		{
			if ( *src == grammar::ampersand ) // "&????;"
			{
				const char_t * next = src + 1;
				if ( *next++ == grammar::dies ) // "&#???;"
				{
					int radix = 10;
					if ( *next == grammar::smX || *next == grammar::grX ) // "&#x??;"
					{
						radix = 16;
						++next;
					}

					char_t * colon = 0;
					long value = xml_strtol( next, &colon, radix );
					if ( !colon || *colon != grammar::colon )
						return NULL;

					src = colon + 1;
					*dst = (char_t)value; // or (char)value; ??
					len = 1;
				}
				else
				{

					const replacement_t * repl = get_replacment( src );
					*dst = repl ? ( src += repl->len, repl->to_what ) : *src;
					len = 1;
				}
			}		

			return src;
		}

		const char_t * skip_space( const char_t * str )
		{
			if ( !str || !*str )
				return str;

			while ( *str && is_space( *str ) )
				++str;

			return str;
		}

		const char_t * read_content( const char_t * str, const string_t& end, parsing_context& ctx, string_t& dest )
		{
			const char_t * end_text = end.c_str();
			const string_t::size_type end_len = end.length();

			if ( !ctx.skip_whitespace )
			{
				while ( *str && !string_n_compare< false >( str, end_text, end_len ) )
				{
					size_t len = 0;
					char_t buffer[ 4 ] = { 0 };
					if ( *str == grammar::ampersand ) // &????
					{
						str = get_char( str, buffer, len );
						if ( str && len != 0 )
							dest.append( buffer, len );
						else
							return NULL;
					}
					else 
						dest += *str++;
				}
			}
			else
			{
				str = skip_space( str );
				while ( *str && !string_n_compare< false >( str, end_text, end_len ) )
				{
					size_t len = 0;
					char_t buffer[ 4 ] = { 0 };
					if ( *str == grammar::ampersand ) // &????
					{
						str = get_char( str, buffer, len );
						dest.append( buffer, len );
					}
					else 
						dest += *str++;

					str = skip_space( str );
				}
			}
			return str + end_len;
			//return str;
		}		

		const mxml_char_t * read_content_fast( const char_t * str, const char_t end, 
			parsing_context& /* ctx */, string_t& dest )
		{
#define STR_BUF_SIZE 512
#define SMALL_STR_BUF_SIZE 4

			mxml_char_t local_buffer[ STR_BUF_SIZE ] = { '\0' };
			size_t local_len = 0;

			//if ( ctx->skip_whitespace )
			//	str = skip_space( str );

			while ( *str && end != *str )
			{
				size_t len = 0;
				mxml_char_t buffer[ SMALL_STR_BUF_SIZE ] = { 0 };

				if ( *str == grammar::ampersand ) // &????
				{
					str = get_char( str, buffer, len );
					if ( str && len != 0 )	
					{
						if ( local_len >= STR_BUF_SIZE - SMALL_STR_BUF_SIZE ) 
						{
							dest.append( local_buffer, local_len );
							local_len = 0;
						}
						xml_strncpy( &local_buffer[local_len], buffer, len );
						local_len += len;
					}
					else
						return NULL;
				}
				else 
				{
					if ( local_len >= STR_BUF_SIZE - 1 ) 
					{
						dest.append( local_buffer, local_len );
						local_len = 0;
					}

					local_buffer[local_len++] = *str++;
				}		

				//if ( ctx->skip_whitespace )
				//	str = skip_space( str );
			}

			dest.append( local_buffer, local_len );

			return str + 1;
#undef STR_BUF_SIZE
#undef SMALL_STR_BUF_SIZE
		}
	}
}
