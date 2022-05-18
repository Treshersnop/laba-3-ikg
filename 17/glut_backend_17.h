#ifndef GLUT_BACKEND_H
#define GLUT_BACKEND_H

#include "callbacks_17.h"
//почти весь код, затрагивающий GLUT, был перемещен сюда
void GLUTBackendInit(int argc, char** argv);

bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, unsigned int bpp, bool isFullScreen, const char* pTitle);

void GLUTBackendRun(ICallbacks* pCallbacks);//интерфейс ICallbacks
//вместо того, что бы приложение само регистрировало функции, теперь этим будет заниматься интерфейс, 
//регистрирующий свои private функции, и доставлять события в объект, указанный в вызове функции выше
#endif /* GLUT_BACKEND_H */