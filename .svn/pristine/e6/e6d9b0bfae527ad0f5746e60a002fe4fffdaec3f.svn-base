#include "../myxml.hpp"
#include "detail.hpp"
#include "grammar.hpp"

#include <assert.h>

namespace myxml
{
	void element::print_out( FILE * file )
	{
		xml_fprintf( file, XML_T("<%s"), this->value().c_str() );
		node * attr = this->first_attribute();
		while( attr != NULL )
		{
			attr->print_out( file );
			attr = attr->next();
		}

		if ( this->first_child() != NULL )
		{
			xml_fprintf( file, XML_T("%s"), XML_T(" >\n\t") );
			text * txt = this->get_text();
			if ( txt != NULL )
			{
				txt->print_out( file );
				xml_fprintf( file, XML_T("\n\t") );
			}

			node * child = this->first_child();
			while( child != NULL )
			{
				if ( child != txt )
				{					
					child->print_out( file );
					xml_fprintf( file, XML_T("%s"), XML_T("\n\t") );
				}
				child = child->next();
			}

			xml_fprintf( file, XML_T("</%s>"), this->value().c_str() );
		}		
		else
		{
			xml_fprintf( file, XML_T("%s"), XML_T(" />") );
		}
	}

	attribute * element::find_attribute( const string_t& name )
	{
		std::list< attribute >::iterator it = this->attributes_.begin();
		std::list< attribute >::iterator e = this->attributes_.end();
		while( it != e )
		{
			if ( (*it).name() == name )
				return &*it;

			++it;
		}

		return NULL;
	}

	attribute& element::insert( const attribute& attr )
	{
		std::list< attribute >::iterator prev = this->attributes_.end();
		if ( !this->attributes_.empty() )
			--prev;

		this->attributes_.push_back( attr );

		attribute& last = this->attributes_.back();
		last.set_next( NULL );
		last.set_parent( this );
		if ( prev != this->attributes_.end() )
		{
			last.set_prev( &(*prev) );
			(*prev).set_next( &last );
		}
		return last;
	}

	attribute * element::first_attribute()
	{
		if ( this->attributes_.empty() )
			return NULL;
		else 
			return &this->attributes_.front();
	}

	void element::append_text( text * text_node )
	{
		node * child = this->last_child();
		if ( child )
		{
			if ( child->type() != node::type_text )
			{
				node * prev_child = child->prev();
				if ( prev_child && prev_child->type() == node::type_text )
				{
					prev_child->value( prev_child->value() + text_node->value() );
					return;
				}
			}			
		}

		this->text_ = text_node;
		this->append_child( text_node );
	}

	const char_t * element::read_tag( const char_t * str, int& closed )
	{	
		closed = 0;
		str = detail::skip_space( str );
		const char_t * beg = str;
		while ( 
				*str 
				&& *str != grammar::greater 
				&& *str != grammar::slash 
				&& !detail::is_space(*str) 
				)
			++str;

		if ( beg < str )
		{
			this->value_.assign( beg, str );
			if ( *str == grammar::slash ) 
			{
				++str;
				if ( *str++ != grammar::greater )
					closed = 1;
				else 
					return NULL;
			}
			return str;
		}

		return NULL;
	}

	const char_t * element::read_attributes( const char_t * str, parsing_context& ctx, int& closed )
	{
		closed = 0;
		// read attributes of tha elemend
		while( *str )
		{
			str = detail::skip_space( str );
			if ( !*str )
				return node::document_set_error( XML_T("error while parsing element tag !") );

			if ( *str == grammar::greater )
			{
				++str;
				break;
			}

			if ( *str == grammar::slash )
			{
				++str;
				if ( *str++ == grammar::greater )
					return ( closed = 1, str );
				else
					return node::document_set_error( XML_T("find incorrect symbol after '/' while parsing element tag !") );
			}

			attribute att( this->get_document() );
			str = att.parse( str, ctx );
			if ( !str )
				return node::document_set_error( XML_T("error while parsing element tag !") );

			this->insert( att );
		}
		return str;
	}

	const char_t * element::read_inner( const char_t * str, parsing_context& ctx )
	{
		document * doc = this->get_document();
		assert( doc );
		
		while ( *str )
		{
			str = detail::skip_space( str );
			if ( detail::string_n_compare<false>( str, XML_T("</"), 2 ) )
				break;

			node * ident = doc->identify( str, ctx );
			if ( !ident || !(str = ident->parse( str, ctx )) )
				return node::document_set_error( XML_T("can't read inner data while parsing element !") );

			if ( ident->type() != node::type_text )
				this->append_child( ident );
			else 
				this->append_text( node::cast< text >( ident ) );
		}
		
		return str;
	}

	const char_t * element::parse( const char_t * str, parsing_context& ctx )
	{
		str = detail::skip_space( str );
		if ( *str != grammar::less )
			return node::document_set_error( XML_T("unexpected character while parsing element tag !") );

		int closed = 0;
		str = this->read_tag( str + 1, closed );
		if ( !str )
			return node::document_set_error( XML_T("can't read tag name while parsing element tag !") );

		if ( !closed )
		{
			str = this->read_attributes( str, ctx, closed );
			if ( !str ) 
				return node::document_set_error( XML_T("can't read attributes while parsing element tag !") );

			if ( !closed )
			{
				str = this->read_inner( str, ctx );
				if ( !str )
					return node::document_set_error( XML_T("error while parsing element tag !") );
				else // end tag ?
				{
					if ( !detail::string_n_compare<false>( str, XML_T("</"), 2 ) )
						return node::document_set_error( XML_T("not found '</' while parsing element tag !") );

					/* 
						исправления по замечаниям WinterMute на RSDN - http://rsdn.ru/Forum/Message.aspx?mid=2400256&only=1 
						пробелы в тексте вида <node>...</ node > не обрабатывались корректно

						15:07 12.03.2007 
						Dreamer
					*/
					/*					
					str += 2;
					const char_t * end = xml_strchr( str, grammar::greater );
					//*/

					str = detail::skip_space( str + 2 );
					if ( !str )
						return node::document_set_error( XML_T("error while parsing element tag !") );

					const char_t * end = str;
					while ( *end && (*end != grammar::greater && !detail::is_space( *end )) )
						++end;

					if ( /* !end || */ !*end )
						return node::document_set_error( XML_T("not found closing '>' while parsing element tag !") );

					string_t end_tag;
					end_tag.assign( str, end );
					if ( end_tag != this->value_ )
						return node::document_set_error( XML_T("end tag not match with open tag while parsing element tag !") );

					str = end + 1;
				}
			}
		}
		
		return str;
	}
}
