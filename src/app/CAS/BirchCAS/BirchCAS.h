#ifndef BIRCHCAS_H
#define BIRCHCAS_H

#include "../CAS.h"
#include "AST.h"
#include <map>

class BirchCas : CAS {
public:
  BirchCas();

  CAS_ERROR parse(QString input, QString &output) override;

private:
  /** @brief Traverses &input and returns a new AST with the result
   * @param input: The AST to traverse
   * @returns AST*: The result of the evaluation. Simplest form is an AST with 1
   * Constant node (A number essentially)
   */
  AST *evaluateAST(const AST &input);

  /** @brief Performs several simplification steps on an AST in order to
   * approach a cannonical form
   * @param input: the AST to simplify
   * @returns AST*: A simpler version of the input
   */
  AST *simplifyAST(const AST &input);

  /** @brief Simplifies the AST until it cant be simplified any more
   * @param input: the AST to simplify
   * @returns AST*: The cannonical form of the input
   */
  AST *totalSimplifyAST(const AST &input);

  /**
   * @brief The map of all variables/ASTs
   */
  std::map<QString, AST *> m_ASTs;
};

#endif