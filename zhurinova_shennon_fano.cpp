#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct node {
    string codw = "";
    char sym = {};
    int pro = 0;
    int top = 0;
} p[100000] = {};

void shannon(int l, int h, node p[])
{
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, j;
    int k = 0;
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        p[h].codw = p[h].codw + "0";
        p[l].codw = p[l].codw + "1";
        return;
    }
    else {
        for (i = l; i <= h - 1; i++)
            pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0)
            diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++)
                pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--)
                pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++)
            p[i].codw = p[i].codw + "1";
        for (i = k + 1; i <= h; i++)
            p[i].codw = p[i].codw + "0";

        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

void sort_by_probability(int n, node p[])
{
    node temp;
    for (int j = 1; j <= n - 1; j++) {
        for (int i = 0; i < n - 1; i++) {
            if ((p[i].pro) < (p[i + 1].pro)) {
                temp.pro = p[i].pro;
                temp.sym = p[i].sym;

                p[i].pro = p[i + 1].pro;
                p[i].sym = p[i + 1].sym;

                p[i + 1].pro = temp.pro;
                p[i + 1].sym = temp.sym;
            }
        }
    }
}

string shennon_fano(string& text)
{
    int n, i, j = 0;
    int total = 0;
    vector <char> abc;
    bool exit_flag = 0;
    abc.push_back(text[0]);
    for (int i = 1; i < text.size(); i++)
    {
        exit_flag = 0;
        for (int j = 0; j < abc.size(); j++)
        {
            if (abc[j] == text[i])						//Если в нашем алфавите уже есть такая буква
            {
                exit_flag = 1;							//Выходим, если нашли такую букву
                break;
            }
        }
        if (exit_flag == 1)								//Если мы находили букву ранее
        {
            continue;									//Переходим на следующую итерацию для след. буквы
        }
        else											//Если буква найдена не была
        {
            abc.push_back(text[i]);
            continue;
        }
    }

    n = abc.size();

    for (i = 0; i < n; i++) {
        p[i].sym += abc[i];
    }

    /* Получение массива частоты использования символов */
    vector <int> frequencies(abc.size());
    for (int i = 0; i < abc.size(); i++)
    {
        frequencies[i] = 0;
    }
    for (int j = 0; j < abc.size(); j++)
    {
        for (int i = 0; i < text.size(); i++)
        {
            if (abc[j] == text[i])
            {
                frequencies[j]++;
            }
        }
    }

    // Input probability of symbols
    for (i = 0; i < n; i++) {
        p[i].pro = frequencies[i];
        total = total + p[i].pro;
    }

    p[i].pro = 1 - total;

    sort_by_probability(n, p);

    for (i = 0; i < n; i++)
        p[i].top = -1;

    shannon(0, n - 1, p);
    map<char, string> map;
    for (int i = 0; i < n; i++) {
        map.insert(make_pair(p[i].sym, p[i].codw));
    }

    string str;
    for (int i = 0; i < text.size(); i++)
    {
        str += map[text[i]];
    }

    return str;
}
