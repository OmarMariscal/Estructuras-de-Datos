#include "benchmarkresult.hpp"

BenchMarkResult::BenchMarkResult() : algorithName("default"), duration(0) {}

BenchMarkResult::BenchMarkResult(const std::string& a,
                                 std::chrono::duration<double, std::milli> d)
    : algorithName(a), duration(d) {}

BenchMarkResult::BenchMarkResult(const BenchMarkResult& other)
    : algorithName(other.algorithName), duration(other.duration) {}

void BenchMarkResult::setAlgorithName(const std::string& algorithName) {
  this->algorithName = algorithName;
}

void BenchMarkResult::setDuration(
    const std::chrono::duration<double, std::milli> duration) {
  this->duration = duration;
}

std::string BenchMarkResult::toString() const {
  std::ostringstream oss;
  int nameWidth = 29;
  int msWidth = 19;
  int sWidth = 18;
  oss << "|" << std::left << std::setw(nameWidth) << this->algorithName << "|"
      << std::left << std::setw(msWidth) << this->duration.count() << "|"
      << std::left << std::setw(sWidth) << this->duration.count() / 1000 << "|";
  return oss.str();
}

std::string BenchMarkResult::getAlgorithName() const {
  return this->algorithName;
}

std::chrono::duration<double, std::milli> BenchMarkResult::getDuration() const {
  return this->duration;
}

bool BenchMarkResult::operator==(const BenchMarkResult& other) {
  return this->duration == other.duration;
}

bool BenchMarkResult::operator!=(const BenchMarkResult& other) {
  return this->duration != other.duration;
}

bool BenchMarkResult::operator<(const BenchMarkResult& other) {
  return this->duration < other.duration;
}

bool BenchMarkResult::operator>(const BenchMarkResult& other) {
  return this->duration > other.duration;
}

bool BenchMarkResult::operator<=(const BenchMarkResult& other) {
  return this->duration <= other.duration;
}

bool BenchMarkResult::operator>=(const BenchMarkResult& other) {
  return this->duration >= other.duration;
}

BenchMarkResult& BenchMarkResult::operator=(const BenchMarkResult& other) {
  this->algorithName = other.algorithName;
  this->duration = other.duration;
  return *this;
}
