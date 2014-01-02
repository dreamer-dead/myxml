/**
* \file types.h
* Заголовочный файл основных структур данных.
*/

#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_TYPES_C_H__
#define __HDR_MYXML_TYPES_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../config.h"
#include "mxml_string.h"

/**
* Позиция в файле.
*/
typedef struct 
{
	int row; /**< строка */
	int col; /**< столбец */
} position_t;

/**
* Перечисление типов узлов.
*/
typedef enum 
{
	type_node,			/**< базовый узел		*/
	type_document,		/**< документ			*/
	type_element,		/**< элемент			*/
	type_comment,		/**< комментарий		*/
	type_attribute,		/**< атрибут			*/
	type_text,			/**< текст				*/
	type_declaration,	/**< заголовок			*/
	type_unknown		/**< неизвестный узел	*/
} mxml_node_type;

/**
* Основная структура данных, представляющая узлы дерева XML документа
*/
typedef struct mxml_node_tag
{
	mxml_node_type type;	/**< тип узла */
	void * document;		/**< документ, к которому принадлежит данный узел */

	/** хранит указатель на расширение данных узла, в зависимости от типа :
	*	- type_document		- mxml_document *
	*	- type_element		- mxml_element *
	*	- type_comment		- всегда NULL
	*	- type_attribute	- mxml_attribute *
	*	- type_text			- всегда NULL
	*	- type_declaration	- mxml_declaration *
	*	- type_unknown		- всегда NULL
	*/
	void * extend;			

	/** 
	*	поле, содержащее текстовое значение, смысл которого определяется типом узла :
	*		- type_document		- имя файла на диске, откуда был загружен документ
	*		- type_element		- имя тега элемента
	*		- type_comment		- текст комментария
	*		- type_attribute	- имя атрибута - для some_attr="value" это будет "some_attr"
	*		- type_text			- текст
	*		- type_declaration	- "?xml"
	*		- type_unknown		- содержимое узла неизвестного типа
	*/
	mxml_string_t value;

	/**
	*	поля для организации дерева узлов
	*/
	struct mxml_node_tag 
		*parent,		/**< родитель для данного узла, NULL для документа */
		*first_child,	/**< первый "ребенок"-узел */
		*last_child,	/**< последний "ребенок"-узел */
		*next,			/**< следующий узел в дереве на том же уровне (sibling) */
		*prev;			/**< предыдущий узел в дереве на том же уровне (sibling) */
} mxml_node;

/**
*	структура данных для представления атрибута XML элемента
*/
typedef struct mxml_attribute_tag
{
	mxml_string_t value; /**< содержит значение атрибута в текстовом виде */
} mxml_attribute;

/**
*	структура данных для представления XML элемента
*/
typedef struct mxml_element_tag
{
	mxml_node * first_attribute; /**< первый атрибут в списке */
	mxml_node * text; /**< текст */
} mxml_element;

/**
*	структура данных для представления XML declaration
*/
typedef struct mxml_declaration_tag
{
	mxml_string_t version;		/**< версия, должна быть "1.0" */
	mxml_string_t encoding;		/**< кодировка документа */
	mxml_string_t standalone;	/**< может принимать 2 значения - "yes" | "no" */
} mxml_declaration;

/**
*	структура данных для документа 
*/
typedef struct mxml_document_tag
{
	const mxml_char_t * error_desc; /**< описание последней ошибки */
	int error_code;					/**< код последней ошибки */
} mxml_document;

#define MAX_LIST_SIZE 16
/**
*	структура для хранения коллекции узлов
*/
typedef struct list_type_tag
{
	mxml_node** items;	/**< массив указателей на элементы. */
	size_t count;		/**< число элементов в списке */
	size_t size;		/**< размерность массива */
} list_type;

/** 
* Макрос инициализации списка.
* Выделяет память размером (cnt)*sizeof(mxml_node*) байт.
*/
#define list_init( lst, cnt ) do { (lst)->count = 0; (lst)->size = 0; (lst)->items = (mxml_node**)malloc( (cnt)*sizeof(mxml_node*) ); if((lst)->items)(lst)->size = cnt; } while (0,0)

/** 
* Макрос удаления списка.
* Освобождает всю занятую списком память.
*/
#define list_free( lst ) do { if((lst)->items) free( (lst)->items ); (lst)->count = 0; (lst)->size = 0; } while(0,0)

/** 
* Макрос добавления элемента в список.
* При необходимости реаллоцирует память.
* Коэффициент реаллокации - 3/2.
*/
#define list_add( lst, n ) do { if( (lst)->size <= (lst)->count ) {(lst)->size = ((lst)->size * 3) / 2; (lst)->items = (mxml_node**)realloc( (lst)->items, (lst)->size ); } if ( (lst)->items ) { (lst)->items[(lst)->count++]=n; } } while(0,0)

/** 
* Перечисление кодов состояния контекста парсинга.
*/
typedef enum 
{
	context_need_more_data,	/**< парсинг не окончен, нужны данные */
	context_failure			/**< парсинг окончен, критическая ошибка при разборе */
} mxml_context_code;

/** 
* Структура контекста парсинга.
* Содержит текущее состояние системы.
*/
typedef struct 
{
	position_t pos;			/**< current parsing pos */
	int skip_whitespace;	/**< skip white spaces in text elements ? */	
	mxml_node * last_node;
	mxml_context_code code;
} parsing_context;

#ifdef __cplusplus
}
#endif /* END extern "C" { */

#endif /* __HDR_MYXML_TYPES_C_H__ */
