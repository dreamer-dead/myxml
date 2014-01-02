#include <stdio.h>
#include <vector>
#include <algorithm>
#include "../myxml.hpp"
#include "grammar.hpp"

namespace myxml
{
	namespace 
	{
		static inline long file_length( FILE * file )
		{
			long length = 0;
			fseek( file, 0, SEEK_END );
			length = ftell( file );
			fseek( file, 0, SEEK_SET );

			return length;
		}
	}

	struct file_closer 
	{ 
		FILE* f_;
		file_closer( FILE* f) : f_(f){} ~file_closer() { if (f_) fclose(f_); }
	};

	void document::clear_error()
	{
		this->error_code_ = 0;
		this->error_desc_.clear();
	}

	const char_t * document::set_error( const string_t& desc, int code )
	{
		if ( this->error_code_ == 0 )
		{
			this->error_code_ = code;
			this->error_desc_ = desc;
		}

		return NULL;
	}

	bool document::load( const string_t& file_name )
	{
		this->value_ = file_name;
		return this->load();
	}

	bool document::load()
	{		
		this->clear_error();

		if ( this->value_.empty() )
			return !!this->set_error( XML_T("empty file name !"), -8 );

		FILE * file = NULL;
		file_closer f( file = xml_file_open( this->value_.c_str(), XML_T("rt") ) );
		if ( file )
		{
			long length = file_length( file );
			if ( !length )
				return !!this->set_error( XML_T("empty file - ") + this->value_, -2 );

			//printf( "file size = %d\n", length );
			std::vector< char_t >::size_type beg = 0;
			std::vector< char_t > buffer( length );

			//printf( "buffer allocated\n" );
			while ( xml_file_gets( &buffer[beg], static_cast<int>(buffer.size() - beg), file ) )
			{
				size_t len = xml_strlen( &buffer[beg] );
				if ( len > buffer.size() - beg )
					return !!this->set_error( XML_T("memory override detected !"), -3 );
				else if ( len == buffer.size() - beg )
				{
					buffer.resize( buffer.size() + buffer.size() / 2 );
				}

				beg += len;
			}

			//printf( "parsing\n" );
			parsing_context ctx(0, 0);
			return !!this->parse( &buffer[0], ctx );
		}

		return !!this->set_error( XML_T("can't open file - ") + this->value_, -1 );
	}

	bool document::save()
	{
		return this->save( this->value() );
	}

	void document::print_out( FILE * file )
	{
		node * child = this->first_child();

		while( child != NULL )
		{			
			child->print_out( file );
			xml_fprintf( file, XML_T("\n") );
			child = child->next();
		}
	}

	bool document::save( const string_t& file_name )
	{
		this->clear_error();

		if ( file_name.empty() )
			return !!this->set_error( XML_T("empty file name !"), -8 );

		FILE * file = NULL;
		file_closer f( file = xml_file_open( file_name.c_str(), XML_T("wt") ) );
		if ( file )
		{			
			this->print_out( file );

			return true;
		}

		return !!this->set_error( XML_T("can't open file - ") + file_name, -1 );
	}

	bool document::load_xml( const string_t& xml )
	{
		this->clear_error();

		if ( xml.empty() )
			return !!this->set_error( XML_T("empty xml !"), -11 );

		parsing_context ctx(0, 0);
		return !!this->parse( xml.c_str(), ctx );
	}

	const char_t * document::parse( const char_t * str, parsing_context& ctx )
	{
		if ( !str )
			return this->set_error( XML_T("NULL pointer data !"), -4 );		

		while ( str && *str )
		{
			str = detail::skip_space( str );
			if ( *str )
			{
				node * ident = this->identify(  str, ctx );

				if ( !ident || !( str = ident->parse( str, ctx ) ) )			
					return this->set_error( XML_T("can't parse node data !"), -5 );

				this->append_child( ident );
			}		
			else 
				break;
		}

		return str;
	}

	node * document::identify( const char_t *str, parsing_context& /* ctx */ )
	{
		node * ident_node = NULL;
		if ( grammar::is< declaration >( str ) )
			ident_node = this->create< declaration >();
		else if ( grammar::is< comment >( str ) )
			ident_node = this->create< comment >();
		else if ( grammar::is< unknown >( str ) )
			ident_node = this->create< unknown >();
		else if ( grammar::is< element >( str ) )
			ident_node = this->create< element >();
		else if ( grammar::is< text >( str ) )
			ident_node = this->create< text >();
		else 
			ident_node = this->create< unknown >();

		return ident_node;
	}
}
