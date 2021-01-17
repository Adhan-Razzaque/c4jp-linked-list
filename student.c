#include <assert.h>
#include "student.h"

static int gpa_comparator(struct ll_node *student_a,
        struct ll_node *student_b) {
    double a_gpa = LL_ENTRY(student_a, struct student, node)->gpa;
    double b_gpa = LL_ENTRY(student_b, struct student, node)->gpa;

    if (a_gpa > b_gpa) {
        return 1;
    }    
    else if (a_gpa < b_gpa) {
        return -1;
    }
    else {
        return 0;
    }
}

struct student *student_worst_performer(struct student *list) {
    assert(list != NULL);

    return LL_ENTRY(ll_min(&list->node, gpa_comparator), struct student, node);
}

struct student *student_valedictorian(struct student *list) {
    assert(list != NULL);
    
    return LL_ENTRY(ll_max(&list->node, gpa_comparator), struct student, node);
}

static bool honour_roll_check(struct ll_node *check) {
    double student_gpa = LL_ENTRY(check, struct student, node)->gpa;
    return student_gpa >= 3.50;
}

struct student *student_honour_roll(struct student *list) {
    assert(list != NULL);

    struct ll_node *result = ll_filter(&list->node, honour_roll_check);
    if (result != NULL) {
        return LL_ENTRY(result, struct student, node);
    }

    return NULL;
}
