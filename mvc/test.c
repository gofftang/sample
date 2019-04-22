#include "controller_student.h"

int main(int argc, char *argv[])
{
	controller_student *ctrl = &c_rose;

	ctrl->update();

	ctrl->set_name("John");
	ctrl->set_roll_no(1);

	ctrl->update();

	return 0;
}