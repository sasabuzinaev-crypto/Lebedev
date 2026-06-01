#pragma once
#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

class FormatRowFile {
private:
    vector<string> fields;

public:

    FormatRowFile();

    FormatRowFile(string line);

    string getField(int index);

    int size();
};

template <class T>
class TextFile {
private:

    string path;

public:

    vector<T> data;

    TextFile();

    TextFile(string apath);

    void print();

    void append(TextFile<T>& other);

    TextFile<T> unique(
        TextFile<T>& other);

    TextFile<T> common(
        TextFile<T>& other);

    void sortAsc();

    void sortDesc();

    double sumNumbers();

    void operator += (
        TextFile<T>& other);

    TextFile<T> operator + (
        TextFile<T>& other);

    void operator -= (
        TextFile<T>& other);

    TextFile<T> operator - (
        TextFile<T>& other);
};

#include "operator.cpp"

#endif