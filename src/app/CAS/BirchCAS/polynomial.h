#include <cstdint>
#include <vector>

struct Polynomial;

union CO {
  double value;
  Polynomial* pointer;
};

struct PolyPart {
  CO coefficient;
  int exponent;
  bool recursive = false;
};

struct Polynomial {
  std::vector<PolyPart> parts;
};
