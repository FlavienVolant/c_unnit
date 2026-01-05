#include "c_unnit.h"

#include "stdio.h"
#include "stdlib.h"

struct TestList *create_test_list()
{
    struct TestList *list = malloc(sizeof(struct TestList));

    list->head = NULL;
    list->length = 0;

    return list;
}

struct TestNode *_create_test_node(testFunction f, char *testName) {
    struct TestNode *node = malloc(sizeof(struct TestNode));

    node->f = f;
    node->testName = testName;
    node->next = NULL;

    return node;
}

void append_test(struct TestList *list, testFunction f, char *testName){
    
    struct TestNode *new_node = _create_test_node(f, testName);

    list->length++;

    struct TestNode *tail = list->head;

    if(tail == NULL) {
        list->head = new_node;
        return;
    }

    while(tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = new_node;
}

int run(testFunction f, _beforeEach before, _afterEach after)
{
    void *params = before();

    int result = f(params);

    after(params);

    return result;
}

void run_tests(struct TestList *list, _beforeEach before, _afterEach after){

    struct TestNode *current = list->head;

    int test_failed[list->length];

    int passed = 0;
    int count = 0;

    while(current != NULL) {
        printf("Running test #%i : %s\n", count, current->testName);
        if(run(current->f, before, after) == 0) {
            passed ++;
            printf("\033[32mPassed\033[0m\n\n");
        } else {
            test_failed[count - passed] = count;
            printf("\033[31mFailed\033[0m\n\n");
        }
        count ++;
        current = current->next;
    }

    printf("%i/%i tests passed\n", passed, count);
    if(passed < count) {
        printf("\nThe following tests failed:\n");
        for(int i = 0; i < count - passed; i++) {
            printf("#%i ", test_failed[i]);
        }
        printf("\n");
    }
}

void free_test_list(struct TestList *list){
    clear_tests(list);
    free(list);
}

void _free_test_nodes(struct TestNode *node) {
    if(node == NULL)
        return;
    _free_test_nodes(node->next);
    node->next = NULL;
    free(node);
}

void clear_tests(struct TestList *list){
    _free_test_nodes(list->head);
    list->head = NULL;
    list->length = 0;
}
