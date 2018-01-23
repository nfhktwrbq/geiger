
#ifndef __PORTABILITY_H__
#define __PORTABILITY_H__


void operator delete( void* pf )
{
}


extern "C" void __cxa_pure_virtual();
extern "C" void _pure_virtual(void);
extern "C" void __pure_virtual(void);
extern "C" int atexit( void (*func)(void));
extern "C" int __cxa_atexit();
void __cxa_pure_virtual() {
}

void _pure_virtual() {
}

void __pure_virtual() {
}

int atexit( void (*func)(void)) {return -1;}
int __cxa_atexit() {return -1;}


#endif
