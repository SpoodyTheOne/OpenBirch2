#ifndef CAS_H
#define CAS_H

#include <QString>

enum CAS_ERROR { None, SyntaxError, InternalError, LoopError };

class CAS {
public:
  /// \todo Add dependency injected "Worksheet"/"Document" interface that is used
  /// for output

  /** 
  * @brief Parses a string input given by the user
  * @param input: The string to parse
  * @param output: The result of the input string
  * @returns #CAS_ERROR: If no problems occur, #None is returned
  */
  virtual CAS_ERROR parse(QString input, QString *output) = 0;
};

#endif