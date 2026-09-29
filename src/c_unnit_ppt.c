#include "c_unnit_ppt.h"

#include <stdlib.h>
#include <time.h>

int SEED;
int REPEAT;

struct TestPPTList *create_property_list()
{

    set_repeat(1000);
    set_seed(time(NULL));

    struct TestPPTList *list = malloc(sizeof(struct TestPPTList));

    list->head = NULL;
    list->length = 0;

    return list;
}

struct TestPPTNode *_create_ppt_node(property ppt, char *pptName, generator gen) {
    struct TestPPTNode *node = malloc(sizeof(struct TestPPTNode));

    node->ppt = ppt;
    node->pptName = pptName;
    node->gen = gen;
    node->next = NULL;

    return node;
}

void append_property(struct TestPPTList *list, property ppt, char *pptName, generator gen)
{
    struct TestPPTNode *new_node = _create_ppt_node(ppt, pptName, gen);

    list->length++;

    struct TestPPTNode *tail = list -> head;

    if(tail == NULL) {
        list->head = new_node;
        return;
    }

    while(tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = new_node;
}

int run_property(property *ppt, generator *gen)
{
    int value = gen();
    int result = ppt(value);

    if (result != 0) {
        printf("Failed with: %i\n", value);
    }

    return result;
}

void run_properties(struct TestPPTList *list)
{
    struct TestPPTNode *current = list->head;

    int ppt_failed[list->length];

    int passed = 0;
    int count = 0;

    while(current != NULL) {
        printf("Running property #%i : %s\n", count, current->pptName);
        for(int i = 0; i < REPEAT; i ++) {
            if(run_property(current->ppt, current->gen) != 0) {
                ppt_failed[count - passed] = count;
                passed --;
                break;
            }
        }

        passed ++;
        count ++;
        current = current->next;
    }

    printf("%i/%i properties passed\n", passed, count);
    if(passed < count) {
        printf("\nThe following properties failed:\n");
        for(int i = 0; i < count - passed; i++) {
            printf("#%i ", ppt_failed[i]);
        }
        printf("\n");
    }
}

void _free_ppt_nodes(struct TestPPTNode *node) {
    if(node == NULL)
        return;

    _free_ppt_nodes(node->next);
    node->next = NULL;
    free(node);
}

void clear_property_list(struct TestPPTList *list)
{
    _free_ppt_nodes(list->head);
    list->head = NULL;
    list->length = 0;
}

void free_property_list(struct TestPPTList *list)
{
    clear_property_list(list);
    free(list);
}

int set_seed(int seed)
{
    SEED = seed;
    srand(SEED);
}

int set_repeat(int repeat)
{
    REPEAT = repeat;
}

int generate_int()
{

    int res;
    char *p = (char *)&res;

    for(size_t i = 0; i < sizeof(int); i ++) {
        p[i] = rand() & 0xFF;
    }

    return res;
}