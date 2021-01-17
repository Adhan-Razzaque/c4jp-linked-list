#include <assert.h>
#include "linked_list.h"

void ll_init(struct ll_node *node) {
    assert(node != NULL);
    node->next = NULL;
    node->prev = NULL;
}

bool ll_has_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next != NULL;
}

bool ll_has_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev != NULL;
}

struct ll_node *ll_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next;
}

struct ll_node *ll_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev;
}

size_t ll_size(struct ll_node *head) {
    assert(head != NULL);
    
    size_t size = 1;

    while(ll_has_next(head)) {
        size++;
        head = ll_next(head);
    }

    return size;
}

struct ll_node *ll_head(struct ll_node *list) {
    assert(list != NULL);
    
    while(ll_has_prev(list)) {
        list = ll_prev(list);
    }

    return list;
}

struct ll_node *ll_tail(struct ll_node *list) {
    assert(list != NULL);
    
    while(ll_has_next(list)) {
        list = ll_next(list);
    }

    return list;
}

struct ll_node *ll_get(struct ll_node *node, size_t index) {
    assert(node != NULL);
    // assert(index < size);

    for (long unsigned int i = 0; i < index; i++) {
        node = ll_next(node);
        
        if(node == NULL) {
            return NULL;
        }
            
    }
    return node;
}

void ll_insert_before(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    
    if(ll_has_prev(existing)) {
        existing->prev->next = existing;
    }

    new->prev = existing->prev;
    new->next = existing;
    
    existing->prev = new;
}

void ll_insert_after(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    
    if(ll_has_next(existing)) {
        existing->next->prev = new;
    }

    new->next = existing->next;
    new->prev = existing;

    existing->next = new;
}

void ll_insert_first(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    
    list = ll_head(list);
    ll_insert_before(new, list);
}

void ll_insert_last(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    
    list = ll_tail(list);
    ll_insert_after(new, list);
}

void ll_remove(struct ll_node *node) {
    assert(node != NULL);
    
    if(ll_has_next(node)) {
        node->next->prev = node->prev;
    }
    if(ll_has_prev(node)) {
        node->prev->next = node->next;
    }
}

struct ll_node *ll_min(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    
    struct ll_node *min = list;

    while(list != NULL) {
        if(comparator(list, min) < 0) {
            min = list;
        } 
        list = ll_next(list);
    }
    
    return min;
}

struct ll_node *ll_max(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    
    struct ll_node *max = list;

    while(list != NULL) {
        if(comparator(list, max) > 0) {
            max = list;
        }    

        list = ll_next(list);
    }

    return max;
}

struct ll_node *ll_filter(struct ll_node *list, ll_predicate_t predicate) {
    assert(list != NULL);
    assert(predicate != NULL);
    
    struct ll_node *new_head = NULL;

    while(list != NULL) {
        if (!predicate(list)) {
            ll_remove(list);
        }
        else if(new_head == NULL) {
            new_head = list;
        }
        list = ll_next(list);
    }
    
    return new_head;
}
