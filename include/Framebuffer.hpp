#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <unordered_map>
#include <vector>

#include "GLBindable.hpp"

class Framebuffer : public GLBindable
{
public:
    Framebuffer(size_t _w, size_t _h);
	~Framebuffer();

	void activeColourAttachments();
	void activeColourAttachments(const std::vector<GLenum> _bufs);
	void addTexture(const std::string &_identifier, GLenum _format, GLenum _iformat, GLenum _attachment);
	void addDepthAttachment(const std::string &_identifier);
	void bind();
	void bindTexture(const GLint _shaderID, const std::string &_tex, const char *_uniform, int _target);
	bool checkComplete();
	void clear();
	void unbind();
	GLuint get(const std::string _id) {return m_textures[_id];}
private:
	GLuint genTexture(int _width, int _height, GLint _format, GLint _internalFormat);
	//Keeps track of textures.
	std::unordered_map< std::string, GLuint > m_textures;
	//Keeps track of the colour attachments that each texture uses.
	std::unordered_map< std::string, GLenum > m_attachments;
	GLuint m_framebuffer;
	int m_h;
	GLenum m_maxColourTarget;
	int m_w;
	std::vector<GLenum> m_colorAttachments;
};

#endif