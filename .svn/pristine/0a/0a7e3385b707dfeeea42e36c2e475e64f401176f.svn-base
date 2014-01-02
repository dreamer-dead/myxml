#include "xpath.hpp"
#include "xpath/parser.hpp"
#include <algorithm>

namespace myxml
{
	namespace detail
	{
		struct deleter 
		{
			template < class T >
			void operator () ( T * pt )
			{
				delete pt;
			}
		};
	}

	void basic_xpath_string::parse( const string_t& path )
	{
		using namespace xpath;

		if ( path.empty() )
			return;

		string_t::size_type off = 0;
		string_t::size_type slash_pos = string_t::npos;
		do 
		{
			slash_pos = path.find_first_of( char_t('/'), off );
			string_t mstr = path.substr( off, slash_pos - off );

			xpath::match_base * m = identify_match( mstr.c_str() );
			if ( m )
				this->paths_.push_back( m );

			off = slash_pos + 1;
		} while( slash_pos != string_t::npos );			
	}

	basic_xpath_string::~basic_xpath_string()
	{
		using namespace detail;

		std::for_each( this->paths_.begin(), this->paths_.end(), deleter() );
	}
}
