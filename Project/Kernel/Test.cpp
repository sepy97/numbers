#include "Test.h"
#include "GrammarTree.h"



Test::Test()
{

}

bool Test::test_degree(Tree & /*t*/, RationalNumber const & /*amust*/)
{
//     RationalNumber v1 = t.evaluate();
// 	RationalNumber must(amust);
// 	must.normalize();
// 	v1.normalize();
//     if (!(v1 == must))
//     {
//         cout << t.toString() << " must be equal to " << must << " but got " << v1 << endl;
//         return false;
//     }
    return true;
}

bool Test::test_tree(Tree & /*t*/, RationalNumber const & /*must*/)
{
//     RationalNumber v1 = t.evaluate();
//     if (!(v1 == must))
//     {
//         cout << t.toString() << " must be equal to " << must << " but got " << v1 << endl;
//         return false;
//     }
    return true;
}

bool Test::test( char op, LargeNumber const &cv1, LargeNumber const &cv2, LargeNumber const &amust )
{
    LargeNumber v1 = cv1;
	LargeNumber must(amust);

    switch (op) 
    {
    case '-':
        v1 -= cv2; break;
    case '+':
        v1 += cv2; break;
    case '*':
        v1 *= cv2; break;
    case '/':
        v1 /= cv2; break;
    case '%':
        v1 %= cv2; break;
    case 'G':
        v1 = LargeNumber::GCD(cv1, cv2); break;
    case 'L':
        v1 = LargeNumber::LCM(cv1, cv2); break;
        default:
            return "Something went wrong in test_LargeNumber... but we'll fix it!";
    }
    if (!(v1 == must))
    {
        cout << cv1.toString() << " " << op << " " << cv2.toString() << " must be " << must.toString() << " but got " << v1.toString() << endl;
        return false;
    }
    return true;
}

bool Test::test( char op, RationalNumber const &cv1, RationalNumber const &cv2, RationalNumber const &must )
{
    RationalNumber v1 = cv1;
    try{    
        switch (op)
        {
        case '-':
            v1 -= cv2; break;
        case '+':
            v1 += cv2; break;
        case '*':
            v1 *= cv2; break;
        case '/':
            v1 /= cv2; break;
        case 'G':
            v1 = RationalNumber::GCD(cv1, cv2); break;
        case 'L':
            v1 = RationalNumber::LCM(cv1, cv2); break;
        default:
            return "Something went wrong in test_RationalNumber... but we'll fix it!";
        }
		v1.normalize();
		RationalNumber copyMust(must);
		copyMust.normalize();
        if (!(v1 == copyMust))
        {
            cout << cv1 << " " << op << " " << cv2 << " must be " << copyMust << " but got " << v1 << endl;
            return false;
        }
        return true;
    }
    catch (NumberException const &e)
    {
        cout << cv1 << " " << op << " " << cv2 << " leads to exception " << e.getMessage() << endl;
        return false;
    }
}


