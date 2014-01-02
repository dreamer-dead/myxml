#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_HPP__
#define __HDR_MYXML_XPATH_HPP__

#include <string>

#include "../config.hpp"
#include "xpath/base.hpp"

namespace myxml
{
	//template < typename CharT >
	class basic_xpath_string
	{
	public :

		typedef std::basic_string< char_t > string_t;
		typedef /* typename */ std::list< xpath::match_base * > list_t;
		typedef /* typename */ list_t::const_iterator iterator;

		basic_xpath_string( const string_t& path )
		{
			this->parse( path );
		}				

		iterator begin() const
		{
			return this->paths_.begin();
		}

		iterator end() const
		{
			return this->paths_.end();
		}

		~basic_xpath_string();

		/*
		void parse( const string_t& path )
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
		//*/

	protected :

		void parse( const string_t& path );

		list_t paths_;
	};
}

#endif /* __HDR_MYXML_XPATH_HPP__ */