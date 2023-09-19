#include "Goodreads.hpp"
#include "functions.hpp"

using namespace std;

int main(int argc,char* argv[])
{
	string address = argv[1];
	Goodreads goodreads;
	goodreads.read_files_content(address);
	do_command(goodreads);
	return 0;
}






