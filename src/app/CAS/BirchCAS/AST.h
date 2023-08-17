#ifndef AST_H
#define AST_H

#include "AST_Node.h"

/** @brief Abstract Syntax Tree, (one of) the internal representation(s) of
 * expressions and polynomials
 */
struct AST {
  /**
   * The root of the tree
   */
  ASTNode *m_Root;
};

#endif