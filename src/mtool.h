
#include <string>

using namespace std;

class mtool 
{
	public:
		mtool();
		~mtool();
		int init(int argc, char* argv[]);
		int run();

	private:
		int _minimum_number_of_lines;
		int _minimum_number_of_columns;
		string _application_name;
		string _application_version;

};

