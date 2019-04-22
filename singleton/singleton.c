#include "singleton.h"
#include <stdio.h>

static void show_msg(void);

static singleton g_single = {
	.get_instance = get_instance,
	.show_msg = show_msg,
};

singleton *get_instance(void)
{
	return &g_single;
}

static void show_msg(void)
{
	// single *sg = &g_single;

	printf("Hello world!\n");
}
