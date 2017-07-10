#include "error_prone.h"



error_prone::error_prone () :
  m_error_code (0),
  m_error_msg ("")
{}


error_prone::~error_prone ()
{}

std::string error_prone::error_msg () const
{
  return m_error_msg;
}

void error_prone::error_log_to (FILE * fout, bool any_key_to_continue) const
{
  fprintf (fout, "%s\n", m_error_msg.c_str ());
  if (any_key_to_continue)
  {
    char key;
    scanf ("%c", &key);
  }
}

void error_prone::error_set (const std::string & error_msg, const int error_code)
{
  m_error_code = error_code;
  m_error_msg = error_msg;
}

void error_prone::error_set (const error_prone & other)
{
  m_error_code = other.m_error_code;
  m_error_msg = other.m_error_msg;
}

bool error_prone::error_occurred () const
{
  return m_error_code;
}
