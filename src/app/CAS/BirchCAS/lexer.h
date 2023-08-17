#ifndef LEXER_H
#define LEXER_H

#include "tokentypes.h"
#include <QString>

namespace BirchCas {

struct Token {};

class Lexer {
public:
  Lexer(QString source);
  ~Lexer();
  std::vector<std::shared_ptr<Token>> tokenize();

private:
  const char delimeter{'.'};
  const std::unordered_map<std::string, TokenType> keywords {
      {"if", TokenType::IF},
      {"elif", TokenType::ELIF},
      {"else", TokenType::ELSE},
      {"then", TokenType::THEN},
      {"end", TokenType::END},
      {"while", TokenType::WHILE},
      {"for", TokenType::FOR},
      {"do", TokenType::DO},
      {"true", TokenType::TRUE},
      {"false", TokenType::FALSE},
      {"InternalCall", TokenType::CALL},
  };
  QString source;
  std::vector<std::shared_ptr<Token>> tokens;

  size_t start{0};
  size_t currentCharIdx{0};
  int currentLine{0};

  /**
   * @brief checks if the given character is not a number
   * @return bool
   */
  bool isalpha(QChar);

  /**
   * @brief returns true if the caracter is a number or a character
   * @return bool
   */
  bool isalnum(QChar);

  /**
   * @brief checks whether or not the current character being
   * processed is at the end of the source.
   * @return true if at the end, else false
   */
  bool isAtEnd() const;

  /**
   * @brief scans the next token. Will go through every character
   * until a token has been identified or its the end of the source.
   * Finally it will push the token to the token list.
   */
  void scanToken();

  /**
   * @brief peeks at the lookahead character. It's a readonly
   * and will not advance.
   * @param ahead: optionally specify how far to peek into the source.
   * The next character is when ahead is set to 0 (default).
   * @return the character at the lookahead position in the source. If
   * the lookahead character is outside of the source '\0' is returned.
   */
  QChar peek(int ahead = 0) const;

  /**
   * @brief consumes the character currently being processed,
   * and advances the current char index, to point to the next
   * character from the source.
   * @return
   */
  QChar advance();

  /**
   * @brief adds a token of type tokenType to the token list.
   * @param tokenType: the token type of the token to be added.
   * @param literal: the data about a literal token to be stored
   * with the token.
   */
  void addToken(TokenType tokenType, QString literal = "");

  /**
   * @brief matches the lookahead character to the expected character.
   * If it's a match then consume the character.
   * @param expected: the character to expect the lookahead character
   * to be.
   * @return true if the lookahead character is what thats expeted,
   * else false
   */
  bool match(char expected);

  /**
   * @brief lexes a string literal. Will advance until a terminating
   * quote is found, and create a string token with the literal data
   * field set to be the content inside of the string.
   */
  void lexString();

  /**
   * @brief lexes spaces until 4 or another character is found. Adds 1 TAB token
   * per 4 spaces
   */
  void lexSpaces();

  /**
   * @brief lexes a number literal. Will create a integer or decimal
   * token depending on the type of number literal. The number will
   * be stored in the token's literal data field in string form.
   */
  void lexNumber();

  void lexIdentifier();
};

} // namespace BirchCas

#endif
