#include "xpath_parser.h"
#include "../detail.h"

static const mxml_string_t attr = { XML_T("attribute::"), 11 };
static const mxml_string_t child = { XML_T("child::"), 7 };
static const mxml_string_t parent = { XML_T("parent::"), 8 };

/*
	заполняет структуру match данными о XPath выражении

	входные данные : 
		str - XPath выражение
		m - указатель на заполняемую структура

	на выходе : 0 в случае успеха, иначе - целое, отличное от 0
*/
int identify_match( const mxml_char_t *str, match *m )
{
	if ( !m )
		return -1;

	m->type = x_unknown;
	if ( m->value.len || m->value.str )
	{
		free_str( &m->value );
	}
	init_str( &m->value );

	if ( *str )
	{
		/* определим тип выражения */
		size_t len = 0;
		m->type = identify_axis( str, &m->value, &len );
		str += len;
	}
	else 
		return -1;

	/* если присутствует предикат */
	if ( *str && *str == (mxml_char_t)('[') )
	{
		/* сформируем предикат */
		if ( 0 != identify_predicate( str, &m->pred ) )
			return -1;

		/* установим флаг использования предиката */
		m->use_pred = 1;
	}		
	else 
		m->use_pred = 0;

	return 0;
}

x_type identify_axis( const mxml_char_t * str, mxml_string_t *cond, size_t* len )
{
	x_type t = x_unknown;

	/* инициализация условия по умолчанию */
	assign_cstr_len( cond, XML_T("*"), 1 );

	/* если задан атрибут */
	if ( *str == (mxml_char_t)('@') )
	{
		t = x_attribute;
		*len = 1;
	}
	else 
	{
		/* иначе определим тип условия */
		if ( xml_strcmp_n( str, attr.str, attr.len ) == 0 )
		{ t = x_attribute; *len = attr.len; }
		else if ( xml_strcmp_n( str, child.str, child.len ) == 0 )
		{ t = x_child; *len = child.len; }
		else if ( xml_strcmp_n( str, parent.str, parent.len ) == 0 )
		{ t = x_parent; *len = parent.len; }										
	}
	str += *len; /* сдвиг текущего положения в анализируемой строке */

	/* 
		если далее идет не предикат, то возможно это условие
		например 'child::elem_name'
	*/
	if ( *str && (*str != (mxml_char_t)('[') ) )
	{		
		size_t cond_len = 0;

#ifdef _0
		/* чего то я перемудрил */

		const mxml_char_t * delim2 = NULL;
		const mxml_char_t * delim = xml_strchr( str, (mxml_char_t)('[') );

		/* если предиката в строке не найдено */
		if ( delim == NULL )
		{
			/* 
				найдем символ '=', как признак окончания условия 
				например при анализе предиката - '[@some_attr="value"]'
			*/
			delim = xml_strchr( str, (mxml_char_t)('=') );				
		}
		
		/* 
			для случая анализа предиката учтем ']' как окончание условия, если '=' не был найден 
			например '[attribute::some_attr]'
		*/
		delim2 = xml_strchr( str, (mxml_char_t)(']') );
		if ( delim && delim2 )
			delim = delim > delim2 ? delim2 : delim;
		else
			delim = delim < delim2 ? delim2 : delim;

		cond_len = ( delim == NULL ? xml_strlen( str ) : (size_t)(delim - str) );
#endif

		const mxml_char_t * delim = str;

		/* найдем конец условия */
		while ( 
			*delim 
			&& *delim != (mxml_char_t)('[')
			&& *delim != (mxml_char_t)('=')
			&& *delim != (mxml_char_t)(']')
			&& !detail_isspace( *delim ) )
		{
			++delim;
		}

		cond_len = (size_t)(delim - str);
		assign_cstr_len( cond, str, cond_len );
		*len += cond_len;
	}

	return t;
}

int identify_predicate( const mxml_char_t * str, predicate *pred )
{
	if ( !*str || *str != (mxml_char_t)('[') )
		return -1;

	str = skip_space( str );
	if ( !str || !*str )
		return -1;
	else
	{
		size_t len = 0;
		mxml_string_t cond = { NULL, 0 };	

		/* при анализе предиката пропустим первый '[' символ и используем identify_axis */
		x_type t = identify_axis( ++str, &cond, &len );
		str += len;

		pred->single = 0;
		pred->type = t;
		pred->value.str = cond.str;
		pred->value.len = cond.len;	
		pred->cond = 0;

		str = skip_space( str );

		/* есть  */
		if ( str && *str == (mxml_char_t)( '=' ) )
		{
			mxml_char_t comma;
			const mxml_char_t * end_comma = NULL;

			str = skip_space( ++str );
			comma = *str++;
			end_comma = xml_strchr( str, comma );
			if ( end_comma != NULL )
			{
				assign_cstr_len( &pred->cond_value, str, (size_t)(end_comma - str) );
				pred->cond = 1;

				return 0;
			}

			return -1;
		}
		
		return 0;
	}

	/* unreachable code */
	//return -1;
}
