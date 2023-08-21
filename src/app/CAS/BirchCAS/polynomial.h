#include <cstdint>
#include <vector>

struct Polynomial;

union CoefficientOrPointer {
  double value;
  Polynomial* pointer;
};

struct PolyPart {
  CoefficientOrPointer coefficient;
  int exponent;
  bool recursive = false;
};

struct Polynomial {
  std::vector<PolyPart> parts;
};
