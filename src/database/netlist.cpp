#include "netlist.hpp"
#include "module_description.hpp"
#include <boost/shared_ptr.hpp>

/// \brief Constructor by name.
Netlist::Netlist(const std::string& name)
	: m_name( name )
{

}

/** \brief Adds given Module Description to the collection.
 *	\param[in] module - The new Module Description.
 */
void Netlist::add_module( const boost::shared_ptr<Module_description>& module)
{
	m_modules.insert( std::pair<std::string, boost::shared_ptr<Module_description> >(module->get_name(), module));
}

/// \brief Returns all Module Descriptions of the current Netlist.
const std::map< std::string, boost::shared_ptr<Module_description> >& Netlist::get_modules() const
{
	return m_modules;	
}

std::string Netlist::get_name() const
{
    return m_name;
}

/** \brief Creates a new empty module description.
 *	\param[in] name - The name of the new module.
 */
void Netlist::create_new_module(const std::string& name)
{
	m_modules.insert( std::pair<std::string, boost::shared_ptr<Module_description> >(name, boost::shared_ptr<Module_description>( new Module_description(name))));
}

/** \brief Gets module description by name.
 *	\param[in] name - The name of the module description.
 */
boost::shared_ptr<Module_description> Netlist::get_module(const std::string& name)
{
	return m_modules[name];
}

