#ifndef GLBUF_H
#define GLBUF_H

#include <glad/glad.h>
#include <core/log/log.h>

struct GLBuf
{
    GLuint elementCount = 0;
    GLuint ID = 0;
    GLenum Target = 0;
    GLsizei ByteSize = 0;

    void Create(GLenum target) {
        Target = target;
        glGenBuffers(1, &ID);
    }

    void Upload(const void* data, GLsizei byteSize, GLuint count, GLenum usage) {
        //XV_ASSERT(ID != 0); TODO: Implement assert later
        ByteSize = byteSize;
        elementCount = count;

        glBindBuffer(Target, ID);
        glBufferData(Target, ByteSize, data, usage);
        glBindBuffer(Target, 0);
    }

    void Bind() const
    {
        glBindBuffer(Target, ID);
    }

    void Unbind() const
    {
        glBindBuffer(Target, 0);
    }

    void Destroy()
    {
        if (ID) {
            glDeleteBuffers(1, &ID);
            ID = 0;
        }

        ByteSize = 0;
    }
};

#endif