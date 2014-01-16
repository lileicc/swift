/*
 * CPPTranslator.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: leili
 */

#include "CPPTranslator.h"

namespace swift {
namespace codegen {

const code::Type CPPTranslator::INT_TYPE("int");
const code::Type CPPTranslator::INT_REF_TYPE("int", true);
const code::Type CPPTranslator::INT_POINTER_TYPE("int*");
const code::Type CPPTranslator::DOUBLE_TYPE("double");
const code::Type CPPTranslator::DOUBLE_POINTER_TYPE("double*");
const code::Type CPPTranslator::STRING_TYPE("std::string");
const code::Type CPPTranslator::BOOL_TYPE("bool");
const code::Type CPPTranslator::VOID_TYPE("void");
const std::string CPPTranslator::SET_EVIDENCE_FUN_NAME = "_set_evidence";
const std::string CPPTranslator::QUERY_EVALUATE_FUN_NAME = "_evaluate_query";
const std::string CPPTranslator::DISTINCT_FIELDNAME = "_name";
const std::string CPPTranslator::DISTRIBUTION_INIT_FUN_NAME = "init";
const std::string CPPTranslator::DISTRIBUTION_GEN_FUN_NAME = "gen";
const std::string CPPTranslator::DISTRIBUTION_LIKELI_FUN_NAME = "likeli";
const std::string CPPTranslator::DISTRIBUTION_LOGLIKELI_FUN_NAME = "loglikeli";
const std::string CPPTranslator::CURRENT_SAMPLE_NUM_VARNAME = "_cur_loop";
const std::string CPPTranslator::WEIGHT_VAR_REF_NAME = "__local_weight";
const std::string CPPTranslator::GLOBAL_WEIGHT_VARNAME = "_weight";
const std::string CPPTranslator::VALUE_VAR_REF_NAME = "__value";
const std::string CPPTranslator::VALUE_ARG_NAME = "__value_arg";
const std::string CPPTranslator::MARK_VAR_REF_NAME = "__mark";
const std::string CPPTranslator::ANSWER_PROCESS_CLASS_NAME = "Hist";
const std::string CPPTranslator::ANSWER_PROCESS_METHOD_NAME = "add";
const std::string CPPTranslator::ANSWER_VAR_NAME_PREFIX = "_answer_";
const std::string CPPTranslator::MAIN_SAMPLING_FUN_NAME = "sample";
const std::string CPPTranslator::SAMPLER_VAR_NAME = "sampler";
const std::string CPPTranslator::MAIN_NAMESPACE_NAME = "swift";
const std::string CPPTranslator::MAIN_INIT_FUN_NAME = "init";
const std::string CPPTranslator::MAIN_FUN_NAME = "main";
const std::string CPPTranslator::LOCAL_NUM_SAMPLE_ARG_NAME = "n";
// randomness
const std::string CPPTranslator::RANDOM_DEVICE_VAR_NAME = "__random_device";
const code::Type CPPTranslator::RANDOM_ENGINE_TYPE(
    "std::default_random_engine");
const std::string CPPTranslator::RANDOM_ENGINE_VAR_NAME = "__random_engine";
const int CPPTranslator::INIT_SAMPLE_NUM = 1;

/**
 * give the name of the type,
 * return the variable name corresponding to the number of objects for this type
 */
std::string getVarOfNumType(std::string name) {
  return "__num_" + name;
}

/**
 * given the name of a variable (can be number var, or random function)
 * return the function name to get the number of objects for this type
 */
std::string getGetterFunName(std::string name) {
  return "__get_" + name;
}

/**
 * given the name of a variable (can be number var, or random function)
 * return the function name to get the likelihood of objects for this type
 */
std::string getLikeliFunName(std::string name) {
  return "__likeli_" + name;
}

/**
 * given the name of a variable (can be number var, or random function)
 * return the function name to set the value
 */
std::string getSetterFunName(std::string name) {
  return "__set_" + name;
}

/**
 * given the name of a variable (can be number var, or random function)
 * return the variable name to get the number of samples for the current variable
 */
std::string getMarkVarName(std::string name) {
  return "__mark_" + name;
}

/**
 * given the name of a variable (can be number var, or random function)
 * return the variable name to get the value of that var/fun
 */
std::string getValueVarName(std::string name) {
  return "__value_" + name;
}

/**
 * get the answer histogram type
 */
code::Type getTemplatedType(std::string containerType, code::Type elementType) {
  code::Type ty(containerType + "<" + elementType.getName() + ">");
  return ty;
}

CPPTranslator::CPPTranslator() {
  useTag = false;
  prog = new code::Code();
  coreNs = new code::NamespaceDecl(MAIN_NAMESPACE_NAME);
  prog->addDecl(coreNs);
  coreCls = NULL;
  coreClsInit = NULL;
}

CPPTranslator::~CPPTranslator() {
  if (!useTag)
    delete prog;
}

void CPPTranslator::translate(swift::ir::BlogModel* model) {
  if (coreCls == NULL) {
    coreCls = code::ClassDecl::createClassDecl(coreNs, model->getName());
    createInit();
  }

  // translate type and distinct symbols;
  for (auto ty : model->getTypes())
    transTypeDomain(ty);

  // translate random function
  for (auto fun : model->getRandFuncs())
    transFun(fun);

  // translate fixed function

  // translate evidence
  transAllEvidence(model->getEvidences());

  transSampleAlg();

  // TODO translate query
  transAllQuery(model->getQueries());

  createMain();
}

code::Code* CPPTranslator::getResult() {
  useTag = true;
  return prog;
}

code::FunctionDecl* CPPTranslator::transSampleAlg() {
  // for the moment, only supporting likelihood weighting algorithm
  // declare the sample method within coreCls
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
      MAIN_SAMPLING_FUN_NAME, VOID_TYPE);
  std::vector<code::ParamVarDecl*> args;
  args.push_back(
      new code::ParamVarDecl(fun, LOCAL_NUM_SAMPLE_ARG_NAME, INT_TYPE));
  fun->setParams(args);
  fun->addStmt(
      new code::DeclStmt(
          new code::VarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE)));
  code::FieldDecl::createFieldDecl(coreCls, GLOBAL_WEIGHT_VARNAME,
      DOUBLE_POINTER_TYPE);
  coreClsInit->addStmt(
      new code::DeleteStmt(new code::VarRef(GLOBAL_WEIGHT_VARNAME), true));
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(GLOBAL_WEIGHT_VARNAME),
          new code::NewExpr(DOUBLE_TYPE,
              new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME)),
          code::OpKind::BO_ASSIGN));
  //call the initialization function
  std::vector<code::Expr*> initArg;
  initArg.push_back(new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME));
  fun->addStmt(
      new code::CallExpr(new code::VarRef(MAIN_INIT_FUN_NAME), initArg));
  // create for loop for the sampling
  code::Stmt* init = new code::BinaryOperator(
      new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME),
      new code::IntegerLiteral(INIT_SAMPLE_NUM), code::OpKind::BO_ASSIGN);
  code::Expr* cond = new code::BinaryOperator(
      new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME),
      new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME), code::OpKind::BO_LEQ);
  code::Expr* step = new code::BinaryOperator(
      new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME), NULL, code::OpKind::BO_INC);
  code::CompoundStmt* body = new code::CompoundStmt();
  // :::=> weight = set_evidence();
  body->addStmt(
      new code::BinaryOperator(new code::VarRef(WEIGHT_VAR_REF_NAME),
          new code::CallExpr(new code::VarRef(SET_EVIDENCE_FUN_NAME)),
          code::OpKind::BO_ASSIGN));
  std::vector<code::Expr*> weightArg;
  weightArg.push_back(new code::VarRef(WEIGHT_VAR_REF_NAME));
  body->addStmt(
      new code::CallExpr(new code::VarRef(QUERY_EVALUATE_FUN_NAME), weightArg));
  // :::==> weight[current_loop] = w;
  body->addStmt(
      new code::BinaryOperator(
          new code::ArraySubscriptExpr(new code::VarRef(GLOBAL_WEIGHT_VARNAME),
              new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME)),
          new code::VarRef(WEIGHT_VAR_REF_NAME), code::OpKind::BO_ASSIGN));
  fun->addStmt(new code::ForStmt(init, cond, step, body));
  return fun;
  //TODO adding other algorithms
}

