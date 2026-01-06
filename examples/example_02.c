#include "c_unnit.h"

int assert_null_success_test(void *_params) {

    int *p = 0;

    ASSERT_NULL(p);

    return 0;
}

int assert_null_fail_test(void *_params) {

    int x = 5;
    ASSERT_NULL(&x);

    return 0;
}

int assert_not_null_succes_test(void *_params) {
    
    int x = 5;
    ASSERT_NOT_NULL(&x);

    return 0;
}

int assert_not_null_fail_test(void *_params) {

    int *p = 0;
    ASSERT_NOT_NULL(p);

    return 0;
}

int test_params_should_be_null_when_no_before_each_function_is_given(void *_params) {
    ASSERT_NULL(_params);

    return 0;
}

int main() {

    struct TestList* tests = create_test_list();

    ADD_TEST(tests, assert_null_success_test);
    ADD_TEST(tests, assert_null_fail_test);
    ADD_TEST(tests, assert_not_null_succes_test);
    ADD_TEST(tests, assert_not_null_fail_test);
    ADD_TEST(tests, test_params_should_be_null_when_no_before_each_function_is_given);

    run_tests(tests, 0, 0);

    free_test_list(tests);

    return 0;
}