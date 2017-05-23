#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "Error.h"
#include "Tree.h"
#include "RationalNumber.h"
#include "NumberException.h"
class Test
{
public:
    Test();
    bool test(char op, LargeNumber const &cv1, LargeNumber const &cv2, LargeNumber const &must);
    bool test(char op, RationalNumber const &cv1, RationalNumber const &cv2, RationalNumber const &must);
    void check();
    bool test_tree(Tree &t, RationalNumber const &must);
    bool test_degree(Tree &t, RationalNumber const &must);
    ~Test();
};
