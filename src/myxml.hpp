#if defined _MSC_VER && _MSC_VER >= 1300
#pragma once
#endif

#if !defined __HDR_MYXML_HPP__
#define __HDR_MYXML_HPP__

/* need for 
	XML_T macro 
	myxml::char_t type
*/
#include "config.hpp"

/*
	need for
	std::basic_string<>
*/
#include <string>

/*
	need for
	std::pair<>
*/
#include <utility>

/*
	need for
	std::list<>
*/
#include <list>

namespace myxml 
{	
	/*
		forward declaration of classes
	*/
	class node;
	class document;
	class element;
	class comment;
	class attribute;
	class text;
	class declaration;
	class unknown;

	typedef std::pair< int, int > position_t;

	/*
		basic string type for library
	*/
	typedef std::basic_string< char_t > string_t;

	/*
		xpath_string typedef
	*/
	//typedef basic_xpath_string/* < char_t > */ xpath_string;

	/*
		.base for all classes, contain position info 
			and some additional user data
		.contain virtual destructor

		now disabled position info and user data
	*/
	struct xml_base
	{
		//position_t pos_;
		//void * user_data_;

		xml_base() 
			//: pos_( -1, -1 ), user_data_(NULL) {}
			{}

		virtual ~xml_base() {}
	};

	/*
		this context describes state for currently parsed document
	*/
	struct parsing_context
	{
		position_t pos; /* current parsing pos */
		bool skip_whitespace; /* skip white spaces in text elements ? */

		parsing_context( int r, int c ) : pos( r, c ), skip_whitespace(false) {}
	};	

#define VIS_DEF_IMPL {}
//#define VIS_DEF_IMPL = 0;
	struct base_visitor
	{
		virtual void visit( node * )		VIS_DEF_IMPL
		virtual void visit( document * )	VIS_DEF_IMPL
		virtual void visit( element * )		VIS_DEF_IMPL
		virtual void visit( comment * )		VIS_DEF_IMPL
		virtual void visit( attribute * )	VIS_DEF_IMPL
		virtual void visit( text * )		VIS_DEF_IMPL
		virtual void visit( declaration * ) VIS_DEF_IMPL
		virtual void visit( unknown * )		VIS_DEF_IMPL

		virtual ~base_visitor() = 0 {};
	};
#undef VIS_DEF_IMPL

	class node : public xml_base
	{	

	public :

		enum node_type
		{
			type_node,
			type_document,
			type_element,
			type_comment,
			type_attribute,
			type_text,
			type_declaration,
			type_unknown
		};

		const string_t& value() const { return this->value_; }
		void value( const char_t * val_ ) { this->value_.assign( val_ ); }
		void value( const string_t& val_ ) { this->value_ = val_; }

		node * parent( void ) { return this->parent_; }
		const node * parent( void ) const { return this->parent_; }

		node * next( void ) { return this->next_; }
		const node * next( void ) const { return this->next_; }

		node * prev( void ) { return this->prev_; }
		const node * prev( void ) const { return this->prev_; }

		node * first_child( void ) { return this->first_child_; }
		const node * first_child( void ) const { return this->first_child_; }
		node * first_child( const string_t& cond ) { return this->find_next( this->first_child_, cond ); }

		node * last_child( void ) { return this->last_child_; }
		const node * last_child( void ) const { return this->last_child_; }

		document * get_document( void ) { return this->document_; }
		const document * get_document( void ) const { return this->document_; }

		void append_child( node * n );
		void append_before_child( node * n, node * before );
		void append_after_child( node * n, node * after );
		void delete_child( node * n );

		node * find( const string_t& path );
		void find( const string_t& path, std::list< node * >& res );
		
		virtual node_type type() = 0;
		virtual const char_t * parse( const char_t * str, parsing_context& ctx ) = 0;
		virtual void print_out( FILE * ) = 0;
		virtual ~node();

		template < typename T >
		static inline T * cast( node * n )
		{
			if ( n->type() == T::ntype )
				return static_cast< T* >( n );
			else 
				return NULL;
		}

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	protected :

		explicit node( const string_t& val_ );
		explicit node( document * doc );
		node( const string_t& val_, node * parent );

		const char_t * document_set_error( const string_t& desc );
		void set_parent( node * parent ) { this->parent_ = parent; }
		void set_next( node * next ) { this->next_ = next; }
		void set_prev( node * prev ) { this->prev_ = prev; }
		void set_first_child( node * ch ) { this->first_child_ = ch; }
		void set_last_child( node * ch ) { this->last_child_ = ch; }
		node * find_next( node * n, const string_t& cond );
		node * find_prev( node * n, const string_t& cond );

		void correct_tails();

		string_t value_;

	private :
				
		document * document_;
		node 
			*parent_,
			*first_child_,
			*last_child_,
			*next_,
			*prev_;
	};

	namespace detail 
	{
		template < node::node_type NType >
		struct type_mixin : node
		{
			static const node::node_type ntype = NType;

			virtual node_type type() { return ntype; }

			explicit type_mixin( const string_t& val_ ) : node(val_) {}
			explicit type_mixin( document * doc ) : node(doc) {}
			type_mixin( const string_t& val_, node * parent ) : node(val_, parent) {}
		};
	}

