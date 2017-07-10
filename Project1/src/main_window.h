#pragma once
#include "gl_handle_base.h"

class main_window : public gl_handle_base
{
private:
  GLFWwindow *m_window;
public:
  main_window ();
  ~main_window ();

  GLFWwindow *raw ();
private:
  void glew_init ();
};

