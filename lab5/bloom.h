#include "bitset.h"
#define ASCII_SIZE 256
#define BLOOM_FILTER_SIZE 1000000

typedef struct bloom{
    Bitset* bitset;
}Bloom;

int hashFunc1(char* word){
    int hashAddress = 0;
    for (int i = 0; word[i]!='\0'; i++){
        hashAddress = word[i] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
    return hashAddress % BLOOM_FILTER_SIZE;
}

int hashFunc2(char* word){
    int hashAddress = 5381;
    for (int i = 0; word[i]!='\0'; i++){
        hashAddress = ((hashAddress << 5) + hashAddress) + word[i];
    }
    return hashAddress % BLOOM_FILTER_SIZE;
}

// create a new, empty Bloom filter of 'size' items
struct bloom * bloom_new(int size){
    Bloom* bp;
    bp = malloc(sizeof(Bloom));
    bp->bitset = bitset_new(size);

    return bp;
};

// check to see if a string is in the set
int bloom_lookup(Bloom * this, char * item){
    int firstSet = hashFunc1(item);
    int secondSet = hashFunc2(item);

    return (bitset_lookup(this->bitset, firstSet)) && (bitset_lookup(this->bitset, secondSet));
}

// add a string to the set
// has no effect if the item is already in the set
void bloom_add(Bloom * this, char * item){
    int firstSet = hashFunc1(item);
    int secondSet = hashFunc2(item);

    bitset_add(this->bitset, firstSet);
    bitset_add(this->bitset, secondSet);
}

// place the union of src1 and src2 into dest
void bloom_union(Bloom * dest, Bloom * src1, Bloom * src2){
    bitset_union(dest->bitset, src1->bitset, src2->bitset);
}

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2){
    bitset_intersect(dest->bitset, src1->bitset, src2->bitset);
}
