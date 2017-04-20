/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 3
 * Nov 7, 2016
 * Data Structures
 * A down heap method, for a 2D matrix index.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct struct_object{
    int key;
    int* array;
} Object;

/**
 * downHeap
 * Down heap an element.
 *
 * IN: (Object*) the index to the matrix, (int) height, (int) index.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
void downHeap(Object* heap, int height, int index) {
    int indexL = (index) * 2;
    int indexR = (index) * 2 + 1;

    //  Validate some conditions
    if (index > floor(height/2)) return;
    if (indexL > height) indexR = height;
    if (indexR > height) indexR = height;

    //  If the children keys are less than the parent swap em
    if (heap[indexL].key < heap[indexR].key) {
        if (heap[index].key > heap[indexL].key) {
            Object temp = heap[index];
            heap[index] = heap[indexL];
            heap[indexL] = temp;
            //  Fix the broken heap
            downHeap(heap, height, indexL);
        }
    } else {
        if (heap[index].key > heap[indexR].key) {
            Object temp = heap[index];
            heap[index] = heap[indexR];
            heap[indexR] = temp;
            //  Fix the broken heap
            downHeap(heap, height, indexR);
        }
    }
}

/**
 * heapify
 * Call the sort function.
 *
 * IN: (Object*) the heap.
 * RETURN: (Type) Description.
 * ERROR: Error.
 *
 **/
void heapify(Object* obj, int height){
  for (int i = floor(height/2); i > 0; i--)
    downHeap(obj,height,i);
}

int main() {
    //  Open the file or die
    FILE* fp = fopen("f.dat","r");
    if (fp == NULL) { printf("Unable to open file."); return 1;}

    //  init the variables we need to parse the matrix
    char line[50];
    int matrix[20][10];
    Object heapArray[21];
    int sum = 0, first = 1, count = 0, xcoord = 0;

    //  Read file and populate matrix
    while(fgets(line, 50, fp) != NULL) {
        //  Some gross parser cause strtok was being stubborn and this was faster
        for (int i = 0; i < 30; i++) {
            if (i < 27) {
                //  Parse the number
                if (line[i] == ' ') {
                    sum = ((line[i+1] - '0') * 10) + (line[i+2] - '0'); //  Parse the two digit number
                    i = i + 2;
                } else if (first) {
                    sum = ((line[i] - '0') * 10) + (line[i+1] - '0');   //  Parse the two digit number
                    first = 0; i++;
                }
                matrix[count][xcoord] = sum;
                xcoord++;
            }
        } xcoord = 0; first = 1;    //  Sooo many counters to reset

        //  heapArray is an index of the matrix storing a key and a pointer to the row.
        heapArray[count+1].key = matrix[count][0] + matrix[count][1] + matrix[count][2];
        heapArray[count+1].array = &matrix[count][0];
        count++;
    }
    fclose(fp);

    //  Apply downheap
    heapify(heapArray, 20);

    //  Print the heap
    printf("\nThe min-heap matrix is: \n\n");
    for (int i = 1; i <= 20; i++) {
        for (int k = 0; k < 10; k++) {
            if (heapArray[i].array[k] < 10)
                printf("0%d ", heapArray[i].array[k]);
            else
                printf("%d ", heapArray[i].array[k]);

        } printf("\tKey: %d",heapArray[i].key);
        printf("\n");
    }

    return 0;
}
