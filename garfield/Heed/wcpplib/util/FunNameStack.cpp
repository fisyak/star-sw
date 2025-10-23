/*
Copyright (c) 1999-2003 I. B. Smirnov

Permission to use, copy, modify, distribute and sell this file for any purpose
is hereby granted without fee, provided that the above copyright notice,
this permission notice, and notices about any modifications of the original
text appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

#include "wcpplib/util/FunNameStack.h"

#include <cstdlib>
#include <iostream>
namespace Heed {

void spexit_action(std::ostream& file) {
  file << "spexit_action: the streams will be now flushed\n";
  file.flush();
  std::cout.flush();
  std::cerr.flush();
  file << "spexit_action: the exit(1) function is called\n";
  std::exit(1);
}

}  // namespace Heed
