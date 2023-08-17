#ifndef CAS_H
#define CAS_H

#include <QString>

enum CAS_ERROR { None, SyntaxError, InternalError, LoopError };

class CAS {
public:
  // TODO: Add dependency injected "Worksheet"/"Document" interface that is used
  // for output
  virtual CAS_ERROR Parse(QString input, QString &output) = 0;
};

#endif