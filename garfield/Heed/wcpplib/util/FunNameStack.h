#ifndef FUNNAMESTACK_H
#define FUNNAMESTACK_H
/*
Copyright (c) 1999 I. B. Smirnov

Permission to use, copy, modify, distribute and sell this file
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
It is provided "as is" without express or implied warranty.
*/
#include <iosfwd>
#include <ostream>

#define check_econd1(condition, a1, stream) \
  if (condition) {                          \
    stream << "ERROR:\n";                   \
    stream << '\n' << #condition << '\n';   \
    stream << #a1 << '=' << (a1) << '\n';   \
    spexit(stream);                         \
  }

#define check_econd11(a, signb, stream)     \
  if (a signb) {                            \
    stream << "ERROR:\n";                   \
    stream << '\n' << #a << #signb << '\n'; \
    stream << #a << '=' << (a) << '\n';     \
    spexit(stream);                         \
  }

#define check_econd12(a, sign, b, stream)                          \
  if (a sign b) {                                                  \
    stream << "ERROR:\n";                                          \
    stream << '\n' << #a << #sign << #b << '\n';                   \
    stream << #a << '=' << (a) << ' ' << #b << '=' << (b) << '\n'; \
    spexit(stream);                                                \
  }

// condition + additional any commands
#define check_econd11a(a, signb, add, stream) \
  if (a signb) {                              \
    stream << "ERROR:\n";                     \
    stream << '\n' << #a << #signb << '\n';   \
    stream << #a << '=' << (a) << '\n';       \
    stream << add;                            \
    spexit(stream);                           \
  }

#define check_econd12a(a, sign, b, add, stream)                    \
  if (a sign b) {                                                  \
    stream << "ERROR:\n";                                          \
    stream << '\n' << #a << #sign << #b << '\n';                   \
    stream << #a << '=' << (a) << ' ' << #b << '=' << (b) << '\n'; \
    stream << add;                                                 \
    spexit(stream);                                                \
  }

// and of two conditions for one variable
#define check_econd21(a, sign1_b1_sign0, sign2_b2, stream)              \
  if (a sign1_b1_sign0 a sign2_b2) {                                    \
    stream << "ERROR:\n";                                               \
    stream << '\n' << #a << #sign1_b1_sign0 << #a << #sign2_b2 << '\n'; \
    stream << #a << '=' << (a) << '\n';                                 \
    spexit(stream);                                                     \
  }

namespace Heed {

void spexit_action(std::ostream& file);

}  // namespace Heed

// Normal exit:
#define spexit(stream)                                                   \
  {                                                                      \
    stream << "File is " << __FILE__ << " , line number is " << __LINE__ \
           << '\n';                                                      \
    spexit_action(stream);                                               \
  }

#endif
