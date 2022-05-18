#include <GL/freeglut.h>

#include "camera_15.h"

const static float STEP_SCALE = 0.1f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)//установка курсора в центр
{
    m_windowWidth = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos = Vector3f(0.0f, 0.0f, 0.0f);
    m_target = Vector3f(0.0f, 0.0f, 1.0f);
    m_target.Normalize();
    m_up = Vector3f(0.0f, 1.0f, 0.0f);

    Init();
}


Camera::Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    m_windowWidth = WindowWidth;//размеры окна
    m_windowHeight = WindowHeight;
    m_pos = Pos;

    m_target = Target;
    m_target.Normalize();

    m_up = Up;
    m_up.Normalize();

    Init();
}


void Camera::Init()
{
    //подсчитывание горизонтального угла
    Vector3f HTarget(m_target.x, 0.0, m_target.z);
    HTarget.Normalize();//нормирование угла
    //проверить какой кватернион соответствует вектору для конечного подсчета значения координаты Z
    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            m_AngleH = 360.0f - ToDegree(asin(HTarget.z));
        }
        else
        {
            m_AngleH = 180.0f + ToDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            m_AngleH = ToDegree(asin(-HTarget.z));
        }
        else
        {
            m_AngleH = 90.0f + ToDegree(asin(-HTarget.z));
        }
    }

    m_AngleV = -ToDegree(asin(m_target.y));//подсчитывание вертикального угла

    m_OnUpperEdge = false;//проверка на границы окна
    m_OnLowerEdge = false;
    m_OnLeftEdge = false;
    m_OnRightEdge = false;
    m_mousePos.x = m_windowWidth / 2;//курсор в центре
    m_mousePos.y = m_windowHeight / 2;

    glutWarpPointer(m_mousePos.x, m_mousePos.y);//перемещение курсора
}


bool Camera::OnKeyboard(int Key)//управление камерой с помощью клавиш
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP://движение камеры вперед
    {
        m_pos += (m_target * STEP_SCALE);
        Ret = true;
    }
    break;

    case GLUT_KEY_DOWN://движение камеры назад
    {
        m_pos -= (m_target * STEP_SCALE);
        Ret = true;
    }
    break;

    case GLUT_KEY_LEFT://налево
    {
        Vector3f Left = m_target.Cross(m_up);
        Left.Normalize();//преобразование к типу enum
        Left *= STEP_SCALE;
        m_pos += Left;
        Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT://направо
    {
        Vector3f Right = m_up.Cross(m_target);
        Right.Normalize();
        Right *= STEP_SCALE;
        m_pos += Right;
        Ret = true;
    }
    break;
    }

    return Ret;
}


void Camera::OnMouse(int x, int y)//управление камерой с помощью мыши
{
    const int DeltaX = x - m_mousePos.x;//разница между новыми координатами мыши и предыдущими
    const int DeltaY = y - m_mousePos.y;

    m_mousePos.x = x;//новые значения для следующих вызовов
    m_mousePos.y = y;

    m_AngleH += (float)DeltaX / 20.0f;
    m_AngleV += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
        if (x <= MARGIN) {
            //    m_AngleH -= 1.0f;
            m_OnLeftEdge = true;
        }
        else if (x >= (m_windowWidth - MARGIN)) {
            //    m_AngleH += 1.0f;
            m_OnRightEdge = true;
        }
    }
    else {
        m_OnLeftEdge = false;
        m_OnRightEdge = false;
    }

    if (DeltaY == 0) {
        if (y <= MARGIN) {
            m_OnUpperEdge = true;
        }
        else if (y >= (m_windowHeight - MARGIN)) {
            m_OnLowerEdge = true;
        }
    }
    else {
        m_OnUpperEdge = false;
        m_OnLowerEdge = false;
    }

    Update();
}


void Camera::OnRender()//если мышь не двигается
{
    bool ShouldUpdate = false;

    if (m_OnLeftEdge) {
        m_AngleH -= 0.1f;
        ShouldUpdate = true;
    }
    else if (m_OnRightEdge) {
        m_AngleH += 0.1f;
        ShouldUpdate = true;
    }

    if (m_OnUpperEdge) {//запрет полного круга
        if (m_AngleV > -90.0f) {
            m_AngleV -= 0.1f;
            ShouldUpdate = true;
        }
    }
    else if (m_OnLowerEdge) {
        if (m_AngleV < 90.0f) {
            m_AngleV += 0.1f;
            ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        Update();
    }
}

void Camera::Update()//обновляет значения векторов направления
{
    const Vector3f Vaxis(0.0f, 1.0f, 0.0f);//сброшенное состояние

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_AngleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.Rotate(m_AngleV, Haxis);

    m_target = View;
    m_target.Normalize();

    m_up = m_target.Cross(Haxis);
    m_up.Normalize();
}