#include <iostream>
#include <string>

#include "Framebuffer.hpp"

Framebuffer::Framebuffer(const size_t _w, const size_t _h) :
    GLBindable()
{
    m_w = _w;
    m_h = _h;

    m_id = glGenFramebuffers(1, &m_framebuffer);

    //bind();
	GLint numColAttachments = 0;
	glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &numColAttachments );
	m_maxColourTarget = numColAttachments + GL_COLOR_ATTACHMENT0;
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_framebuffer);
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void framebuffer::activeColourAttachments()
{
	for(auto &buf : m_colorAttachments)
	{
		if(buf > m_maxColourTarget)
			errorExit( "Error! Attempting to use colour target " + std::to_string((int)buf) + "that is not available on this system (max is " + std::to_string((int)m_maxColourTarget) + ").\n");
	}
	glDrawBuffers(m_colorAttachments.size(), &m_colorAttachments[0]);
}

void framebuffer::activeColourAttachments(const std::vector<GLenum> _bufs)
{
	for(auto &buf : _bufs)
	{
		if(buf > m_maxColourTarget)
			errorExit( "Error! Attempting to use colour target " + std::to_string((int)buf) + "that is not available on this system (max is " + std::to_string((int)m_maxColourTarget) + ").\n");
	}
	glDrawBuffers(_bufs.size(), &_bufs[0]);
}

void framebuffer::addDepthAttachment(const std::string &_identifier)
{
	GLuint depth;
	glGenRenderbuffers(1, &depth);
	glBindRenderbuffer(GL_RENDERBUFFER, depth);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, m_w, m_h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

	std::pair<std::string, GLuint> tex ( _identifier, depth );
	m_textures.insert( tex );
}

void framebuffer::addTexture(const std::string &_identifier, GLenum _format, GLenum _iformat , GLenum _attachment)
{
	//Create texture.
	std::pair<std::string, GLuint> tex ( _identifier, genTexture(m_w, m_h, _format, _iformat) );
	m_textures.insert( tex );

	glFramebufferTexture2D(GL_FRAMEBUFFER, _attachment, GL_TEXTURE_2D, m_textures[ _identifier ], 0);

	m_colorAttachments.push_back( _attachment );
}



void framebuffer::bindTexture(const GLint _shaderID, const std::string &_tex, const char *_uniform, int _target)
{
	GLint loc = glGetUniformLocation(_shaderID, _uniform);

	if(loc == -1)
		std::cerr << "Uh oh! Invalid uniform location in framebuffer::bindTexture!! " << _uniform << '\n';

	glUniform1i(loc, _target);

	glActiveTexture(GL_TEXTURE0 + _target);
	glBindTexture(GL_TEXTURE_2D, m_textures[_tex]);
}

bool framebuffer::checkComplete()
{
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void framebuffer::clear()
{
	activeColourAttachments( );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint framebuffer::genTexture(int _width, int _height, GLint _format, GLint _internalFormat)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return tex;
}

void framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
