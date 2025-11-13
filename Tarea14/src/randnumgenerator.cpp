#include "randnumgenerator.hpp"

int RandNumGenerator::randIntGenerator(const int& minimun, const int& maximun) {
  std::random_device seed;
  std::default_random_engine gen(seed());
  std::uniform_int_distribution<> dist(minimun, maximun);
  return dist(gen);
}