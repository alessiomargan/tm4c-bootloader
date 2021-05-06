#ifndef __DPRINT_H__
#define __DPRINT_H__

#ifdef ESC_DEBUG
	extern void UARTprintf(const char *pcString, ...);
	#define DPRINT(...) UARTprintf ("esc_dbg: "__VA_ARGS__) /* TODO */
#else
	#define DPRINT(...)
#endif  /* DEBUG */


#endif
