#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 1000
#define MAX_CYLINDER 5000

void read_requests(const char* filename, int requests[]);
int fcfs(int requests[], int start_pos, int n);
int scan(int requests[], int start_pos, int n, int optimize);
int c_scan(int requests[], int start_pos, int n, int optimize);
void sort_requests(int requests[], int n);

int main() {
    int requests[MAX_REQUESTS];
    int sorted_requests[MAX_REQUESTS];
    int start_pos = 1000; 
    read_requests("input.txt", requests);

    for (int i = 0; i < MAX_REQUESTS; i++) {
        sorted_requests[i] = requests[i];
    }
    sort_requests(sorted_requests, MAX_REQUESTS);

    printf("Original FCFS Total Head Movements: %d\n", fcfs(requests, start_pos, MAX_REQUESTS));
    printf("Original SCAN Total Head Movements: %d\n", scan(requests, start_pos, MAX_REQUESTS, 0));
    printf("Original C-SCAN Total Head Movements: %d\n", c_scan(requests, start_pos, MAX_REQUESTS, 0));

    printf("Optimized FCFS Total Head Movements: %d\n", fcfs(sorted_requests, start_pos, MAX_REQUESTS));
    printf("Optimized SCAN Total Head Movements: %d\n", scan(sorted_requests, start_pos, MAX_REQUESTS, 1));
    printf("Optimized C-SCAN Total Head Movements: %d\n", c_scan(sorted_requests, start_pos, MAX_REQUESTS, 1));

    return 0;
}

void read_requests(const char* filename, int requests[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_REQUESTS; i++) {
        if (fscanf(file, "%d", &requests[i]) != 1) {
            perror("Error reading file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
}

int fcfs(int requests[], int start_pos, int n) {
    int total_movement = 0;
    total_movement += abs(start_pos - requests[0]);
    for (int i = 1; i < n; i++) {
        total_movement += abs(requests[i] - requests[i - 1]);
    }
    return total_movement;
}

int scan(int requests[], int start_pos, int n, int optimize) {
    if (optimize) {
        sort_requests(requests, n);
    }
    int total_movement = 0;
    int i = 0;

    while (i < n && requests[i] < start_pos) i++;
    for (int j = i; j < n; j++) {
        total_movement += abs(start_pos - requests[j]);
        start_pos = requests[j];
    }

    for (int j = i - 1; j >= 0; j--) {
        total_movement += abs(start_pos - requests[j]);
        start_pos = requests[j];
    }

    return total_movement;
}

int c_scan(int requests[], int start_pos, int n, int optimize) {
    if (optimize) {
        sort_requests(requests, n);
    }
    int total_movement = 0;
    int i = 0;

    while (i < n && requests[i] < start_pos) i++;
    for (int j = i; j < n; j++) {
        total_movement += abs(start_pos - requests[j]);
        start_pos = requests[j];
    }

    if (i > 0) {
        total_movement += abs(start_pos - MAX_CYLINDER - 1);
        start_pos = 0;
        for (int j = 0; j < i; j++) {
            total_movement += abs(start_pos - requests[j]);
            start_pos = requests[j];
        }
    }

    return total_movement;
}

void sort_requests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}
