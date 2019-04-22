#include "observer.h"
#include "subject.h"

#include <stdio.h>

static void hexa_update(void);

observer_base g_hexa = {
	.subject = &g_subject,
	.update = hexa_update
};

static void hexa_update(void)
{
	observer_base *obs = &g_hexa;
	subject_base *sub = obs->subject;

	printf("Hexa String: %x\n", sub->get_state());
}
