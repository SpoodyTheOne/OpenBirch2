#include "BirchCAS.h"
#include "lexer.h"

namespace BirchCas {

BirchCas::BirchCas() {
  // Do stuff
}

CAS_ERROR BirchCas::parse(QString input, QString &output) {

  // Lexer *lexer = new Lexer(input);

  // std::vector<std::shared_ptr<Token>> tokens = lexer->tokenize();

  output = "Not Implemented :P";
  return CAS_ERROR::None;
}

} // namespace BirchCas