#include "module_description.hpp"
#include "module_instance.hpp"
#include "instance_port.hpp"
#include "module_port.hpp"
#include "net.hpp"

/** \brief Constructor with name.
 *	\param[in] name - Name of the Module Description.
 */
Module_description::Module_description( const std::string& name)
	: m_name( name )
{
	
}

/// \brief Getter function for the Module name.	
const std::string& Module_description::get_name() const
{
	return m_name;
}

/** \brief Function to get all module instances in the module description.
 *	\ret The vector containing all module instances in current module description.
 */
const std::map<std::string, boost::shared_ptr<Module_instance> >& 
Module_description::get_module_instances() const
{
	return m_modules;
}

/** \brief Adds given module instance to the current module description.
 *  \param[in] module_instance - Module instance to add.
 */
void Module_description::add_module_instance(boost::shared_ptr<Module_instance> module_instance)
{
	m_modules.insert( std::pair<std::string, boost::shared_ptr<Module_instance> >(module_instance->get_name(), module_instance) );
}

/** \brief Adds module instance based on it's name, module_description name, and Wire-port name pairs.
 *	\param[in] module_name - Module description name of the new instance.
 *	\param[in] instance_name - Name of the instance.
 *	\param[in] wire_port_name_pairs - Vector of (wire name, port name) pairs.
 */
void Module_description::add_module_instance(const std::string& module_name, const std::string& instance_name, const std::vector< std::pair< std::string, std::string> >& wire_port_name_pairs)
{
	// Create and add instance.
	boost::shared_ptr<Module_instance> new_instance(new Module_instance(instance_name, module_name));
	add_module_instance( new_instance );

	int len = wire_port_name_pairs.size();
	// Create instance ports.
	for (int i = 0; i < len; ++i)
	{
		new_instance->create_new_port( wire_port_name_pairs[i].second );
	}
}

/** \brief Returns Module Instance by its name. Throws if does not exist.
 *	\param[in] name - Name of the Instance.
 */	
boost::shared_ptr<Module_instance>& Module_description::get_module_instance_by_name(const std::string& name)
{
	std::map<std::string, boost::shared_ptr<Module_instance> >::iterator iter = m_modules.find(name);
	if (iter == m_modules.end())
	{
		throw std::string("Unable to get instance with given name.");
	}
return iter->second;
}

/** \brief Function to get all ports in the module description.
 *	\ret The vector containing ports of the current module description.
 */
const std::map<std::string, boost::shared_ptr<Module_port> >& 
Module_description::get_ports() const
{
	return m_ports;
}

/** \brief Adds given port to the current module description.
 *  \param[in] port - Port to add.
 */
void Module_description::add_port(boost::shared_ptr<Module_port> port)
{
	m_ports.insert( std::pair<std::string, boost::shared_ptr<Module_port> >( port->get_name(), port) );
}

/** \brief Returns Port by its name. Throws if does not exist.
 *	\param[in] name - Name of the Port.
 */	
boost::shared_ptr<Module_port>&
Module_description::get_module_port_by_name(const std::string& name)
{
	std::map<std::string, boost::shared_ptr<Module_port> >::iterator iter = m_ports.find(name);
    if (iter == m_ports.end())
    {
        throw std::string("Unable to get port with given name.");
    }
return iter->second;
}

/** \brief Function to get all nets in the module description.
 *	\ret The vector containing nets of the current module description.
 */
const std::map<std::string, boost::shared_ptr<Net> >&
Module_description::get_nets() const
{
	return m_nets;
}

/** \brief Adds given net to the current module description.
 *	\param[in] net - Net to add.
 */
void Module_description::add_net(boost::shared_ptr<Net> net)
{
	m_nets.insert( std::pair<std::string, boost::shared_ptr<Net> >(net->get_name(), net) );
}

/** \brief Returns Net by its name. Throws if does not exist.
 *	\param[in] name - Name of the Net.
 */	
boost::shared_ptr<Net>& Module_description::get_net_by_name(const std::string& name)
{
	std::map< std::string, boost::shared_ptr<Net> >::iterator iter = m_nets.find(name);
    if (iter == m_nets.end())
    {
        throw std::string("Unable to get Net with given name.");
    }
return iter->second;
}

