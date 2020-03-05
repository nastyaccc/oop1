#include "functions.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    // заполняем массив 10 элементами
    int length = 10;
    float* array = new float[length];
    array_random_fill(array, length);
    array_output(array, length);
    
    // ищем минимальный по модулю элемент
    
    int maximum_from_negative_index = get_index_of_maximum_element(array, length, [](float value) {return value < 0; });
    int minimum_from_positive_index = get_index_of_minimum_element(array, length, [](float value) {return value >= 0; });
    
    float min_mod;
    if (array[minimum_from_positive_index] < array[maximum_from_negative_index] * -1) {
        min_mod = array[minimum_from_positive_index];
    }
    else {
        min_mod = array[maximum_from_negative_index];
    }
    
    cout << min_mod << endl << endl;
    
    // находим сумму элементов, значение которых принадлежит интервалу [а, b];
    float a, b;
    cin >> a >> b;
    
    cout << get_sum_of_elements_of_array(array, length, [a, b](float value) {return value >= a && value <= b; }) << endl;
    
    // преобразуем массив таким образом, чтобы сначала располагались все отрицательные элементы, а потом – все остальные.
    bubble_sort(array, length);
    array_output(array, length);
    
    system("pause");
}
