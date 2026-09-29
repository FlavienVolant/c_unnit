#include "c_unnit.h"

#ifndef C_UNNIT_PPT_H
#define C_UNNIT_PPT_H

typedef int generator();
typedef int property(int);

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

int set_seed(int seed);
int set_repeat(int repeat);

int generate_int();

#endif