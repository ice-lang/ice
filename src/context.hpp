#pragma once

#include <map>
#include <stack>
#include <string>
#include <exception>
#include <stdexcept>
#include <filesystem>
#include "code.hpp"
#include "error.hpp"
#include "scope.hpp"
#include "helper.hpp"

namespace ice_language
{
// Context should be contructed by make_shared
class Context : public std::enable_shared_from_this<Context>
{
  private:
    using StackType = std::stack<Ptr<ObjectPtr>>;

  public:
    // this for resume from ContObject
    Context(Ptr<Context> resume)
      : pre_context_(resume->pre_context_),
        scope_(std::make_shared<Scope>(resume->scope_)),
        code_(resume->code_), pc_(resume->pc_),
        stack_(std::make_shared<StackType>(*resume->stack_)),
        current_path_(resume->current_path_) {}

    // copy ctor
    Context(const Context &context)
      : pre_context_(context.pre_context_),
        scope_(context.scope_),
        code_(context.code_), pc_(context.pc_),
        stack_(std::make_shared<StackType>(*context.stack_)),
        current_path_(context.current_path_) {}

    Context(Ptr<Code> code, std::filesystem::path path = std::filesystem::current_path())
      : pre_context_(nullptr),
        scope_(std::make_shared<Scope>(nullptr)),
        code_(code), pc_(0),
        stack_(std::make_shared<StackType>()),
        current_path_(std::move(path)) {}

    Context(Ptr<Context> pre, Ptr<Scope> scope,
        Ptr<Code> code, std::size_t pc = 0)
      : pre_context_(pre), scope_(std::make_shared<Scope>(scope)),
        code_(code), pc_(pc), stack_(pre->stack_),
        current_path_(pre->current_path_) {}

    static void execute();

    static void
    add_not_defined_symbol(const std::string &name,
        Ptr<ObjectPtr> ptr);
    static void
    rm_not_defined_symbol(Ptr<ObjectPtr> ptr);
    static const std::string
    &get_not_defined_symbol(Ptr<ObjectPtr> ptr);

    Ptr<Context> pre_context()
    {
        return pre_context_;
    }

    Ptr<Scope> &scope()
    {
        return scope_;
    }

    Ptr<Code> &code()
    {
        return code_;
    }

    std::size_t &pc()
    {
        return pc_;
    }

    Instruction &ins()
    {
        return code_->get_instructions()[pc_];
    }

    Instruction &ins_at(std::size_t index) {
        return code_->get_instructions()[index];
    }

    Opcode opcode()
    {
        return code_->opcode_at(pc_);
    }

    std::any &oprand()
    {
        return code_->oprand_at(pc_);
    }

    void push(ObjectPtr value)
    {
        stack_->push(std::make_shared<ObjectPtr>(value));
    }

    void push_straight(Ptr<ObjectPtr> ptr)
    {
        stack_->push(ptr);
    }

    template <typename R = Object>
    Ptr<R> top()
    {
        if (*stack_->top() == nullptr)
        {
            throw RuntimeError(
                "no such var named " +
                get_not_defined_symbol(stack_->top()));
        }
        return std::reinterpret_pointer_cast<R>(*stack_->top());
    }

    Ptr<ObjectPtr> &top_straight()
    {
        return stack_->top();
    }

    void set_top(ObjectPtr ptr)
    {
        stack_->top() = std::make_shared<ObjectPtr>(ptr);
    }

    template <typename R = Object>
    Ptr<R> pop()
    {
        auto res = top<R>();
        stack_->pop();
        return res;
    }

    Ptr<ObjectPtr> pop_straight()
    {
        auto res = top_straight();
        stack_->pop();
        return res;
    }

    std::size_t size()
    {
        return stack_->size();
    }

    std::filesystem::path &current_path()
    {
        return current_path_;
    }

  private:
    Ptr<Context> pre_context_;
    Ptr<Scope> scope_;
    Ptr<Code> code_;
    std::size_t pc_;
    Ptr<StackType> stack_;
    std::filesystem::path current_path_;
};

inline Ptr<Context> theCurrentContext = nullptr;
}
