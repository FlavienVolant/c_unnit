#include "c_unnit.h"

#ifndef C_UNNIT_PPT_H
#define C_UNNIT_PPT_H

struct GeneratedValue {
    void *value;
    size_t size_of;

    void (*freeValue)(void *);
    void (*printValue)(struct GeneratedValue*);
};

typedef int generator(struct GeneratedValue* value);
typedef int property(struct GeneratedValue* value);

struct TestPPTList {
    struct TestPPTNode *head;
    int length;
};

struct TestPPTNode {
    property *ppt;
    char *pptName;
    generator *gen;
    struct TestPPTNode *next;
};

struct TestPPTList* create_property_list();

void append_property(struct TestPPTList *list, property ppt, char *pptName, generator gen);

int run_property(property ppt, generator gen);
void run_properties(struct TestPPTList *list);

void clear_property_list(struct TestPPTList *list);
void free_property_list(struct TestPPTList *list);

void set_seed(unsigned int seed);
void set_repeat(unsigned int repeat);

int generate_int(struct GeneratedValue* value);
int generate_array_of_int(struct GeneratedValue* value);

#endif