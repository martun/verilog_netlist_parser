#ifndef NET_H
#define NET_H

#include <string>
#include <vector>

class Port;

/// Class for Net.
class Net
{
public:

	/** \brief Constructor by name.
	 *	\param[in] name - Name of the Net.
	 *	\param[in] source_port - Source port for the net, if not provided sets to NULL.
	 */
	Net(const std::string name, const Port * source_port = 0);

	/// \brief Getter for the name of the Net.
	const std::string& get_name() const;

	/// \brief Returns the source port if exists, else throws an exception.
	const Port& get_source_port() const;

	/** \brief Sets source port.
	 *	\param[in] source_port - New Source Port.
	 */
	void set_source_port(const Port& source_port);

	/// \brief Getter for all the destination ports of the Net.
	const std::vector<const Port* >& get_destination_ports() const;

	/** \brief Adds a destination port to the Net.
	 *	\param[in] destination_port - New destination Port for this net.
	 */
	void add_destination_port( const Port * destination_port);

private:

	/// Name of the wire.
	std::string m_name;

	/// Source port for current Net.
	const Port * m_source_port;

	/// The collection of destination ports for this net.
	std::vector<const Port*> m_destination_ports;

};

#endif // NET_H
