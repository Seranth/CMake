/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmCTestHandlerCommand_h
#define cmCTestHandlerCommand_h

#include <cmConfigure.h>

#include "cmCTestCommand.h"
#include "cmTypeMacro.h"

#include <stddef.h>
#include <string>
#include <vector>

class cmCTestGenericHandler;
class cmExecutionStatus;

/** \class cmCTestHandler
 * \brief Run a ctest script
 *
 * cmCTestHandlerCommand defineds the command to test the project.
 */
class cmCTestHandlerCommand : public cmCTestCommand
{
public:
  cmCTestHandlerCommand();

  /**
   * This is called when the command is first encountered in
   * the CMakeLists.txt file.
   */
  bool InitialPass(std::vector<std::string> const& args,
                   cmExecutionStatus& status) CM_OVERRIDE;

  cmTypeMacro(cmCTestHandlerCommand, cmCTestCommand);

  enum
  {
    ct_NONE,
    ct_RETURN_VALUE,
    ct_CAPTURE_CMAKE_ERROR,
    ct_BUILD,
    ct_SOURCE,
    ct_SUBMIT_INDEX,
    ct_LAST
  };

protected:
  virtual cmCTestGenericHandler* InitializeHandler() = 0;

  // Command argument handling.
  virtual bool CheckArgumentKeyword(std::string const& arg);
  virtual bool CheckArgumentValue(std::string const& arg);
  enum
  {
    ArgumentDoingNone,
    ArgumentDoingError,
    ArgumentDoingKeyword,
    ArgumentDoingLast1
  };
  int ArgumentDoing;
  unsigned int ArgumentIndex;

  bool AppendXML;
  bool Quiet;

  std::string ReturnVariable;
  std::vector<const char*> Arguments;
  std::vector<const char*> Values;
  size_t Last;
};

#define CTEST_COMMAND_APPEND_OPTION_DOCS                                      \
  "The APPEND option marks results for append to those previously "           \
  "submitted to a dashboard server since the last ctest_start.  "             \
  "Append semantics are defined by the dashboard server in use."

#endif
