#include <iostream>
#include "netlist_builder.hpp"
#include "netlist_keywords.hpp"
#include "module_description.hpp"
#include "module_instance.hpp"
#include "port.hpp"
#include "net.hpp"
#include "module_port.hpp"

/// Helper functions.		
namespace
{
	/** \brief Removes leading and trailing spaces from the given string.
	 *	\param[in,out] str - the String to remove spaces. Result is put into the same string.
	 */
	void trim_leading_trailing_spaces(std::string& str)
	{
		int st, end, len = str.size();
		for (st = 0; (st < len) && ( str[st] == ' '); ++st);
		for (end = len - 1; (end > 0) && ( str[end] == ' '); --end);

		str = str.substr(st, end - st + 1);
	}

	/** \brief Separates the information from the comment starting with "//" from given string.
	 *  \param[in] line - The full string. Can be one line of the netlist file.
	 *	\param[out] info - The information part of the string.(Everything except the comment)
	 *	\param[out] comment - The comment part of the string. (What comes after "//")
	 */
	void divide_info_comment(const std::string& line, std::string& info, std::string& comment)
	{
		/// Get the first // position.
		size_t comment_start = line.find("//");

		info = line.substr(0, comment_start);
		trim_leading_trailing_spaces(info);
		/// +2 stands for 2 characters of "//".
		comment = line.substr(comment_start + 2);
		trim_leading_trailing_spaces(comment);
	}
}

/** \brief Constructor with file path.
 *	\param[in] source_file - Full path to the netlist file.
 */
Netlist_builder::Netlist_builder(const std::string& source_file)
	: m_netlist( new Netlist( source_file ))
{
	std::fstream * file = new std::fstream(source_file.c_str());
	m_source_stream = boost::shared_ptr<std::istream>( file );
}	

/** \brief Constructor with input stream.
 *	\param[in] source_stream - Input stream to read the Netlist from.
 */
Netlist_builder::Netlist_builder(std::istream& source_stream, const std::string& netlist_name)
	: m_netlist( new Netlist(netlist_name))
{
	m_source_stream = boost::shared_ptr<std::istream>( &source_stream );
}
	
/// \brief The main routine for netlist parsing and constructing. Reads from the constructed stream and creates a Netlist Object.
void Netlist_builder::construct_netlist()
{
	/// Read all the Modules.
	while (!m_source_stream->eof())
	{
		read_next_module_description();
	}

	/// Fix the references to the Module Descriptions from instances.
	fix_instance_to_description_pointers();
}

/// \brief Reads next Module description from the stream.
void Netlist_builder::read_next_module_description()
{
	std::string line;
	std::string info, comment;

	while (std::getline( *m_source_stream, line))
	{
        // std::cout << "line=" << line << std::endl;
        if (line.size() == 0)
        {
            continue;
        }

		divide_info_comment(line, info, comment);

		// If there is no information in current line, move to the next one.
		if (info.size() < 2)
		{
			continue;
		}
		
		// Check if a module is starting.
		if ( (info.size() >= Netlist_keywords::module.size()) && (info.substr(0, Netlist_keywords::module.size()) == Netlist_keywords::module) )
		{
			start_new_module( info );
			continue;
		}

		// Verify that the module started with "module" keyword as expected.
		if (!current_module)
		{
			throw "Module starts with not a \"module \" keyword.";
		}

		// Check if the module finished.
		if ( (info.size() >= Netlist_keywords::endmodule.size()) 
			&& (info.substr(0, Netlist_keywords::endmodule.size()) == Netlist_keywords::endmodule) )
		{
			finish_module( );
			break;
		}

		// Check if it's an input port.
		if ( (info.size() >= Netlist_keywords::input.size()) && (info.substr(0, Netlist_keywords::input.size()) == Netlist_keywords::input) )
		{
			add_input_port( info, comment );
			continue;
		}
	
		// Check if it's an output port.
		if ( (info.size() >= Netlist_keywords::output.size()) && (info.substr(0, Netlist_keywords::output.size()) == Netlist_keywords::output) )
		{
			add_output_port( info, comment );
			continue;
		}

		// Check if it's an inout port.
		if ( (info.size() >= Netlist_keywords::inout.size()) && (info.substr(0, Netlist_keywords::inout.size()) == Netlist_keywords::inout) )
		{
			add_inout_port( info, comment );
			continue;
		}
	
		// Check if a new wire description comes next.
		if ( (info.size() >= Netlist_keywords::wire.size()) && (info.substr(0, Netlist_keywords::wire.size()) == Netlist_keywords::wire) )
		{
			add_wire( info, comment );
			continue;
		}

		// If nothing was found till now, then we must have an instance declaration(or invalid something). 
		add_module_instance( info, comment );
	}
}

