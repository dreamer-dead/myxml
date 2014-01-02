/**
* \file detail.h
* Заголовочный файл структур и функций для работой со строками и символами.
*/

#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_DETAIL_C_H__
#define __HDR_MYXML_DETAIL_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include "../myxml.h"
#include "mxml_string.h"

/** 
* Макрос для проверки вхождения символа в диапазон букв алфавита.
*/
#define detail_isalpha( c ) isalpha( (c) )

/** 
* Макрос для проверки вхождения символа в диапазон букв алфавита либо цифр.
*/
#define detail_isalphaum( c ) isalnum( (c) )

/** 
* Макрос для проверки символа.
*/
#define detail_issymbol( c ) (isalnum( (c) ) || ( (c) != (mxml_char_t)( '<' ) && (c) != (mxml_char_t)( '>' ) ) )

/** 
* Макрос для получения символа в верхнем регистре.
*/
#define detail_toupper( c ) toupper( (c) )

/** 
* Макрос для получения символа в нижнем регистре.
*/
#define detail_tolower( c ) tolower( (c) )

/** 
* Макрос для проверки пробелов, табуляций и переводов строк.
*/
#define detail_isspace( c ) ( isspace( (c) ) || ( (c) == (mxml_char_t)( '\r' ) || (c) == (mxml_char_t)( '\n' ) ) )


/** 
* Структура соответствия символа специальным символам HTML.
*/
typedef struct replacement_tag
{
	const mxml_char_t * value;	/**< спецсимвол HTML */
	size_t len;					/**< длина спецсимвола */
	mxml_char_t to_what;		/**< соответствующий символ */
} replacement_t;

/**
* Находит структуру соответствия для заданного спецсимвола HTML.
* @param str - значение спецсимвола HTML.
* @see replacement_t
* @return найденную структуру замены, либо NULL.
*/
const replacement_t * get_replacment( const mxml_char_t * str );

/**
* Заменяет спецсимвол HTML на его символьное представление.
* @param str - значение спецсимвола HTML.
* @param dst - буфер с результатом.
* @param str - длина результирующей строки( на данный моменит всегда 1 в случае успеха ).
* @return указатель на первый символ во входной строке после обработанных, либо NULL в случае неудачи.
*/
const mxml_char_t * get_char( const mxml_char_t * src, mxml_char_t * dst, size_t* len );

/**
* Пропускает в заданной строке все пробелы( пробелы, табуляции, переводы строк ).
* @param str - входная строка.
* @return указатель на первый символ в заданной строке, не являющийся пробелом.
*/
const mxml_char_t * skip_space( const mxml_char_t * str );

/**
* Переводит строку, содержащую спецсимволы HTML в символьное представление.
* Разбор производится до встречи терминальной последовательности.
* @param str - строка, сожержащая спецсимволы HTML.
* @param end - строка, сожержащая терминальную последовательность.
* @param end_len - длина терминальной последовательности.
* @param ctx - контекст парсинга.
* @param dest - принимающий буфер.
* @see parsing_context
* @see mxml_string_t
* @return указатель на первый символ во входной строке после терминальной последовательности, либо NULL в случае неудачи.
*/
const mxml_char_t * read_content( 
						const mxml_char_t * str, 
						const mxml_char_t* end, size_t end_len, 
						parsing_context* ctx, 
						mxml_string_t* dest );

/**
* Выводит заданную строку в файл, заменяя символы.
* @param str - входная строка.
* @param file - поток вывода.
* @see mxml_string_t
* @see FILE
* @return нет возвращаемого значения.
*/
void file_write_content( mxml_string_t* str, FILE *file );

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_DETAIL_C_H__ */
