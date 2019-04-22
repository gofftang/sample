#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#define SUBJECT_MAX 	16

typedef struct subject_base_tag {
	void *observers[SUBJECT_MAX];

	int state;
	int (*get_state)(void);
	void (*set_state)(int state);

	void (*attach)(void *obs);

	void (*notify_all_observers)(void);
} subject_base;

subject_base g_subject;

#endif /* _SUBJECT_H_ */