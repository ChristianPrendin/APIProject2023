#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// Constants
#define MAX_VEHICLES 512

// Structure to represent a gas station
typedef struct GasStation {
    int distance;
    int num_vehicles;
    int vehicles[MAX_VEHICLES];
    struct GasStation* left;
    struct GasStation* right;
} GasStation;

// Structure to represent a node in the BFS
typedef struct BFS {
    int distance;
    int vehicle;
    int visited;
    int from;
} BFS;

//Finding max on an array
int findMaxArr(int vet[], int num)
{
    int max = 0;
    for (int i = 0; i < num; i++)
    {
        if (vet[i] > max)
        {
            max = vet[i];
        }
    }
    return max;
}


// Function to create a new gas station node
GasStation* createGasStation(int distance, int num_vehicles, int vehicles[]) {
    GasStation* station = (GasStation*)malloc(sizeof(GasStation));
    if (station) {
        station->distance = distance;
        station->num_vehicles = num_vehicles;
        for (int i = 0; i < num_vehicles; i++) {
            station->vehicles[i] = vehicles[i];
        }
        station->left = NULL;
        station->right = NULL;
    }
    return station;
}

// Function to insert a gas station into the BST
GasStation* insertStation(GasStation* root, int distance, int num_vehicles, int vehicles[]) {
    if (root == NULL) {
        return createGasStation(distance, num_vehicles, vehicles);
    }

    if (distance < root->distance) {
        root->left = insertStation(root->left, distance, num_vehicles, vehicles);
    } else if (distance > root->distance) {
        root->right = insertStation(root->right, distance, num_vehicles, vehicles);
    }

    return root;
}

// Function to find a gas station in the BST
GasStation* findStation(GasStation* root, int distance) {
    GasStation* station = root;
    while (station != NULL) {
        if (distance < station->distance) {
            station = station->left;
        } else if (distance > station->distance) {
            station = station->right;
        } else {
            return station; // Found the station
        }
    }
    return NULL; // Station not found
}



// Function to delete the minimum node in the BST and return the new root
GasStation* deleteMinNode(GasStation* root) {
    if (root == NULL) {
        return root;
    }

    if (root->left == NULL) {
        GasStation* temp = root->right;
        free(root);
        return temp;
    }

    root->left = deleteMinNode(root->left);
    return root;
}

