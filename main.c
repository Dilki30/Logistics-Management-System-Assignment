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
    }










































































































































    return 0;
}
