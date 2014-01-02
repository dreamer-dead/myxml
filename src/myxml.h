/**
* \file myxml.h
* Основной заголовочный файл проекта.
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
* Выделяет память и создает объект типа mxml_node.
* @param value - строковое значение объекта.
* @param parent - родитель объекта в иерархии.
* @see mxml_char_t
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_node			( const mxml_char_t* value, mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_attribute( значение атрибута пустое ).
* @param value - имя XML атрибута.
* @param parent - родитель объекта в иерархии.
* @see mxml_char_t
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_attribute	( const mxml_char_t* name,  mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_element.
* @param value - имя XML элемента.
* @param parent - родитель объекта в иерархии.
* @see mxml_char_t
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_element		( const mxml_char_t* value, mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_comment.
* @param parent - родитель объекта в иерархии.
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_comment		( mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_text.
* @param parent - родитель объекта в иерархии.
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_text			( mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_unknown.
* @param parent - родитель объекта в иерархии.
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_unknown		( mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_declaration.
* @param parent - родитель объекта в иерархии.
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_declaration	( mxml_node * parent );

/**
* Выделяет память и создает объект типа mxml_node, представляющий mxml_document.
* @param value - имя файла документа.
* @see mxml_node
* @return созданный и инициализированный объект или NULL  в случае неудачи.
*/
mxml_node * create_document		( const mxml_char_t* value );


/**
* Присоединяет заданный узел n последним ребенком(child) узла to.
* @param to - узел-родитель(parent).
* @param n - узел-ребенок(child).
* @see mxml_node
* @return нет возвращаемого значения.
*/
void append_child( mxml_node * to, mxml_node * n );

/**
* Присоединяет заданный узел n перед указанным ребенком before родительского узла to.
* @param parent - узел-родитель(parent).
* @param n - узел-ребенок(child).
* @param before - узел-ребенок(child), перед которым будет произведена вставка.
* @see mxml_node
* @return нет возвращаемого значения.
*/
void append_before_child( mxml_node * parent, mxml_node * n, mxml_node * before );

/**
* Присоединяет заданный узел n после указанного ребенка before родительского узла to.
* @param parent - узел-родитель(parent).
* @param n - узел-ребенок(child).
* @param after - узел-ребенок(child), после которого будет произведена вставка.
* @see mxml_node
* @return нет возвращаемого значения.
*/
void append_after_child( mxml_node * parent, mxml_node * n, mxml_node * after );

/**
* Удаляет заданный узел n из списка детей узла to.
* Освобождение памяти не производится.
* @param parent - узел-родитель(parent).
* @param n - узел-ребенок(child).
* @see mxml_node
* @return нет возвращаемого значения.
*/
void remove_child( mxml_node * parent, mxml_node * n );

/**
* Освобождает память объекта.
* @param n - указатель на освобождаемый объект.
* @see mxml_node
* @return нет возвращаемого значения.
*/
void node_destroy( mxml_node * n );

/**
* Выводит значение узла в заданный дескриптором file поток.
* @param node - выводимый узел.
* @param file - поток вывода.
* @see mxml_node
* @see FILE
* @return нет возвращаемого значения.
*/
void node_print_out( mxml_node * node, FILE * file );

/**
* Находит один элемент по заданному XPath(1.0) выражению относительно заданного узла.
* @param node - начальный узел.
* @param path - XPath выражение.
* @see mxml_node
* @see mxml_char_t
* @see XPath
* @return найденный элемент, либо NULL.
*/
mxml_node * node_find_single( mxml_node *node, const mxml_char_t * path );

/**
* Находит все элементы по заданному XPath(1.0) выражению относительно заданного узла.
* @param node - начальный узел.
* @param path - XPath выражение.
* @param lst - список, содержащий найденные элементы.
* @see mxml_node
* @see mxml_char_t
* @see list_type
* @see XPath
* @return 0 в случае успеха, иначе ненулевое значение.
*/
int node_find( mxml_node *node, const mxml_char_t * path, list_type *lst );

/**
* Добавляет заданный XML атрибут к элементу.
* Копирование не производится, как и отсоединение от предыдущего элемента-владельца.
* @param node - элемент-родитель(parent).
* @param attr - XML атрибут.
* @see mxml_node
* @return указатель на добавленный атрибут, либо NULL.
*/
mxml_node * element_add_attribute( mxml_node *node, mxml_node * attr );

/**
* Возвращает первый атрибут элемента.
* @param node - элемент-родитель(parent).
* @see mxml_node
* @return указатель на первый атрибут, либо NULL, если нет атрибутов.
*/
mxml_node * element_first_attribute( mxml_node * node );

/**
* Возвращает атрибут элемента с заданным именем.
* @param node - элемент-родитель(parent).
* @param value - имя искомого атрибута.
* @see mxml_node
* @return указатель на найденный атрибут, либо NULL.
*/
mxml_node * element_find_attribute( mxml_node * node, const mxml_char_t * value );

/**
* Возвращает элемент, представляющий текст заданного элемента.
* @param node - элемент-родитель(parent).
* @see mxml_node
* @return указатель на найденный атрибут, либо NULL.
*/
mxml_node * element_get_text( mxml_node * node );

/**
* Устанавливает описание ошибки для документа.
* @param doc - XML документ.
* @param errdescr - описание ошибки.
* @see mxml_node
* @return всегда NULL.
*/
const mxml_char_t *document_set_error( mxml_node *doc, const mxml_char_t * errdescr );

/**
* Сбрасывает данные об ошибках XML документа.
* @param doc - XML документ.
* @see mxml_node
* @return нет возвращаемого значения.
*/
void document_clear_error( mxml_node * doc );

/**
* Загружает XML документ из файла с именем, заданным в поле value структуры doc.
* @param doc - XML документ.
* @see mxml_node
* @return 0 в случае успеха, иначе ненулевое значение.
*/
int document_load( mxml_node * doc );

/**
* Инициализирует XML документ содержимым параметра content.
* @param doc - XML документ.
* @param content - содержимое XML документа.
* @see mxml_node
* @return 0 в случае успеха, иначе ненулевое значение.
*/
int document_load_content( mxml_node * doc, const mxml_char_t * content );

/**
* Сохраняет содержимое XML документа в файл с именем, заданным параметром fname.
* @param doc - XML документ.
* @param fname - имя файла.
* @see mxml_node
* @return 0 в случае успеха, иначе ненулевое значение.
*/
int document_save( mxml_node * doc, const mxml_char_t * fname );

#ifdef __cplusplus
}
/* END extern "C" { */
#endif

#endif /* __HDR_MYXML_C_H__ */
