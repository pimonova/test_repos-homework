#pragma once

#include <iostream>

struct node {
    string codw = "";
    char sym = {};
    int pro = 0;
    int top = 0;
} p[100000] = {};

//Маша Журинова
void shannon(int, int, node);
void shannon_fano(std::string&);
void sort_by_probability(int, node);

//


