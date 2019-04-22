#ifndef _OBSERVER_H_
#define _OBSERVER_H_

typedef struct observer_base_tag {
	void *subject;
	void (*update)(void);
} observer_base;

observer_base g_binary;
observer_base g_octal;
observer_base g_hexa;

#endif /* _OBSERVER_H_ */