#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Knapsack.h"
#include <string>
#include "StrL.h"

//ПРИМЕЧАНИЕ. МНОГИЕ ВЕЩИ В ПРОГРАММЕ РЕАЛИЗОВАНЫ НЕ ОПТИМАЛЬНО, НО СОГЛАСНО ТРЕБОВАНИЯМ ПРЕПОДАВАТЕЛЯ.
//МНЕ НУЖНО БЫЛО ПО МИНИМУМУ ИСПОЛЬЗОВАТЬ СТАНДАРТНЫЕ БИБЛИОТЕКИ И ПО ВОЗМОЖНОСТИ РЕАЛИЗОВЫВАТЬ ВСЕ С НУЛЯ.

bool isw(int x) {
    return x == '\0' || x == ' ' || x == '\n';
}

int sizeOfElements(string s) {
    int size = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isw(s[i]) && isw(s[i + 1])) {
            size++;
        }
    }
    return size;
}

int *split(string s, int size) {
    int *a = new int[size];
    int j = 0, l = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isw(s[i]) && !isw(s[i + 1])) {
            l = i + 1;
        }
        if (!isw(s[i]) && isw(s[i + 1])) {
            a[j++] = stoi(s.substr(l, i - l + 1));
        }
        if (j == size) {
            break;
        }
    }
    return a;
}

string toString(LinkedList<StrL> list){
    string s = "";
    for (int i = 0; i < list.getSize(); ++i) {
        s += list.get(i).arr;
    }
    return s;
}

int main() {
    const int CAPACITY = 10, N = 10;
    LinkedList<LinkedList<int>> list;
    LinkedList<LinkedList<StrL>> names;
    LinkedList<int> stoke;//кочегарка
    LinkedList<int> track;//грузовик
    LinkedList<int> stay;//осталось на делянке
    LinkedList<int> ind;//индексы дров которые забрали из stay

    fstream fin;
    fin.open("in.txt", ios::in);
    fstream fout;
    fout.open("out.txt", ios::out);
    fstream ptc;
    ptc.open("protocol.txt", ios::out);

    int n = 0;
    string s;
    while (!fin.eof()) {
        //название
        getline(fin, s);
        LinkedList<StrL> name;
        for (int i = 0; i < (s.length() + N - 1) / N; i++) {
            name.add(StrL(s.substr(i * N, N)));
        }
        names.add(name);
        //дрова
        getline(fin, s);
        int k = sizeOfElements(s);
        int *a = split(s, k);
        LinkedList<int> tmp;
        for (int i = 0; i < k; i++) {
            tmp.add(a[i]);
            n++;
        }
        delete[] a;
        list.add(tmp);
    }
    fin.close();

    int way = 1;
    while (n > 0) {
        fout << "объезд №" << way << ") ";
        ptc << "объезд №" << way << ") ";
        way++;
        for (int i = 0; i < list.getSize(); i++) {
            stay = list.get(i);
            for (int j = 0; j < track.getSize(); ++j) {
                stay.add(track.get(j));
            }
            track.clear();
            int *w = stay.toArray();
            calc(w, w, stay.getSize(), CAPACITY, ind, track);
            for (int j = 0; j < ind.getSize(); ++j) {
                stay.remove(ind.get(j) - j);
            }
            ind.clear();
            list.set(stay, i);
            fout << "делянка " << toString(names.get(i)) << ": ";
            for (int j = 0; j < stay.getSize(); j++) {
                fout << stay.get(j) << ", ";
            }
            fout << "; ";
            ptc << "грузовик увез с делянки " << toString(names.get(i)) << ": ";
            for (int j = 0; j < track.getSize(); j++) {
                ptc << track.get(j) << ", ";
            }
            ptc << "; ";
            delete[] w;
        }
        stoke.insertList(track, stoke.getSize());
        fout << "кочегарка: ";
        for (int j = 0; j < stoke.getSize(); j++) {
            fout << stoke.get(j) << ", ";
        }
        fout << "\n";
        ptc << "грузовик привез в кочегарку: ";
        for (int j = 0; j < track.getSize(); j++) {
            ptc << track.get(j) << ", ";
        }
        ptc << "\n";
        n -= track.getSize();
        track.clear();
    }
    fout.close();
    list.clear();
    track.clear();
    stoke.clear();
    return 0;
}
