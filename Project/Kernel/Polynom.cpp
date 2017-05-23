#include "Polynom.h"
#include "GrammarTree.h"
#include "Primes.h"
#include "PrimeFactoring.h"

Polynom::Polynom(void)
{
	initialized = false;
}


Polynom::Polynom(Tree const &init)
{
	initialized = false;		
    initialize(init);
	tree = init;
	treeIntact = true;
}

bool Polynom::initialize(Polynom const &p)
{
	initialized = p.initialized;
	vars = p.vars;
	coeffs = p.coeffs;
	tree = p.tree;
	treeIntact = p.treeIntact;
	return initialized;
}

bool Polynom::initialize(const string &s)
{
	GrammarTree gp(s);
//	Polynom pt = gp.getPolynom();
//	initialize(pt);
	return initialized;
}


#if 0
deque<Polynom> Polynom::factor() const
{
	deque<Polynom> ret;
	Polynom cp(*this);
	Number root;
	while(cp.root(root))
	{
//		LargeNumber newRoot;
//		if (root.isGoodEnough(newRoot))
//		{
//			root = newRoot;
//		}
		string sret;
		sret += "(";
		sret += vars[0].name;
		Number ri = root;
		if (ri.isNegative())
		{
			sret += "+";
		    ri.negate();
		}
		else
		{
			sret += "-";
		}
		sret += ri.toString();
		sret += ")";
		GrammarTree np(sret);
		Polynom divider = np.getPolynom();
		ret.push_back(divider);
		Polynom newth, newremain;
		Polynom::divmod(cp, divider, newth, newremain);
//		printf("f=%s newth=%s\n", divider.toString().c_str(), newth.toString().c_str());
		cp = newth;
		if (cp.vars.size() == 0) 
		{
			break;
		}
	}
	bool needPushCp = false;
	if (cp.vars.size() != 0)
	{
		needPushCp = true;
	}
	else 
	{ 
//		fo
		vector<SparseVector::vint> cf = cp.coeffs.getAll();
		if (cf.size() > 0)
		{
			RationalNumber val = cp.coeffs.get(cf[0]);
			if (val != RationalNumber("1"))
			{
				needPushCp = true;
			}
		}
	}
	if (needPushCp)
	{
		ret.push_front(cp);
	}
	return ret;
}

#endif
// vector<Polynom> Polynom::factor() const
// {
// 	vector<Polynom> ret;
//     vector<RationalNumber> roots;
// 	if (vars.size() == 1)
// 	{
// 		vector<int> degrees = coeffs.getMaxDegrees();
// 		if (degrees.size() == 0) 
// 		{
// 			ret.push_back(*this);
// 			return ret;
// 		}
//         if (degrees[0] == 2)
//         {
// 	        vector <RationalNumber> x;
// 		    SparseVector::vint v(1);
// 		    v[0] = 2;
// 		    RationalNumber a = coeffs.get(v);
// 		    v[0] = 1;
// 		    RationalNumber b = coeffs.get(v);
// 		    v[0] = 0;
// 		    RationalNumber c = coeffs.get(v);
// 		    //квадратное уравнение
// 		    RationalNumber m(b);
// 		    m.negate();
// 		    RationalNumber l = m;
// 		    RationalNumber n(a);
// 		    n *= c;
// 		    n *= RationalNumber("4");
// 		    RationalNumber k(b);
// 		    k *= b;
// 		    k -= n;
// 		    if (k < RationalNumber("0"))
// 		    {
// 			    ret.push_back(*this);
// 			    return ret;
// 		    }
// 		    RationalNumber sq = k;
// 		    sq = sq.sqrt();
// 		    m += sq;
// 		    m /= RationalNumber("2");
// 		    m /= a;
// 		    l -= sq;
// 		    l /= RationalNumber("2");
// 		    l /= a;
//     	    
// 		    x.push_back(m);
// 		    x.push_back(l);
// 			if (a != RationalNumber("1"))
// 			{
// 				GrammarTree np(a.toString());
// 				ret.push_back(np.getPolynom());
// 			}
//         
// 		    for (int i = 0; i < (int)x.size(); i++)
// 		    {
// 			    string sret;
// 			    sret += "(";
// 			    sret += vars[0].name;
// 			    if (x[i].isNegative())
// 			    {
// 				    sret += "+";
// 				    x[i].negate();
// 			    }
// 			    else
// 			    {
// 				    sret += "-";
// 			    }
// 			    sret += x[i].toString();
// 			    sret += ")";
// 			    GrammarTree np(sret);
// 			    ret.push_back(np.getPolynom());
// 	        }
//         }
//         else 
//         {
// 			Primes primes(1000);
//             // Should check for leading one
//             SparseVector::vint v(1);
//             Polynom th(*this);
//             v[0] = 0;
//             bool done = false;
//             while (!done)
//             {
//                 done = true;
//                 RationalNumber fr = th.coeffs.get(v);
//                 LargeNumber num = fr.getNumerator();
//                 if (num.isNegative())
//                 {
//                     num.negate();
//                 }
// 				vector<LargeNumber> vp = PrimeFactoring::factor(num, primes);
//                 for (int i = 0 ; i < (int)vp.size(); i++) 
//                 {
//                     LargeNumber t (num);
//                     t %= LargeNumber(vp[i]);
//                     if (t.isZero()) 
//                     {
// 						vector<RationalNumber> probableSolutions;
// 						probableSolutions.push_back(RationalNumber(vp[i],"1"));
// 						vp[i].negate();
// 						probableSolutions.push_back(RationalNumber(vp[i],"1"));
// 						LargeNumber big(num);
// 						vp[i].negate();
// 						big /= vp[i];
// 						probableSolutions.push_back(RationalNumber(big,"1"));
// 						big.negate();
// 						probableSolutions.push_back(RationalNumber(big,"1"));
//                         for (int q = 0; q < (int)probableSolutions.size(); q++)
//                         {
//                             vector<RationalNumber> evvect(1);
//                             evvect[0] = probableSolutions[q];
//                             if (th.evaluate(evvect).isZero())
//                             {
//                                 done = false;
//                                 Polynom newth, newremain;
//                                 string sret;
//                                 sret += "(";
//                                 sret += vars[0].name;
//                                 RationalNumber ri = probableSolutions[q];
//                                 if (ri.isNegative())
//                                 {
//                                     sret += "+";
//                                     ri.negate();
//                                 }
//                                 else
//                                 {
//                                     sret += "-";
//                                 }
//                                 sret += ri.toString();
//                                 sret += ")";
//                                 GrammarTree np(sret);
//                                 Polynom divider = np.getPolynom();
//                                 ret.push_back(divider);
//                                 Polynom::divmod(th, divider, newth, newremain);
// //                                printf("newth=%s\n", newth.toString().c_str());
//                                 th = newth;
//                             }
//                         }
//                     }
//                 }
//             }
//             ret.push_back(th);
//         }
// 	}
//     return ret;
// }

