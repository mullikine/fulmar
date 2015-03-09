/* This file was generated by fulmar version 0.9.2. */

#include<stdlib.h>
#include<iostream>
#include<assert.h>
struct Zero {};

template<typename N>
 struct Succ {};

template<typename Name, typename Body>
 struct MLambda {};

template<typename Fun, typename Arg>
 struct App {};

template<typename Name>
 struct Ref {};

template<typename T>
 struct Lit {};

struct Emptyenv {};

template<typename Name, typename Value, typename Env>
 struct Binding {};

template<typename Lam, typename Env>
 struct Closure {};

template<typename Name, typename Env>
 struct EnvLookup;

template<typename Exp, typename Env>
 struct MEval;

template<typename Proc, typename Value>
 struct MApply;

template<typename A, typename B>
 struct MEqual;

template<typename Name, typename Value, typename Env>
 struct EnvLookup<Name, Binding<Name, Value, Env> > { Value typedef result; };

template<typename Gensym7, typename Name2, typename Value, typename Env>
 struct EnvLookup<Gensym7, Binding<Name2, Value, Env> > {
   typename EnvLookup<Gensym7, Env>::result typedef result;
};

template<typename T, typename Gensym8>
 struct MEval<Lit<T>, Gensym8> { T typedef result; };

template<typename Name, typename Gensym9>
 struct MEval<Ref<Name>, Gensym9> {
   typename EnvLookup<Name, Gensym9>::result typedef result;
};

template<typename Name, typename Body, typename Gensym10>
 struct MEval<MLambda<Name, Body>, Gensym10> {
   Closure<MLambda<Name, Body>, Gensym10> typedef result;
};

template<typename Fun, typename Arg, typename Gensym11>
 struct MEval<App<Fun, Arg>, Gensym11> {
   typename MApply<typename MEval<Fun, Gensym11>::result,
                   typename MEval<Arg, Gensym11>::result>::result typedef result
   ;
};

template<typename Name, typename Body, typename Env, typename Gensym12>
 struct MApply<Closure<MLambda<Name, Body>, Env>, Gensym12> {
   typename MEval<Body, Binding<Name, Gensym12, Env> >::result typedef result;
};

template<typename V>
 struct MEqual<V, V> { V typedef result; };
class X {};
class Y {};

int main (int argc, char* argv[]) {

  // Testing [2 => 1, 3 => 0](3):
  EnvLookup<X, Binding<Y, Succ<Zero>,
                                Binding<X, Zero,
                                        Emptyenv> > > :: result typedef result1;

  MEqual<result1, Zero>::result typedef assert1;

  // Testing ((lambda (x) x) 2):

  MEval<App<MLambda<X,Ref<X> >,Lit<Succ<Succ<Zero> > > >,Emptyenv> :: result typedef result2;

  MEqual<result2, Succ<Succ<Zero> > >::result typedef assert2;

  std::cout << "All tests passed!" << std::endl;

  return EXIT_SUCCESS ;
}
