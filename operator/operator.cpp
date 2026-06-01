#include "operator.h"

// ===== FormatRowFile =====

FormatRowFile::FormatRowFile() {}

FormatRowFile::FormatRowFile(
    string line) {

    string temp;

    for (size_t i = 0;
         i < line.size();
         i++) {

        if (line[i] == ' ' ||
            line[i] == '\t') {

            if (!temp.empty()) {

                fields.push_back(temp);

                temp.clear();
            }
        }
        else {

            temp += line[i];
        }
    }

    if (!temp.empty()) {

        fields.push_back(temp);
    }
}

string FormatRowFile::getField(
    int index) {

    return fields[index];
}

int FormatRowFile::size() {

    return fields.size();
}

// ===== TextFile =====

template <class T>
TextFile<T>::TextFile() {}

template <class T>
TextFile<T>::TextFile(
    string apath) {

    path = apath;

    ifstream file(path);

    if (!file.is_open()) {

        cout << "Файл не открылся"
             << endl;

        return;
    }

    string line;

    while (getline(file, line)) {

        if (!line.empty()) {

            data.push_back(line);
        }
    }

    file.close();
}

// ===== print =====

template <class T>
void TextFile<T>::print() {

    for (size_t i = 0;
         i < data.size();
         i++) {

        cout << data[i]
             << endl;
    }
}

// ===== append =====

template <class T>
void TextFile<T>::append(
    TextFile<T>& other) {

    for (size_t i = 0;
         i < other.data.size();
         i++) {

        data.push_back(
            other.data[i]
        );
    }
}

// ===== unique =====

template <class T>
TextFile<T> TextFile<T>::unique(
    TextFile<T>& other) {

    TextFile<T> result;

    set<T> s;

    for (size_t i = 0;
         i < data.size();
         i++) {

        s.insert(data[i]);
    }

    for (size_t i = 0;
         i < other.data.size();
         i++) {

        s.insert(other.data[i]);
    }

    for (typename set<T>::iterator it =
         s.begin();

         it != s.end();

         it++) {

        result.data.push_back(*it);
    }

    return result;
}

// ===== common =====

template <class T>
TextFile<T> TextFile<T>::common(
    TextFile<T>& other) {

    TextFile<T> result;

    for (size_t i = 0;
         i < data.size();
         i++) {

        for (size_t j = 0;
             j < other.data.size();
             j++) {

            if (data[i] ==
                other.data[j]) {

                result.data.push_back(
                    data[i]
                );
            }
        }
    }

    return result;
}

// ===== sortAsc =====

template <class T>
void TextFile<T>::sortAsc() {

    sort(data.begin(),
         data.end());
}

// ===== sortDesc =====

template <class T>
void TextFile<T>::sortDesc() {

    sort(data.rbegin(),
         data.rend());
}

// ===== sum =====

template <class T>
double TextFile<T>::sumNumbers() {

    double sum = 0;

    for (size_t i = 0;
         i < data.size();
         i++) {

        sum += atof(
            data[i].c_str()
        );
    }

    return sum;
}

// ===== += =====

template <class T>
void TextFile<T>::operator += (
    TextFile<T>& other) {

    for (size_t i = 0;
         i < other.data.size();
         i++) {

        bool found = false;

        for (size_t j = 0;
             j < data.size();
             j++) {

            if (data[j] ==
                other.data[i]) {

                found = true;

                break;
            }
        }

        if (!found) {

            data.push_back(
                other.data[i]
            );
        }
    }
}

// ===== + =====

template <class T>
TextFile<T> TextFile<T>::operator + (
    TextFile<T>& other) {

    return unique(other);
}

// ===== -= =====

template <class T>
void TextFile<T>::operator -= (
    TextFile<T>& other) {

    vector<T> result;

    for (size_t i = 0;
         i < data.size();
         i++) {

        bool found = false;

        for (size_t j = 0;
             j < other.data.size();
             j++) {

            if (data[i] ==
                other.data[j]) {

                found = true;

                break;
            }
        }

        if (!found) {

            result.push_back(
                data[i]
            );
        }
    }

    data = result;
}

// ===== - =====

template <class T>
TextFile<T> TextFile<T>::operator - (
    TextFile<T>& other) {

    TextFile<T> result;

    for (size_t i = 0;
         i < data.size();
         i++) {

        bool found = false;

        for (size_t j = 0;
             j < other.data.size();
             j++) {

            if (data[i] ==
                other.data[j]) {

                found = true;

                break;
            }
        }

        if (!found) {

            result.data.push_back(
                data[i]
            );
        }
    }

    return result;
}