#if 0
Number Polynom::evaluate(vector<Number> const &argvars)
{
    Number x("0");
    if (argvars.size() != 1 || vars.size() != 1)
    {
        // Throw
        return x;
    }
    vector<SparseVector::vint> p = coeffs.getAll();
    RationalNumber r = argvars[0];
    for (int i = 0; i < (int)p.size(); i++)
    {
        int pow = p[i][0];
        RationalNumber c = coeffs.get(p[i]);
        RationalNumber rp = RationalNumber::pow(r, LargeNumber(pow));
        rp *= c;
        x += rp;
    }
    return x;
}
#endif
 
#if 0
Number Polynom::evaluate(Number const &argvar)
{
    RationalNumber x("0");
    vector<SparseVector::vint> p = coeffs.getAll();
    RationalNumber r = argvar;
    for (int i = 0; i < (int)p.size(); i++)
    {
        int pow = p[i][0];
        RationalNumber c = coeffs.get(p[i]);
        RationalNumber rp = RationalNumber::pow(r, LargeNumber(pow));
        rp *= c;
        x += rp;
    }
    return x;
}
#endif

#if 1
Number Polynom::evaluate()
{
	Number ret("0");
	if (vars.size() == 0) {
		return coeffs[0][0];
	}
// 
// 	vector<SparseVector::vint> p = coeffs.getAll();
// 	RationalNumber r = argvar;
// 	for (int i = 0; i < (int)p.size(); i++)
// 	{
// 		int pow = p[i][0];
// 		RationalNumber c = coeffs.get(p[i]);
// 		RationalNumber rp = RationalNumber::pow(r, LargeNumber(pow));
// 		rp *= c;
// 		x += rp;
// 	}
// 	return x;
}
#endif

#if 0
Number Polynom::evaluate()
{
	Number x("0");
	vector<SparseVector::vint> p = coeffs.getAll();
	RationalNumber r("0");
	for (int i = 0; i < (int)p.size(); i++)
	{
		int pow = p[i][0];
		RationalNumber c = coeffs.get(p[i]);
		RationalNumber rp = RationalNumber::pow(r, LargeNumber(pow));
		rp *= c;
		x += rp;
	}
	return x;
}
#endif


