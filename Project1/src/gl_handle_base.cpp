#include "gl_handle_base.h"

#include "auto_file.h"

gl_handle_base::gl_handle_base ()
{
  glfw_init ();
}


gl_handle_base::~gl_handle_base ()
{
  glfwTerminate ();
}

GLuint gl_handle_base::compile_shader (const char * path, const GLenum shader_type)
{
  auto_file shader_file (path, "r");

  if (shader_file.error_occurred ())
  {
    error_set (shader_file);
    return 0;
  }

  char line_buf[SHADER_MAX_STRING_LEN];
  std::string shader_code;

  while (fgets (line_buf, SHADER_MAX_STRING_LEN, shader_file.raw ()))
  {
    shader_code.append (line_buf);
    if (feof (shader_file.raw ()))
      break;
  }

  if (ferror (shader_file.raw ()))
  {
    error_set (std::string ("Some error occurred during reading shader: ") + 
               std::string (path), base_error_code::READING_ERROR);
    return 0;
  }

  GLuint shader_id = glCreateShader (shader_type);

  GLint result = GL_FALSE;
  int info_log_length;


  const char *shader_code_ptr = shader_code.c_str ();
  glShaderSource (shader_id, 1, &shader_code_ptr, NULL);
  glCompileShader (shader_id);

  glGetShaderiv (shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0)
  {
    std::vector<char> local_err (info_log_length + 1);
    glGetShaderInfoLog (shader_id, info_log_length, NULL, local_err.data ());
    printf ("%s\n", local_err.data ());
  }


  return shader_id;
}

GLuint gl_handle_base::link_shaders (const std::vector<GLuint> &shader_ids) const
{
  GLuint program_id = glCreateProgram ();
  for (auto id : shader_ids)
    glAttachShader (program_id, id);

  glLinkProgram (program_id);

  GLint result = GL_FALSE;
  GLint info_log_length;


  glGetProgramiv (program_id, GL_LINK_STATUS, &result);
  glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0)
  {
    std::vector<char> local_error (info_log_length + 1);
    glGetProgramInfoLog (program_id, info_log_length, NULL, local_error.data ());
    printf ("%s\n", local_error.data ());
    return 0;
  }

  for (auto id : shader_ids)
  {
    glDeleteShader (id);
  }

  return program_id;
}

void gl_handle_base::glfw_init ()
{
  if (!glfwInit ())
  {
    error_set ("glfw init failed", base_error_code::FATAL);
    return;
  }

  glfwWindowHint (GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

}


