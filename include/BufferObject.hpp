#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP

#include <vector>

#include "GLBindable.hpp"

class BufferObject : public GLBindable
{
    public:
        BufferObject();
        virtual ~BufferObject();

        void bind();

        template <typename T>
        void bufferData(const std::vector<T>& _data)
        {
            glBufferData(
                getEnum(),
                _data.size() * sizeof(T),
                &_data[0],
                GL_STATIC_DRAW
            );
        }

        void unbind();

    protected:

    private:
        virtual GLuint getEnum() {return 0;}
};

#endif // BUFFEROBJECT_HPP
