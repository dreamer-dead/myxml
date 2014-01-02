#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_PRED_HPP__
#define __HDR_MYXML_XPATH_PRED_HPP__

#include "base.hpp"

namespace myxml 
{
	namespace xpath 
	{
		template < 
			typename Iter, 
			typename Value, 
			bool Single
		>
		struct predicate : public predicate_base 
		{
			typedef Iter iterator;
			typedef Value value_type;

			Value value_;

			predicate( const Value& v) : predicate_base(Single), value_(v) {}

			virtual bool match( node * n )
			{			
				Iter it( n );

				while ( it.get() != NULL )
				{				
					if ( it.pred( this->value_ ) )
						return true;

					it.next();
				}
				return false;
			}
		}; 

		template < 
			typename Iter, 
			typename Value, 
			typename Cond,
			bool Single
		>
		struct cond_predicate : 
			public predicate< Iter, Value, Single >
		{
			Cond cond_;

			typedef predicate< Iter, Value, Single > base_type;

			cond_predicate( const Value& v, const Cond& cond) : base_type(v), cond_(cond) {}

			//*
			virtual bool match( node * n )
			{
				Iter it( n );

				while ( it.get() != NULL )
				{				
					if ( it.pred( this->value_, this->cond_ ) )
						return true;

					it.next();
				}
				return false;
			}
			//*/
		}; 
	}
}

#endif /* __HDR_MYXML_XPATH_PRED_HPP__ */
