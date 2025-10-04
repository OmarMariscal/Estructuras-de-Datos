#ifndef __BENCHMARKRESULT_H__
#define __BENCHMARKRESULT_H__

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

class BenchMarkResult {
 private:
  std::string algorithName;
  std::chrono::duration<double, std::milli> duration;

 public:
  BenchMarkResult();
  BenchMarkResult(const std::string&,
                  std::chrono::duration<double, std::milli>);
  BenchMarkResult(const BenchMarkResult&);

  // Setter's
  void setAlgorithName(const std::string&);
  void setDuration(const std::chrono::duration<double, std::milli>);

  // Getter's
  std::string toString() const;
  std::string getAlgorithName() const;
  std::chrono::duration<double, std::milli> getDuration() const;

  bool operator==(const BenchMarkResult&);
  bool operator!=(const BenchMarkResult&);
  bool operator<(const BenchMarkResult&);
  bool operator>(const BenchMarkResult&);
  bool operator<=(const BenchMarkResult&);
  bool operator>=(const BenchMarkResult&);

  BenchMarkResult& operator=(const BenchMarkResult&);
};

#endif  // __BENCHMARKRESULT_H__