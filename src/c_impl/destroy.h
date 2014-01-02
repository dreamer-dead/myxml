/**
* \file destroy.h
* ������������ ���� ������� ��� �������� �������� ������.
* �������� ��� ������������ ����� ���������. ���������� �� node_destroy().
* ��� ����������� �������������.
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
* ����������� ������� mxml_declaration.
* @param decl - ��������� �� ���������.
* @see mxml_declaration
* @return ��� ������������� ��������.
*/
void destroy_declaration( mxml_declaration	*decl	); /* ����������� ������� mxml_declaration */

/**
* ����������� ������� mxml_element.
* @param elem - ��������� �� ���������.
* @see mxml_element
* @return ��� ������������� ��������.
*/
void destroy_element	( mxml_element		*elem	); /* ����������� ������� mxml_element */

/**
* ����������� ������� mxml_attribute.
* @param attr - ��������� �� ���������.
* @see mxml_attribute
* @return ��� ������������� ��������.
*/
void destroy_attribute	( mxml_attribute	*attr	); /* ����������� ������� mxml_attribute */

/**
* ����������� ������� mxml_document.
* @param doc - ��������� �� ���������.
* @see mxml_document
* @return ��� ������������� ��������.
*/
void destroy_document	( mxml_document		*doc	); /* ����������� ������� mxml_document */

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_DESTROY_C_H__ */
