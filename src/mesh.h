#ifndef MESH_H
#define MESH_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QDebug>
#include <QOpenGLShaderProgram>

#include <vector>
#include <string>

namespace black {

class Mesh
{
public:
    /**
     * @brief Creates a empty vao object
     *
     * @version 0.2
     *
     * @throw NoSupportedException
     * @date 07.03.2017
     * @author george popoff <popoff96@live.com>
     */
    Mesh(QOpenGLShaderProgram *program);

    /**
     * @brief Creates vao object and
     *  fills it with given position data.
     *
     * @param position Array of vertex elements
     * @param program A pointer to program. Need to
     *  set attribute array properly.
     *
     * @throw NoSupportedException
     * @date 07.03.2017
     * @author george popoff <popoff96@live.com>
     */
    Mesh(QOpenGLShaderProgram *program,
         const std::vector<float> &position);

    void setPositionData(const std::vector<float> &position);

    /**
     * @brief render Renders mesh with given
     *  primitive type, starting offset and count of
     *  vertices. If all parameters if empty then whole mesh
     *  will be rendered with GL_TRIANGLES.
     *
     * @param primitive
     *  OpenGL primitive type. Defaults to GL_TRIANGLE
     *
     * @param offset
     *  Offset in vertices to start with
     *
     * @param count
     *  Count of vertices to render
     */
    void render(int primitive = GL_TRIANGLE_STRIP,
                int offset = 0, int count = -1);

    /**
     * @brief bind Binds vertex array buffer
     *  to the current context to be used as
     *  current VAO. You can use it to set up
     *  vertexAttribPointers or so.
     */
    void bind();
    void release();

    ~Mesh();
private:
    bool m_isDataProvided = false;

    QOpenGLVertexArrayObject m_vao;

    QOpenGLBuffer            m_positionVBO;
    std::vector<float>       m_position;

    QOpenGLShaderProgram     *m_program;
};


/** ========================================================== **/
/*
 *                       Exceptions
 ** ========================================================== **/
class NotSupportedException : public std::exception
{

public:
    /**
     * @brief NotSupportedException
     *  Constructs exception by providing a name
     *  of feature that hasn't been created.
     *
     * @param feature NotSupported feature name
     */
    NotSupportedException(const std::string &feature)
        : m_feature(feature)
    {

    }

    // exception interface
public:
    const char *what() const throw()
    {
        std::string msg = m_feature + " not supported!"
            " Check your OpenGL support for this feature.";

        return msg.c_str();
    }

private:
    std::string m_feature;

};
class NoDataProvidedException : public std::exception {

    // exception interface
public:
    const char *what() const throw()
    {
        return "Cannot render empty buffer!";
    }

private:
};
}
#endif // MESH_H
