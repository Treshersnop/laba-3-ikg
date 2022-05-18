#include <iostream>
#include "texture_16.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_pImage = NULL;
}

bool Texture::Load()
{
    try 
    {
        m_pImage = new Magick::Image(m_fileName);
        m_pImage->write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) //выводит ошибку если файл не будет найден
    {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureObj);//генерирует указанное число объектов текстур
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//фильтры для увеличения и минимизации
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//для совпадения пропорций текстуры для треугольника

    return true;
}

void Texture::Bind(GLenum TextureUnit)//привязка объекта текстуры
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}