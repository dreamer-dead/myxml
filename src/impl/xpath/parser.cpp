#include <utility>
#include "../detail.hpp"
#include "parser.hpp"
#include "iterators.hpp"
#include "match.hpp"
#include "predicate.hpp"

namespace myxml
{
	namespace xpath 
	{
		static const string_t attr = XML_T("attribute::");
		static const string_t child = XML_T("child::");
		static const string_t parent = XML_T("parent::");

		x_type identify_axis( const char_t * str, string_t& cond, size_t& len )
		{
			x_type t = x_unknown;
			cond = XML_T("*");

			if ( *str == char_t('@') )
			{
				t = x_attribute;
				len = 1;
			}
			else 
			{
				if ( detail::string_n_compare<false>( str, attr.c_str(), attr.length() ) )
				{ t = x_attribute; len = attr.length(); }
				else if ( detail::string_n_compare<false>( str, child.c_str(), child.length() ) )
				{ t = x_child; len = child.length(); }
				else if ( detail::string_n_compare<false>( str, parent.c_str(), parent.length() ) )
				{ t = x_parent; len = parent.length(); }								
			}
			str += len;

			if ( *str && (*str != char_t('[') ) )
			{			
				const char_t * delim = xml_strchr( str, char_t('[') );
				if ( delim == NULL )
				{
					delim = xml_strchr( str, char_t('=') );				
				}
				const char_t * delim2 = xml_strchr( str, char_t(']') );
				if ( delim && delim2 )
					delim = delim > delim2 ? delim2 : delim;
				else
					delim = delim < delim2 ? delim2 : delim;

				size_t cond_len = ( delim == NULL ? xml_strlen( str ) : (size_t)(delim - str) );
				cond.assign( str, str + cond_len );
				len += cond_len;
			}

			return t;
		}

		predicate_base * identify_predicate( const char_t * str )
		{
			if ( !*str || *str != char_t('[') )
				return NULL;

			str = detail::skip_space( str );
			if ( !str || !*str )
				return NULL;

			string_t pred_value;
			string_t cond = XML_T("*");
			size_t len = 0;
			x_type t = identify_axis( ++str, cond, len );
			str += len;

			str = detail::skip_space( str );
			if ( str && *str == char_t( '=' ) )
			{
				str = detail::skip_space( ++str );
				char_t comma = *str++;
				const char_t * end_comma = xml_strchr( str, comma );
				if ( end_comma != NULL )
				{
					pred_value.assign( str, end_comma );

					switch( t )
					{
					case x_attribute : 
						return new cond_predicate< 
							attribute_iterator, string_t, string_t, false
						>( cond, pred_value ); 

					case x_child	 :
					case x_unknown	 : 
						return new cond_predicate< 
							child_iterator, string_t, string_t, false
						>( cond, pred_value ); 

					case x_parent	 : 
						return new cond_predicate< 
							parent_iterator, string_t, string_t, false
						>( cond, pred_value ); 
						break;
					}
				}

				return NULL;
			}

			switch( t )
			{
			case x_attribute : 
				return new predicate< 
					attribute_iterator, string_t, false
				>( cond ); 

			case x_child	 :
			case x_unknown	 : 
				return new predicate< 
					child_iterator, string_t, false
				>( cond );

			case x_parent	 : 
				return new predicate< 
					parent_iterator, string_t, false
				>( cond );
				break;
			}
			return NULL;
		}

		match_base * identify_match( const char_t * str )
		{
			x_type t = x_unknown;
			string_t cond = XML_T("*");

			if ( *str )
			{
				size_t len = 0;
				t = identify_axis( str, cond, len );
				str += len;
			}
			else 
				return NULL;

			predicate_base * pred = NULL;
			if ( *str && *str == char_t('[') )
			{
				pred = identify_predicate( str );
			}		

			match_base * m = NULL;
			switch( t )
			{
			case x_attribute : m = new match< attribute_iterator, string_t >( cond, pred ); break;

			case x_child	 :
			case x_unknown	 : m = new match< child_iterator, string_t >( cond, pred ); break;

			case x_parent	 : m = new match< parent_iterator, string_t >( cond, pred ); break;
			}

			return m;
		}
	}
}