#if 0
RationalNumber Polynom::evaluate(VarTable const &vt)
{
	RationalNumber x("0");
	vector<SparseVector::vint> p = coeffs.getAll();
	vector<Variable> v;
	for (size_t i = 0; i < vars.size(); i++)
	{
		Variable v0;
		v0.name = "a"; 
		v0.name[0] = (char)(v0.name[0] + i);
		v0.values.push_back(RationalNumber("0","1"));
		if (vt.find(vars[i].name,v0))
		{
			v.push_back(v0);
		}
		else
		{
			v.push_back(v0);
		}
	}
	for (int i = 0; i < (int)p.size(); i++)
	{
		RationalNumber prod = coeffs.get(p[i]);
		RationalNumber sum("0");
		for (size_t j = 0; j < p[i].size(); j++)
		{
			int pow = p[i][j]; 
			if (pow != 0)
			{
				RationalNumber rp = RationalNumber::pow(v[j].values[0], pow);
				prod *= rp;
			}
		}
		x += prod;
	}
	return x;
}
#endif

#if 1
bool Polynom::initialize(Tree const &init)
{
	treeIntact = true;
	initialized = true;
	tree = init;
	if (init.op == O_NUM)
    {
		// vars - empty  {} {c}
		vector<Number> c; 
		c.push_back(init.num);
		coeffs.push_back(c);
        return initialized;
    }
	if (init.op == O_VAR) // {"x"} {c, 0}
    {
        vars.push_back(init.var);
		vector<Number> c;
		c.push_back(Number("0"));
		c.push_back(Number("1"));
        coeffs.push_back(c);
        return initialized;
    }


    switch (init.op)
    {
    case O_ADD:
        {
            initialize(init.nodes[0]); // What if does not exists?
            for (int i = 1; i < (int)init.nodes.size(); i++)
            {
                operator += (Polynom(init.nodes[i]));
            }
        }
        break;
    case O_MUL:
        {
//            initialize(init.nodes[0]); // What if does not exists?
//            for (int i = 1; i < (int)init.nodes.size(); i++)
//            {
//                operator *= (Polynom(init.nodes[i]));
//            }
        }
        break;
    case O_SUB:
        {
//            initialize(init.nodes[0]); // What if does not exists?
//            operator -= (Polynom(init.nodes[1]));
        }
        break;
    case O_POWER:
        {
            initialize(init.nodes[0]); // What if does not exists?
			Polynom right(init.nodes[1]);
            Polynom::pow(*this, right.evaluate());
        }
        break;
    case O_DIV:
        {
//            Polynom a, b;
//            Polynom::divmod(init.nodes[0], init.nodes[1], a, b);
//			initialize(a);
//			printf("%s\n", toString().c_str());
        }
		break;
    case O_MOD:
        {
//            Polynom a, b;
//            Polynom::divmod(init.nodes[0], init.nodes[1], a, b);
//			initialize(b);
        }
		break;
    case O_UNARYMINUS:
    {
//		{
//			Polynom a; a.initialize("0");
//			printf("UMINUS: before:%s\n", init.nodes[0].toString().c_str());
//			a -= (init.nodes[0]);
//			initialize(a);
//			printf("UMINUS: after:%s\n", toString().c_str());
//		}
        break;
    }
    case O_UNARYPLUS:
    {
		{
			initialize(init.nodes[0]);
		}
        break;
    }
	case O_EMPTY:
		{

		}
		break;
	case O_VAR:
		{
			initialized = false;
		}
		break;
	case O_NUM:
		{
			initialized = false;
		}
		break;
	case O_RBCKT:
		{
			initialized = false;
		}
		break;
	case O_LBCKT:
		{
			initialized = false;
		}
		break;
	case O_ASSIGN:
		{
			initialized = false;
		}
		break;
	case O_PRINT:
		{
			initialized = false;
		}
		break;
	case O_LIST:
		{
			initialized = false;
		}
		break;
    }
	return initialized;
}
#endif

#if 0
bool Polynom::initialize( vector<Variable> const &vv, SparseVector const &sv )
{
	vars = vv;
	coeffs = sv;
	treeIntact = false;
	initialized = true;
	return initialized;
}
#endif


Polynom::Polynom( Polynom const &oth )
{
	this->coeffs = oth.coeffs;
	this->vars = oth.vars;
	this->tree = oth.tree;
	this->treeIntact = oth.treeIntact;
}

Polynom::~Polynom(void)
{
}

