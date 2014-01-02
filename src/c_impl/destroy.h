/**
* \file destroy.h
* Заголовочный файл функций для удаления структур данных.
* Делетеры для определенных узлов документа. вызываются из node_destroy().
* Для внутреннего использования.
*/

#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_DESTROY_C_H__
#define __HDR_MYXML_DESTROY_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
* освобождает ресурсы mxml_declaration.
* @param decl - указатель на структуру.
* @see mxml_declaration
* @return нет возвращаемого значения.
*/
void destroy_declaration( mxml_declaration	*decl	); /* освобождает ресурсы mxml_declaration */

/**
* освобождает ресурсы mxml_element.
* @param elem - указатель на структуру.
* @see mxml_element
* @return нет возвращаемого значения.
*/
void destroy_element	( mxml_element		*elem	); /* освобождает ресурсы mxml_element */

/**
* освобождает ресурсы mxml_attribute.
* @param attr - указатель на структуру.
* @see mxml_attribute
* @return нет возвращаемого значения.
*/
void destroy_attribute	( mxml_attribute	*attr	); /* освобождает ресурсы mxml_attribute */

/**
* освобождает ресурсы mxml_document.
* @param doc - указатель на структуру.
* @see mxml_document
* @return нет возвращаемого значения.
*/
void destroy_document	( mxml_document		*doc	); /* освобождает ресурсы mxml_document */

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_DESTROY_C_H__ */
