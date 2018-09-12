#ifndef NETLIST_BUILDER_HPP
#define NETLIST_BUILDER_HPP

#include <boost/shared_ptr.hpp>
#include <string>
#include <fstream>

#include "netlist.hpp"

/// Class for reading Netlist, creating Netlist object.
class Netlist_builder
{
public:
	
	/** \brief Constructor with file path.
	 *	\param[in] source_file - Full path to the netlist file.
	 */
	Netlist_builder(const std::string& source_file);
	
	/** \brief Constructor with input stream.
	 *	\param[in] source_stream - Input stream to read the Netlist from.
	 */
	Netlist_builder(std::istream& source_stream, const std::string& netlist_name);
	
	/// \brief The main routine for netlist parsing and constructing. Reads from the constructed stream and creates a Netlist Object.
	void construct_netlist();

	/// \brief Returns a shared pointer to the Netlist constructed. Must be called after @construct_netlist.
	boost::shared_ptr<Netlist> get_netlist();

private:

	/// \brief Reads next Module description from the stream.
	void read_next_module_description();

	/// \brief Fixes the references to the Module Descriptions from instances. Must be called after reading all the Modules.
	void fix_instance_to_description_pointers();

	/** \brief Must be called by parser when a new module starts.
	 *	\param[in] info - The line of netlist that declares a new module.
	 */
	void start_new_module( const std::string& info );

	/// \brief Finished parsing of current module.
	void finish_module( );

	/** \brief Called by parser to add new input port to current module description.
	 *	\param[in] info - The information part of the current string.
	 *	\param[in] comment - The comment part of the current string.
	 */
	void add_input_port( const std::string& info, const std::string& comment );

	/** \brief Called by parser to add new output port to current module description.
	 *	\param[in] info - The information part of the current string.
	 *	\param[in] comment - The comment part of the current string.
	 */
	void add_output_port( const std::string& info, const std::string& comment );

	/** \brief Called by parser to add new inout port to current module description.
	 *	\param[in] info - The information part of the current string.
	 *	\param[in] comment - The comment part of the current string.
	 */
	void add_inout_port( const std::string& info, const std::string& comment );

	/** \brief Called by parser to add new wire to current module description.
	 *	\param[in] info - The information part of the current string.
	 *	\param[in] comment - The comment part of the current string.
	 */
	void add_wire( const std::string& info, const std::string& comment );

	/** \brief Called by parser to add new instance to current module description.
	 *	\param[in] info - The information part of the current string.
	 *	\param[in] comment - The comment part of the current string.
	 */
	void add_module_instance( const std::string& info, const std::string& comment );

private:

	/// The netlist currently being constructed.
	boost::shared_ptr<Netlist> m_netlist;
	
	/// The stream we're reading from to construct the Netlist.
	boost::shared_ptr<std::istream> m_source_stream;	

	/// Stores a shared pointer to the module description that is currently being read.
	boost::shared_ptr<Module_description> current_module;

};

#endif // NETLIST_BUILDER_HPP
