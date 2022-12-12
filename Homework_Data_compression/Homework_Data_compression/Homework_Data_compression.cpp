// Homework_Data_compression.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Datasets.h"
#include "Utils.h"
#include <chrono>
#include "Header_algorithms.h"

using namespace std;

/*void run(string methodName, int (*fcnPtr)(string), string data)
{
    auto start = chrono::system_clock::now();
    string result = p(data);
    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    
    cout << "Method: " << methodName << endl
        << "Time: " << time << endl
        << "Compression" << endl;
}*/

int main()
{
    cout << "Hello!\n"
         << "This is our team homework - data compression algorithms\n"
         << "Our team: Kate Borushko, Farid Mystafaev, Maria Zhurinova, Maria Stepura, Julius Tokar', Stepan Lavrentev and Antonina Pimonova\n";
    
    cout << "Enter dataset size:" << endl;
    uint32_t datasetSize;
    getCorrect(datasetSize);
    string stringData = createDatatset(datasetSize);
    cout << stringData << endl;

    //run("Shannon - Fano", shannon_fano(stringData), stringData);
}

