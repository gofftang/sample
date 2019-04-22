#ifndef _SINGLETON_H_
#define _SINGLETON_H_

typedef struct singleton_tag {
	struct singleton_tag *(*get_instance)(void);
	void (*show_msg)(void);
} singleton;

singleton *get_instance(void);

#endif /* _SINGLETON_H_ */