// Function to find the minimum node in the BST
GasStation* findMin(GasStation* node) {
    GasStation* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a gas station from the BST
GasStation* deleteStation(GasStation* root, int distance) {
    if (root == NULL) {
        return root;
    }

    if (distance < root->distance) {
        root->left = deleteStation(root->left, distance);
    } else if (distance > root->distance) {
        root->right = deleteStation(root->right, distance);
    } else {
        if (root->left == NULL) {
            GasStation* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            GasStation* temp = root->left;
            free(root);
            return temp;
        }

        GasStation* temp = findMin(root->right);
        root->distance = temp->distance;
        root->num_vehicles = temp->num_vehicles;
        for (int i = 0; i < temp->num_vehicles; i++) {
            root->vehicles[i] = temp->vehicles[i];
        }

        root->right = deleteMinNode(root->right);
    }

    return root;
}

// Function to add a car to a gas station
bool addCarToStation(GasStation* station, int distance, int autonomy) {
    if (station == NULL || station->distance != distance || station->num_vehicles == MAX_VEHICLES) {
        return false;
    }

    station->vehicles[station->num_vehicles++] = autonomy;
    return true;
}

// Function to scrap a car from a gas station
bool scrapCarFromStation(GasStation* station, int distance, int autonomy) {
    if (station == NULL || station->distance != distance || station->num_vehicles == 0) {
        return false;
    }

    int i;
    for (i = 0; i < station->num_vehicles; i++) {
        if (station->vehicles[i] == autonomy) {
            break;
        }
    }

    if (i == station->num_vehicles) {
        return false;
    }

    for (int j = i; j < station->num_vehicles - 1; j++) {
        station->vehicles[j] = station->vehicles[j + 1];
    }

    station->num_vehicles--;
    return true;
}

// Function to destroy the BST and free memory
void destroyBST(GasStation* root) {
    if (root == NULL) {
        return;
    }

    destroyBST(root->left);
    destroyBST(root->right);
    free(root);
}

// Function to find the previous station given the key
GasStation* prevStation(GasStation* root, int key) {
    GasStation* prev = NULL;
    while (root != NULL) {
        if (key > root->distance) {
            prev = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return prev;
}

// Function to find the next station given the key
GasStation* nextStation(GasStation* root, int key) {
    GasStation* next = NULL;
    while (root != NULL) {
        if (key < root->distance) {
            next = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return next;
}

void front_planroute(GasStation* root, int start, int end) {
    int num_nodes = 1;
    GasStation* startStation = findStation(root, start);
    GasStation* endStation = findStation(root, end);
    while (startStation != endStation) {
        num_nodes++;
        endStation = prevStation(root, endStation->distance);
    }

    BFS* stations = (BFS*)malloc(sizeof(BFS) * num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        stations[i].distance = startStation->distance;
        stations[i].vehicle = findMaxArr(startStation->vehicles, startStation->num_vehicles);
        stations[i].visited = 0;
        stations[i].from = -1;
        startStation = nextStation(root, startStation->distance);
    }
    int* queue = (int*)malloc(sizeof(int) * num_nodes);
    int head = 0;
    int tail = 0;

    queue[tail++] = 0;
    stations[0].visited = 1;
    
    while (head < tail) {
        int current = queue[head++];
        for (int i = current; i < num_nodes; i++) {
            if (stations[i].visited == 0 && stations[current].vehicle >= stations[i].distance - stations[current].distance) {
                stations[i].visited = 1;
                stations[i].from = current;
                queue[tail++] = i;
            }
        }
    }

    if(stations[num_nodes - 1].visited == 0)
    {
        printf("nessun percorso\n");
        return;
    }

    int* path = (int*)malloc(sizeof(int) * num_nodes);
    int path_length = 0;
    int current = num_nodes - 1;
    while (current != -1) {
        path[path_length++] = current;
        current = stations[current].from;
    }

    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d ", stations[path[i]].distance);
    }
    printf("\n");

    free(stations);
    free(queue);
    free(path);
}

void reverse_planroute(GasStation* root, int start, int end)
{
    int num_nodes = 1;
    GasStation* startStation = findStation(root, start);
    GasStation* endStation = findStation(root, end);
    while (startStation != endStation) {
        num_nodes++;
        startStation = prevStation(root, startStation->distance);
    }

    BFS* stations = (BFS*)malloc(sizeof(BFS) * num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        stations[i].distance = endStation->distance;
        stations[i].vehicle = findMaxArr(endStation->vehicles, endStation->num_vehicles);
        stations[i].visited = 0;
        stations[i].from = -1;
        endStation = nextStation(root, endStation->distance);
    }
    int* queue = (int*)malloc(sizeof(int) * num_nodes);
    int head = 0;
    int tail = 0;

    queue[tail++] = 0;
    stations[0].visited = 1;
    
    while (head < tail) {
        int current = queue[head++];
        for (int i = current; i < num_nodes; i++) {
            if (stations[i].visited == 0 && stations[i].vehicle >= stations[i].distance - stations[current].distance) {
                stations[i].visited = 1;
                stations[i].from = current;
                queue[tail++] = i;
            }
        }
    }

    if(stations[num_nodes - 1].visited == 0)
    {
        printf("nessun percorso\n");
        return;
    }

    int* path = (int*)malloc(sizeof(int) * num_nodes);
    int path_length = 0;
    int current = num_nodes - 1;
    while (current != -1) {
        path[path_length++] = current;
        current = stations[current].from;
    }

    for (int i = 0; i < path_length; i++) {
        printf("%d ", stations[path[i]].distance);
    }
    printf("\n");

    free(stations);
    free(queue);
    free(path);
}


void plan_route(GasStation* root, int start, int end)
{
    if (start == end)
    {
        printf("%d", start);
        return;
    }
    if (start < end)
    {
        front_planroute(root, start, end);
    }
    if (start > end)
    {
        reverse_planroute(root, start, end);
    }
    
    
}

// Inside the main function, simplified conditionals and improved error handling

int main() {
    char line[100];
    GasStation* root = NULL;

    while (scanf("%s", line) != EOF) {
        if (strcmp(line, "aggiungi-stazione") == 0) {
            int distance, num_vehicles;
            if (scanf("%d %d", &distance, &num_vehicles) != 2) {
                perror("Invalid input");
                exit(EXIT_FAILURE);
            }

            int vehicles[MAX_VEHICLES];
            for (int i = 0; i < num_vehicles; i++) {
                if (scanf("%d", &vehicles[i]) != 1) {
                    perror("Invalid input");
                    exit(EXIT_FAILURE);
                }
            }

            GasStation* temp = findStation(root, distance);
            if (!temp) {
                root = insertStation(root, distance, num_vehicles, vehicles);
                printf("aggiunta\n");
            } else {
                printf("non aggiunta\n");
            }
        } else if (strcmp(line, "demolisci-stazione") == 0) {
            int distance;
            if (scanf("%d", &distance) != 1) {
                perror("Invalid input");
                exit(EXIT_FAILURE);
            }

            GasStation* station_to_remove = findStation(root, distance);
            if (station_to_remove) {
                root = deleteStation(root, distance);
                printf("demolita\n");
            } else {
                printf("non demolita\n");
            }
        } else if (strcmp(line, "aggiungi-auto") == 0) {
            int distance, autonomy;
            if (scanf("%d %d", &distance, &autonomy) != 2) {
                perror("Invalid input");
                exit(EXIT_FAILURE);
            }

            GasStation* station_to_add_car = findStation(root, distance);
            if (station_to_add_car) {
                bool added = addCarToStation(station_to_add_car, distance, autonomy);
                if (added) {
                    printf("aggiunta\n");
                } else {
                    printf("non aggiunta\n");
                }
            } else {
                printf("non aggiunta\n");
            }
        } else if (strcmp(line, "rottama-auto") == 0) {
            int distance, autonomy;
            if (scanf("%d %d", &distance, &autonomy) != 2) {
                perror("Invalid input");
                exit(EXIT_FAILURE);
            }

            GasStation* station_to_scrap_car = findStation(root, distance);
            if (station_to_scrap_car) {
                bool scrapped = scrapCarFromStation(station_to_scrap_car, distance, autonomy);
                if (scrapped) {
                    printf("rottamata\n");
                } else {
                    printf("non rottamata\n");
                }
            } else {
                printf("non rottamata\n");
            }
        } else if (strcmp(line, "pianifica-percorso") == 0) {
            int start_distance, end_distance;
            if (scanf("%d %d", &start_distance, &end_distance) != 2) {
                perror("Invalid input");
                exit(EXIT_FAILURE);
            }

            plan_route(root, start_distance, end_distance);
        }
    }

    destroyBST(root);
    return 0;
}
