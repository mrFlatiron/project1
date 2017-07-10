#pragma once
#include "error_prone.h"
#include <cstdio>
class auto_file : public error_prone
{
private:
  FILE *m_fd;
public:
  auto_file (const char *file, const char *mode);
  ~auto_file ();

  FILE *raw ();
};