void CPPTranslator::transTypeDomain(std::shared_ptr<ir::TypeDomain> td) {
  const std::string& name = td->getName();
  code::ClassDecl* cd = code::ClassDecl::createClassDecl(coreNs, name);
  code::FieldDecl::createFieldDecl(cd, DISTINCT_FIELDNAME, STRING_TYPE);
  int len = td->getPreLen();
  std::string numvar = getVarOfNumType(name);
  // create a field in the main class:::    int numvar;
  code::FieldDecl::createFieldDecl(coreCls, numvar, INT_TYPE);
  // create a field in the main class:::    int mark_numvar;
  std::string marknumvar = getMarkVarName(numvar);
  code::FieldDecl::createFieldDecl(coreCls, marknumvar, INT_TYPE);
  // add in the init function:::            numvar = len;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(numvar),
          new code::IntegerLiteral(len), code::OpKind::BO_ASSIGN));
  // add in the init function:::            mark_numvar = -1;
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(marknumvar),
          new code::IntegerLiteral(INIT_SAMPLE_NUM), code::OpKind::BO_ASSIGN));
  if (len > 0) {
    // create the function for getting number of objects in this instance, i.e. numvar
    code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
        getGetterFunName(numvar), INT_TYPE, true);
    fun->addStmt(new code::ReturnStmt(new code::VarRef(numvar)));
    // TODO please add the corresponding distinct name

  }
  // handle number statement
  int numstlen = td->getNumberStmtSize();
  if (numstlen > 0) {
    // TODO create functions for number statement and their likelihood

  }
}

