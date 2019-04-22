#include <string.h>
#include "model_student.h"

static int get_roll_no(void);
static void set_roll_no(int roll_no);
static char *get_name(void);
static void set_name(char *name);

model_student m_rose = {
	.name = "Rose",
	.roll_no = 0,
	.get_roll_no = get_roll_no,
	.set_roll_no = set_roll_no,
	.get_name = get_name,
	.set_name = set_name,
};

static int get_roll_no(void)
{
	model_student *stu = &m_rose;

	return stu->roll_no;
}

static void set_roll_no(int roll_no)
{
	model_student *stu = &m_rose;

	stu->roll_no = roll_no;
}

static char *get_name(void)
{
	model_student *stu = &m_rose;

	return stu->name;
}

static void set_name(char *name)
{
	model_student *stu = &m_rose;

	if (name)
		strncpy(stu->name, name, NAME_SIZE);
}
