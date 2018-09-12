#include "module_instance.hpp"
#include "module_description.hpp"
#include "instance_port.hpp"

/** \brief Constructor with name.
 *	\param[in] name - Name of the instance.
 *	\param[in] description_name - Name of the Module Description for current instance.
 */
Module_instance::Module_instance(const std::string& name, const std::string& description_name)
	: m_name( name )
	, m_description_name( description_name )
	, m_module_description( 0 )
	, m_parent_module_description( 0 )
{

}

/// \brief Getter function for the instance name.	
const std::string& Module_instance::get_name() const
{
	return m_name;
}

/// \brief Getter function for the description name.	
const std::string& Module_instance::get_description_name() const
{
	return m_description_name;
}


/// \brief Returns if current instance has description. If this is an instance of built-in module, or the descriptio was not found in the netlist will return false.
bool Module_instance::has_description() const
{
	return (0 != m_module_description);
}

/// \brief Returns the Module Description if available( not available to built-in modules and not found modules), else throws an error string.
const Module_description& Module_instance::get_module_description() const
{
	return *m_module_description;
}

/** \brief Sets Module description for current instance to given.
 *  \param[in] description - The new description of current module instance.
 */
void Module_instance::set_module_description(const Module_description& description)
{
	m_module_description = &description;
}

/// \brief Returns the Parent Module Description.
const Module_description* const Module_instance::get_parent_module_description() const
{
	return m_parent_module_description;
}

/** \brief Sets Parent Module description for current instance to given.
 *  \param[in] description - The new description of parent module.
 */
void Module_instance::set_parent_module_description(const Module_description* description)
{
	m_parent_module_description = description;
}


/** \brief Function to get all ports in the module instance.
 *	\ret The vector containing ports of the current module instance.
 */
const std::vector<Instance_port>& Module_instance::get_ports() const
{
	return m_ports;
}

/** \brief Adds given port to the current module instance.
 *  \param[in] port - Port to add.
 */
void Module_instance::add_port(const Instance_port& port)
{
	m_ports.push_back(port);
}

/** Creates an instance port with given name. The type will be set later when mapping description ports with instance ports.
 *	\param[in] name - The name of the new port.
 */	
void Module_instance::create_new_port(const std::string& name)
{
	add_port(Instance_port(name, IN, this));
}


