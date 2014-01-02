#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_XPATH_PARSER_HPP__
#define __HDR_MYXML_XPATH_PARSER_HPP__

#include <string>
#include "../../config.hpp"
#include "base.hpp"

namespace myxml 
{
	namespace xpath 
	{
		enum x_type
		{
			x_unknown,
			x_child,
			x_parent,
			x_attribute
		};

		match_base*		identify_match( const myxml::char_t * str );
		x_type			identify_axis( const myxml::char_t * str, std::basic_string< myxml::char_t >& cond, size_t& len );
		predicate_base* identify_predicate( const myxml::char_t * str );
		match_base*		identify_match( const myxml::char_t * str );
	}
}

#endif /* __HDR_MYXML_XPATH_PARSER_HPP__ */
