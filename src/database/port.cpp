#include "port.hpp"

/** \brief Constructor by name and type.
 *	\param[in] name - Name of the Port.
 *	\param[in] type - Type of the Port. 
 */
Port::Port(const std::string name, PortType type)
	: m_name( name )
	, m_type( type )
{

}

/// \brief Getter for the name.
const std::string& Port::get_name() const
{
	return m_name;
}

/// \brief Getter for the type.
PortType Port::get_type() const
{
	return m_type;
}