void Test::check()
{
    bool norm = true;
    //*********************************************Ì‡˜‡ÎÓ ÚÂÒÚ‡ ‰Îˇ largenumber***********************************
    //”ÃÕŒ∆≈Õ»≈
	norm &= test('-', LargeNumber("100000000"), LargeNumber("12345678"), LargeNumber("87654322"));
	norm &= test('-', LargeNumber("25"), LargeNumber("5"), LargeNumber("20"));
	norm &= test('-', LargeNumber("0"), LargeNumber("25"), LargeNumber("-25"));
	norm &= test('-', LargeNumber("0"), LargeNumber("0"), LargeNumber("0"));
	norm &= test('-', LargeNumber("25"), LargeNumber("0"), LargeNumber("25"));
	norm &= test('-', LargeNumber("-96"), LargeNumber("72"), LargeNumber("-168"));
	norm &= test('-', LargeNumber("43"), LargeNumber("-81"), LargeNumber("124"));
	norm &= test('-', LargeNumber("-31"), LargeNumber("-46"), LargeNumber("15"));

	norm &= test('*', LargeNumber("12"), LargeNumber("34"), LargeNumber("408"));
	norm &= test('*', LargeNumber("1111111111"), LargeNumber("1111111111"), LargeNumber("1234567900987654321"));
	norm &= test('*', LargeNumber("25"), LargeNumber("5"), LargeNumber("125"));
    norm &= test('*', LargeNumber("25"), LargeNumber("0"), LargeNumber("0"));
    norm &= test('*', LargeNumber("0"), LargeNumber("25"), LargeNumber("0"));
    norm &= test('*', LargeNumber("0"), LargeNumber("0"), LargeNumber("0"));
    norm &= test('*', LargeNumber("-10"), LargeNumber("7"), LargeNumber("-70"));
    norm &= test('*', LargeNumber("10"), LargeNumber("-15"), LargeNumber("-150"));
    norm &= test('*', LargeNumber("-9"), LargeNumber("-22"), LargeNumber("198"));
    
    //ƒ≈À≈Õ»≈
    norm &= test('/', LargeNumber("25"), LargeNumber("5"), LargeNumber("5"));
    norm &= test('/', LargeNumber("0"), LargeNumber("25"), LargeNumber("0"));
    norm &= test('/', LargeNumber("-25"), LargeNumber("5"), LargeNumber("-5"));
    norm &= test('/', LargeNumber("72"), LargeNumber("-6"), LargeNumber("-12"));
    norm &= test('/', LargeNumber("-90"), LargeNumber("-5"), LargeNumber("18"));
    
    //—ÀŒ∆≈Õ»≈
    norm &= test('+', LargeNumber("25"), LargeNumber("5"), LargeNumber("30"));
    norm &= test('+', LargeNumber("25"), LargeNumber("0"), LargeNumber("25"));
    norm &= test('+', LargeNumber("0"), LargeNumber("0"), LargeNumber("0"));
    norm &= test('+', LargeNumber("0"), LargeNumber("25"), LargeNumber("25"));
    norm &= test('+', LargeNumber("-20"), LargeNumber("7"), LargeNumber("-13"));
    norm &= test('+', LargeNumber("134"), LargeNumber("-57"), LargeNumber("77"));
    norm &= test('+', LargeNumber("-27"), LargeNumber("-65"), LargeNumber("-92"));
    
    //¬€◊»“¿Õ»≈
    
    //Õ¿»¡ŒÀ‹ÿ»… Œ¡Ÿ»… ƒ≈À»“≈À‹
    norm &= test('G', LargeNumber("25"), LargeNumber("5"), LargeNumber("5"));
    norm &= test('G', LargeNumber("0"), LargeNumber("25"), LargeNumber("25"));
    norm &= test('G', LargeNumber("1879"), LargeNumber("3541"), LargeNumber("1")); 
    norm &= test('G', LargeNumber("25"), LargeNumber("0"), LargeNumber("25")); 
    
    //Õ¿»Ã≈Õ‹ÿ≈≈ Œ¡Ÿ≈≈  –¿“ÕŒ≈
    norm &= test('L', LargeNumber("25"), LargeNumber("5"), LargeNumber("25"));
    norm &= test('L', LargeNumber("0"), LargeNumber("25"), LargeNumber("0"));
    norm &= test('L', LargeNumber("1571"), LargeNumber("2377"), LargeNumber("3734267"));
    
    //Œ—“¿“Œ  Œ“ ƒ≈À≈Õ»ﬂ
    norm &= test('%', LargeNumber("25"), LargeNumber("5"), LargeNumber("0"));
    norm &= test('%', LargeNumber("25"), LargeNumber("7"), LargeNumber("4"));
    norm &= test('%', LargeNumber("25"), LargeNumber("30"), LargeNumber("25"));
    norm &= test('%', LargeNumber("0"), LargeNumber("25"), LargeNumber("0"));
    norm &= test('%', LargeNumber("-25"), LargeNumber("5"), LargeNumber("0"));
    norm &= test('%', LargeNumber("-25"), LargeNumber("7"), LargeNumber("3"));
    norm &= test('%', LargeNumber("25"), LargeNumber("-7"), LargeNumber("-4"));
    //******************************************ÍÓÌÂˆ ÚÂÒÚ‡ ‰Îˇ largenumber****************************************

    //******************************************Ì‡˜‡ÎÓ ÚÂÒÚ‡ ‰Îˇ rationalnumber********************************
    
    //—ÀŒ∆≈Õ»≈
    
    //¬€◊»“¿Õ»≈
    norm &= test('+', RationalNumber("0/13"), RationalNumber("0/8"), RationalNumber("0/1"));
    norm &= test('+', RationalNumber("27/2"), RationalNumber("9/5"), RationalNumber("153/10"));
    norm &= test('+', RationalNumber("0/7"), RationalNumber("7/20"), RationalNumber("7/20"));
    norm &= test('+', RationalNumber("7.5"), RationalNumber("9/11"), RationalNumber("183/22"));
    norm &= test('+', RationalNumber("8.3"), RationalNumber("7.1"), RationalNumber("15.4"));
    norm &= test('+', RationalNumber("-7.5"), RationalNumber("9/11"), RationalNumber("-147/22"));
    norm &= test('+', RationalNumber("8.3"), RationalNumber("-7.1"), RationalNumber("1.2"));
    norm &= test('+', RationalNumber("-27/2"), RationalNumber("-9/5"), RationalNumber("-153/10"));

	norm &= test('-', RationalNumber("7/12"), RationalNumber("80/9"), RationalNumber("-299/36"));
    norm &= test('-', RationalNumber("143/13"), RationalNumber("11/25"), RationalNumber("264/25"));
    norm &= test('-', RationalNumber("0/21"), RationalNumber("8/43"), RationalNumber("-8/43"));
    norm &= test('-', RationalNumber("0/11"), RationalNumber("0/9"), RationalNumber("0/1"));
    norm &= test('-', RationalNumber("7.3"), RationalNumber("20.9"), RationalNumber("-13.6"));
    norm &= test('-', RationalNumber("27.5"), RationalNumber("6.8"), RationalNumber("20.7"));
    norm &= test('-', RationalNumber("0.2"), RationalNumber("1.3"), RationalNumber("-1.1"));
    norm &= test('-', RationalNumber("0.2"), RationalNumber("-1.3"), RationalNumber("1.5"));
    
    //”ÃÕŒ∆≈Õ»≈
    norm &= test('*', RationalNumber("9/5"), RationalNumber("13/9"), RationalNumber("13/5"));
    norm &= test('*', RationalNumber("11/8"), RationalNumber("7/29"), RationalNumber("77/232"));
    norm &= test('*', RationalNumber("0/7"), RationalNumber("15/3"), RationalNumber("0/1"));
    norm &= test('*', RationalNumber("13/27"), RationalNumber("0/11"), RationalNumber("0/1"));
    norm &= test('*', RationalNumber("1.2"), RationalNumber("5.1"), RationalNumber("6.12"));
    norm &= test('*', RationalNumber("7.2"), RationalNumber("3/11"), RationalNumber("108/55"));
    norm &= test('*', RationalNumber("9/25"), RationalNumber("11.6"), RationalNumber("522/125"));
    norm &= test('*', RationalNumber("-9/5"), RationalNumber("13/9"), RationalNumber("-13/5"));
    norm &= test('*', RationalNumber("11/8"), RationalNumber("-7/29"), RationalNumber("-77/232"));
    norm &= test('*', RationalNumber("-9/25"), RationalNumber("-11.6"), RationalNumber("522/125"));

    //ƒ≈À≈Õ»≈
    norm &= test('/', RationalNumber("11/8"), RationalNumber("7/9"), RationalNumber("99/56"));
    norm &= test('/', RationalNumber("1.7"), RationalNumber("2.9"), RationalNumber("17/29"));
    norm &= test('/', RationalNumber("3.2"), RationalNumber("0.5"), RationalNumber("32/5"));
    norm &= test('/', RationalNumber("0.1"), RationalNumber("7.4"), RationalNumber("1/74"));

    //Õ¿»¡ŒÀ‹ÿ»… Œ¡Ÿ»… ƒ≈À»“≈À‹    
    norm &= test('G', RationalNumber("11/8"), RationalNumber("7/9"), RationalNumber("1/72"));
    norm &= test('G', RationalNumber("1.7"), RationalNumber("2.9"), RationalNumber("1/10"));
    norm &= test('G', RationalNumber("3.2"), RationalNumber("0.5"), RationalNumber("1/10"));
    norm &= test('G', RationalNumber("0.1"), RationalNumber("7.4"), RationalNumber("1/10"));

    //Õ¿»Ã≈Õ‹ÿ≈≈ Œ¡Ÿ≈≈  –¿“ÕŒ≈
    norm &= test('L', RationalNumber("11/8"), RationalNumber("7/9"), RationalNumber("77"));
    norm &= test('L', RationalNumber("1.7"), RationalNumber("2.9"), RationalNumber("493/10"));
    norm &= test('L', RationalNumber("3.2"), RationalNumber("0.5"), RationalNumber("16"));
    norm &= test('L', RationalNumber("0.1"), RationalNumber("7.4"), RationalNumber("37/5")); 
//    norm &= test('L', RationalNumber("78/81"), RationalNumber("4/27"), RationalNumber("52/27"));

    //******************************************Ì‡˜‡ÎÓ ÚÂÒÚ‡ ‰Îˇ Tree********************************

    //norm &= test_tree("");
    if (norm)
    {
       cout << "Everything works great!!!!!" << endl;
    }
}

Test::~Test()
{

}
