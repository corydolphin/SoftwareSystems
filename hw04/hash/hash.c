/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// VALUE: represents a value in a key-value pair

/* Here's one way of making a polymorphic object in C */

typedef struct {
    enum Type {INT, STRING} type;
    union {
	int i;
	char *s;
    };
} Value;


/* Makes a Value object that contains an int. */
Value *make_int_value(int i) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string. */
Value *make_string_value(char *s) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = STRING;
    value->s = s;
    return value;
}


/* Prints a value object. */
void print_value (Value *value) 
{
    if (value == NULL) {
        printf ("%p", value);
	return;
    }
    switch (value->type) {
    case INT:
	printf ("%d", value->i);
	break;
    case STRING:
	printf ("%s", value->s);
	break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

hash is a pointer to a function that knows how to hash the key.
equal is a pointer to a function that knows how to compare keys.

 */

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;


/* Makes a Hashable object. */
Hashable *make_hashable(void *key, 
			int (*hash) (void *),
			int (*equal) (void *, void *)
			)
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    return hashable;
}


/* Prints a Hashable object. */
void print_hashable(Hashable *hashable)
{
    printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer. */
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string. */
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
	total += s[i];
	i++;
    }
    return total;
}


/* Hashes any Hashable. */
int hash_hashable(Hashable *hashable)
{
    return hashable->hash (hashable->key);
}


/* Checks two integers for equality
    Returns 1 if equal, 0 otherwise
*/
int equal_int (void *ip, void *jp)
{
    return *(int*)ip == *(int*)jp;
}


/* Checks two strings for equality
    Returns 1 if equal, 0 otherwise
*/
int equal_string (void *s1, void *s2)
{
    return strcmp(s1,s2) ==0;
}


/* Checks two Hashables for equality
    Returns 1 if equal, 0 otherwise
    Two hashables are equal if both their key and value are equivalent
*/
int equal_hashable(Hashable *h1, Hashable *h2)
{
    return hash_hashable(h1) == hash_hashable(h2) && h1->equal(h2,h2);
}


/* Makes a Hashable int. 

Allocates space and copies the int.
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int);
}


/* Makes a Hashable string. 

Stores a reference to the string (not a copy).
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string);
}



// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;


/* Makes a Node. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
    Node *result = (Node*)malloc(sizeof(Node));
    result->key = key;
    result->value = value;
    result->next = next;
    return result;
}


/* Prints a Node. */
void print_node(Node *node)
{
    print_hashable(node->key);
    printf("value ");
    print_value(node->value);
    printf("\n");   
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. */
void print_list(Node *node)
{
    Node* current = node;
    while(current){
        print_node(current);
        current = current->next;
    } 
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.
 */
Node *prepend(Hashable *key, Value *value, Node *rest)
{
    return make_node(key, value, rest);
}


/* Looks up a key and returns the corresponding value, or NULL */
Value *list_lookup(Node *list, Hashable *key)
{
    Node* current = list; // Initialized to the start of the list
    while(current){
        if(equal_hashable(current->key,key)){
            return current->value;
        }
        current = current->next;
    } 

    return NULL;
}


// MAP: a map is a list of key-value pairs

typedef struct map {
    int n;
    Node **lists;
} Map;


/* Makes a Map with n lists. */
Map *make_map(int n)
{
    // FIX ME!
    Map* result = (Map *)malloc(sizeof(Map));
    result->lists = (Node **)malloc(n*sizeof(Node));
    for(int i=0; i < n;i++){
        result->lists[i] = NULL; // Ensure all point to null
    }
    result->n = n;
    return result;
}


/* Prints a Map. */
void print_map(Map *map)
{
    int i;

    for (i=0; i<map->n; i++) {
	if (map->lists[i] != NULL) {
	    printf ("%d\n", i);
	    print_list (map->lists[i]);
	}
    }
}


int get_list_index(Map* map, Hashable* key){
    return hash_hashable(key) % (map->n);
}

/* Adds a key-value pair to a map. */
void map_add(Map *map, Hashable *key, Value *value)
{
    int list_index = get_list_index(map,key);
    Node* front = map->lists[list_index];
    Node* newFront = prepend(key,value,front);
    map->lists[list_index] = newFront;
}

/* Looks up a key and returns the corresponding value, or NULL. */
Value *map_lookup(Map *map, Hashable *key)
{
    return list_lookup(map->lists[get_list_index(map,key)],key);
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value (value);
    printf ("\n");
}

