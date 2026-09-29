#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "c_unnit_ppt.h"

int add_zero(int x) {
    if(x % 400 == 0)
        return x + 1;

    return x;
}

int ppt_add_zero_to_x_equal_x(int x) {
    ASSERT_EQUALS(add_zero(x), x);
    return 0;
}

int main() {

    set_seed(time(NULL));

    struct TestPPTList *list = create_property_list();

    append_property(list, ppt_add_zero_to_x_equal_x, "x + 0 == 0", generate_int);

    run_properties(list);

    free_property_list(list);

    return 0;
}