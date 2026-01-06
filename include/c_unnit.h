#include "stdio.h"

#ifndef C_UNNIT_H
#define C_UNNIT_H

#define ADD_TEST(list, func) append_test(list, func, #func)

#define ASSERT_TRUE(boolean)\
if (!(boolean)) { \
    printf("[ASSERT_TRUE] expected {%s} to be TRUE but was FALSE (%s:%d)\n", \
           #boolean, __FILE__, __LINE__); \
    return -1; \
}

#define ASSERT_FALSE(boolean)\
if (boolean) { \
    printf("[ASSERT_FALSE] expected {%s} to be FALSE but was TRUE (%s:%d)\n", \
           #boolean, __FILE__, __LINE__); \
    return -1; \
}

#define ASSERT_NULL(ptr)\
if ((ptr) != NULL) { \
    printf("[ASSERT_NULL] expected {%s} to be NULL but was %p (%s:%d)\n", \
           #ptr, (void*)(ptr), __FILE__, __LINE__); \
    return -1; \
}

#define ASSERT_NOT_NULL(ptr)\
if ((ptr) == NULL) { \
    printf("[ASSERT_NOT_NULL] expected {%s} to be NOT NULL but was NULL (%s:%d)\n", \
           #ptr, __FILE__, __LINE__); \
    return -1; \
}

#define ASSERT_EQUALS(actual, expected)\
if ((actual) != (expected)) { \
    printf("[ASSERT_EQUALS] expected {%s} == {%s} but it was not (%s:%d)\n", \
           #actual, #expected, __FILE__, __LINE__); \
    return -1; \
}

typedef void*(_beforeEach()); // return the struct of params as void*
typedef int(testFunction(void *params)); // params are given by _beforeEach, return 0 == success; other == fail
typedef void(_afterEach(void *params)); // used to free the params allocated in _beforeEach

struct TestList {
    struct TestNode *head;
    int length;
};

struct TestNode {
    testFunction *f;
    char *testName;
    struct TestNode *next;
};

struct TestList* create_test_list();

void append_test(struct TestList *list, testFunction f, char *testName);

int run(testFunction f, _beforeEach before, _afterEach after);
void run_tests(struct TestList *list, _beforeEach before, _afterEach after);

void clear_tests(struct TestList *list);
void free_test_list(struct TestList *list);

#endif // C_UNITS_H