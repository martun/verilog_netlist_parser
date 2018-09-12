#include <iostream>
#include "database/netlist_builder.hpp"

int main()
{
    Netlist_builder bld( "test_data/ALU_PLUS_MINUS_last.v" );	
    bld.construct_netlist();

	boost::shared_ptr<Netlist> netlist = bld.get_netlist();

	if (netlist != 0)
	{
		std::cout << "DB UT passed!\n";
	}
return 0;
}