void CPPTranslator::transFun(std::shared_ptr<ir::FuncDefn> fd) {
  if (fd->isRand()) {
    // translate random function
    // create gettfunname function
    transGetterFun(fd);

    // add likelihood function::: double likeli_fun(int, ...);
    transLikeliFun(fd);

    // add setter function::: double set_fun(int, ,,,);
    transSetterFun(fd);
  }
  // TODO handle fixed function
}

code::FunctionDecl* CPPTranslator::transGetterFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string getterfunname = getGetterFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  // adding in the initialization function
  code::FieldDecl::createFieldDecl(coreCls, valuevarname, INT_POINTER_TYPE);
  coreClsInit->addStmt(
      new code::DeleteStmt(new code::VarRef(valuevarname), true));
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(valuevarname),
          new code::NewExpr(INT_TYPE,
              new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME)),
          code::OpKind::BO_ASSIGN));
  // adding in the initialization function
  code::FieldDecl::createFieldDecl(coreCls, markvarname, INT_POINTER_TYPE);
  coreClsInit->addStmt(
      new code::DeleteStmt(new code::VarRef(markvarname), true));
  coreClsInit->addStmt(
      new code::BinaryOperator(new code::VarRef(markvarname),
          new code::NewExpr(INT_TYPE,
              new code::VarRef(LOCAL_NUM_SAMPLE_ARG_NAME)),
          code::OpKind::BO_ASSIGN));
  code::FunctionDecl* getterfun = code::FunctionDecl::createFunctionDecl(
      coreCls, getterfunname, valuetype);
  getterfun->setParams(transParamVarDecls(getterfun, fd->getArgs()));

  addFunValueRefStmt(getterfun, valuevarname, getterfun->getParams(),
      VALUE_VAR_REF_NAME);
  addFunValueRefStmt(getterfun, markvarname, getterfun->getParams(),
      MARK_VAR_REF_NAME);
  // now translating::: if (markvar == current sample num) then return value;
  code::Stmt* st = new code::IfStmt(
      new code::BinaryOperator(new code::VarRef(MARK_VAR_REF_NAME),
          new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME), code::OpKind::BO_EQU),
      new code::ReturnStmt(new code::VarRef(VALUE_VAR_REF_NAME)), NULL);
  getterfun->addStmt(st);
  // now should sample
  // mark the variable first
  st = new code::BinaryOperator(new code::VarRef(MARK_VAR_REF_NAME),
      new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME), code::OpKind::BO_ASSIGN);
  getterfun->addStmt(st);
  //now translate actual sampling part
  transClause(fd->getBody(), VALUE_VAR_REF_NAME);
  // now return the value
  getterfun->addStmt(
      new code::ReturnStmt(new code::VarRef(VALUE_VAR_REF_NAME)));
  return getterfun;
}