#if 0
bool Polynom::operator==(Polynom const &oth)
{
	if (!(vars.size() == oth.vars.size()))
	{
		return false;
	}

	vector<SparseVector::vint> thisCoeffs = coeffs.getAll();
	vector<SparseVector::vint> othCoeffs = oth.coeffs.getAll();

	if (thisCoeffs.size() != othCoeffs.size())
	{
		return false;
	}

	for (int j = 0; j < (int)thisCoeffs.size(); j++)
	{
		for (int i = 0; i < (int)thisCoeffs[j].size(); i++)
		{
			if (!(thisCoeffs[j][i] == othCoeffs[j][i]))
			{
				return false;
			}
		}
	}
	return true;
}
#endif

Polynom & Polynom::operator+=( Polynom const &coth )
{
	Polynom oth(coth);
	
//	mergeVars(oth);
	for (int i = 0; i < (int)coth.coeffs.size(); i++) {
		add(coth.vars[0].name, i, coth.coeffs[0][i]);
	}
    return *this;
}


void Polynom::pow(Polynom &what, Number const &p)
{
//	Polynom cp(what);
	if (what.isPureVar()) {
		what.coeffs.clear();
		what.add(what.vars[0].name, (int)p.toIntegerTrunc().getLongLongValue(), Number("1"));
	}
//	for (Number r("1"); !(r == p); r += Number("1")) {
//		what *= cp;
//	}
}

#if 0


Polynom & Polynom::operator-=( Polynom const &coth )
{
	Polynom oth(coth);
	mergeVars(oth);
	vector<SparseVector::vint> othCoeffs = oth.coeffs.getAll();
	for (int i = 0; i < (int)othCoeffs.size(); i++)
	{
		RationalNumber rn = oth.coeffs.get(othCoeffs[i]);
		rn.negate();
		coeffs.add(othCoeffs[i],rn);
	}
	return *this;
}

Polynom & Polynom::operator*=( Polynom const &coth )
{
	Polynom oth(coth);
	mergeVars(oth);
	SparseVector ret;
	vector<SparseVector::vint> othCoeffs = oth.coeffs.getAll();
	vector<SparseVector::vint> thisCoeffs = coeffs.getAll();
	for (int i = 0; i < (int)thisCoeffs.size(); i++)
	{
		RationalNumber ri = coeffs.get(thisCoeffs[i]);
		for (int j = 0; j < (int)othCoeffs.size(); j++)
		{
			RationalNumber rj = oth.coeffs.get(othCoeffs[j]);
			SparseVector::vint nv(thisCoeffs[i]);
			for (int k = 0; k < (int)nv.size(); k++)
			{
				nv[k] += othCoeffs[j][k];
			}
			rj *= ri;
			ret.add(nv, rj);
		}
	}
	coeffs = ret;
	// initialize()
	return *this;
}


void Polynom::pow( Polynom &what, RationalNumber const &p )
{
	if (p == RationalNumber("0"))
	{
		what.initialize("1");
		return;
	}
	// x^-2 -> x^-2!
	if (what.vars.size() == 1) // && p < RationalNumber("0")) 
	{
		// x^-3 -> {-3} {1}
		if (what.coeffs.getMaxDegrees()[0] == 1)
		{
			SparseVector::vint v(1);
			v[0] = 0;
			RationalNumber zn = what.coeffs.get(v);
			if (zn.isZero())
			{
				v[0] = 1;
				SparseVector newCoeffs;
				RationalNumber rn = what.coeffs.get(v);
				//rn *= p;
				LargeNumber ln = p.getDenominator(), quot;
				LargeNumber::divmod(p.getNumerator(), p.getDenominator(), ln, quot);
				v[0] = (int)ln.getLongLongValue();	
				newCoeffs.add(v, rn);
				what.initialize(what.vars, newCoeffs);
//				printf("%d: %s\n", v[0], rn.toString().c_str());
				return;
			}
		}
	}
	Polynom m;
	m.initialize("1");
	RationalNumber copyp(p);
	if (p.isNegative())
	{
		Polynom rem;
		Polynom::divmod(m, what, m, rem);
		copyp *= RationalNumber("-1");
	}
	Polynom copywhat(what);
	for (RationalNumber i = RationalNumber("1"); i.operator <(copyp); i += RationalNumber("1"))
	{
		what *= copywhat;
	}
}

// Only for one-variable polynom yet!
void Polynom::normalize()
{
//	printf("normalize(%s)\n", toString().c_str());
	vector<SparseVector::vint> c = coeffs.getAll();
	SparseVector newCoeffs;
	bool varsUsed = false;
    for (size_t i = 0; i < c.size(); i++)
    {
		RationalNumber r = coeffs.get(c[i]);
		if (!r.isZero())
		{
			if (c[i][0] != 0)
			{
				varsUsed = true;
			}
			newCoeffs.add(c[i],r);
		}
    }
	treeIntact = false;
	coeffs = newCoeffs;
	if (!varsUsed)
	{
		vars.clear();
	}
//	printf("normalize returns %s\n", toString().c_str());
}
#endif


