#include "lexer.h"
#include <stdexcept>

namespace BirchCas {

Lexer::Lexer(QString _source) : source{_source} {}

Lexer::~Lexer() {}

std::vector<std::shared_ptr<Token>> Lexer::tokenize() {
  while (!isAtEnd()) {
    // Scan next token
    start = currentCharIdx;

    scanToken();
  }

  // Source is scanned, lastly append EOL token and return
  addToken(TokenType::END_OF_FILE);
  return tokens;
}

void Lexer::scanToken() {
  // std::cout << "current char idx: " << currentCharIdx << std::endl;
  printf("current char idx: %zu\n", currentCharIdx);
  QChar c = advance();
  switch (c.unicode()) {
  // Single char tokens
  case u'(':
    addToken(TokenType::LPAREN, QString(c));
    break;
  case u')':
    addToken(TokenType::RPAREN, QString(c));
    break;
  case u',':
    addToken(TokenType::COMMA, QString(c));
    break;
  case u'.':
    addToken(TokenType::DOT, QString(c));
    break;
  case u'-':
    addToken(TokenType::MINUS, QString(c));
    break;
  case u'+':
    addToken(TokenType::PLUS, QString(c));
    break;
  case u';':
    addToken(TokenType::SEMICOLON, QString(c));
    break;
  case u'*':
    addToken(TokenType::STAR, QString(c));
    break;

  // Ignore comments
  case u'#':
    while (peek() != '\n' && !isAtEnd())
      advance();
    break;

  // One or two char tokens
  case u':':
    if (match('='))
      addToken(TokenType::COLON_EQUALS, ":=");
    else
      addToken(TokenType::COLON, QString(c));
    break;

  case u'/':
    if (match('='))
      addToken(TokenType::SLASH_EQUALS, "/=");
    else
      addToken(TokenType::SLASH, QString(c));
    break;

  case u'!':
    if (match('='))
      addToken(TokenType::BANG_EQUALS, "!=");
    else
      addToken(TokenType::BANG, QString(c));
    break;

  case u'=':
    if (match('='))
      addToken(TokenType::EQUAL_EQUAL, "==");
    else
      addToken(TokenType::EQUAL, QString(c));
    break;

  case u'<':
    if (match('='))
      addToken(TokenType::LESS_EQUAL, "<=");
    else
      addToken(TokenType::LESS, QString(c));
    break;

  case u'>':
    if (match('='))
      addToken(TokenType::GREATER_EQUAL, ">=");
    else
      addToken(TokenType::GREATER, QString(c));
    break;

  // Ignore whitespace and tabs.
  case u'\r':
    break;

  case u'\t':
    addToken(TokenType::TAB);
    break;

  case u' ':
    lexSpaces();
    break;

  // String literals
  case u'"':
    lexString();
    break;

  case u'^':
    addToken(TokenType::EXPONENT, QString(c));
    break;

  case u'\n':
    currentLine++;
    break;

  default:
    if (c.isDigit()) {
      // Number literals
      lexNumber();
    } else if (isalpha(c)) {
      // Identifiers
      lexIdentifier();
    } else {
      /// \todo custom lexer exception
      throw std::runtime_error("Unexpected character");
    }
  }
}

bool Lexer::isalpha(QChar c) {
  if (c.isLetter())
    return true;

  switch (c.unicode()) {
  case u'_':
    return true;
  }

  return false;
}

bool Lexer::isalnum(QChar c) { return c.isDigit() || isalpha(c); }

bool Lexer::isAtEnd() const { return currentCharIdx >= source.size(); }

QChar Lexer::advance() { return source[currentCharIdx++]; }

QChar Lexer::peek(int ahead) const {
  if (currentCharIdx + ahead >= source.size())
    return '\0';
  return source[currentCharIdx + ahead];
}

void Lexer::addToken(TokenType tokenType, QString literal) {
  tokens.push_back(std::make_shared<Token>(tokenType, literal, currentLine,
                                           start, currentCharIdx));
}

bool Lexer::match(char expected) {
  if (isAtEnd())
    return false;
  if (source[currentCharIdx] != expected)
    return false;

  // It's match - consume the char
  currentCharIdx++;
  return true;
}

void Lexer::lexString() {
  // Consume all characters between the quotes
  while (peek() != '"' && !isAtEnd()) {
    // There can be newlines in the string literal
    if (peek() == '\n')
      currentLine++;

    advance();
  }

  // Check for unterminated string
  if (isAtEnd())
    throw std::runtime_error("Unterminated string");

  // Consume the last quote
  advance();

  // Trim the start and end quote from the token
  // std::cout << source << std::endl;
  printf("%s\n", source.toStdString().c_str());
  std::string literal =
      source.toStdString().substr(start + 1, currentCharIdx - 1 - (start + 1));
  addToken(TokenType::STRING, QString(literal.c_str()));
}

void Lexer::lexSpaces() {
  int spaces = 1;
  while (peek() == ' ' && !isAtEnd()) {
    spaces++;
    advance();
    if (spaces == 4) {
      addToken(TokenType::TAB);
      break;
    }
  }
}

void Lexer::lexNumber() {
  // Look for first part of the number
  while (peek().isDigit())
    advance();

  bool isFractional{false};

  // Look for fractional part
  if (peek() == delimeter && peek(1).isDigit()) {
    isFractional = true;

    // Consume the delimiter
    advance();

    while (peek().isDigit())
      advance();
  } else if (peek() == delimeter) {
    throw std::runtime_error("Unfinished delimeter");
  }

  TokenType tokenType{isFractional ? TokenType::DECIMAL : TokenType::INTEGER};
  addToken(
      tokenType,
      QString(
          source.toStdString().substr(start, currentCharIdx - start).c_str()));
}

void Lexer::lexIdentifier() {
  while (isalnum(static_cast<QChar>(peek())))
    advance();

  std::string identifier =
      source.toStdString().substr(start, currentCharIdx - start);

  // Check if identifier is a reserved keyword
  std::unordered_map<std::string, TokenType>::const_iterator it =
      keywords.find(identifier);
  if (it != keywords.end()) {
    // The identifier is a keyword
    addToken(it->second);
    return;
  }

  // The identifier is user defined
  addToken(TokenType::IDENTIFIER, QString(identifier.c_str()));
}

} // namespace BirchCas