code::FunctionDecl* CPPTranslator::transLikeliFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string likelifunname = getLikeliFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // __mark__name
  std::string markvarname = getMarkVarName(name);

  code::FunctionDecl* likelifun = code::FunctionDecl::createFunctionDecl(
      coreCls, likelifunname, DOUBLE_TYPE);
  likelifun->setParams(transParamVarDecls(likelifun, fd->getArgs()));

  // now the value of this function app var is in RETURN_VAR_NAME
  addFunValueRefStmt(likelifun, valuevarname, likelifun->getParams(),
      VALUE_VAR_REF_NAME);
  // declare the weight variable and setting its init value
  // it is recording the log likelihood
  // ::: __weight = 0
  code::VarDecl* weightvar = new code::VarDecl(likelifun, WEIGHT_VAR_REF_NAME,
      DOUBLE_TYPE, new code::FloatingLiteral(0));
  likelifun->addStmt(new code::DeclStmt(weightvar));
  // translate the Clause and calculate weight
  transClause(fd->getBody(), WEIGHT_VAR_REF_NAME, VALUE_VAR_REF_NAME);
  // now return the value
  likelifun->addStmt(
      new code::ReturnStmt(new code::VarRef(WEIGHT_VAR_REF_NAME)));
  return likelifun;
}

code::FunctionDecl* CPPTranslator::transSetterFun(
    std::shared_ptr<ir::FuncDefn> fd) {
  const std::string & name = fd->getName();
  std::string likelifunname = getLikeliFunName(name);
  code::Type valuetype = mapIRTypeToCodeType(fd->getRetTyp());
  // __value__name for recording the value of the function application variable
  std::string valuevarname = getValueVarName(name);
  // __mark__name
  std::string markvarname = getMarkVarName(name);
  std::string setterfunname = getSetterFunName(name);
  code::FunctionDecl* setterfun = code::FunctionDecl::createFunctionDecl(
      coreCls, setterfunname, DOUBLE_TYPE);
  std::vector<code::ParamVarDecl*> args_with_value = transParamVarDecls(
      setterfun, fd->getArgs());
  addFunValueRefStmt(setterfun, valuevarname, args_with_value,
      VALUE_VAR_REF_NAME, valuetype);
  addFunValueRefStmt(setterfun, markvarname, args_with_value,
      MARK_VAR_REF_NAME);
  args_with_value.push_back(
      new code::ParamVarDecl(setterfun, VALUE_ARG_NAME, valuetype));
  setterfun->setParams(args_with_value);
  code::Stmt* st = new code::BinaryOperator(new code::VarRef(MARK_VAR_REF_NAME),
      new code::VarRef(CURRENT_SAMPLE_NUM_VARNAME), code::OpKind::BO_ASSIGN);
  setterfun->addStmt(st);
  // :::==> value_var = value_arg
  st = new code::BinaryOperator(new code::VarRef(VALUE_VAR_REF_NAME),
      new code::VarRef(VALUE_ARG_NAME), code::OpKind::BO_ASSIGN);
  setterfun->addStmt(st);
  std::vector<code::Expr*> args_ref;
  for (auto a : fd->getArgs()) {
    args_ref.push_back(new code::VarRef(a->getVar()));
  }
  st = new code::ReturnStmt(
      new code::CallExpr(new code::VarRef(likelifunname), args_ref));
  setterfun->addStmt(st);
  return setterfun;
}

