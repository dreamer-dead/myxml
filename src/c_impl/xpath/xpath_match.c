#include "../../myxml.h"
#include "xpath_match.h"
#include "xpath_parser.h"
#include <string.h>

//* 
#define DEBUG_XPATH_ 1
//*/

static int xpath_match_predicate( mxml_node *n, predicate * pred );

#define XP_MATCH_PRED( fname, n, p ) xpath_match_predicate( n, p )
#define XPATH_MATCH_TEMPLATE( fname )int xpath_match_##fname( LIST_TYPE dst, mxml_node *n, match *m ) \
{ mxml_node * from_it = NULL; ITERATOR_TYPE_INIT( it, n ); if ( xml_strcmp( m->value.str, XML_T("*") ) == 0 ) {from_it = ITERATOR_GET( it ); while ( from_it != NULL ){ if ( !m->use_pred || !XP_MATCH_PRED( fname, from_it, &m->pred ) ) LIST_PUSH_BACK( dst, from_it ); from_it = ITERATOR_NEXT( it ); }}else { from_it = ITERATOR_GET( it ); while ( from_it != NULL ) { if ( ITERATOR_CMP( it, m->value ) && ( !m->use_pred || XP_MATCH_PRED( fname, from_it, &m->pred ) ) ) LIST_PUSH_BACK( dst, from_it ); from_it = ITERATOR_NEXT( it );} } return 0; } 

#define XP_MATCH_PRED_TEMPLATE(fname) int xpath_match_predicate_##fname( mxml_node *n, predicate *pred )\
{\
	mxml_node * from_it = NULL;\
	ITERATOR_TYPE_INIT( it, n );\
	from_it = ITERATOR_GET( it );\
	if ( !pred->cond )\
	{\
		while ( from_it != NULL )\
		{				\
			if ( ITERATOR_PREDICATE1( it, pred->value ) )\
				return 1;\
			from_it = ITERATOR_NEXT( it );\
		}\
	}\
	else\
	{\
		while ( from_it != NULL )\
		{				\
			if ( ITERATOR_PREDICATE2( it, &pred->value, &pred->cond_value ) )\
				return 1;\
			from_it = ITERATOR_NEXT( it );\
		}\
	}\
	return 0;\
}

#define ITERATOR_TYPE mxml_node *
#define ITERATOR_TYPE_INIT( itname, n ) \
	ITERATOR_TYPE itname = ( n != NULL ? n->first_child : NULL )

#define ITERATOR_GET( it ) it
#define ITERATOR_SET( it, v ) it = v
#define ITERATOR_CMP( it, s ) ( (it != NULL) && (xml_strcmp( it->value.str, (s).str ) == 0) )
#define ITERATOR_NEXT( it ) ( it = ( it != NULL ? it->next : NULL ) )
#define ITERATOR_PREDICATE1( it, s ) ( it != NULL && (xml_strcmp( it->value.str, (s).str ) == 0) )
#define ITERATOR_PREDICATE2 iterator_child_pred2

static 
int iterator_child_pred2( mxml_node *it, const mxml_string_t *val, const mxml_string_t *cond )
{
	if ( !it )
		return 0;

	if ( it->type == type_element && it->extend != NULL )
	{
		mxml_node * txt = element_get_text( it );
		if ( !txt )
			return 0;

		return ( xml_strcmp(it->value.str, val->str) == 0 && xml_strcmp(txt->value.str, cond->str) == 0 );
	}

	return 0;
}

XP_MATCH_PRED_TEMPLATE( child )

#ifdef DEBUG_XPATH_

int xpath_match_child( LIST_TYPE dst, mxml_node *n, match *m ) 
{ 
	mxml_node * from_it = NULL; 
	ITERATOR_TYPE_INIT( it, n ); 
	
	if ( xml_strcmp( m->value.str, XML_T("*") ) == 0 ) 
	{
		from_it = ITERATOR_GET( it ); 
		
		while ( from_it != NULL )
		{ 
			if ( !m->use_pred || !XP_MATCH_PRED( fname, from_it, &m->pred ) ) 
				LIST_PUSH_BACK( dst, from_it ); 
			
			from_it = ITERATOR_NEXT( it ); 
		}
	}
	else 
	{ 
		from_it = ITERATOR_GET( it ); 
		
		while ( from_it != NULL ) 
		{ 
			if ( ITERATOR_CMP( it, m->value ) && ( !m->use_pred || XP_MATCH_PRED( fname, from_it, &m->pred ) ) ) 
				LIST_PUSH_BACK( dst, from_it ); 
			
			from_it = ITERATOR_NEXT( it );
		} 
	} 
	
	return 0; 
} 

