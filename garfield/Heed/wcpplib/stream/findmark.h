#ifndef FINDMARK_H
#define FINDMARK_H
/*
The functions of this family are for finding wanted sequences of symbols
in strings or input streams. Such functions are often needed
at treating of any data for finding right
position from which some meaningful data begin at stream.

Copyright (c) 2000 I. B. Smirnov

Permission to use, copy, modify, distribute and sell this file for any purpose
is hereby granted without fee, provided that the above copyright notice,
this permission notice, and notices about any modifications of the original
text appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/
#include <istream>

namespace Heed {

// The function findmark finds string s in stream file
// and returns 1 at current position at the next symbol.
// Finding no string it returns 0.
int findmark(std::istream& file, const char* s);

}  // namespace Heed

#endif
