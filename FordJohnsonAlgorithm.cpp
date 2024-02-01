# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <cstdlib>

void printV(std::vector<int> &lst) {
    std::vector<int>::iterator itl;
    int i = 0;
    for (itl = lst.begin(); itl != lst.end(); ++itl) {
        i++;
        std::cout << *itl << " ";
        if (i == 20)
            break;
    }
    if (itl != lst.end() && ++itl != lst.end())
        std::cout << "[...]";
    std::cout << std::endl;
}

void insertSizeV(std::vector<int> &a, std::vector<int>::iterator b, std::vector<int>::iterator c, int size) {

    std::vector<int>::iterator d = c + size;
    std::vector<int> ins(c, d);
    a.erase(c, d);
    a.insert(b, ins.begin(), ins.end());
}

std::vector<int>::iterator binSearchV(std::vector<int> &a, int size, std::vector<int>::iterator k, int target) {

    std::vector<int>::iterator left = a.begin();
    std::vector<int>::iterator right = k - size;
    std::vector<int>::iterator mid = left + (std::distance(left, right) / size) / 2 * size;
    while (!(left == right || left + size == right)) {

        if (*mid > target) {
            right = mid;
            mid = left + (std::distance(left, right) / size) / 2 * size;
        } else if (*mid < target) {
            left = mid;
            mid = left + (std::distance(left, right) / size) / 2 * size;
        } else {
            return mid;
        }
    }
    if (target > *right)
        return right + size;
    if (target > *mid)
        return mid + size;
    return mid;
}

void sortV(std::vector<int> &a) {

    int size = 1;
    int len = a.size();
    int tab;
    std::vector<int>::iterator j;
    std::vector<int>::iterator k;
    while (2 * size <= len) {
        
        tab = len / (2 * size);
        j = a.begin();
        k = j + size;
        if (*j < *k) {
            insertSizeV(a, j, k, size);
        }
        for (int i = 1; i < tab; i++) {
            j += 2 * size;
            k += 2 * size;
            if (*j < *k) {
                insertSizeV(a, j, k, size);
            }
        }
        size *= 2;
    }
    size /= 2;

    while (size >= 1) {
        j = a.begin();
        k = j + size;
        insertSizeV(a, j, k, size);
        tab = len / (size * 2);
        for (int i = 1; i < tab; i++) {
            k += 2 * size;
            j = binSearchV(a, size, k, *k);
            insertSizeV(a, j, k, size);
        }
        if ((len / size) % 2) {
            k += size;
            j = binSearchV(a, size, k, *k);
            insertSizeV(a, j, k, size);
        }
        size /= 2;
    }
}

int main(int argi, char **argv) {

    if (argi < 2) {
        return 1;
    }
    std::vector<int> vct;
    int i = 0;
    while(++i < argi) {

        std::string s(argv[i]);
        if (s.empty()) {
            continue;
        }
        int i = -1;
        while (s[++i]) {
            if (!std::isdigit(s[i])) {
                std::cout << "Error" << std::endl;
                return 1;
            }
        }
        i = std::atoi(s.c_str());
        vct.push_back(i);
    }
    std::cout << "Before: ";
    printV(vct);
    time_t start, end;
    start = clock();
    sortV(vct);
    end = clock();
    std::cout << "After:  ";
    printV(vct);
    std::cout << "Time to process a range of: "
        << argi - 1 << " elements with vector : " 
        << (end - start) << " us" << std::endl;

    for (std::vector<int>::iterator it = vct.begin(); it + 1 != vct.end(); it++) {
        if (*it > *(it + 1)) {
            std::cout << "xxxxx" << std::endl;
            return 1;
        }
    }
    std::cout << "vvvvvv" << std::endl;
    return 0;
}
