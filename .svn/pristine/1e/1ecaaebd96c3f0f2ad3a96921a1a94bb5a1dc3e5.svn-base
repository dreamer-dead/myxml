/***************************************************************************************************************/
/* PROJECT   : myxml_test                                                                                       /
/* FILE      : iterator.hpp                                                                                     /
/* AUTHOR    : Dreamer                                                                                          /
/***************************************************************************************************************/

#if defined _MSC_VER && _MSC_VER >= 1000
#pragma once
#endif /* defined _MSC_VER && _MSC_VER >= 1000 */

#ifndef AUTO_HDR__ITERATOR_HPP
#define AUTO_HDR__ITERATOR_HPP

#include "../myxml.hpp"
#include <iterator>
#include <functional>

namespace myxml
{
	template < typename Node >
	struct node_next_walker : std::unary_function< Node *, Node * >
	{
		Node * operator () ( Node * n ) const 
		{
			return node::cast< Node >( n->next() );
		}

		static Node * next( Node * n ) 
		{ 
			//return node::cast< Node >( n->next() ); 

			node * tmp = n->next();
			Node * res = NULL;

			while( tmp && !res )
			{				
				res = node::cast< Node >( tmp );
				tmp = tmp->next();
			}

			return res;
		}

		static Node * prev( Node * n ) 
		{ 
			node * tmp = n->prev();
			Node * res = NULL;

			while( tmp && !res )
			{				
				res = node::cast< Node >( tmp );
				tmp = tmp->prev();
			}

			return res;
		}
	};

	template <>
	struct node_next_walker<node> : std::unary_function< node *, node * >
	{
		result_type operator () ( argument_type n ) const 
		{
			return n->next();
		}

		static result_type next( argument_type n ) { return n->next(); }
		static result_type prev( argument_type n ) { return n->prev(); }
	};

	struct node_child_walker : std::unary_function< node *, node * >
	{
		node * operator () ( node * n ) const 
		{
			return n->first_child();
		}

		static node * next( node * n ) { return n->first_child(); }
		static node * prev( node * n ) { return n->parent(); }
	};

	template < typename Node, typename Walker = node_next_walker<Node> >
	struct node_traits
	{
		typedef Node node_type;
		typedef Node * node_handle_type;
		typedef Walker walker_type;

		static node_handle_type next_node( node_handle_type n ) { return walker_type::next(n); }
		static node_handle_type prev_node( node_handle_type n ) { return walker_type::prev(n); }

		static bool compare( const node_handle_type left, const node_handle_type right )
		{
			return ( left == right );
		}
	};

	template < typename Traits = node_traits<node> >
	class node_iterator : public std::iterator
		< std::bidirectional_iterator_tag, typename Traits::node_handle_type >
	{
	private :

		typedef std::iterator< 
			std::bidirectional_iterator_tag, 
			typename Traits::node_handle_type 
		> base_iterator_type;

		value_type node_;

	public :

		node_iterator() : node_(NULL) {}
		explicit node_iterator( value_type n) : node_(n) {}
		node_iterator( const node_iterator& other ) : node_(other.node_) {}

		node_iterator& operator ++ ()
		{
			if ( this->node_ )
				//this->node_ = this->node_->next();
				this->node_ = Traits::next_node( this->node_ );

			return *this;
		}

		node_iterator operator ++ ( int )
		{
			node_iterator res( this->node_ );

			++*this;
			return (res);
		}

		node_iterator& operator -- ()
		{
			if ( this->node_ )
				//this->node_ = this->node_->prev();
				this->node_ = Traits::prev_node( this->node_ );

			return *this;
		}

		node_iterator operator -- ( int )
		{
			node_iterator res( this->node_ );

			--*this;
			return (res);
		}

		bool operator == ( const node_iterator& rhs ) const
		{
			//return ( *this->node_ == *rhs.node_ );
			return ( this->node_ == rhs.node_ );
		}

		bool operator != ( const node_iterator& rhs ) const
		{
			return !( *this == rhs );
		}

		value_type const operator * () 
		{
			return this->node_;
		}

		const value_type operator * () const
		{
			return this->node_;
		}
	};

	node_iterator<> make_node_iterator( node * n ) { return node_iterator<>( n ); }

	node_iterator<> make_child_iterator( node * n ) { return node_iterator<>( n->first_child() ); }

	node_iterator< node_traits< attribute > > make_attribute_iterator( node * n ) 
	{ 
		if ( !n )
			return node_iterator< node_traits< attribute > >();

		element * el = node::cast< element >(n);

		return ( el ) ? 
			node_iterator< node_traits< attribute > >( el->first_attribute() ) 
			: node_iterator< node_traits< attribute > >(); 
	}
	
} // namespace myxml

#endif /* AUTO_HDR__ITERATOR_HPP */