string Polynom::toString() const
{
    string ret;
	int count = coeffs.size();
	if (count == 0) return "";
	vector<string> names;
	if (vars.empty())
	{
		names.push_back("@");
	}
	else
	{
		for (int i = 0; i < (int)vars.size(); i++)
		{
			names.push_back(vars[i].name);
		}
	}
	for (int v = 0; v < (int)coeffs.size(); v++) {
		string name = names[v];
		for (int i = coeffs[v].size(); --i >= 0; )   {
			Number rn = coeffs[v][i];
			if (rn.isZero()) continue;
			if (!rn.isNegative()) {
				ret += "+";
			}
			ret += rn.toString();
			if (i > 0) {
				ret += name;
			}
			if (i > 1) {
				ret += "^";
				ret += Number(i).toString();
			}
		}
	}
    return ret;
}

#if 0
string Polynom::toTexString() const
{
	string ret;
	int count = coeffs.count();
	if (count == 0) return "";
	vector<string> names;
	if (vars.empty())
	{
		names.push_back("@");
	}
	else
	{
		for (int i = 0; i < (int)vars.size(); i++)
		{
			names.push_back(vars[i].name);
		}
	}
	vector<SparseVector::vint> vv = coeffs.getAll();
	for (int i = count; --i >= 0; )
	{
		RationalNumber rn = coeffs.get(vv[i]);
        rn.normalize();
        bool negative = rn.isNegative();
        if (negative)
        {
            rn.abs();
            ret += "-";
        }
		if (rn == RationalNumber("0") && count != 1)
		{
			continue;
		}
		if (i != count-1 && !negative)
		{
			ret += "+";
		}
		bool bareConst = true;
		for (int j = 0; j < (int)vv[i].size(); j++)
		{
			if (vv[i][j] != 0)
			{
				bareConst = false;
				break;
			}
		}
		if (bareConst)
		{
			ret += rn.toTexString();
			continue;
		}
		if (!(rn.getDenominator() == LargeNumber("1")))
		{
//			ret += "(";
			ret += rn.toTexString();
//			ret += ")";
		}
		else
		{
			if (rn == RationalNumber("-1"))
            {
			} 
            else if (!(rn == RationalNumber("1")))
			{
				ret += rn.toTexString();
			}
		}
		for (int j = 0; j < (int)vv[i].size(); j++)
		{
			int ln = vv[i][j]; // power of j-th variable 
			if (ln == 0) continue;
			ret += names[j];
			if (ln != 1)
			{
				ret += "^{";
				ret += LargeNumber(ln).toString();
				ret += "} ";
			}
		}
	}
	return ret;
}
#endif

