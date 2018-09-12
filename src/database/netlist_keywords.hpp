#ifndef NETLIST_KEYWORDS_HPP
#define NETLIST_KEYWORDS_HPP

#include <string>

/// This class is supposed to have only static constant field values for all Netlist specific constants.
class Netlist_keywords
{
public:

	static const std::string module;
	static const std::string input;
	static const std::string output;
	static const std::string inout;
	static const std::string endmodule;
	static const std::string wire;

};

#endif // NETLIST_KEYWORDS_HPP
