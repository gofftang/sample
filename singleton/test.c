#include "singleton.h"

int main(int argc, char *argv[])
{
	singleton *sg = get_instance();
	
	sg->show_msg();

	return 0;
}