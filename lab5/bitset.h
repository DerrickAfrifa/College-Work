#define INT_BITS 32
#define ASCII_SIZE 256

typedef struct bitset{
    int size;
    int* bitVector;
}Bitset;


Bitset* bitset_new(int size){
    Bitset* bsp;
    int arraySize = ceil((float)size/INT_BITS);
    bsp = malloc(sizeof(Bitset));
    bsp->size = arraySize;
    bsp->bitVector = calloc(arraySize, sizeof(int));
    return bsp;
}

//return 1 if in set, 0 if not -1 if out of bounds
int bitset_lookup(Bitset * this, int item){
    if (item < 0 || item > this->size*INT_BITS) return -1; //out of bounds

    int arrayIndex = item/INT_BITS;
    int bitIndex = item % INT_BITS;
    int element = this->bitVector[arrayIndex];

    return((element >> bitIndex)& 1) == 1;
}

//return 0 if out of bounds 1 otherwise
int bitset_add(Bitset * this, int item){
    if (item < 0 || item > this->size*INT_BITS) return 0;

    int arrayIndex = item/INT_BITS;
    int bitIndex = item % INT_BITS;
    int mask = 1 << bitIndex;
    this->bitVector[arrayIndex] = this->bitVector[arrayIndex] | mask;

    return 1;
}

//return 0 if out of bounds 1 otherwise
int bitset_remove(struct bitset * this, int item){
    if (item < 0 || item > this->size*INT_BITS) return 0;

    int arrayIndex = item/INT_BITS;
    int bitIndex = item % INT_BITS;
    int mask = 1 << bitIndex;
    mask = ~mask;
    this->bitVector[arrayIndex] = this->bitVector[arrayIndex] & mask;

    return 1;
}

void bitset_union(Bitset * dest, Bitset * src1, Bitset * src2){
    for(int i=0; i<8; i++){
        dest->bitVector[i] = src1->bitVector[i] | src2->bitVector[i];
    }

}

void bitset_intersect(Bitset * dest, Bitset * src1, Bitset * src2){
    for(int i=0; i<dest->size; i++){
        dest->bitVector[i] = src1->bitVector[i] & src2->bitVector[i];
    }
}

//prints string of bitset
void bitset_print(Bitset* this, char string[]){
    int set=0;
    for(int i=0; i<ASCII_SIZE; i++){
        if(bitset_lookup(this, i) == 1){
            string[set++] = i;
        }
    }
    string[set] = '\0';

    printf("%s\n", string);
}

//returns string of bitset
char* bitset_toString(Bitset* this){
    char* s;
    s = malloc(ASCII_SIZE*sizeof(char));
    int set=0;

    for(int i=0; i<ASCII_SIZE; i++){
        if(bitset_lookup(this, i)) s[set++] = i;
    }

    s[set] = '\0';
    s = realloc(s, (set)*sizeof(char));

    return s;
}
