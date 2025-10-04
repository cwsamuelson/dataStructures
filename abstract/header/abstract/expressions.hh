#pragma once

#include <box.hh>

#include <string>
#include <variant>
#include <vector>

namespace flp::Abstract {

struct Assignment;
struct BinaryExpression;
struct UnaryExpression;
struct FunctionExpression;
struct CallExpression;

using VariableExpression = std::string;
using ConstantExpression = double;
using ValueExpression =
  std::variant<
    VariableExpression,
    ConstantExpression
  >;
using Expression =
  std::variant<
    Box<BinaryExpression>,
    Box<UnaryExpression>,
    Box<ValueExpression>,
    Box<ConstantExpression>,
    Box<FunctionExpression>,
    Box<CallExpression>
  >;
using TopLevel =
  std::variant<
    std::monostate,
    Box<Expression>,
    Box<Assignment>
  >;

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

struct FunctionExpression {
  std::string name;
  std::vector<Expression> parameters;
  std::vector<Expression> body;
};

struct CallExpression {
  std::string name;
  std::vector<Expression> arguments;
};

struct Assignment {
  std::string variable;
  Box<Expression> expression;
};

}
