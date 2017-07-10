#include "main_window.h"

main_window::main_window ()
{
  m_window = nullptr;

  m_window = glfwCreateWindow (1024, 780, "main window", NULL, NULL);
  if (!m_window)
  {
    error_set ("Failed to create a window", base_error_code::FATAL);
    m_window = nullptr;
    return;
  }
  glfwMakeContextCurrent (m_window);

  glew_init ();
}


main_window::~main_window ()
{
  glfwTerminate ();
}

GLFWwindow * main_window::raw ()
{
  return m_window;
}

void main_window::glew_init ()
{
    glewExperimental = true;
    GLenum check;
    check = glewInit ();
    if (check != GLEW_OK)
      error_set (std::string ((const char *)glewGetErrorString (check)
                                          + std::string (": Failed to GLEW init")), base_error_code::FATAL);
}
