#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_BASE_HPP__
#define __HDR_MYXML_XPATH_BASE_HPP__

#include <list>

namespace myxml 
{
	class node;

	namespace xpath
	{
		struct match_base 
		{
			virtual ~match_base() {}
			virtual bool operator () ( node * n, std::list< node * >& ) const = 0;
		};

		struct predicate_base
		{
		protected : 

			bool single_;
			predicate_base( bool s ) : single_( s ) {}

		public :
			virtual bool match( node* n ) = 0;

			inline bool single() const
			{
				return this->single_;
			}
		};	
	}	
}

#endif /* __HDR_MYXML_XPATH_BASE_HPP__ */
