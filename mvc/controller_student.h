#ifndef _CONTROLLER_STUDENT_H_
#define _CONTROLLER_STUDENT_H_

typedef struct controller_student_tag {
	void *model;
	void *view;

	void (*set_name)(char *name);
	char *(*get_name)(void);
	void (*set_roll_no)(int roll_no);
	int (*get_roll_no)(void);

	void (*update)(void);
} controller_student;

controller_student c_rose;

#endif /* _CONTROLLER_STUDENT_H_ */
