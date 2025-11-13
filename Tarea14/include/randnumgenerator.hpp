#ifndef __RANDNUMGENERATOR_H__
#define __RANDNUMGENERATOR_H__

#include <random>
#include "configure.hpp"

class RandNumGenerator {
 public:
  static int randIntGenerator(const int& = Configure::minimunRandNum,
                              const int& = Configure::maximunRandNum);
};

#endif  // __RANDNUMGENERATOR_H__