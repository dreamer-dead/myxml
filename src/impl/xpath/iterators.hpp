#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_ITERATORS_HPP__
#define __HDR_MYXML_XPATH_ITERATORS_HPP__

#include "../../myxml.hpp"

namespace myxml 
{
	namespace xpath 
	{
		//struct base_node_iterator 
		//{
		//};

		struct child_iterator 
		{
			typedef node value_type;

			node * child_cursor;

			child_iterator( node * n ) : child_cursor( NULL )
			{			
				if ( n )
					this->child_cursor = n->first_child();
			}

			node * next()
			{
				node * last = this->child_cursor;
				this->child_cursor = ( last != NULL ? last->next() : NULL );
				return this->child_cursor;
			}

			node * get()
			{
				return this->child_cursor;			
			}

			const string_t& operator * () const
			{
				return this->child_cursor->value();
			}

			bool pred( const string_t& name )
			{
				return ( this->child_cursor != NULL ? this->child_cursor->value() == name : false ); 
			}

			bool pred( const string_t& name, const string_t& text_value )
			{
				if ( !this->child_cursor )
					return false;

				element * elem = node::cast< element >( this->child_cursor );
				if ( !elem )
					return false;

				text * txt = elem->get_text();
				if ( !txt )
					return false;

				return 			 
					(this->child_cursor->value() == name && txt->value() == text_value ); 
			}
		};

		struct parent_iterator 
		{
			typedef node value_type;

			node * parent_cursor;

			parent_iterator( node * n ) : parent_cursor( NULL )
			{			
				if ( n )
					this->parent_cursor = n->parent();
			}

			node * next()
			{
				this->parent_cursor = NULL;
				return NULL;
			}

			node * get()
			{
				return this->parent_cursor;			
			}

			const string_t& operator * () const
			{
				return this->parent_cursor->value();
			}

			bool pred( const string_t& name )
			{
				return ( this->parent_cursor != NULL ? this->parent_cursor->value() == name : false ); 
			}

			bool pred( const string_t& /* name */, const string_t& /* text_value */ )
			{
				return true; 
			}
		};

		struct descendant_iterator {};

		struct attribute_iterator 
		{
			typedef attribute value_type;

			attribute * attribute_cursor;

			attribute_iterator( node * n ) : attribute_cursor( NULL )
			{
				element * elem = node::cast< element >( n );
				if ( elem )
					this->attribute_cursor = elem->first_attribute();
			}

			attribute * next()
			{
				if ( this->attribute_cursor != NULL )
				{
					node * last_next = this->attribute_cursor != NULL ? this->attribute_cursor->next() : NULL;
					this->attribute_cursor = ( last_next != NULL ? node::cast< attribute >(last_next) : NULL );
				}			
				//return last;
				return this->attribute_cursor;
			}

			attribute * get()
			{
				return this->attribute_cursor;			
			}

			const string_t& operator * () const
			{
				return this->attribute_cursor->name();
			}

			bool pred( const string_t& name )
			{
				return ( this->attribute_cursor != NULL ? this->attribute_cursor->name() == name : false ); 
			}

			bool pred( const string_t& name, const string_t& text_value )
			{
				return ( 
					this->attribute_cursor != NULL ? 
					(this->attribute_cursor->name() == name && this->attribute_cursor->value() == text_value ): false ); 
			}
		};
	}
}

#endif /* __HDR_MYXML_XPATH_ITERATORS_HPP__ */
