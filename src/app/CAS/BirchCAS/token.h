#ifndef TOKEN_H
#define TOKEN_H

#include "tokentypes.h"
#include <string>
#include <QString>

class Token
{
public:
    Token(TokenType _type, QString _literal, int _lineNo, int _charNo, int _length);
    QString toString() const;
    int charStart() { return charNo; };
    int charEnd() { return charNo + length; };
    TokenType type() { return tokenType; };
    QString getLiteral() { return literal; };
private:
    const TokenType tokenType;
    const QString literal;
    const int lineNo;
    const int charNo;
    const int length;
};

#endif // TOKEN_H
