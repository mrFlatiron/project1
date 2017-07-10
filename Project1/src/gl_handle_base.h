#pragma once
#include "error_prone.h"
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SHADER_MAX_STRING_LEN  1024

class gl_handle_base : public error_prone
{
public:
  gl_handle_base ();
  virtual ~gl_handle_base ();
  GLuint compile_shader (const char *path, const GLenum shader_type);
  GLuint link_shaders (const std::vector<GLuint> &shader_ids) const;
private:
  void glfw_init ();
};

