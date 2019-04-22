#include "subject.h"

int main(int argc, char *argv[])
{
	subject_base *subject = &g_subject;

	subject->set_state(5);
	subject->set_state(10);

	return 0;
}