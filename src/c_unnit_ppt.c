#include "c_unnit_ppt.h"

#include <stdlib.h>
#include <time.h>

void defaultPrint(struct GeneratedValue *genValue);

unsigned int SEED;
unsigned int REPEAT;

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

int run_property(property ppt, generator gen)
{
    struct GeneratedValue genValue = {
        .value = NULL,
        .size_of = 0,
        .freeValue = NULL,
        .printValue = defaultPrint
    };
    
    if(!gen(&genValue)) {
        printf("Failed to generate a value, check the generator used\n");
        return -1;
    }

    int result = ppt(&genValue);

    if (result != 0) {
        printf("Failed with: ");
        genValue.printValue(&genValue);
        printf("\n");
    }

    genValue.freeValue(genValue.value);

    return result;
}

void run_properties(struct TestPPTList *list)
{
    struct TestPPTNode *current = list->head;

    int ppt_failed[list->length];

    int passed = 0;
    int count = 0;

    printf("SEED: %u\n", SEED);

    while(current != NULL) {
        set_seed(SEED); // reset before each properties
        printf("\nRunning property #%i : %s\n", count, current->pptName);
        for(size_t i = 0; i < REPEAT; i ++) {
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

    printf("\n%i/%i properties passed\n", passed, count);
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

void set_seed(unsigned int seed)
{
    SEED = seed;
    srand(SEED);
}

void set_repeat(unsigned int repeat)
{
    REPEAT = repeat;
}

void defaultPrint(struct GeneratedValue *genValue)
{
    unsigned char *bytes = genValue->value;

    printf("value=%p [", genValue->value);

    for (size_t i = 0; i < genValue->size_of; i++) {
        printf("%02X", bytes[i]);

        if (i + 1 < genValue->size_of)
            printf(" ");
    }

    printf("]\n");
}

void print_int(struct GeneratedValue *genValue) {
    printf("%d", *(int *)genValue->value);
}

int generate_int(struct GeneratedValue* genValue)
{
    genValue->value = malloc(sizeof(int));
    genValue->size_of = sizeof(int);
    genValue->freeValue = free;
    genValue->printValue = print_int;

    if(genValue->value == NULL) 
        return 0;

    unsigned char *bytes = genValue->value;

    for (size_t i = 0; i < sizeof(int); i++) {
        bytes[i] = rand() & 0xFF;
    }

    return 1;
}

void print_array_of_int(struct GeneratedValue* genValue) {

    if(genValue->value == NULL || genValue->size_of == 0) {
        printf("[ ]");
        return;
    }

    int *array = genValue->value;

    printf("[ ");
    for(size_t i = 0; i * sizeof(int) < genValue->size_of; i++) {
        printf("%d", array[i]);
        if(i + 1 < genValue->size_of)
            printf(", ");
    }
    printf(" ]");
}

int generate_array_of_int(struct GeneratedValue *genValue)
{
    int max_array_size = 1000;
    int min_value = -1000;
    int max_value = 1000;

    size_t size;

    if (rand() % 500 == 0)
        size = 0;
    else
        size = 1 + rand() % max_array_size;
    

    genValue->size_of = size * sizeof(int);
    genValue->freeValue = free;
    genValue->printValue = print_array_of_int;

    if (size == 0) {
        genValue->value = NULL;
        return 1;
    }

    genValue->value = malloc(genValue->size_of);

    if (genValue->value == NULL)
        return 0;

    int *array = genValue->value;

    for (size_t i = 0; i < size; i++) {
        array[i] = min_value + rand() % (max_value - min_value + 1);
    }

    return 1;
}
