#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define CITY_NAME_LEN 50
#define FUEL_PRICE 310.0

typedef struct {
    char name[CITY_NAME_LEN];
} City;

typedef struct {
    int capacity;
    int rate_per_km;
    int avg_speed;
    int fuel_efficiency;
    char name[20];
} Vehicle;

typedef struct {
    int src;
    int dest;
    int weight;
    int vehicle_type;
    double distance;
    double delivery_cost;
    double fuel_cost;
    double operational_cost;
    double profit;
    double customer_charge;
    double delivery_time;
} Delivery;

City cities[MAX_CITIES];
int cityCount = 0;
int distance[MAX_CITIES][MAX_CITIES] = {0};

Vehicle vehicles[3];

Delivery deliveries[MAX_DELIVERIES];
int delivery_count = 0;

int main() {
    int choice;
    while (1) {
        printf("----- Logistics Management System -----");
        printf("1. Add City");
        printf("2. Rename City");
        printf("3. Remove City");
        printf("4. Input/Edit Distance");
        printf("5. Display Distance Table");
        printf("6. New Delivery Request");
        printf("7. Estimate Latest Delivery");
        printf("8. Show Performance Reports");
        printf("9. Exit");
        printf("Choose an option : ");
        if
            (scanf("%d", &choice)!=1){
            printf("Invalid input!");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch(choice) {
    case 1: AddCity();
    break;
    case 2: RenameCity();
    break;
    case 3: RemoveCity();
    break;
    case 4: InputDistance();
    break;
    case 5: DisplayDistances();
    break;
    case 6: NewDeliveryRequest();
    break;
    case 7: CalculateAndDisplayLatestDelivery();
    break;
    case 8: ShowReports();
    break;
    case 9: exit(0);
    default: printf("Invalid choice! Try again.");
}
    }
    return 0;
}
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
void AddCity() {
    if (cityCount >= MAX_CITIES) {
        printf("City limit reached.");
        return;
    }
    char new_name[CITY_NAME_LEN];
    printf("Enter city name to add: ");
    fgets(new_name, CITY_NAME_LEN, stdin);
    new_name[strcspn(new_name, " ")] = 0;

    for (int i = 0; i < cityCount; i++) {
        if (strcasecmp(cities[i].name, new_name) == 0) {
            printf("City name already exists.");
            return;
        }
    }
    strcpy(cities[cityCount].name, new_name);
    for (int i = 0; i <= cityCount; i++) {
        distance[cityCount][i] = 0;
        distance[i][cityCount] = 0;
    }
     cityCount++;
    printf("City '%s' added successfully.", new_name);
}
void RenameCity() {
    if (cityCount == 0) {
        printf("No cities to rename.");
        return;
    }
    int idx;
    printf("Enter city index to rename (0 to %d) : ", cityCount-1);
    for (int i=0; i<cityCount; i++) {
        printf("%d: %s", i, cities[i].name);
    }
    if(scanf("%d", &idx)!=1) {
        printf("Invalid input.");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (idx < 0 || idx >= cityCount) {
        printf("Invalid city index.");
        return;
    }
    char new_name[CITY_NAME_LEN];
    printf("Enter new name for city '%s' : ", cities[idx].name);
    fgets(new_name, CITY_NAME_LEN, stdin);
    new_name[strcspn(new_name, " ")] = 0;

    for (int i = 0; i < cityCount; i++) {
        if (i != idx && strcasecmp(cities[i].name, new_name) == 0) {
            printf("Another city already has this name.");
            return;
        }
    }
    strcpy(cities[idx].name, new_name);
    printf("City renamed successfully.");
}
void RemoveCity() {
    if (cityCount == 0) {
        printf("No cities to remove.");
        return;
    }
    int idx;
    printf("Enter city index to remove (0 to %d):", cityCount-1);
    for (int i=0; i<cityCount; i++) {
        printf("%d: %s", i, cities[i].name);
    }
    if(scanf("%d", &idx)!= 1) {
        printf("Invalid input.");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (idx < 0 || idx >= cityCount) {
        printf("Invalid city index.");
        return;
    }
 for (int i = idx; i < cityCount - 1; i++) {
        strcpy(cities[i].name, cities[i+1].name);
        for (int j = 0; j < cityCount; j++) {
            distance[i][j] = distance[i+1][j];
            distance[j][i] = distance[j][i+1];
        }
    }
    cityCount--;
    printf("City removed successfully.");
}
