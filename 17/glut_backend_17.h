#ifndef GLUT_BACKEND_H
#define GLUT_BACKEND_H

#include "callbacks_17.h"
//����� ���� ���, ������������� GLUT, ��� ��������� ����
void GLUTBackendInit(int argc, char** argv);

bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, unsigned int bpp, bool isFullScreen, const char* pTitle);

void GLUTBackendRun(ICallbacks* pCallbacks);//��������� ICallbacks
//������ ����, ��� �� ���������� ���� �������������� �������, ������ ���� ����� ���������� ���������, 
//�������������� ���� private �������, � ���������� ������� � ������, ��������� � ������ ������� ����
#endif /* GLUT_BACKEND_H */