/// \brief Fixes the references to the Module Descriptions from instances. Must be called after reading all the Modules.
void Netlist_builder::fix_instance_to_description_pointers()
{
	// Run over all module descriptions.
	const std::map< std::string, boost::shared_ptr<Module_description> >& modules = m_netlist->get_modules();
	std::map< std::string, boost::shared_ptr<Module_description> >::const_iterator I, iter_found;
	for (I = modules.begin(); I != modules.end(); ++I)
	{
		boost::shared_ptr<Module_description> current_module = m_netlist->get_module(I->first);

		// Run over all Instances of the current Module.
		const std::map<std::string, boost::shared_ptr<Module_instance> >& instances = current_module->get_module_instances();
		std::map<std::string, boost::shared_ptr<Module_instance> >::const_iterator iter_instances;
		for (iter_instances = instances.begin(); iter_instances != instances.end(); ++iter_instances)
		{
			boost::shared_ptr<Module_instance>& current_instance = current_module->get_module_instance_by_name( iter_instances->first );
			iter_found = modules.find( current_instance->get_description_name() );
			if (modules.end() != iter_found)
			{
				// Set the module description to the real value.
				current_instance->set_module_description(*iter_found->second);
			}
		}
	}
}

/// \brief Returns a shared pointer to the Netlist constructed. Must be called after @construct_netlist.
boost::shared_ptr<Netlist> Netlist_builder::get_netlist()
{
	return m_netlist;
}

/** \brief Must be called by parser when a new module starts.
 *	\param[in] info - The line of netlist that declares a new module.
 */
void Netlist_builder::start_new_module( const std::string& info )
{
	int st = info.find(" "), end = info.find("(");
	std::string name = info.substr(st + 1, end - st - 1);

	m_netlist->create_new_module(name);
	current_module = m_netlist->get_module(name);
}

/// \brief Finished parsing of current module.
void Netlist_builder::finish_module( )
{
	current_module = boost::shared_ptr<Module_description>();
}

/** \brief Called by parser to add new input port to current module description.
 *	\param[in] info - The information part of the current string.
 *	\param[in] comment - The comment part of the current string.
 */
void Netlist_builder::add_input_port( const std::string& info, const std::string& comment )
{
	int st = info.find(" "), end = info.find(";");
	std::string name = info.substr(st + 1, end - st - 1);
	current_module->add_port(  boost::shared_ptr<Module_port>( new Module_port(name, IN, current_module.get()) )  );
}

/** \brief Called by parser to add new output port to current module description.
 *	\param[in] info - The information part of the current string.
 *	\param[in] comment - The comment part of the current string.
 */
void Netlist_builder::add_output_port( const std::string& info, const std::string& comment )
{
	int st = info.find(" "), end = info.find(";");
	std::string name = info.substr(st + 1, end - st - 1);
	current_module->add_port(  boost::shared_ptr<Module_port>( new Module_port(name, OUT, current_module.get()) )  );
}

/** \brief Called by parser to add new inout port to current module description.
 *	\param[in] info - The information part of the current string.
 *	\param[in] comment - The comment part of the current string.
 */
void Netlist_builder::add_inout_port( const std::string& info, const std::string& comment )
{
	int st = info.find(" "), end = info.find(";");
	std::string name = info.substr(st + 1, end - st - 1);
	current_module->add_port(  boost::shared_ptr<Module_port>( new Module_port(name, INOUT, current_module.get()) )  );
}

/** \brief Called by parser to add new wire to current module description.
 *	\param[in] info - The information part of the current string.
 *	\param[in] comment - The comment part of the current string.
 */
void Netlist_builder::add_wire( const std::string& info, const std::string& comment )
{
	int st = info.find(" "), end = info.find(";");
	std::string name = info.substr(st + 1, end - st - 1);
	current_module->add_net(  boost::shared_ptr<Net>( new Net(name) )  );
}

/** \brief Called by parser to add new instance to current module description. Parses the parameters from string line and calls another "add_module_instance".
 *	\param[in] info - The information part of the current string.
 *	\param[in] comment - The comment part of the current string.
 */
void Netlist_builder::add_module_instance( const std::string& info, const std::string& comment )
{
	std::string module_name, instance_name;
	std::vector< std::pair< std::string, std::string> > wire_port_pairs;

	int first_space = info.find(" ");
	module_name = info.substr(0, first_space);

	std::string rest = info.substr(first_space + 1);
	trim_leading_trailing_spaces( rest );	

	first_space = rest.find(" ");
	instance_name = rest.substr(0, first_space);

	rest = rest.substr(first_space + 1);
	
	// Now parsing this part: (.s(s), .i1(i12), .o2(o8), .o1(w3));
	size_t dot_position, open_brack, close_brack;
	std::string wire_name, port_name;

	while (true)
	{
		dot_position = rest.find(".");
		if (dot_position == std::string::npos)	
		{
			break;
		}
		
		open_brack = rest.find("(");
		if (open_brack == std::string::npos)	
		{
			break;
		}

		close_brack = rest.find(")");
		if (close_brack == std::string::npos)	
		{
			break;
		}
		wire_name = rest.substr(dot_position + 1, open_brack - dot_position - 1);
		port_name = rest.substr(open_brack + 1, close_brack - open_brack - 1);
		wire_port_pairs.push_back( std::make_pair(wire_name, port_name) );	
		rest = rest.substr(close_brack + 1);
	}
	current_module->add_module_instance(module_name, instance_name, wire_port_pairs);
}


