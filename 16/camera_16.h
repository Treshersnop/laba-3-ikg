#ifndef CAMERA_H
#define	CAMERA_H

#include "math_3d_16.h"


class Camera
{
public:

    Camera(int WindowWidth, int WindowHeight);

    Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    bool OnKeyboard(int Key);//событие клавиатуры в класс

    void OnMouse(int x, int y);

    void OnRender();

    const Vector3f& GetPos() const
    {
        return m_pos;
    }

    const Vector3f& GetTarget() const
    {
        return m_target;
    }

    const Vector3f& GetUp() const
    {
        return m_up;
    }

private:

    void Init();
    void Update();

    Vector3f m_pos;//позиция камеры
    Vector3f m_target;//направление
    Vector3f m_up;//верхний вектор

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    Vector2i m_mousePos;
};

#endif	/* CAMERA_H */