#if 0
void Polynom::divmod( Polynom const &_cleft, Polynom const &_cright, Polynom &quot, Polynom &rem )
{
//	if (cleft.vars.size() > 1 || cright.vars.size() > 1 || cleft.vars[0].name != cright.vars[0].name)
//	{
//		// throw Error::YetNotImplemented;
//		return;
//	}
	// NOTE: multivar division yet not ready!!!
	Polynom left(_cleft);
	Polynom right(_cright);
	left.mergeVars(right);
    rem.coeffs.clear();
    rem.vars = left.vars;
	int namesCount = (int)left.vars.size();
    quot.coeffs.clear();
    quot.vars = left.vars;
	for (int nameNo = 0; nameNo < namesCount; nameNo++)
	{
		int rsize = (int)right.coeffs.getMaxDegrees()[nameNo];
		int lsize = (int)left.coeffs.getMaxDegrees()[nameNo];
		deque<RationalNumber> quotCoeffs;
		deque<RationalNumber> remCoeffs;
	//	printf("divmod(%s , %s); lsize=%d rsize=%d\n", left.toString().c_str(), right.toString().c_str(), lsize, rsize);
		if (lsize < rsize)
		{
			SparseVector::vint v(namesCount);
			v[0] = nameNo;
			quot.coeffs.add(v, RationalNumber("0"));
			rem = left;
			return;
		}
		quotCoeffs.resize(lsize-rsize+1);    
		// Find the right coeff with the most power
		vector<SparseVector::vint> leftCoeffs = left.coeffs.getAll();
		vector<SparseVector::vint> rightCoeffs = right.coeffs.getAll();
		deque<RationalNumber> leftDeque(lsize+1);
		for (int i = 0; i < lsize+1; i++)
		{
			SparseVector::vint v(namesCount);
			int c = lsize-i; // leftCoeffs[i][0];
			v[nameNo] = i;
			leftDeque[c] = left.coeffs.get(v);

	//		printf("l[%d]=%s\n", c, leftDeque[c].toString().c_str());
		}

		deque<RationalNumber> rightDeque(rsize+1);
		for (int i = 0; i < rsize+1; i++)
		{
			SparseVector::vint v(namesCount);
			int c = rsize-i; // leftCoeffs[i][0];
			v[nameNo] = i;
			rightDeque[c] = right.coeffs.get(v);
	//		printf("r[%d]=%s\n", c, rightDeque[c].toString().c_str());
		}
	#if 1
		for (int i = 0; i < (int)leftDeque.size(); i++)
		{
			printf("left[%d]=%s\n", i, leftDeque[i].toString().c_str());
		}
		for (int i = 0; i < (int)rightDeque.size(); i++)
		{
			printf("right[%d]=%s\n", i, rightDeque[i].toString().c_str());
		}
	#endif
		printf("lsize1=%d rsize1=%d\n", lsize, rsize);
		deque<RationalNumber> quotDeque(lsize-rsize+1); 
		for (int i = 0; i < lsize-rsize+1; i++)
		{
			RationalNumber q(leftDeque[i]);
			printf("q0=%s\n", q.toString().c_str());
			q /= rightDeque[nameNo]; 
			printf("q1=%s, rd[%d]=%s\n", q.toString().c_str(), nameNo, rightDeque[nameNo].toString().c_str());
			for (int j = 0; j <= rsize; j++) 
			{
				RationalNumber z(rightDeque[j]);
				z *= q;
				printf("q=%s z=%s\n", q.toString().c_str(), z.toString().c_str());
				leftDeque[j+i] -= z;
			}
			quotDeque[i] = q;
		}
#if 1
		for (int i = 0; i < (int)leftDeque.size(); i++)
		{
			printf("new left[%d]=%s\n", i, leftDeque[i].toString().c_str());
		}
		for (int i = 0; i < (int)rightDeque.size(); i++)
		{
			printf("new right[%d]=%s\n", i, rightDeque[i].toString().c_str());
		}
#endif
		// copy back 
		for (int i = 0; i < (int)quotDeque.size(); i++)
		{
			SparseVector::vint v(namesCount);
			v[nameNo] = (int)quotDeque.size()-1-i;
			if (!quotDeque[i].isZero())
			{
				quot.coeffs.add(v, quotDeque[i]);
			}
		}
		for (int i = 0; i < (int)leftDeque.size(); i++)
		{
			SparseVector::vint v(namesCount);
			v[nameNo] = (int)leftDeque.size()-1-i;
			if (!leftDeque[i].isZero())
			{
				rem.coeffs.add(v, leftDeque[i]);
			}
		}
		printf("rem='%s'\n", rem.toString().c_str());
	}
	quot.normalize();
	rem.normalize();
//	printf("divmod(%s , %s) = (%s , %s)\n", left.toString().c_str(), right.toString().c_str(), quot.toString().c_str(), rem.toString().c_str());
}
#endif

// this: {x} {1} 
// oth:  {y} {2}
// result: {x, y} {1, 2};
// thisTranslate: {0}
// othTranslate: {1} (var #0 becomes var#1 in result)

