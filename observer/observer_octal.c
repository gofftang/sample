#include "observer.h"
#include "subject.h"

#include <stdio.h>

static void octal_update(void);

observer_base g_octal = {
	.subject = &g_subject,
	.update = octal_update
};

static void octal_update(void)
{
	observer_base *obs = &g_octal;
	subject_base *sub = obs->subject;

	printf("Octal String: %d\n", sub->get_state());
}
