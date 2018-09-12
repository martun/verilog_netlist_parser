#include "net.hpp"

/** \brief Constructor by name.
 *	\param[in] name - Name of the Net.
 *	\param[in] source_port - Source port for the net, if not provided sets to NULL.
 */
Net::Net(const std::string name, const Port * source_port)
	: m_name( name )
	, m_source_port( source_port )
{
}

/// \brief Getter for the name of the Net.
const std::string& Net::get_name() const
{
	return m_name;
}

/// \brief Returns the source port if exists, else throws an exception.
const Port& Net::get_source_port() const
{
	if (0 == m_source_port)
	{
		throw std::string("Non-Existing source port requested.");
	}

	return *m_source_port;
}

/** \brief Sets source port.
 *	\param[in] source_port - New Source Port.
 */
void Net::set_source_port(const Port& source_port)
{
	m_source_port = &source_port;
}

/// \brief Getter for all the destination ports of the Net.
const std::vector<const Port* >& Net::get_destination_ports() const
{
	return m_destination_ports;
}

/** \brief Adds a destination port to the Net.
 *	\param[in] destination_port - New destination Port for this net.
 */
void Net::add_destination_port( const Port * destination_port)
{
	m_destination_ports.push_back( destination_port );
}

