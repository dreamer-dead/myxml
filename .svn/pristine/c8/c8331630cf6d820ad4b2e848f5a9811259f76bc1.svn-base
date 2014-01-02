#include "grammar.hpp"

namespace myxml
{		
	const grammar::tag grammar::header_tag		= { XML_T("<?xml"), 5 };
	const grammar::tag grammar::comment_tag		= { XML_T("<!--"), 4 };
	const grammar::tag grammar::comment_end_tag	= { XML_T("-->"), 3 };
	const grammar::tag grammar::dtd_tag			= { XML_T("<!"), 2 };

	namespace detail 
	{
		bool is_element_impl( const char_t *& str )
		{
			return ( 
				*str++ == grammar::less 
				&& (str = detail::skip_space( str )) != NULL
				&& (detail::is_alpha( *str++ ) 
				|| *str == grammar::underscore ) 
				);
		}
	}	
}
