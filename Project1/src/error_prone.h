#pragma once

#include <string>
#include <cstdio>

enum base_error_code
{
  FATAL = -1,
  FILE_NOT_FOUND = -2,
  READING_ERROR = -3
};

class error_prone
{
protected:
  int m_error_code;
  std::string m_error_msg;
public:
  error_prone ();
  virtual ~error_prone ();
  std::string error_msg () const;
  void error_log_to (FILE *fout = stderr, bool any_key_to_continue = false) const;
  bool error_occurred () const;
protected:
  void error_set (const std::string &error_msg = "Error occurred\n", const int error_code = -1);
  void error_set (const error_prone &other);
};

