#ifndef _VIEW_STUDENT_H_
#define _VIEW_STUDENT_H_

typedef struct view_student_tag {
	void (*update)(char *name, int roll_no);
} view_student;

view_student v_rose;

#endif /* _VIEW_STUDENT_H_ */
