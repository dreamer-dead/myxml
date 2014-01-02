#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_MATCH_HPP__
#define __HDR_MYXML_XPATH_MATCH_HPP__

#include "base.hpp"
#include <iterator>

namespace myxml 
{
	namespace xpath 
	{
		template < typename Iter, typename Value >
		struct match : public match_base 
		{
			Value value_;
			predicate_base * pred_;

			match( const Value& v, predicate_base * pred ) : value_(v), pred_(pred) {}
			~match() { delete this->pred_; }

			virtual bool operator () ( node * n, std::list< node * >& dst ) const
			{
				Iter it( n );

				if ( this->value_ == XML_T("*") )
				{
					while ( it.get() != NULL )
					{
						if ( this->pred_ == NULL || this->pred_->match( it.get() ) )
							dst.push_back( it.get() );
						it.next();
					}
				}
				else
				{
					while ( it.get() != NULL )
					{				
						if ( *it == this->value_ && (this->pred_ == NULL || this->pred_->match( it.get() )) )
							dst.push_back( it.get() );

						it.next();
					}
				}

				return true;
			}
		};

		template < typename Iter, typename Value >
		struct match_iterator : std::iterator< std::bidirectional_iterator_tag, node* >
		{
			Value value_;
			predicate_base * pred_;
			Iter it_;
			bool all_;

			match_iterator( node * n, const Value& v, predicate_base * pred ) 
				: it_(n), value_(v), pred_(pred), all_( v == XML_T("*") ) {}

			match_iterator( const match_iterator& other ) 
				: it_(other.it_), value_(other.value_), pred_(other.pred_), all_( other.all_ ) {}

			match_iterator& operator ++ ()
			{
				while ( this->it_.get() != NULL )
				{				
					if ( this->all_ || (*this->it_ == this->value_)
						&& (this->pred_ == NULL || this->pred_->match( this->it_.get() )) )
						break;

					this->it_.next();
				}

				return *this;
			}

			match_iterator operator ++ ( int )
			{
				match_iterator res( *this );

				++*this;
				return (res);
			}

			bool operator == ( const match_iterator& rhs ) const
			{				
				return ( this->value_ == rhs.value_ && this->pred_ == rhs.pred_ );
			}

			bool operator != ( const match_iterator& rhs ) const
			{
				return !( *this == rhs );
			}

			node * const operator * () 
			{
				return this->it_.get();
			}

			const node * const operator * () const
			{
				return this->it_.get();
			}

			virtual bool operator () ( node * n, std::list< node * >& dst ) const
			{
				Iter it( n );

				if ( this->value_ == XML_T("*") )
				{
					while ( it.get() != NULL )
					{
						if ( this->pred_ == NULL || this->pred_->match( it.get() ) )
							dst.push_back( it.get() );
						it.next();
					}
				}
				else
				{
					while ( it.get() != NULL )
					{				
						if ( *it == this->value_ && (this->pred_ == NULL || this->pred_->match( it.get() )) )
							dst.push_back( it.get() );

						it.next();
					}
				}

				return true;
			}
		};
	}
}

#endif /* __HDR_MYXML_XPATH_MATCH_HPP__ */
