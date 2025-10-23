#include "wcpplib/stream/findmark.h"

#include <cstring>

/*
Copyright (c) 2000 I. B. Smirnov

Permission to use, copy, modify, distribute and sell this file for any purpose
is hereby granted without fee, provided that the above copyright notice,
this permission notice, and notices about any modifications of the original
text appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

namespace Heed {

int findmark(std::istream &file, const char *s) {
  int ic;
  int l = strlen(s);  // length does not include end symbol
  char *fs = new char[l + 1];
  for (int n = 0; n < l; n++) {
    if ((ic = file.get()) == EOF) {
      delete[] fs;
      return 0;
    }
    fs[n] = ic;
  }
  fs[l] = '\0';
  while (strcmp(fs, s) != 0) {
    for (int n = 1; n < l; n++) fs[n - 1] = fs[n];
    if ((ic = file.get()) == EOF) {
      delete[] fs;
      return 0;
    }
    fs[l - 1] = ic;
    fs[l] = '\0';
  }
  delete[] fs;
  return 1;
}

}  // namespace Heed
