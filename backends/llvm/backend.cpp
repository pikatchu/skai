#include <stdio.h>

#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"

#include "skip/Finalized.h"


using namespace llvm;


extern "C" {

  // LLVM compilation context.
  struct Context {
    LLVMContext context;
    std::unique_ptr<Module> module;
    std::map<std::string, Value*> variables;
  };


  Context* SKIP_create_context() {
    Context* ctx = new Context(); 
    ctx->module = std::make_unique<Module>("dasil", ctx->context);
    return ctx;
  }

  void SKIP_release_context(Context* context) {
    delete context;
  }

  Type* SKIP_create_float_type(Context* ctx) {
    return Type::getFloatTy(ctx->context);
  }

  Type* SKIP_create_int_type(Context* ctx) {
    return Type::getInt32Ty(ctx->context);
  }

  std::vector<Type*>* SKIP_create_arg_list() {
    std::vector<Type*>* arg_list = new std::vector<Type*>();
    return arg_list;
  }

  std::vector<Type*>* SKIP_release_arg_list(std::vector<Type*>* args) {
    delete args;
  }

  void SKIP_add_argument(skip::String name, Type* type, std::vector<std::pair<std::string, Type*>>* args) {
    args->push_back({name.toCppString(), type});
  }

  Function* SKIP_create_function(skip::String name, std::vector<std::pair<std::string, Type*>>* args, Type* return_type, Context* ctx) {
    std::vector<std::string> names;
    std::vector<Type*> arg_types;
    for(int i = 0; i < args->size(); ++i){
      names.push_back(args->at(i).first);
      arg_types.push_back(args->at(i).second);
    }
    Function* function = Function::Create(FunctionType::get(return_type, arg_types, false), Function::ExternalLinkage, name.toCppString(), ctx->module.get());
    auto arg_iter = function->arg_begin();
    for (int i = 0; i < names.size(); ++i) {
      auto function_arg = &*arg_iter++;
      function_arg->setName(names[i]);
      ctx->variables.insert({names[i], function_arg});
    }
    return function;
  }


  BasicBlock* SKIP_create_basic_block(skip::String name, Function* function, Context* ctx) {
    BasicBlock* basic_block = BasicBlock::Create(ctx->context, name.toCppString(), function);
    return basic_block;
  }

  IRBuilder<>* SKIP_create_ir_builder(BasicBlock* block) {
    IRBuilder<>* builder = new IRBuilder<>(block);
    return builder;
  }

  void SKIP_release_ir_builder(IRBuilder<>* builder) {
    delete builder;
  }

  Value* SKIP_emit_int_const(int value, IRBuilder<>* builder) {
    return builder->getInt32(value);
  }

  void SKIP_create_variable(skip::String name, Value* value, Context* ctx) {
    ctx->variables.insert({name.toCppString(), value});
    value->setName(name.toCppString());
  }

  Value* SKIP_null_value() {
    return nullptr;
  }


  Value* SKIP_get_variable(skip::String name, const Context* ctx) {
   const std::string c_name = name.toCppString();
   auto var_iter = ctx->variables.find(c_name);
   if (var_iter != ctx->variables.end()) {
     return var_iter->second;
   }
   // FIXME : Better error handeling ?
   throw std::invalid_argument("Can't find variable " + c_name);
  }

  // FIXME: handle float.
  Value* SKIP_emit_float_const(double value, IRBuilder<>* builder) {
    return SKIP_emit_int_const(value, builder);
  }

  void SKIP_print_module(Context* ctx) {
    outs() << *ctx->module;
  }

  Value* SKIP_build_add_op(Value* arg1, Value* arg2, IRBuilder<>* builder) {
    return builder->CreateAdd(arg1, arg2);
  }

  Value* SKIP_build_sub_op(Value* arg1, Value* arg2, IRBuilder<>* builder) {
    return builder->CreateSub(arg1, arg2);
  }

  Value* SKIP_build_mul_op(Value* arg1, Value* arg2, IRBuilder<>* builder) {
    return builder->CreateMul(arg1, arg2);
  }

  void SKIP_build_return(Value* val, IRBuilder<>* builder) {
    builder->CreateRet(val);
  }

}
