/**
* \file detail.c
* Заголовочный файл структур и функций для работой со строками и символами.
*/

#include <stddef.h>
#include "../myxml.h"
#include "../config.h"
#include "detail.h"
#include "grammar.h"

/** 
* Таблица соответствий спецсимволов.
*/
static const replacement_t replacements[] = 
{
	{ XML_T( "&amp;" ),  5, (mxml_char_t)('&')  },
	{ XML_T( "&lt;" ),   4, (mxml_char_t)('<')  },
	{ XML_T( "&gt;" ),   4, (mxml_char_t)('>')  },
	{ XML_T( "&quot;" ), 6, (mxml_char_t)('\"') },
	{ XML_T( "&apos;" ), 6, (mxml_char_t)('\'') }
};

const replacement_t * get_replacment( const mxml_char_t * str )
{
	static const size_t size = sizeof( replacements ) / sizeof( replacements[0] );

	size_t ii = 0;
	for ( ; ii < size; ++ii )
	{
		if ( xml_strcmp_i_n( str, replacements[ii].value, replacements[ii].len ) == 0 )
			return &replacements[ii];
	}

	return NULL;
}

const mxml_char_t * get_char( const mxml_char_t * src, mxml_char_t * dst, size_t* len )
{
	if ( *src == ampersand ) // "&????;"
	{
		const mxml_char_t * next = src + 1;
		if ( *next++ == dies ) // "&#???;"
		{
			mxml_char_t * colon = 0;
			int radix = 10;
			long value = 0;

			if ( *next == smX || *next == grX ) // "&#x??;"
			{
				radix = 16;
				++next;
			}
			
			value = xml_strtol( next, &colon, radix );
			if ( !colon )
				return NULL;

			src = colon + 1;
			*dst = (mxml_char_t)value; //1
			*len = 1;
		}
		else
		{
			const replacement_t * repl = get_replacment( src );
			*dst = repl ? ( src += repl->len, repl->to_what ) : *src;
			*len = 1;
		}
	}		

	return src;
}

const mxml_char_t * skip_space( const mxml_char_t * str )
{
	if ( !str || !*str )
		return str;

	while ( *str && detail_isspace( *str ) )
		++str;

	return str;
}

const mxml_char_t * read_content( 
						const mxml_char_t * str, 
						const mxml_char_t* end, size_t end_len,
						parsing_context* ctx, 
						mxml_string_t* dest )
{
#define STR_BUF_SIZE 512
#define SMALL_STR_BUF_SIZE 4
	
	mxml_char_t local_buffer[ STR_BUF_SIZE ] = { '\0' };
	size_t local_len = 0;

	if ( ctx->skip_whitespace )
		str = skip_space( str );

	while ( *str && !(xml_strcmp_n( str, end, end_len ) == 0) )
	{
		size_t len = 0;
		mxml_char_t buffer[ SMALL_STR_BUF_SIZE ] = { 0 };

		if ( *str == ampersand ) // &????
		{
			str = get_char( str, buffer, &len );
			if ( str && len != 0 )	
			{
				if ( local_len >= STR_BUF_SIZE - SMALL_STR_BUF_SIZE ) 
				{
					append_str( dest, local_buffer, local_len );
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
				append_str( dest, local_buffer, local_len );
				local_len = 0;
			}

			local_buffer[local_len++] = *str++;
		}		

		if ( ctx->skip_whitespace )
			str = skip_space( str );
	}

	append_str( dest, local_buffer, local_len );

	return str + end_len;
#undef STR_BUF_SIZE
#undef SMALL_STR_BUF_SIZE
}

void file_write_content( mxml_string_t* str_ptr, FILE *file )
{
	if ( !file || !str_ptr || !str_ptr->len )
		return;
	else
	{
		mxml_char_t *str = str_ptr->str;
		const mxml_char_t *begin = str_ptr->str;
		size_t count = 0;

#define MAP_SIZE 256 >> 3
		static const size_t map_size = MAP_SIZE;		
		unsigned char map[ MAP_SIZE ];
#undef MAP_SIZE

		/* Clear control map */
		for (count = 0; count < map_size; ++count)
			map[ count ] = 0;

		/* Set bits in delimiter table */
		for ( count = 0; count < 5; ++count )
		{
			unsigned char c = (unsigned char)replacements[count].to_what;
			map[ c >> 3 ] |= (1 << (c & 7));
		}

		while ( *str && *begin )
		{
			/* Find beginning of token (skip over leading delimiters). Note that
			* there is no token if this loop sets str to point to the terminal
			* null (*str == '\0') */	

#ifndef XML_UNICODE
			while ( !(map[*str >> 3] & (1 << (*str & 7))) && *str )
				++str;
#else
			while ( *str > 255 || ( !(map[*str >> 3] & (1 << (*str & 7))) && *str ) )
				++str;
#endif

			if ( *str )
			{
				mxml_char_t old_char = *str;
				/* Find the replacement */
				for ( count = 0; (count < 5) && (replacements[count].to_what != old_char); ++count )
				{}

				/* Print out string and replacement */
				*str = (mxml_char_t)( '\0' );
				xml_fprintf( file, XML_T("%s%s"), begin, replacements[count].value );
				*str = old_char;
				begin = ++str;
			}		
			else
			{
				xml_fprintf( file, XML_T("%s"), begin );
			}
		}		
	}
}