code::Stmt* CPPTranslator::transClause(std::shared_ptr<ir::Clause> clause,
    std::string retvar, std::string valuevar) {
  std::shared_ptr<ir::Branch> br = std::dynamic_pointer_cast<ir::Branch>(
      clause);
  if (br) {
    return transBranch(br, retvar, valuevar);
  }
  std::shared_ptr<ir::IfThen> ith = std::dynamic_pointer_cast<ir::IfThen>(
      clause);
  if (ith) {
    return transIfThen(ith, retvar, valuevar);
  }
  std::shared_ptr<ir::Expr> expr = std::dynamic_pointer_cast<ir::Expr>(clause);
  if (expr) {
    code::CompoundStmt* cst = new code::CompoundStmt();
    cst->addStmt(
        new code::BinaryOperator(new code::VarRef(retvar),
            transExpr(expr, valuevar), code::OpKind::BO_ASSIGN));
    // TODO no 100% correct here why??
    return cst;
  }
  //todo: warning should not reach here
  return NULL;
}

code::ParamVarDecl* CPPTranslator::transParamVarDecl(code::DeclContext* context,
    const std::shared_ptr<ir::VarDecl> var) {
  return new code::ParamVarDecl(context, var->getVar(),
      mapIRTypeToCodeType(var->getTyp()));
}

std::vector<code::ParamVarDecl*> CPPTranslator::transParamVarDecls(
    code::DeclContext* context,
    const std::vector<std::shared_ptr<ir::VarDecl> > & vars) {
  std::vector<code::ParamVarDecl*> vds;
  for (auto v : vars) {
    vds.push_back(transParamVarDecl(context, v));
  }
  return vds;
}

code::Stmt* CPPTranslator::transBranch(std::shared_ptr<ir::Branch> br,
    std::string retvar, std::string valuevar) {
  code::SwitchStmt* sst = new code::SwitchStmt(transExpr(br->getVar()));
  code::CaseStmt* cst;
  for (size_t i = 0; i < br->size(); i++) {
    cst = new code::CaseStmt(transExpr(br->getCond(i)),
        transClause(br->getBranch(i), retvar));
    sst->addStmt(cst);
    sst->addStmt(new code::BreakStmt());
  }
  return sst;
}

code::Stmt* CPPTranslator::transIfThen(std::shared_ptr<ir::IfThen> ith,
    std::string retvar, std::string valuevar) {
  // TODO translate ifthenelse
  return NULL;
}

code::Expr* CPPTranslator::transExpr(std::shared_ptr<ir::Expr> expr,
    std::string valuevar) {
  std::vector<code::Expr*> args;
  for (size_t k = 0; k < expr->argSize(); k++) {
    args.push_back(transExpr(expr->get(k)));
  }
  // warning::: better to put the above code in separate function
  // translate distribution expression
  std::shared_ptr<ir::Distribution> dist = std::dynamic_pointer_cast<
      ir::Distribution>(expr);
  if (dist) {
    return transDistribution(dist, args, valuevar);
  }

  // translate variable reference
  std::shared_ptr<ir::FunctionCall> fc = std::dynamic_pointer_cast<
      ir::FunctionCall>(expr);
  if (fc) {
    return transFunctionCall(fc, args);
  }

  std::shared_ptr<ir::ConstSymbol> cs = std::dynamic_pointer_cast<
      ir::ConstSymbol>(expr);
  if (cs) {
    // TODO translate the constsymbol
    // for the moment just simple trick
    return new code::IntegerLiteral(0);
  }
  
  std::shared_ptr<ir::MapExpr> mex = std::dynamic_pointer_cast<
      ir::MapExpr>(expr);
  if (mex) {
    return transMapExpr(mex);
  }
  

  // TODO translate other expression
  // if valuevar is provided it should be
  return NULL;
}

code::Expr* CPPTranslator::transMapExpr(std::shared_ptr<ir::MapExpr> mex) {
  
}

