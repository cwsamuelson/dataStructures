#pragma once

#include <box.hh>

#include <string>
#include <variant>
#include <vector>

namespace flp::Abstract {

struct Expression;
struct Assignment;
struct BinaryExpression;
struct UnaryExpression;
struct VariableExpression;
struct ConstantExpression;
struct FunctionExpression;

using ValueExpression = std::variant<VariableExpression, ConstantExpression>;

struct TopLevel {
  std::variant<std::monostate, Box<Expression>, Box<Assignment>> value;
};

struct BinaryExpression {
  enum class Operator {
    POW,
    TIMES,
    DIV,
    PLUS,
    MINUS,
  };

  Operator op;
  Box<Expression> lhs;
  Box<Expression> rhs;
};

struct UnaryExpression {
  enum class Operator {
    PLUS,
    MINUS,
  };

  Operator op;
  Box<Expression> operand;
};

struct VariableExpression {
  std::string name;
};

struct NamedConstantExpression {
  std::string name;
};

struct ConstantExpression {
  double value;
};

struct FunctionExpression {
  std::string name;
  std::vector<Expression> arguments;
};

struct Expression {
  std::variant<
    std::monostate,
    Box<BinaryExpression>,
    Box<UnaryExpression>,
    Box<ValueExpression>,
    Box<NamedConstantExpression>,
    Box<FunctionExpression>
  > expression;
};

struct Assignment {
  std::string variable;
  Box<Expression> expression;
};

}