#if 0
void Polynom::mergeVars( Polynom &oth )
{
	set<string> setMergedNames;
	for (int i = 0; i < (int)vars.size(); i++)
	{
		setMergedNames.insert(vars[i].name);
	}
	for (int i = 0; i < (int)oth.vars.size(); i++)
	{
		setMergedNames.insert(oth.vars[i].name);
	}
	vector<string> vectorMergedNames;
	for (set<string>::const_iterator ci = setMergedNames.begin(); ci != setMergedNames.end(); ci++)
	{
		vectorMergedNames.push_back(*ci);
	}
	if (vectorMergedNames.size() == vars.size() && vectorMergedNames.size() == oth.vars.size())
	{
		return; // nothing to translate
	}
	vector<int> thisTranslate(vars.size());
	vector<int> thisBackTranslate(vectorMergedNames.size());
	for (int i = 0; i < (int)thisBackTranslate.size(); i++)
	{
		thisBackTranslate[i] = -1;
	}
	vector<int> othTranslate(oth.vars.size());
	vector<int> othBackTranslate(vectorMergedNames.size());
	for (int i = 0; i < (int)othBackTranslate.size(); i++)
	{
		othBackTranslate[i] = -1;
	}
	int mergedSize = (int)vectorMergedNames.size();
	for (int i = 0; i < (int)vars.size(); i++)
	{
		for (int j = 0; j < (int)vectorMergedNames.size(); j++)
		{
			if (vars[i].name == vectorMergedNames[j])
			{
				thisTranslate[i] = j;
				thisBackTranslate[j] = i;
				break;
			}
		}
	}
	for (int i = 0; i < (int)oth.vars.size(); i++)
	{
		for (int j = 0; j < (int)vectorMergedNames.size(); j++)
		{
			if (oth.vars[i].name == vectorMergedNames[j])
			{
				othTranslate[i] = j;
				othBackTranslate[j] = i;
				break;
			}
		}
	}
	// Change coeffs in SparseVector's
	vector<SparseVector::vint> thisCoeffs = coeffs.getAll();
	vector<SparseVector::vint> newThisCoeffs(thisCoeffs.size());

	for (int i = 0; i < (int)thisCoeffs.size(); i++)
	{
		SparseVector::vint newThisCoeff(mergedSize);
		for (int j = 0; j < (int)newThisCoeff.size(); j++)
		{
			if (thisBackTranslate[j] != -1)
			{
				newThisCoeff[j] = thisCoeffs[i][thisBackTranslate[j]];
			}
		}
		newThisCoeffs[i] = newThisCoeff;
	}
// 	for (int i = 0; i < mergedSize; i++)
// 	{
// 		if (newThisCoeffs[i].size() == 0)
// 		{
// 			SparseVector::vint tmp(mergedSize);
// 			newThisCoeffs[i] = tmp;
// 		}
// 	}

	// x+2y   -> vars={x,y} coeffs= {{1,0}, {1}}, {0,1}, {2}}
	// 3y+4x  -> vars={y,z} coeffs= {{1,0}, {3}}, {0,1}, {4}}

	// after merge:
	// x+2y   -> vars={x,y,z} coeffs={{1,0,0}, {1}}, {{0,1,0},{2}}
	// 3y+4z  -> vars={x,y,z} coeffs={{0,1,0}, {3}}, {{0,0,1},{4}}
	vector<SparseVector::vint> othCoeffs = oth.coeffs.getAll();
	vector<SparseVector::vint> newOthCoeffs(othCoeffs.size());
	for (int i = 0; i < (int)othCoeffs.size(); i++)
	{
		SparseVector::vint newOthCoeff(mergedSize);
		for (int j = 0; j < (int)newOthCoeff.size(); j++)
		{
			if (othBackTranslate[j] != -1)
			{
				newOthCoeff[j] = othCoeffs[i][othBackTranslate[j]];
			}
		}
		newOthCoeffs[i] = newOthCoeff;
	}

// 	for (int i = 0; i < mergedSize; i++)
// 	{
// 		if (newOthCoeffs[i].size() == 0)
// 		{
// 			SparseVector::vint tmp(mergedSize);
// 			newOthCoeffs[i] = tmp;
// 		}
// 	}
	
	//	initialize(newThisCoeffs);
//	oth.initialize(newOthCoeffs);
	vector<Variable> newVars;
	for (int i = 0; i < mergedSize; i++)
	{
		Variable v(vectorMergedNames[i]);
		newVars.push_back(v);
	}
	SparseVector thisSparseVector;
	for (int i = 0; i < (int)thisCoeffs.size(); i++)
	{
		RationalNumber rn = coeffs.get(thisCoeffs[i]);
		thisSparseVector.add(newThisCoeffs[i],rn);
	}
	SparseVector othSparseVector;
	for (int i = 0; i < (int)othCoeffs.size(); i++)
	{
		RationalNumber rn = oth.coeffs.get(othCoeffs[i]);
		othSparseVector.add(newOthCoeffs[i],rn);
	}
	initialize(newVars, thisSparseVector);
//	SparseVector othSparseVector;
	oth.initialize(newVars, othSparseVector);
}
#endif

Polynom & Polynom::operator=( Polynom const &oth )
{
	coeffs = oth.coeffs;
	vars = oth.vars;
	tree = oth.tree;
	treeIntact = oth.treeIntact;
	return *this;
}

//Note: @@ does not work as partial derivative yet
#if 0
Polynom Polynom::derivative( string const &varname ) const
{
	string name = varname;
	int nameindex = 0;
	if (vars.size() == 1 && varname.size() == 0)
	{
		name = vars[0].name;
		nameindex = 0;
	}
	else 
	{
		for (nameindex = 0; nameindex < (int)vars.size(); nameindex++)
		{
			if (vars[nameindex].name == name)
			{
				break;
			}
		}
	}
	if (nameindex == (int)vars.size())
	{
		GrammarTree gp("0");
		return gp.getPolynom();
	}
	SparseVector newCoeffs;
	vector<SparseVector::vint> oldCoeffs = coeffs.getAll();
	for (int i = 0; i < (int)oldCoeffs.size(); i++)
	{
		RationalNumber rn = coeffs.get(oldCoeffs[i]);
		SparseVector::vint nv(oldCoeffs[i].size());
		for (int j = 0; j < (int)oldCoeffs[i].size(); j++)
		{
			rn *= RationalNumber(oldCoeffs[i][j],"1");
			nv[j] = oldCoeffs[i][j]-1;
		}
		if (!rn.isZero())
		{
			newCoeffs.add(nv, rn);
		}
//		printf("%s\n", rn.toString().c_str());
	}
	Polynom ret;
	ret.initialize(vars, newCoeffs);
	return ret;
}
#endif