	class element : public detail::type_mixin<node::type_element> 
	{
		typedef detail::type_mixin<node::type_element> base_type;

	public :		

		element() : base_type( XML_T("") ), text_( NULL ) {}
		explicit element( document * doc ) : base_type( doc ), text_( NULL ) {}

		attribute& insert( const attribute& attr );
		attribute * first_attribute();
		attribute * find_attribute( const string_t& name );

		text * get_text() const { return this->text_; }
		
		virtual const char_t * parse( const char_t * /* str */, parsing_context& );
		virtual void print_out( FILE * );
		
	protected :

		const char_t * read_tag( const char_t * str, int& closed );
		const char_t * read_attributes( const char_t * str, parsing_context&, int& closed );
		const char_t * read_inner( const char_t * str, parsing_context& );
		void append_text( text * text_node );
		virtual void visit( base_visitor * v ) { v->visit( this ); }

	private :
		std::list< attribute > attributes_;
		text * text_;
	};

	class comment : public detail::type_mixin<node::type_comment>  
	{
		typedef detail::type_mixin<node::type_comment> base_type;

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	public :

		comment() : base_type( XML_T("") ) {}
		explicit comment( document * doc ) : base_type( doc ) {}

		virtual const char_t * parse( const char_t * /* str */, parsing_context& );
		virtual void print_out( FILE * );
	};
	
	class attribute : public detail::type_mixin<node::type_attribute> 
	{
		friend class element;

		typedef detail::type_mixin<node::type_attribute> base_type;

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	public :

		attribute() : base_type( XML_T("") ) {}
		explicit attribute( document * doc ) : base_type( doc ) {}

		const string_t& name() const { return this->name_; }

		virtual const char_t * parse( const char_t * /* str */, parsing_context& );
		virtual void print_out( FILE * );

	private :
		string_t name_;
	};
	
	class text : public detail::type_mixin<node::type_text>  
	{
		typedef detail::type_mixin<node::type_text> base_type;

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	public :

		text() : base_type( XML_T("") ) {}
		explicit text( document * doc ) : base_type( doc ) {}

		virtual const char_t * parse( const char_t * str, parsing_context& );
		virtual void print_out( FILE * );
	};

	class declaration : public detail::type_mixin<node::type_declaration> 
	{
		typedef detail::type_mixin<node::type_declaration> base_type;

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	public :

		declaration() : base_type( XML_T("") ) {}
		explicit declaration( document * doc ) : base_type( doc ) {}

		const string_t& version() const { return this->version_; }
		const string_t& encoding() const { return this->encoding_; }
		const string_t& standalone() const { return this->standalone_; }

		virtual const char_t * parse( const char_t * /* str */, parsing_context& );
		virtual void print_out( FILE * );
		
	private :

		string_t version_;
		string_t encoding_;
		string_t standalone_;
	};

	class unknown : public detail::type_mixin<node::type_unknown> 
	{
		typedef detail::type_mixin<node::type_unknown> base_type;

		virtual void visit( base_visitor * v ) { v->visit( this ); }

	public :

		unknown() : base_type( XML_T("") ) {}
		explicit unknown( document * doc ) : base_type( doc ) {}
		
		virtual const char_t * parse( const char_t * str, parsing_context& );
		virtual void print_out( FILE * );
	};

	class document : public detail::type_mixin<node::type_document> 
	{
		typedef detail::type_mixin<node::type_document> base_type;
	public :

#if defined _MSC_VER
#	pragma warning(push)
#	pragma warning(disable: 4355)
#endif
		document() 
			: base_type(this), skip_spaces_(false) 
		{ clear_error(); }

		explicit document( const string_t& file_name) 
			: base_type(file_name, this), skip_spaces_(false) 
		{ clear_error(); }

#if defined _MSC_VER
//#	pragma warning(default: 4355)
#	pragma warning(pop)
#endif

		bool load( const string_t& file_name );	
		bool load();
		bool save();
		bool save( const string_t& file_name );
		bool load_xml( const string_t& xml );
		const string_t& get_error() const { return this->error_desc_; }
		bool skip_spaces() const { return this->skip_spaces_; }
		void skip_spaces( bool skip ) { this->skip_spaces_ = skip; }

		element		* create_element()		{ return this->create< element >(); }
		attribute	* create_attribute()	{ return this->create< attribute >(); }
		text		* create_text()			{ return this->create< text >(); }
		comment		* create_comment()		{ return this->create< comment >(); }
		declaration * create_declaration()	{ return this->create< declaration >(); }
		unknown		* create_unknown()		{ return this->create< unknown >(); }

		virtual const char_t * parse( const char_t * str, parsing_context& );
		virtual void print_out( FILE * );

	private :

		friend class node;
		friend class element;

		virtual void visit( base_visitor * v ) { v->visit( this ); }
		node * identify( const char_t *str, parsing_context& );
		const char_t * set_error( const string_t& desc, int code );
		void clear_error();
		
		template < typename T >
		inline T * create()
		{
			return new T( this );
		}

	private :
		string_t error_desc_;
		int error_code_;
		bool skip_spaces_;
	};	
}

#endif /* __HDR_MYXML_HPP__ */
