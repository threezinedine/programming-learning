#pragma once
#include "common.h"
#include "expression/expression.h"
#include "tokenizer.h"

namespace ntt {

Expression* parseExp(const std::vector<Token>& tokens);

} // namespace ntt