#if 0
bool Polynom::root( RationalNumber &val )
{
    Polynom der = derivative("");
	// Approximate some tries
	RationalNumber min;
	RationalNumber zero("0");
	RationalNumber leftVal = evaluate(RationalNumber("-40"));
	if (leftVal.isZero())
	{
		val = RationalNumber("-40");
		return true;
	}
	RationalNumber x;
	for (x = RationalNumber("-40"); x < RationalNumber("40"); x += RationalNumber("1"))
	{
		RationalNumber rightVal = evaluate(x);
//		printf("root:x=%s vx=%s\n", x.toString().c_str(), rightVal.toString().c_str());
		if (rightVal.isZero())
		{
			val = x;
			return true;
		}
		if (leftVal < zero && rightVal > zero || leftVal > zero && rightVal < zero)
		{
			break;
		}
	}
    RationalNumber a(x);
	int iterations;
    for (iterations = 0; iterations < 100; iterations++)
    {
        RationalNumber va = evaluate(a);
        RationalNumber vda = der.evaluate(a);
//        printf("root:x=%s vx=%s vdx=%s\n", a.toStringDecimal().c_str(), va.toStringDecimal().c_str(), vda.toStringDecimal().c_str());
        if (vda.isZero()) 
        {
			a += "0.0001";
			continue;;
        }
        RationalNumber delta = va;
        delta /= vda;
        RationalNumber absDelta(delta);
        absDelta.abs();
		if (absDelta < RationalNumber::ROOT_EPSILON)
        {
            val = a;
            return true;
        }
        a -= delta;
        a.round(RationalNumber::ROOT_DIGITS+2);
    }
    return false;
}
#endif

bool Polynom::isPureNumberic() const
{
	return vars.size() == 0;
}

Tree Polynom::getTree()
{
	if (!treeIntact)
	{
		rebuildTree();
		treeIntact = true;
	}
	return tree;
}

void Polynom::rebuildTree()
{
	Tree ret;
	vector<Tree> subnodes;
	for (int i = 0; i < (int)coeffs.size(); i++) {
		for (int j = 0; j < (int)coeffs[i].size(); j++) {
			Number rn = coeffs[i][j];
			if (rn.isZero()) continue;
			Tree subnode(O_MUL);
			subnode.nodes.push_back(Tree(rn));
			if (rn.isOne())	{
				subnode.nodes.push_back(Tree(vars[i]));
			} else {
				Tree powerNode = Tree(O_POWER);
				powerNode.nodes.push_back(Tree(vars[i]));
				powerNode.nodes.push_back(Tree(Number(j)));
				subnode.nodes.push_back(powerNode);
			}
//			if (!rn.isOne() != RationalNumber("1"))
//			{
//				subnodes.push_back(subnode.clone());
//			}
//			else
//			{
//				subnodes.push_back(subnode.nodes[1].clone());
//			}
		}
		if (subnodes.size() == 1) {
			tree = subnodes[0].clone();
		} else {
			tree.op = O_ADD;
			tree.nodes = subnodes;
		}
	}		
}


void Polynom::add(string const &var, int pow, Number const &num)
{
	int varNum = -1;
	for (int i = 0; i < (int)vars.size(); i++) {
		if (vars[i].name == var) {
			varNum = i;
			break;
		}
	}
	if (varNum < 0) {
		Variable v(var);
		vars.push_back(v);
		varNum = vars.size() - 1;
	}
	if (varNum >= (int)coeffs.size()) {
		coeffs.resize(varNum + 1);
	}
	if (pow > (int)coeffs[varNum].size()) {
		coeffs[varNum].resize(pow + 1);
	}
	coeffs[varNum][pow] += num;
}

bool Polynom::isValid() const
{
	return initialized;
}

bool Polynom::isPureVar()
{
	if (vars.size() == 1 && coeffs[0].size() == 2 && coeffs[0][0].isZero() && coeffs[0][1].isOne()) {
		return true;
	}
	return false;

}
