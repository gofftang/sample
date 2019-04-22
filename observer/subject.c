#include "string.h"
#include "subject.h"
#include "observer.h"

static int get_state(void);
static void set_state(int state);
static void attach(void* obs);
static void notify_all_observers(void);

subject_base g_subject = {
	.observers = {
		&g_binary,
		&g_octal,
		&g_hexa,
		NULL
	},
	.state = 0,
	.get_state = get_state,
	.set_state = set_state,
	.attach = attach,
	.notify_all_observers = notify_all_observers,
};

static int get_state(void)
{
	subject_base *sub = &g_subject;

	return sub->state;
}

static void set_state(int state)
{
	subject_base *sub = &g_subject;

	sub->state = state;
	notify_all_observers();
}

static void attach(void *obs)
{
	subject_base *sub = &g_subject;
	int i;

	for (i = 0; i < SUBJECT_MAX; i++) {
		if (!sub->observers[i]) {
			sub->observers[i] = obs;
			break;
		}
	}
}

static void notify_all_observers(void)
{
	subject_base *sub = &g_subject;
	observer_base *obs;
	int i;

	for (i = 0; i < SUBJECT_MAX; i++) {
		obs = (observer_base *)sub->observers[i];
		if (obs)
			obs->update();
	}
}
