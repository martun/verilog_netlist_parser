#include "instance_port.hpp"
#include "module_instance.hpp"

/** \brief Constructor by name and type.
 *	\param[in] name - Name of the Port.
 *	\param[in] type - Type of the Port. 
 *	\param[in] parent_module_instance - Instance of the parent Module.
 */
Instance_port::Instance_port(const std::string name, PortType type, const Module_instance * const parent_module_instance)
	: Port(name, type)
	, m_parent_module_instance( parent_module_instance )
{
	
}

/// \brief Getter for the parent Module Instance.
const Module_instance * Instance_port::get_parent_module_instance() const
{
	return m_parent_module_instance;	
}