code::Expr* CPPTranslator::transDistribution(
    std::shared_ptr<ir::Distribution> dist, std::vector<code::Expr*> args,
    std::string valuevar) {
  std::string name = dist->getDistrName();
  std::string distname = name + std::to_string((size_t) dist.get());
  if (valuevar.empty()) {
    // now actual sampling a value from the distribution
    // define a field in the main class corresponding to the distribution
    code::FieldDecl::createFieldDecl(coreCls, distname, code::Type(name));
    //put initialization in coreClasInit
    coreClsInit->addStmt(
        new code::CallExpr(
            new code::BinaryOperator(new code::VarRef(distname),
                new code::VarRef(DISTRIBUTION_INIT_FUN_NAME),
                code::OpKind::BO_FIELD), args));
    // :::==> distribution.gen(random_engine);
    std::vector<code::Expr *> rd;
    rd.push_back(new code::VarRef(RANDOM_ENGINE_VAR_NAME));
    return new code::CallExpr(
        new code::BinaryOperator(new code::VarRef(distname),
            new code::VarRef(DISTRIBUTION_GEN_FUN_NAME),
            code::OpKind::BO_FIELD), rd);
  } else {
    // calculating likelihood
    // :::==> distribution.loglikeli
    std::vector<code::Expr *> args;
    args.push_back(new code::VarRef(valuevar));
    return new code::CallExpr(
        new code::BinaryOperator(new code::VarRef(distname),
            new code::VarRef(DISTRIBUTION_LOGLIKELI_FUN_NAME),
            code::OpKind::BO_FIELD), args);
  }
}

void CPPTranslator::createInit() {
  // TODO adding setup for
  // 2. member declarations for core class, need valuearray, mark array, ...
  // 3. initialization function to initialize the values (function called in sample(n)
  coreClsInit = code::FunctionDecl::createFunctionDecl(coreCls,
      MAIN_INIT_FUN_NAME, VOID_TYPE);
  std::vector<code::ParamVarDecl*> args;
  args.push_back(
      new code::ParamVarDecl(coreClsInit, LOCAL_NUM_SAMPLE_ARG_NAME, INT_TYPE));
  coreClsInit->setParams(args);
  code::FieldDecl::createFieldDecl(coreCls, CURRENT_SAMPLE_NUM_VARNAME,
      INT_TYPE);
  code::FieldDecl::createFieldDecl(coreCls, RANDOM_DEVICE_VAR_NAME,
      RANDOM_ENGINE_TYPE);
}

void CPPTranslator::addFunValueRefStmt(code::FunctionDecl* fun,
    std::string valuevarname, std::vector<code::ParamVarDecl*>& valueindex,
    std::string valuerefname, code::Type varType) {
  // the value of this function application variable is stored in
  // valuevarname[index1][index2]...
  // where the index are corresponding to the arguments
  code::Expr* exp = new code::VarRef(valuevarname);
  for (auto prm : valueindex) {
    exp = new code::ArraySubscriptExpr(exp, new code::VarRef(prm->getId()));
  }

  // assign the function application variable value to valuerefname
  code::VarDecl* retvar = new code::VarDecl(fun, valuerefname, varType, exp);
  code::DeclStmt* dst = new code::DeclStmt(retvar);
  fun->addStmt(dst);
}

void CPPTranslator::transEvidence(code::FunctionDecl* fun,
    std::shared_ptr<ir::Evidence> evid) {
  const std::shared_ptr<ir::Expr>& left = evid->getLeft();
  // check whether left is a function application variable
  std::shared_ptr<ir::FunctionCall> leftexp = std::dynamic_pointer_cast<
      ir::FunctionCall>(left);
  if (leftexp) {
    // left side of the evidence is a function application
    std::string blogfunname = leftexp->getRefer()->getName(); // the function name in blog model
    std::string setterfunname = getSetterFunName(blogfunname); // setter function for the blog function predicate
    std::vector<code::Expr*> args;
    // now translate arguments to this setter function
    for (auto a : leftexp->getArgs()) {
      args.push_back(transExpr(a));
    }
    // assign the right side of the evidence to left function application variable
    args.push_back(transExpr(evid->getRight()));
    // call setter function and calculate likelihood
    code::Stmt* st = new code::BinaryOperator(
        new code::VarRef(WEIGHT_VAR_REF_NAME),
        new code::CallExpr(new code::VarRef(setterfunname), args),
        code::OpKind::BO_SPLUS);
    fun->addStmt(st);
  }
  // TODO adding support for other evidence
  // 1. Cardinality evidence
  // 2. Set evidence
}

