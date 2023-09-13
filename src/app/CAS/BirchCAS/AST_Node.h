#ifndef AST_NODE_H
#define AST_NODE_H

#include <stdexcept>
#include <vector>

struct ASTNode {
  ASTNode *m_Parent;
  std::vector<ASTNode *> m_Children;

  // TODO: Implement ASTVisitor class
  void visit() { throw std::logic_error("Not yet implemented"); };
};

#endif