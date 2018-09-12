#ifndef INSTANCE_PORT_H
#define INSTANCE_PORT_H

#include <cstring>
#include "port.hpp"

class Module_instance;

/// Class for Instance Ports.
class Instance_port : public Port
{
public:

	/** \brief Constructor by name and type.
	 *	\param[in] name - Name of the Port.
	 *	\param[in] type - Type of the Port. 
	 *	\param[in] parent_module_instance - Instance of the parent Module.
	 */
	Instance_port(const std::string name, PortType type, const Module_instance * const parent_module_instance);

	/// \brief Getter for the parent Module Instance.
	const Module_instance * get_parent_module_instance() const;

private:

	/// The name of the same port in Module Description.
	// std::string m_description_port_name;

	/// Pointer to the parent Module Description.
	const Module_instance * m_parent_module_instance;
	
};

#endif // INSTANCE_PORT_H
