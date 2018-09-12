#ifndef MODULE_PORT_H
#define MODULE_PORT_H

#include <cstring>
#include "port.hpp"

class Module_description;

/// Class for Module Ports.
class Module_port : public Port
{
public:

	/** \brief Constructor by name and type.
	 *	\param[in] name - Name of the Port.
	 *	\param[in] type - Type of the Port. 
	 *	\param[in] parent_module_description - Description of the parent Module.
	 */
	Module_port(const std::string name, PortType type, const Module_description * const parent_module_description);

	/// \brief Getter for the parent Module Description.
	const Module_description * const get_parent_module_description() const;

private:

	/// Pointer to the parent Module Description.
	const Module_description * m_parent_module_description;
	
};

#endif // MODULE_PORT_H
