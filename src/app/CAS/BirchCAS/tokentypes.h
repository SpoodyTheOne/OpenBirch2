#ifndef TOKENTYPES_H
#define TOKENTYPES_H

#include <string>
#include <unordered_map>

enum TokenType
{
    // Single character tokens
    LPAREN,
    RPAREN,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    STAR,
    SLASH,
    SEMICOLON,
    COLON,
    TAB,
    EXPONENT,

    // One or two character tokens
    BANG,
    EQUAL,
    GREATER,
    LESS,
    BANG_EQUALS,
    EQUAL_EQUAL,
    COLON_EQUALS,
    SLASH_EQUALS,
    GREATER_EQUAL,
    LESS_EQUAL,

    // Literals
    IDENTIFIER,
    STRING,
    INTEGER,
    DECIMAL,

    // Keywords
    IF,
    ELIF,
    ELSE,
    THEN,
    END,
    WHILE,
    FOR,
    DO,
    TRUE,
    FALSE,
    CALL,

    NEWLINE, // End Of Line
    END_OF_FILE, // End Of File/input
};

const std::unordered_map<TokenType, std::string> tokenType2String{
    {TokenType::LPAREN, "Left Parenthesis"},
    {TokenType::RPAREN, "Right Parenthesis"},
    {TokenType::COMMA, "Comma"},
    {TokenType::DOT, "Dot"},
    {TokenType::MINUS, "Minus"},
    {TokenType::PLUS, "Plus"},
    {TokenType::STAR, "Asterik"},
    {TokenType::SLASH, "Slash"},
    {TokenType::SEMICOLON, "Semicolon"},
    {TokenType::COLON, "Colon"},
    {TokenType::TAB, "Tab"},
    {TokenType::EXPONENT, "Exponent"},
    {TokenType::BANG, "Exclamation"},
    {TokenType::EQUAL, "Equal"},
    {TokenType::GREATER, "Greater"},
    {TokenType::LESS, "Less"},
    {TokenType::BANG_EQUALS, "Not Equals (Bang)"},
    {TokenType::EQUAL_EQUAL, "Equality"},
    {TokenType::SLASH_EQUALS, "Not Equals (Slash)"},
    {TokenType::GREATER_EQUAL, "Greater Equal"},
    {TokenType::LESS_EQUAL, "Less Equal"},
    {TokenType::IDENTIFIER, "Identifier"},
    {TokenType::STRING, "String"},
    {TokenType::INTEGER, "Integer"},
    {TokenType::DECIMAL, "Decimal"},
    {TokenType::IF, "If"},
    {TokenType::ELIF, "Else if"},
    {TokenType::ELSE, "Else"},
    {TokenType::THEN, "Then"},
    {TokenType::END, "End"},
    {TokenType::WHILE, "While"},
    {TokenType::FOR, "For"},
    {TokenType::DO, "Do"},
    {TokenType::TRUE, "True"},
    {TokenType::FALSE, "False"},
    {TokenType::NEWLINE, "New Line"},
    {TokenType::END_OF_FILE, "End of File"}
};

#endif // TOKENTYPES_H
