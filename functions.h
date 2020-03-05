#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<typename T> // для сортировки
void flipflop(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

bool inLength(int length, int index) { // проверка, есть ли элемент с таким индексом
    return (index >= 0 && index < length);
}

template<typename T>
void array_random_fill(T * array, int& length) {
    for (int i = 0; i < length; i++) {
        int rnd = 0;
        while (rnd == 0) {
            rnd = rand();
        }
        int polar = rand() % 2 == 0 ? -1 : 1;
        array[i] = (T)(1.0 * rand() / rnd * polar);
    }
}

template<typename T>
void array_output(T * array, int length) {
    cout << "\nYour array:\n";
    for (int i = 0; i < length; i++) {
        cout << array[i] << "\n";
    }
    cout << "\n";
}

template<typename T>
void push_by_index(T * &array, int& length, int index, T value)
{
    if (!inLength(length, index)) {
        return;
    }
    T* tmp_array = new T[length + 1];
    for (int i = 0; i < index; i++) {
        tmp_array[i] = array[i];
    }
    tmp_array[index] = value;
    length++;
    for (int i = index + 1; i < length; i++) {
        tmp_array[i] = array[i - 1];
    }
    delete[] array;
    array = tmp_array;
}

template<typename T>
void remove_element_by_index(T * array, int& length, int index) {
    if (!inLength(length, index)) {
        return;
    }
    for (int i = index; i < length - 1; i++) {
        array[i] = array[i + 1];
    }
    array[length - 1] = (T)0;
}

template<typename T>
void bubble_sort(T * array, int length)
{
    for (int i = 0; i < length; i++) {
        for (int j = length - 1; j > i; j--) {
            if (array[j - 1] > array[j]) flipflop(array[j - 1], array[j]);
        }
    }
}

template<typename T>
void insertion_sort(T * array, int length)
{
    for (int i = 1; i < length; i++) {
        int tmp_i = i;
        for (int j = i - 1; j >= 0; j--) {
            if (array[i - 1] > array[i]) {
                flipflop(array[tmp_i], array[j]);
                tmp_i--;
            }
        }
    }
}

template<typename T>
void optimized_bubble_sort(T * array, int length)
{
    bool flipped;
    for (int i = 0; i < length; i++) {
        flipped = false;
        for (int j = length - 1; j > i; j--) {
            if (array[j - 1] > array[j]) {
                flipflop(array[j - 1], array[j]);
                flipped = true;
            }
        }
        if (!flipped) {
            return;
        }
    }
}

template<typename T, class F>
int find_first_predicated_index(T * array, int length, F predicat) {
    int needed_index = 0;
    while (!predicat(array[needed_index])) {
        
        needed_index++;
        if (needed_index == length) {
            return -1;
        }
    }
    return needed_index;
}

template<typename T, class F>
int get_index_of_minimum_element(T * array, int length, F predicat = []() {return true; })
{
    //find first predicated index
    int needed_index = find_first_predicated_index(array, length, predicat);
    if (needed_index == -1) {
        return needed_index;
    }
    
    for (int i = needed_index + 1; i < length; i++) {
        // если значение не определено - пропускаем итерацию
        if (!predicat(array[i])) {
            continue;
        }
        
        if (array[needed_index] > array[i]) {
            needed_index = i;
        }
    }
    return needed_index;
}

template<typename T, class F>
int get_index_of_maximum_element(T * array, int length, F predicat = []() {return true; })
{
    int needed_index = find_first_predicated_index(array, length, predicat);
    if (needed_index == -1) {
        return needed_index;
    }
    
    for (int i = needed_index + 1; i < length; i++) {
        if (!predicat(array[i])) {
            continue;
        }
        
        if (array[needed_index] < array[i]) {
            needed_index = i;
        }
    }
    return needed_index;
}

template<typename T>
int iteration_linear_find_element_of_array(T * array, int length, T value)
{
    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

template<typename T>
int iteration_binary_find_element_of_array(T * array, int length, T value)
{
    int left_index = 0;
    int right_index = length - 1;
    int middle_index;
    
    while (true) {
        middle_index = (left_index + right_index) / 2;
        
        if (value < array[middle_index]) {
            right_index = middle_index - 1;
        }
        else if (value > array[middle_index]) {
            left_index = middle_index + 1;
        }
        else {
            return middle_index;
        }
        
        if (left_index > right_index) {
            return -1;
        }
    }
}

template<typename T>
int recursive_linear_find_element_of_array(T * array, int length, T value)
{
    return length - 1 == -1 ? -1 : array[length - 1] == value ? length - 1 : recursive_linear_find_element_of_array(array, length - 1, value);
}

template<typename T>
int recursive_binary_find_element_of_array(T * array, int length, T value, int left_index, int right_index)
{
    if (right_index == -1) {
        right_index = length - 1;
    }
    int middle_index = (left_index + right_index) / 2;
    if (value < array[middle_index]) {
        right_index = middle_index - 1;
    }
    else if (value > array[middle_index]) {
        left_index = middle_index + 1;
    }
    else {
        return middle_index;
    }
    if (left_index > right_index) {
        return -1;
    }
    return recursive_binary_find_element_of_array(array, length, value, left_index, right_index);
}

template<typename T, class F>
int get_count_of_elements_of_array(T * array, int length, F predicat)
{
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (predicat(array[i])) {
            count++;
        }
    }
    return count;
}

template<typename T, class F>
T get_sum_of_elements_of_array(T * array, int length, F predicat)
{
    T sum = 0;
    for (int i = 0; i < length; i++) {
        if (predicat(array[i])) {
            if (!sum) {
                sum = array[i];
            }
            else {
                sum += array[i];
            }
        }
    }
    return sum;
}

template<typename T, class F>
T get_multiplication_of_elements_of_array(T * array, int length, F predicat)
{
    T multiplication = array[0];
    for (int i = 1; i < length; i++) {
        if (predicat(array[i])) {
            multiplication *= array[i];
        }
    }
    return multiplication;
}

template<typename T, class F>
int* get_predicat_index_of_array(T * array, int length, F predicat) // получаем индексы элементов, удовлетворяющих условиям предиката
{
    int* needed_array = new int[get_count_of_elements_of_array(array, length, predicat)];
    
    int needed_i = 0;
    for (int i = 0; i < length; i++) {
        if (predicat(array[i])) {
            needed_array[needed_i] = i;
            needed_i++;
        }
    }
    return needed_array;
}

string get_array_data_by_file(string path)
{
    string result = "";
    string line;
    ifstream in(path);
    if (in.is_open()) {
        while (getline(in, line)) {
            result += line;
        }
    }
    else {
        throw std::invalid_argument("Invalide path to file!");
    }
    in.close();
    return result;
}

template<typename T>
void fill_array_by_file(T * &array, int& length, string path)
{
    string array_data = get_array_data_by_file(path);
    
    length = 0;
    for (int i = 0; i < array_data.size(); i++) {
        if (array_data[i] == ';') {
            length++;
        }
    }
    
    delete[] array;
    array = new T[length];
    
    int current_index = 0;
    string current_value = "";
    for (int i = 0; i < array_data.size(); i++) {
        if (array_data[i] == ';') {
            array[current_index] = (T)(current_value);
            current_index++;
            current_value = "";
            continue;
        }
        current_value.push_back(array_data[i]);
    }
}
