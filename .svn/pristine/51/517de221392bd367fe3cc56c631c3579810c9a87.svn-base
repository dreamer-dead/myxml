#include "../myxml.hpp"
#include "../impl/xpath.hpp"

namespace myxml
{
	/*
	xpath_string typedef
	*/
	typedef basic_xpath_string/* < char_t > */ xpath_string;

	namespace detail
	{
		static
		node * find_internal( 
			node * n,
			xpath_string::iterator xpath_it, 
			xpath_string::iterator xpath_end,
			std::list< node * >& res )
		{
			/*
			пустое выражение XPath
			//*/
			if ( xpath_it == xpath_end )
				return NULL; 

			/*
			здесь храним промежуточные результаты
			//*/
			std::list< node * > lst;
			if ( (**xpath_it)( n, lst ) ) // вызывается virtual bool match_base::operator ( node *, std::list< node * >& )
			{
				++xpath_it;

				std::list< node * >::iterator beg = lst.begin();
				if ( xpath_it != xpath_end ) // если не последнее XPath выражение
				{			
					/*
					рекурсивно ищем дальше в уже найденных узлах
					//*/
					for ( ; beg != lst.end() && *beg != NULL; ++beg )
						//(*beg)->find_internal( xpath_it, xpath_end, res );
						find_internal( (*beg), xpath_it, xpath_end, res );
				}	
				else  // конец рекурсии, найденные узлы добавим к результатам поиска
				{
					for ( ; beg != lst.end() && *beg != NULL; ++beg )
						res.push_back( *beg );				
				}
			}		

			return NULL;
		}
	}

	node::node( const string_t& val_ ) : 
		value_( val_ ), 
		parent_( NULL ),
		document_( NULL ),
		first_child_( NULL ),
		last_child_( NULL ),
		next_( NULL ),
		prev_( NULL )
	{
	}

	node::node( document * doc ) : 
		value_(), 
		parent_( doc ),
		document_( doc ),
		first_child_( NULL ),
		last_child_( NULL ),
		next_( NULL ),
		prev_( NULL )
	{
	}

	node::node( const string_t& val_, node * parent ) : 
		value_( val_ ), 
		parent_( parent ),
		document_( NULL ),
		first_child_( NULL ),
		last_child_( NULL ),
		next_( NULL ),
		prev_( NULL )
	{
	}

	const char_t * node::document_set_error( const string_t& desc )
	{
		return this->document_->set_error( desc, -10 );
	}

	void node::append_child( node * n )
	{
		if ( !n )
			return;
		else
		{
			node * nparent = n->parent();

			if ( nparent )
			{
				nparent->delete_child( n );
			}

			if ( !this->last_child_ && !this->first_child_ )
			{
				this->first_child_ = n;
				this->last_child_ = n;
				n->prev_ = NULL;
			}
			else if ( this->last_child_ )
			{
				this->last_child_->next_ = n;
				n->prev_ = this->last_child_;
				this->last_child_ = n;
			}

			n->parent_ = this;
			n->next_ = NULL;
			if ( !n->document_ )
				n->document_ = this->document_;
		}		
	}

	void node::append_before_child( node * n, node * before )
	{
		if ( before == NULL )
		{
			if ( !this->last_child() && !this->first_child() )
				return this->append_child( n );
			else
			{
				if ( this->first_child_ )
					this->first_child_->set_prev( n );

				n->set_next( this->first_child_ );
				this->set_first_child( n );
			}
		}
		else
		{
			if ( before->parent() == this )
			{
				node * aprev = before->prev();
				node * nparent = n->parent();

				if ( nparent )
				{
					nparent->delete_child( n );
				}

				before->set_prev( n );
				n->set_prev( aprev );
				if ( aprev )
				{					
					aprev->set_next( n );
				}
				n->set_next( before );		

				if ( before == this->first_child() )
					this->set_first_child( n );
			}
			else // logic error !	
				return; 		
		}

		n->set_parent( this );
		if ( !n->document_)
			n->document_ = this->get_document();
	}

	void node::append_after_child( node * n, node * after )
	{
		if ( after == NULL )
			return this->append_child( n );
		else
		{
			if ( after->parent() == this )
			{
				node * anext = after->next();
				node * nparent = n->parent();

				if ( nparent )
				{
					nparent->delete_child( n );
				}				
				
				after->set_next( n );
				n->set_next( anext );
				if ( anext )
				{					
					anext->set_prev( n );
				}
				n->set_prev( after );	

				if ( after == this->last_child() )
					this->set_last_child( n );
			}
			else // logic error !		
				return; 	
		}

		n->set_parent( this );
		if ( !n->document_)
			n->document_ = this->get_document();
	}

	void node::correct_tails()
	{
		
	}

	void node::delete_child( node * n )
	{
		if ( n != NULL && n->parent() == this)
		{
			node * nnext = n->next();
			node * nprev = n->prev();

			if ( nnext )
			{
				nnext->set_prev( nprev );

				if ( n == this->first_child() )
					this->set_first_child( nnext );
			}

			if( nprev )
			{
				nprev->set_next( nnext );

				if ( n == this->last_child() )
					this->set_last_child( nprev );
			}

			n->set_parent( NULL );
		}
		else // logic error !		
			return;
	}

	node * node::find_next( node * n, const string_t& cond )
	{
		if ( !n )
			return NULL;

		while ( n && n->value() != cond )	
			n = n->next();		

		return n;
	}

	node * node::find_prev( node * n, const string_t& cond )
	{
		if ( !n )
			return NULL;

		while ( n && n->value() != cond )	
			n = n->prev();		

		return n;
	}

	node * node::find( const string_t& path )
	{
		using namespace detail;

		xpath_string xpath( path );

		std::list< node * > res;
		//this->find_internal( xpath.begin(), xpath.end(), res );
		find_internal( this, xpath.begin(), xpath.end(), res );

		return (res.empty() ? NULL : *res.begin());
	}

	void node::find( const string_t& path, std::list< node * >& res )
	{
		using namespace detail;

		xpath_string xpath( path );

		//this->find_internal( xpath.begin(), xpath.end(), res );
		find_internal( this, xpath.begin(), xpath.end(), res );

		return;
	}	

	node::~node()
	{
		node * n = this->first_child();

		while( n )
		{
			node * tmp = n->next();
			delete n;

			n = tmp;
		}
	}
}
