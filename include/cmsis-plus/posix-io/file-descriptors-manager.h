/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CMSIS_PLUS_POSIX_IO_FILE_DESCRIPTORS_MANAGER_H_
#define CMSIS_PLUS_POSIX_IO_FILE_DESCRIPTORS_MANAGER_H_

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

#include <cmsis-plus/posix-io/types.h>

#include <cstddef>
#include <cassert>

// ----------------------------------------------------------------------------

namespace os
{
  namespace posix
  {

    // ------------------------------------------------------------------------

    class io;
    class socket;

    // ------------------------------------------------------------------------

    class file_descriptors_manager
    {
    public:

      file_descriptors_manager (std::size_t size);
      file_descriptors_manager (const file_descriptors_manager&) = delete;

      ~file_descriptors_manager ();

      // ----------------------------------------------------------------------

      static size_t
      size (void);

      static bool
      valid (int fildes);

      static class io*
      io (int fildes);

      static class socket*
      socket (int fildes);

      static int
      alloc (class io* io);

      static int
      assign (file_descriptor_t fildes, class io* io);

      static int
      free (file_descriptor_t fildes);

      // ----------------------------------------------------------------------
    private:

      static std::size_t size__;

      static class io** descriptors_array__;
    };

  } /* namespace posix */
} /* namespace os */

// ===== Inline & template implementations ====================================

namespace os
{
  namespace posix
  {
    // ------------------------------------------------------------------------

    inline size_t
    file_descriptors_manager::size (void)
    {
      return size__;
    }

  } /* namespace posix */
} /* namespace os */

// ----------------------------------------------------------------------------

#endif /* __cplusplus */

#endif /* CMSIS_PLUS_POSIX_IO_FILE_DESCRIPTORS_MANAGER_H_ */