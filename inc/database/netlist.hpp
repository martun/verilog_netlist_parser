#ifndef NETLIST_H
#define NETLIST_H

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

class Module_description;

/// Class for holding a complete Netlist.
class Netlist
{
public:

	/// \brief Constructor by name.
	Netlist(const std::string& name);


	/** \brief Creates a new empty module description.
	 *	\param[in] name - The name of the new module.
	 */
	void create_new_module(const std::string& name);

	/** \brief Gets module description by name.
	 *	\param[in] name - The name of the module description.
	 */
	boost::shared_ptr<Module_description> get_module(const std::string& name);

	/** \brief Adds given Module Description to the collection.
	 *	\param[in] module - The new Module Description.
	 */
	void add_module( const boost::shared_ptr<Module_description>& module);

	/// \brief Returns all Module Descriptions of the current Netlist.
	const std::map< std::string, boost::shared_ptr<Module_description> >& get_modules() const;

    std::string get_name() const;

private:

	/// Name for the Netlist.
	std::string m_name;

	/// Collection of the Modules in the Netlist.
	std::map< std::string, boost::shared_ptr<Module_description> > m_modules;

};

#endif // NETLIST_H
