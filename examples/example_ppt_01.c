#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "c_unnit_ppt.h"

int add_zero(int x) {
    if(x % 1000 == 0)
        return x + 1;

    return x;
}

int ppt_add_zero_to_x_equal_x(struct GeneratedValue* value) {

    int *x = value->value;
    ASSERT_EQUALS(add_zero(*x), *x);
    return 0;
}

void bubble_sort(int *array, size_t size)
{
    for (size_t i = size; i > 1; i--) {
        for (size_t j = 0; j < i - 1; j++) {
            if (array[j + 1] < array[j]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int sorted_array_of_int_every_number_is_greater_or_equals_to_the_previous_one(struct GeneratedValue* genValue) {

    int *array = genValue->value;
    size_t size = genValue->size_of / sizeof(int);

    bubble_sort(array, size);

    for(size_t i = 1; i < size; i ++) {
        ASSERT_TRUE(array[i-1] <= array[i]);
    }

    return 0;
}

int main() {

    struct TestPPTList *list = create_property_list();

    append_property(list, ppt_add_zero_to_x_equal_x, "x + 0 == 0", generate_int);
    append_property(list, sorted_array_of_int_every_number_is_greater_or_equals_to_the_previous_one, "array[i] <= array[i+1]", generate_array_of_int);

    run_properties(list);

    free_property_list(list);

    return 0;
}