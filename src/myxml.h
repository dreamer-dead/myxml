/**
* \file myxml.h
* �������� ������������ ���� �������.
*/

#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_C_H__
#define __HDR_MYXML_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "./config.h"
#include "./c_impl/types.h"
#include <stdio.h>

/**
* �������� ������ � ������� ������ ���� mxml_node.
* @param value - ��������� �������� �������.
* @param parent - �������� ������� � ��������.
* @see mxml_char_t
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_node			( const mxml_char_t* value, mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_attribute( �������� �������� ������ ).
* @param value - ��� XML ��������.
* @param parent - �������� ������� � ��������.
* @see mxml_char_t
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_attribute	( const mxml_char_t* name,  mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_element.
* @param value - ��� XML ��������.
* @param parent - �������� ������� � ��������.
* @see mxml_char_t
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_element		( const mxml_char_t* value, mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_comment.
* @param parent - �������� ������� � ��������.
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_comment		( mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_text.
* @param parent - �������� ������� � ��������.
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_text			( mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_unknown.
* @param parent - �������� ������� � ��������.
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_unknown		( mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_declaration.
* @param parent - �������� ������� � ��������.
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_declaration	( mxml_node * parent );

/**
* �������� ������ � ������� ������ ���� mxml_node, �������������� mxml_document.
* @param value - ��� ����� ���������.
* @see mxml_node
* @return ��������� � ������������������ ������ ��� NULL  � ������ �������.
*/
mxml_node * create_document		( const mxml_char_t* value );


/**
* ������������ �������� ���� n ��������� ��������(child) ���� to.
* @param to - ����-��������(parent).
* @param n - ����-�������(child).
* @see mxml_node
* @return ��� ������������� ��������.
*/
void append_child( mxml_node * to, mxml_node * n );

/**
* ������������ �������� ���� n ����� ��������� �������� before ������������� ���� to.
* @param parent - ����-��������(parent).
* @param n - ����-�������(child).
* @param before - ����-�������(child), ����� ������� ����� ����������� �������.
* @see mxml_node
* @return ��� ������������� ��������.
*/
void append_before_child( mxml_node * parent, mxml_node * n, mxml_node * before );

/**
* ������������ �������� ���� n ����� ���������� ������� before ������������� ���� to.
* @param parent - ����-��������(parent).
* @param n - ����-�������(child).
* @param after - ����-�������(child), ����� �������� ����� ����������� �������.
* @see mxml_node
* @return ��� ������������� ��������.
*/
void append_after_child( mxml_node * parent, mxml_node * n, mxml_node * after );

/**
* ������� �������� ���� n �� ������ ����� ���� to.
* ������������ ������ �� ������������.
* @param parent - ����-��������(parent).
* @param n - ����-�������(child).
* @see mxml_node
* @return ��� ������������� ��������.
*/
void remove_child( mxml_node * parent, mxml_node * n );

/**
* ����������� ������ �������.
* @param n - ��������� �� ������������� ������.
* @see mxml_node
* @return ��� ������������� ��������.
*/
void node_destroy( mxml_node * n );

/**
* ������� �������� ���� � �������� ������������ file �����.
* @param node - ��������� ����.
* @param file - ����� ������.
* @see mxml_node
* @see FILE
* @return ��� ������������� ��������.
*/
void node_print_out( mxml_node * node, FILE * file );

/**
* ������� ���� ������� �� ��������� XPath(1.0) ��������� ������������ ��������� ����.
* @param node - ��������� ����.
* @param path - XPath ���������.
* @see mxml_node
* @see mxml_char_t
* @see XPath
* @return ��������� �������, ���� NULL.
*/
mxml_node * node_find_single( mxml_node *node, const mxml_char_t * path );

/**
* ������� ��� �������� �� ��������� XPath(1.0) ��������� ������������ ��������� ����.
* @param node - ��������� ����.
* @param path - XPath ���������.
* @param lst - ������, ���������� ��������� ��������.
* @see mxml_node
* @see mxml_char_t
* @see list_type
* @see XPath
* @return 0 � ������ ������, ����� ��������� ��������.
*/
int node_find( mxml_node *node, const mxml_char_t * path, list_type *lst );

/**
* ��������� �������� XML ������� � ��������.
* ����������� �� ������������, ��� � ������������ �� ����������� ��������-���������.
* @param node - �������-��������(parent).
* @param attr - XML �������.
* @see mxml_node
* @return ��������� �� ����������� �������, ���� NULL.
*/
mxml_node * element_add_attribute( mxml_node *node, mxml_node * attr );

/**
* ���������� ������ ������� ��������.
* @param node - �������-��������(parent).
* @see mxml_node
* @return ��������� �� ������ �������, ���� NULL, ���� ��� ���������.
*/
mxml_node * element_first_attribute( mxml_node * node );

/**
* ���������� ������� �������� � �������� ������.
* @param node - �������-��������(parent).
* @param value - ��� �������� ��������.
* @see mxml_node
* @return ��������� �� ��������� �������, ���� NULL.
*/
mxml_node * element_find_attribute( mxml_node * node, const mxml_char_t * value );

/**
* ���������� �������, �������������� ����� ��������� ��������.
* @param node - �������-��������(parent).
* @see mxml_node
* @return ��������� �� ��������� �������, ���� NULL.
*/
mxml_node * element_get_text( mxml_node * node );

/**
* ������������� �������� ������ ��� ���������.
* @param doc - XML ��������.
* @param errdescr - �������� ������.
* @see mxml_node
* @return ������ NULL.
*/
const mxml_char_t *document_set_error( mxml_node *doc, const mxml_char_t * errdescr );

/**
* ���������� ������ �� ������� XML ���������.
* @param doc - XML ��������.
* @see mxml_node
* @return ��� ������������� ��������.
*/
void document_clear_error( mxml_node * doc );

/**
* ��������� XML �������� �� ����� � ������, �������� � ���� value ��������� doc.
* @param doc - XML ��������.
* @see mxml_node
* @return 0 � ������ ������, ����� ��������� ��������.
*/
int document_load( mxml_node * doc );

/**
* �������������� XML �������� ���������� ��������� content.
* @param doc - XML ��������.
* @param content - ���������� XML ���������.
* @see mxml_node
* @return 0 � ������ ������, ����� ��������� ��������.
*/
int document_load_content( mxml_node * doc, const mxml_char_t * content );

/**
* ��������� ���������� XML ��������� � ���� � ������, �������� ���������� fname.
* @param doc - XML ��������.
* @param fname - ��� �����.
* @see mxml_node
* @return 0 � ������ ������, ����� ��������� ��������.
*/
int document_save( mxml_node * doc, const mxml_char_t * fname );

#ifdef __cplusplus
}
/* END extern "C" { */
#endif

#endif /* __HDR_MYXML_C_H__ */
