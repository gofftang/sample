#include "observer.h"
#include "subject.h"

#include <stdio.h>

static void binary_update(void);

observer_base g_binary = {
	.subject = &g_subject,
	.update = binary_update
};

static void binary_update(void)
{
	observer_base *obs = &g_binary;
	subject_base *sub = obs->subject;

	printf("Binary String: %d\n", sub->get_state());
}