#else

XPATH_MATCH_TEMPLATE( child )

#endif /* DEBUG_XPATH_ */

#undef ITERATOR_PREDICATE2
#undef ITERATOR_TYPE_INIT
#undef ITERATOR_NEXT

#define ITERATOR_TYPE_INIT( itname, n ) \
	ITERATOR_TYPE itname = ( n != NULL ? n->parent : NULL )
#define ITERATOR_NEXT( it ) ( it = NULL )
#define ITERATOR_PREDICATE2( it, val, cond ) (1,1)

XP_MATCH_PRED_TEMPLATE( parent )
XPATH_MATCH_TEMPLATE( parent )

#undef ITERATOR_PREDICATE2
#undef ITERATOR_TYPE_INIT
#undef ITERATOR_NEXT

#define ITERATOR_TYPE_INIT( itname, n ) \
	ITERATOR_TYPE itname = ( (n != NULL && n->type == type_element && n->extend != NULL ) ? ((mxml_element *)n->extend)->first_attribute : NULL )
#define ITERATOR_NEXT( it ) ( it = ( it != NULL ? it->next : NULL ) )
#define ITERATOR_PREDICATE2 iterator_attr_pred2
//#define ITERATOR_PREDICATE1( it, s ) ( it != NULL && (xml_strcmp( it->name.str, (s).str ) == 0) )

static 
int iterator_attr_pred2( mxml_node *it, const mxml_string_t *val, const mxml_string_t *cond )
{
	if ( !it )
		return 0;

	if ( it->type == type_attribute && it->extend != NULL )
	{
		mxml_attribute * attr = (mxml_attribute *)it->extend;

		return ( xml_strcmp(it->value.str, val->str) == 0 && xml_strcmp(attr->value.str, cond->str) == 0 );
	}

	return 0;
}

#ifdef DEBUG_XPATH_

int xpath_match_predicate_attr( mxml_node *n, predicate *pred )
{
	mxml_node * from_it = NULL;
	ITERATOR_TYPE_INIT( it, n );
	from_it = ITERATOR_GET( it );
	if ( !pred->cond )
	{
		while ( from_it != NULL )
		{				
			if ( ITERATOR_PREDICATE1( it, pred->value ) )
				return 1;
			from_it = ITERATOR_NEXT( it );
		}
	}
	else
	{
		while ( from_it != NULL )
		{				
			if ( ITERATOR_PREDICATE2( it, &pred->value, &pred->cond_value ) )
				return 1;
			from_it = ITERATOR_NEXT( it );
		}
	}
	return 0;
}

#else

XP_MATCH_PRED_TENPLATE( attr )

#endif

XPATH_MATCH_TEMPLATE( attr )

#undef ITERATOR_PREDICATE2
#undef ITERATOR_TYPE_INIT
#undef ITERATOR_NEXT
#undef ITERATOR_GET
#undef ITERATOR_SET
#undef ITERATOR_CMP
#undef ITERATOR_TYPE

int xpath_match( LIST_TYPE dst, mxml_node *n, match *m )
{
	switch( m->type )
	{
	case x_parent	: return xpath_match_parent	( dst, n, m );
	case x_attribute: return xpath_match_attr	( dst, n, m );
	case x_unknown:
	case x_child	: return xpath_match_child	( dst, n, m );
	}

	return -1;
}

int xpath_match_predicate( mxml_node *n, predicate * pred )
{
	switch( pred->type )
	{
	case x_parent	: return xpath_match_predicate_parent	( n, pred );
	case x_attribute: return xpath_match_predicate_attr		( n, pred );
	case x_unknown:
	case x_child	: return xpath_match_predicate_child	( n, pred );
	}

	return -1;
}
