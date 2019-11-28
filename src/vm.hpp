#pragma once

#include <stack>
#include <memory>
#include "scope.hpp"

namespace ice_language
{
class VM
{
  public:
    VM() : scope_(nullptr) {}

    void execute_ins(Instruction &ins)
    {
        scope_.execute_ins(ins);
    }

    void execute_code(Code &code)
    {
        scope_.execute_code(code);
    }

  private:
    Scope scope_;
};
} // namespace ice_language