void CPPTranslator::transAllEvidence(
    std::vector<std::shared_ptr<ir::Evidence> > evids) {
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
      SET_EVIDENCE_FUN_NAME, DOUBLE_TYPE);
  code::VarDecl* weightvar = new code::VarDecl(fun, WEIGHT_VAR_REF_NAME,
      DOUBLE_TYPE, new code::FloatingLiteral(0));
  fun->addStmt(new code::DeclStmt(weightvar));
  for (auto evid : evids) {
    transEvidence(fun, evid);
  }
  fun->addStmt(new code::ReturnStmt(new code::VarRef(WEIGHT_VAR_REF_NAME)));
}

void CPPTranslator::transAllQuery(
    std::vector<std::shared_ptr<ir::Query> > queries) {
  code::FunctionDecl* fun = code::FunctionDecl::createFunctionDecl(coreCls,
      QUERY_EVALUATE_FUN_NAME, VOID_TYPE, true);
  std::vector<code::ParamVarDecl*> args;
  // query function has one argument of double, for weight
  args.push_back(new code::ParamVarDecl(fun, WEIGHT_VAR_REF_NAME, DOUBLE_TYPE));
  fun->setParams(args);
  int index = 0;
  for (auto qr : queries) {
    transQuery(fun, qr, index);
    ++index;
  }
}

void CPPTranslator::transQuery(code::FunctionDecl* fun,
    std::shared_ptr<ir::Query> qr, int n) {
  std::string answervarname = ANSWER_VAR_NAME_PREFIX + std::to_string(n);
  code::FieldDecl(coreCls, answervarname,
      getTemplatedType(ANSWER_PROCESS_CLASS_NAME,
          mapIRTypeToCodeType(qr->getVar()->getTyp())));
  std::vector<code::Expr*> args;
  args.push_back(transExpr(qr->getVar()));
  args.push_back(new code::VarRef(WEIGHT_VAR_REF_NAME));
  fun->addStmt(
      new code::CallExpr(
          new code::BinaryOperator(new code::VarRef(answervarname),
              new code::VarRef(ANSWER_PROCESS_METHOD_NAME),
              code::OpKind::BO_FIELD), args));
}

code::Type CPPTranslator::mapIRTypeToCodeType(const ir::Ty* ty) {
  switch (ty->getTyp()) {
  case ir::IRConstant::BOOL:
    return BOOL_TYPE;
  case ir::IRConstant::INT:
    return INT_TYPE;
  case ir::IRConstant::DOUBLE:
    return DOUBLE_TYPE;
  case ir::IRConstant::STRING:
    return STRING_TYPE;
  default:
    return INT_TYPE; // all declared type return int type
  }
}

code::Expr* CPPTranslator::transFunctionCall(
    std::shared_ptr<ir::FunctionCall> fc, std::vector<code::Expr*> args) {
  std::string getterfunname;
  switch (fc->getKind()) {
  case ir::IRConstant::RANDOM:
    getterfunname = getGetterFunName(fc->getRefer()->getName());
    return new code::CallExpr(new code::VarRef(getterfunname), args);
  case ir::IRConstant::FIXED:
    // todo
  default:
    return NULL;
  }
}

void CPPTranslator::createMain() {
  mainFun = code::FunctionDecl::createFunctionDecl(prog, MAIN_FUN_NAME,
      INT_TYPE);
  // todo better way to name the type
  code::Stmt* st = new code::DeclStmt(
      new code::VarDecl(mainFun, SAMPLER_VAR_NAME,
          code::Type(
              coreNs->getName() + std::string("::") + coreCls->getName())));
  mainFun->addStmt(st);
  std::vector<code::Expr*> args;
  args.push_back(new code::IntegerLiteral(10000));
  st = code::CallExpr::createMethodCall(SAMPLER_VAR_NAME,
      MAIN_SAMPLING_FUN_NAME, args);
  mainFun->addStmt(st);
  // todo add printing
}

} /* namespace codegen */
} /* namespace swift */

