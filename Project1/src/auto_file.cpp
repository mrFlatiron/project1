#include "auto_file.h"

auto_file::auto_file (const char *file, const char *mode)
{
  m_fd = fopen (file, mode);
  if (!m_fd)
  {
    error_set (std::string ("File ") + std::string (file) + std::string (" not found\n"), base_error_code::FILE_NOT_FOUND);
    m_fd = nullptr;
    return;
  }
}


auto_file::~auto_file ()
{
  if (m_fd)
    fclose (m_fd);
}

FILE * auto_file::raw ()
{
  return m_fd;
}

