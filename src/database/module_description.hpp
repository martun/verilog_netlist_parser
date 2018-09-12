#ifndef MODULE_DESCRIPTION_H
#define MODULE_DESCRIPTION_H

#include <vector>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

class Module_instance;
class Module_port;
class Net;

/// Class for holding descriptions of Modules.
class Module_description
{
public:

	/** \brief Constructor with name.
	 *	\param[in] name - Name of the Module Description.
	 */
    Module_description( const std::string& name);

	/// \brief Getter function for the Module name.	
	const std::string& get_name() const;

	/** \brief Function to get all module instances in the module description.
	 *	\ret The vector containing all module instances in current module description.
	 */
    const std::map<std::string, boost::shared_ptr<Module_instance> >& get_module_instances() const;

	/** \brief Adds given module instance to the current module description.
	 *  \param[in] module_instance - Module instance to add.
	 */
	void add_module_instance(boost::shared_ptr<Module_instance> module_instance);

	/** \brief Adds module instance based on it's name, module_description name, and Wire-port name pairs.
	 *	\param[in] module_name - Module description name of the new instance.
	 *	\param[in] instance_name - Name of the instance.
	 *	\param[in] wire_port_name_pairs - Vector of (wire name, port name) pairs.
	 */
	void add_module_instance(const std::string& module_name, const std::string& instance_name, const std::vector< std::pair< std::string, std::string> >& wire_port_name_pairs);

	/** \brief Returns Module Instance by its name. Throws if does not exist.
	 *	\param[in] name - Name of the Instance.
	 */	
	boost::shared_ptr<Module_instance>& get_module_instance_by_name(const std::string& name);

	/** \brief Function to get all ports in the module description.
	 *	\ret The vector containing ports of the current module description.
	 */
    const std::map<std::string, boost::shared_ptr<Module_port> >& get_ports() const;

	/** \brief Adds given port to the current module description.
	 *  \param[in] port - Port to add.
	 */
	void add_port(boost::shared_ptr<Module_port> port);
	
	/** \brief Returns Port by its name. Throws if does not exist.
	 *	\param[in] name - Name of the Port.
	 */	
	boost::shared_ptr<Module_port>& get_module_port_by_name(const std::string& name);

	/** \brief Function to get all nets in the module description.
	 *	\ret The vector containing nets of the current module description.
	 */
    const std::map<std::string, boost::shared_ptr<Net> >& get_nets() const;

	/** \brief Adds given net to the current module description.
	 *	\param[in] net - Net to add.
	 */
	void add_net(boost::shared_ptr<Net> net);
	
	/** \brief Returns Net by its name. Throws if does not exist.
	 *	\param[in] name - Name of the Net.
	 */	
	boost::shared_ptr<Net>& get_net_by_name(const std::string& name);

private:

	/// Name of the module.
	std::string m_name;

    /// Ports of the module.
    std::map<std::string, boost::shared_ptr<Module_port> > m_ports;

    /// All net Instances used in this module description.
    std::map<std::string, boost::shared_ptr<Net> > m_nets;

    /// All the Module Instances used in this module description.
    std::map<std::string, boost::shared_ptr<Module_instance> > m_modules;

};

#endif // MODULE_DESCRIPTION_H

