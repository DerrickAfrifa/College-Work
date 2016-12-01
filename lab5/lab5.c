#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bloom.h"


int main(int argc, char* argv[]){
    const char LAB5[] = "bloom";
    const char LAB4[] = "bitset";

    if(strcmp(argv[1], LAB5) == 0){
        FILE *fp1;
        FILE *fp2;
        FILE *fp3;
        char buff[ASCII_SIZE];
        Bloom* first = bloom_new(BLOOM_FILTER_SIZE);
        Bloom* second = bloom_new(BLOOM_FILTER_SIZE);
        Bloom* seen = bloom_new(BLOOM_FILTER_SIZE);
        Bloom* written = bloom_new(BLOOM_FILTER_SIZE);

        fp1 = fopen(argv[2], "r");
        fp2 = fopen(argv[3], "r");
        fp3 = fopen(argv[4], "r");

        while(!feof(fp1)){
            fscanf(fp1, "%s", buff);
            bloom_add(first, buff);
        }

        while(!feof(fp2)){
            fscanf(fp2, "%s", buff);
            bloom_add(second, buff);
        }

        bloom_intersect(seen, first, second);

        while(!feof(fp3)){
            fscanf(fp3, "%s", buff);
            if(bloom_lookup(seen, buff)) {
                if(!bloom_lookup(written, buff)) printf("%s\n", buff);
                bloom_add(written, buff);
            }
        }

        fclose(fp1);
        fclose(fp2);
        fclose(fp3);

    }else if(strcmp(argv[1], LAB4) == 0){
        Bitset* bsp1 = bitset_new(ASCII_SIZE);
        Bitset* bsp2 = bitset_new(ASCII_SIZE);
        Bitset* bspUnion = bitset_new(ASCII_SIZE);
        Bitset* bspIntersect = bitset_new(ASCII_SIZE);

        char unionString[ASCII_SIZE];
        char* string;
        //char intersectString[256];

        printf("%s\n", argv[2]);
        printf("%s\n", argv[3]);

        int i=0;
        while(argv[2][i] != '\0'){
            bitset_add(bsp1, argv[2][i++]);
        }
        i =0;
        while(argv[3][i] != '\0'){
            bitset_add(bsp2, argv[3][i++]);
        }

        bitset_union(bspUnion, bsp1, bsp2);
        bitset_print(bspUnion, unionString);
        bitset_intersect(bspIntersect, bsp1, bsp2);
        string = bitset_toString(bspIntersect);
        printf("%s\n", string);
    }else{
        printf("Input was invalid.\n");
    }

    return 0;
}
