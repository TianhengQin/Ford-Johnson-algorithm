# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <cstdlib>

std::vector<int> gOrder(int k) {
    std::vector<int> re;

    int prev = 2;
    int curr;
    int i = 1;
    int g = 2;
    int size = 2;

    re.push_back(2);
    re.push_back(1);

    while (++i < k) {
        size *=2;
        g = size - g;
        curr = prev + g;
        while (curr > prev)
            re.push_back(curr--);
        prev = prev + g;
    }
    return re;
}

std::vector<int> order = gOrder(13);

void printV(std::vector<int> &lst) {
    std::vector<int>::iterator itl;
    int i = 0;
    for (itl = lst.begin(); itl != lst.end(); ++itl) {
        i++;
        std::cout << *itl << " ";
        if (i == 10)
            break;
    }
    if (itl != lst.end() && ++itl != lst.end())
        std::cout << "[...]";
    std::cout << std::endl;
}

void swapSizeV(std::vector<int> &a, std::vector<int>::iterator b, std::vector<int>::iterator c, int size) {

    std::vector<int>::iterator d = c + size;
    std::vector<int> ins(c, d);
    a.erase(c, d);
    a.insert(b, ins.begin(), ins.end());
}

void insertSizeV(std::vector<int> &a, std::vector<int>::iterator b, std::vector<int>::iterator c, int size) {

    std::vector<int>::iterator d = c + size;
    std::vector<int> ins(c, d);
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
    std::vector<int> sort;

    while (2 * size <= len) {
        
        tab = len / (2 * size);
        j = a.begin();
        k = j + size;
        if (*j < *k) {
            swapSizeV(a, j, k, size);
        }
        for (int i = 1; i < tab; i++) {
            j += 2 * size;
            k += 2 * size;
            if (*j < *k) {
                swapSizeV(a, j, k, size);
            }
        }
        size *= 2;
    }
    size /= 2;
    int sortSize;
    int o;
    while (size >= 1) {
        sort.clear();
        j = a.begin();
        k = j + size;
        while (distance(j, a.end()) >= 2 * size) {
            insertSizeV(sort, sort.end(), j, size);
            j += 2 * size;
        }
        insertSizeV(sort, sort.begin(), k, size);
        tab = len / (size * 2);
        o = 0;
        sortSize = 2;
        for (int i = 1; i < tab; i++) {
            if (o == 0 || order[o] > order[o - 1])
                sortSize *= 2;
            if (sortSize > sort.size() / size)
                sortSize = sort.size() / size;
            while (order[o] >= tab)
                o++;
            k = a.begin() + size + 2 * size * order[o++];
            j = binSearchV(sort, size, sort.begin() + (sortSize - 1) * size, *k);
            insertSizeV(sort, j, k, size);
        }
        if ((len / size) % 2) {
            k = a.begin() + size * 2 * tab;
            j = binSearchV(sort, size, sort.end(), *k);
            insertSizeV(sort, j, k, size);
        }
        size /= 2;
        j = a.end() - (a.size() - sort.size());
        sort.insert(sort.end(), j, a.end());
        a = sort;
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
    std::cout << "Order: ";
    printV(order);
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
