#ifndef MODULE_INSTANCE_H
#define MODULE_INSTANCE_H

#include <vector>
#include <string>

class Module_description;
class Instance_port;

/// Class for holding single instance of a Modules.
class Module_instance
{
public:

    /** \brief Constructor with name.
	 *	\param[in] name - Name of the instance.
	 *	\param[in] description_name - Name of the Module Description for current instance.
	 */
    Module_instance(const std::string& name, const std::string& description_name);

	/// \brief Getter function for the instance name.	
	const std::string& get_name() const;

	/// \brief Getter function for the description name.	
	const std::string& get_description_name() const;

	/// \brief Returns if current instance has description. If this is an instance of built-in module, or the descriptio was not found in the netlist will return false.
	bool has_description() const;

	/// \brief Returns the Module Description if available( not available to built-in modules and not found modules), else throws an error string.
	const Module_description& get_module_description() const;

	/** \brief Sets Module description for current instance to given.
	 *  \param[in] description - The new description of current module instance.
	 */
	void set_module_description(const Module_description& description);

	/// \brief Returns the Parent Module Description.
	const Module_description* const get_parent_module_description() const;

	/** \brief Sets Parent Module description for current instance to given.
	 *  \param[in] description - The new description of parent module.
	 */
	void set_parent_module_description(const Module_description* description);

	/** \brief Function to get all ports in the module instance.
	 *	\ret The vector containing ports of the current module instance.
	 */
    const std::vector<Instance_port>& get_ports() const;

	/** \brief Adds given port to the current module instance.
	 *  \param[in] port - Port to add.
	 */
	void add_port(const Instance_port& port);

	/** Creates an instance port with given name. The type will be set later when mapping description ports with instance ports.
	 *	\param[in] name - The name of the new port.
	 */	
	void create_new_port(const std::string& name);

private:

	/// All ports of the current instance.
	std::vector<Instance_port> m_ports;

	/// Name of the instance.
    std::string m_name;

	/// Name of the Module description for this instance. It can be got from the m_module_description too, but this is needed not to read the file twice.
	std::string m_description_name;

	/// Pointer to the description of this object. Is set to null for built-in models(and, or, ... etc.), or when model description was not found in the netlist.
	const Module_description * m_module_description;

	/// Pointer to the parent Module Description. Must be NULL for the main instance.
	const Module_description * m_parent_module_description;

};

#endif // MODULE_INSTANCE_H
