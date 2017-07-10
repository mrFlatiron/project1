#include "main_window.h"
#include <vector>

int main (int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  main_window first_window;

  if (first_window.error_occurred ())
  {
    first_window.error_log_to (stderr, true);
    return -1;
  }

  std::vector<GLuint> shader_ids;
  shader_ids.push_back (first_window.compile_shader ("src/shaders/fragment_shader.frag",
                                                     GL_FRAGMENT_SHADER));
  shader_ids.push_back (first_window.compile_shader ("src/shaders/vertex_shader.vert",
                                                     GL_VERTEX_SHADER));

  GLuint program_id = first_window.link_shaders (shader_ids);
  GLuint vao;
  glCreateVertexArrays (1, &vao);
  glBindVertexArray (vao);

  glfwSetInputMode (first_window.raw (), GLFW_STICKY_KEYS, GL_TRUE);

  do
  {
    const GLfloat color[] = { 1.0f, 0.2f, 0.0f, 1.0f };

    glClearBufferfv (GL_COLOR, 0, color);

    glUseProgram (program_id);

    glDrawArrays (GL_TRIANGLES, 0, 3);

    glfwSwapBuffers (first_window.raw ());
    glfwPollEvents ();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey (first_window.raw (), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose (first_window.raw ()) == 0);

  glDeleteVertexArrays (1, &vao);
  glDeleteProgram (program_id);

  glfwTerminate ();

  return 0;
}