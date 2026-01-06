#include "c_unnit.h"

int assert_true_success_test(void *_params) {

    ASSERT_TRUE(5 == 2 + 3);

    return 0;
}

int assert_true_fail_test(void *_params) {

    ASSERT_TRUE(5 == 3 + 3);

    return 0;
}

int assert_false_succes_test(void *_params) {
    
    ASSERT_FALSE(5 == 3 + 3);

    return 0;
}

int assert_false_fail_test(void *_params) {

    ASSERT_FALSE(5 == 2 + 3);

    return 0;
}

int assert_equals_succed_test(void *_params) {

    int x = 5;

    ASSERT_EQUALS(x, 2 + 3);

    return 0;
}

int assert_equals_fail_test(void *_params) {

    int x = 5 + 1;

    ASSERT_EQUALS(x, 2 + 3);

    return 0;
}

int main() {

    struct TestList* tests = create_test_list();

    ADD_TEST(tests, assert_true_success_test);
    ADD_TEST(tests, assert_true_fail_test);
    ADD_TEST(tests, assert_false_succes_test);
    ADD_TEST(tests, assert_false_fail_test);
    ADD_TEST(tests, assert_equals_succed_test);
    ADD_TEST(tests, assert_equals_fail_test);

    run_tests(tests, 0, 0);

    free_test_list(tests);

    return 0;
}