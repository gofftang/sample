#ifndef _MODEL_STUDENT_H_
#define _MODEL_STUDENT_H_

#define NAME_SIZE	16

typedef struct model_student_tag {
	char name[NAME_SIZE];
	int roll_no;

	int (*get_roll_no)(void);
	void (*set_roll_no)(int roll_no);
	char *(*get_name)(void);
	void (*set_name)(char *name);
} model_student;

model_student m_rose;

#endif /* _MODEL_STUDENT_H_ */