#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_ 1

#include "Primes.h"
#include "Executor.h"
#include "PrimeFactoring.h"
#include "GrammarTree.h"
#include "NumberException.h"
#include "LexicalScaner.h"
#include "Tree.h"
#include "Error.h"
#include "Optimizer.h"
//#include "Polynom.h"
#include <string>
using namespace std;

class Executor
{
public:
    Executor() : primes(100000)
    {

    }

    ~Executor() {}

    typedef set<Variable>::const_iterator set_const_iterator;

    string execAll(string const &inp)
    {
        try
        {
            LexicalScanner ls(inp);
            Token tok = ls.get();
            vector<LargeNumber> soleNumbers;
            if (tok.code == Token::Identifier)
            {
                string name = tok.val;
                if (name == "$clear")
                {
                    Tree::vartable().clearNonSystem();
                    return "";
                }
                else if (name == "$vars")
                {
                    string ret;
                    vector<string> vars = Tree::vartable().getAllNames();
                    for (size_t i = 0; i < vars.size(); i++)
                    {
                        Variable var;
                        Tree::vartable().find(vars[i], var);
                        ret += var.name;
                        ret += "=";
                        ret += var.values[0].toString();
                        ret += "\\medskip\n";
                    }
                    return ret;
                }
                Token t1 = ls.peek();
                if (t1.code == Token::OpAssign)
                {
                    ls.get(); // skip '='
                    string rest(&inp[inp.find('=') + 1]);
                    GrammarTree gp(rest);
                    Tree t = gp.getTree();
                    Number value = t.evaluate(NULL);
                    Variable v;
                    if (Tree::vartable().find(name, v) != Error::OK)
                    {
                        v.name = name;
                        v.values.push_back(value);
                        Tree::vartable().add(v);
                    }
                    else
                    {
                        Tree::vartable().setValue(name, value);
                    }
                    value.normalize();
                    if (name == "$digits")
                    {
                        Number::setPresentationMode(value);
                    }
                    return ""; // value.toString();
                }
            }
            if (tok.code == Token::IntegerConst && (
                ls.peek().code == Token::IntegerConst ||
                ls.peek().code == Token::Empty ||
                ls.peek().code == Token::OpEOF ||
                ls.peek().code == Token::Error))
            {
                soleNumbers.push_back(LargeNumber(tok.val));
            }
            if (tok.code == Token::IntegerConst && ls.peek().code == Token::IntegerConst)
            {
                soleNumbers.push_back(LargeNumber(ls.peek().val));
            }
            string ret;
            GrammarTree gp(inp);
			Tree t = gp.getTree();
#if 0
            Polynom p(t);
            if (p.isValid()) {
                printf("Tree='%s'\n", t.debugPrint("tree", 0).c_str());
                printf("Polynom='%s'\n", p.toString().c_str());
            }
#endif
            string gs = t.toString();
            set<Variable> vars;
            t.usedVariables(vars);
            bool evaluateOnly = true;
            for (set_const_iterator it = vars.begin(); it != vars.end(); it++)
            {
                Variable var;
                if (Tree::vartable().find(it->name, var) != Error::OK)
                {
                    evaluateOnly = false;
                    break;
                }
            }
            if (evaluateOnly && vars.size() != 0)
            {
                Number r = t.evaluate(NULL);
                r.normalize();
                ret = r.toTexString();
                return ret;
            }
            if (vars.size() == 0)
            {
                Number rn = t.evaluate(NULL);
                rn.normalize();
                if (rn.isInteger())
                {
                    if (soleNumbers.size() == 1)
                    {
                        if (rn.toIntegerTrunc() >= LargeNumber("1000000000000000000"))
                        {
                            ret = "@: Factoring would be too long";
                        }
                        else
                        {
                            vector<LargeNumber> f = PrimeFactoring::factor(rn.toIntegerTrunc(), primes);
                            if (f.size() > 1)
                            {
                                ret = rn.toString();
                                ret += " = ";
                                for (int i = 0; i < (int)f.size(); i++)
                                {
                                    ret += f[i].toString();
                                    if (i != (int)f.size() - 1)
                                    {
                                        ret += " * ";
                                    }
                                }
                            }
                            else
                            {
                                ret = rn.toString();
                                ret += " - is prime number";
                            }
                        }
                    }
                    else if (soleNumbers.size() >= 2)
                    {
                        LargeNumber gcd = LargeNumber::GCD(soleNumbers[0], soleNumbers[1]);
                        LargeNumber lcm = LargeNumber::LCM(soleNumbers[0], soleNumbers[1]);
                        ret = "GCD(";
                        ret += soleNumbers[0].toString();
                        ret += ",";
                        ret += soleNumbers[1].toString();
                        ret += ") = ";
                        ret += gcd.toString();
                        ret += "\\ \\ \n LCM(";
                        ret += soleNumbers[0].toString();
                        ret += ",";
                        ret += soleNumbers[1].toString();
                        ret += ") = ";

                        ret += lcm.toString();
                        ret += "\\medskip \n";
                    }
                    else
                    {
                        ret = rn.toTexString();
                    }
                }
                else
                {
                    ret = rn.toTexString();
                }
                return ret;
            }
            else
            {
                //printf("many");
				Tree t2 = t.clone();
				t2.canonify();
				string dp = t.toString(); // .debugPrint("Tree:", 0);
				string dp2 = t2.toString();
				vector<Number> roots = t2.findRoots(Number(-100.0), Number(100.0), 0.000001);
                ret+=dp;//@@@@

                ret += " \\ ";

                ret.push_back('\n');//@@@@
                ret+=dp2;//@@@@

                ret.push_back('\n');//@@@@
				printf("%s\n%s\n", dp.c_str(), dp2.c_str());
				if (roots.size() > 0) {
                    ret += "roots found: ";//@@@@
					printf("roots found: ");
                    for (int i = 0; i < (int)roots.size(); i++) {
                        ret+=roots[i].toString();//@@@@
                        ret.push_back(' ');
						printf("%s ", roots[i].toString().c_str());
                    }

                    ret += " \\ ";

                    ret.push_back('\n');//@@@@
					printf("\n");
				}
				NVector start(1, -100.);
				NVector end(1, 100.);
				Number val;
				Number minval = minimize(&t2, start, end, 1, 0.001, val);
                printf("Minimum %g reached at %g\n", minval.toDouble(),
                       val.toDouble());
                ret+="Minimum ";//@@@@
                ret+=minval.toString();//@@@@
                ret+=" reached at ";//@@@@
                ret+=val.toString();//@@@@

                ret += " \\ ";

                ret.push_back('\n');//@@@@
                return ret;
            }
        }
        catch (Error::Code er)
        {
            string ret = "@: ";
            return ret + Error::explainCode(er);
        }
        catch (NumberException const &er)
        {
            string ret = "@: ";
            return ret + er.getMessage();
        }
        catch (const char *s)
        {
            return string("@: ") + s;
        }
    }

//     string exec(string const &inp)
//     {
//         try
//         {
//             LexicalScanner ls(inp);
//             Token t = ls.get();
//             RationalNumber value;
//             if (t.code == Token::Identifier)
//             {
//                 if (t.val == "factor")
//                 {
//                     string ret;
//                     if (ls.peek().code == Token::IntegerConst)
//                     {
//                         t = ls.get();
//                         vector<LargeNumber> d = PrimeFactoring::factor(t.val, primes);
//                         for (size_t i = 0; i < d.size(); i++)
//                         {
//                             ret += d[i].toString();
//                             if (i != d.size()-1)
//                             {
//                                 ret += "*";
//                             }
//                         }
//                     }
//                     else
//                     {
//                         GrammarTree gp(&inp[6]);
//                         Tree t = gp.getTree();
//                         ret = t.toString();
//                     }
//                     return ret;
//                 }
//                 if (t.val == "sqrt")
//                 {
//                     string ret;
//                     GrammarTree gp(&inp[5]);
//                     Tree p = gp.getTree();
//                     Number rn = p.evaluate(Tree::vartable);
// 					Number r = Number::sqrt(rn);
//                     ret = r.toString();
//                     return ret;
//                 }
//                 string name = t.val;
//                 Token t1 = ls.peek();
//                 if (t1.code == Token::OpAssign)
//                 {
//                     ls.get(); // skip '='
//                     string rest(&inp[inp.find('=') + 1]);
//                     GrammarTree gp(rest);
//                     Tree t = gp.getTree();
//                     Number value = t.evaluate();
//                     Variable v;
//                     if (Tree::vartable.find(name, v) != Error::OK)
//                     {
//                         v.name = name;
//                         v.values.push_back(value);
//                         Tree::vartable.add(v);
//                     }
//                     else
//                     {
//                         Tree::vartable.setValue(name, RationalNumber(value));
//                     }
//                     value.normalize();
//                     if (name == "$digits")
//                     {
//                         T::setPresentationMode((int)value.getNumerator().getLongLongValue());
//                     }
//                     return value.toString();
//                 }
//             }
//             if (t.code == Token::OpQuestion)
//             {
//                 ls.get(); // skip '='
//                 string rest(&inp[+inp.find('?')+1]);
//                 GrammarTree<T> gp(rest);
//                 Tree<T> t = gp.getTree();
//                 value = t.evaluate();
//                 value.normalize();
//                 return value.toString();
//             }
//             GrammarTree<T> gp(inp);
//             Polynom<T> p = gp.getPolynom();
//             if (!p.isValid())
//             {
//                 Tree<T> t = gp.getTree();
//             //	string tt = p.toString() + "\n-------\n";
//             //	Tree tr = p.getTree();
//             //	tt += tr.toString();
//             //	return tt;
//                 return t.toString();
//             }
//             else
//             {
//                 return p.toTexString();
//             }
//         }
//         catch (Error::Code er)
//         {
//             return Error::explainCode(er);
//         }
//         catch (const char *s)
//         {
//             return s;
//         }
//     }

    Primes primes;

};

#endif
