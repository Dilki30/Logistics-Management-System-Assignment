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

Vehicle vehicles[3] = {
{1000, 30, 60, 12, "Van"},
{5000, 40, 50, 6, "Truck"},
{10000, 80, 45, 4, "Lorry"}
};

Delivery deliveries[MAX_DELIVERIES];
int delivery_count = 0;

int main() {
    int choice;
    while (1) {
        printf("----- Logistics Management System -----\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Input/Edit Distance\n");
        printf("5. Display Distance Table\n");
        printf("6. New Delivery Request\n");
        printf("7. Estimate Latest Delivery\n");
        printf("8. Show Performance Reports\n");
        printf("9. Exit\n");
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
    default: printf("Invalid choice! Try again.\n");
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
        printf("City limit reached.\n");
        return;
    }
    char new_name[CITY_NAME_LEN];
    printf("Enter city name to add: \n");
    fgets(new_name, CITY_NAME_LEN, stdin);
    new_name[strcspn(new_name, " ")] = 0;

    for (int i = 0; i < cityCount; i++) {
        if (strcasecmp(cities[i].name, new_name) == 0) {
            printf("City name already exists.\n");
            return;
        }
    }
    strcpy(cities[cityCount].name, new_name);
    for (int i = 0; i <= cityCount; i++) {
        distance[cityCount][i] = 0;
        distance[i][cityCount] = 0;
    }
     cityCount++;
    printf("City '%s' added successfully.\n", new_name);
}
void RenameCity() {
    if (cityCount == 0) {
        printf("No cities to rename.\n");
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
            printf("Another city already has this name.\n");
            return;
        }
    }
    strcpy(cities[idx].name, new_name);
    printf("City renamed successfully.\n");
}
void RemoveCity() {
    if (cityCount == 0) {
        printf("No cities to remove.\n");
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
    printf("City removed successfully.\n");
}
void InputDistance() {
    if (cityCount < 2) {
        printf("Add at least two cities first.\n");
        return;
    }
    int from, to;
    printf("Cities : ");
    for (int i = 0; i < cityCount; i++) {
        printf("%d: %s", i, cities[i].name);
    }
    printf("Enter source city index: ");
    if(scanf("%d", &from)!=1) {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }
    printf("Enter destination city index: ");
    if(scanf("%d", &to)!= 1) {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
          }
    clear_input_buffer();

    if (from < 0 || from >= cityCount || to < 0 || to >= cityCount) {
        printf("Invalid city indices.");
        return;
    }
    if (from == to) {
        printf("Distance from city to itself is zero.\n");
        return;
    }
    int dist;
    printf("Enter distance from %s to %s (km): ", cities[from].name, cities[to].name);
    if(scanf("%d", &dist)!= 1) {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }
    if (dist <= 0) {
        printf("Distance must be positive.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    distance[from][to] = dist;
    distance[to][from] = dist;
    printf("Distance updated.\n");
}
void DisplayDistances() {
    if (cityCount == 0) {
        printf("No cities added yet.\n");
        return;
    }
    printf("Distance Matrix : ");
    for(int i = 0; i<cityCount; i++) {
        printf("%-10s", cities[i].name);
    }
    printf(" ");
    for (int i = 0; i < cityCount; i++) {
        printf("%-6s", cities[i].name);
        for (int j = 0; j < cityCount; j++) {
            printf("%-10d", distance[i][j]);
        }
        printf(" ");
    }
}
void NewDeliveryRequest() {
    if (cityCount < 2) {
        printf("At least two cities are required for deliveries.\n");
        return;
    }
    if (delivery_count >= MAX_DELIVERIES) {
        printf("Max delivery records reached.\n");
        return;
    }
    int src, dest, weight, vtype;

    printf("Select source city : ");
    for(int i=0; i < cityCount; i++) {
        printf("%d: %s", i, cities[i].name);
    }
    if(scanf("%d", &src)!= 1) {
        printf("Invalid input.");
        clear_input_buffer();
        return;
    }
    printf("Select destination city:");
    if(scanf("%d", &dest)!= 1) {
        printf("Invalid input.");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (src < 0 || src >= cityCount || dest < 0 || dest >= cityCount || src == dest) {
        printf("Invalid source/destination selected.\n");
        return;
    }
    printf("Enter weight (kg) : ");
    if(scanf("%d", &weight)!= 1) {
        printf("Invalid input.");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (weight <= 0) {
        printf("Weight must be positive.\n");
        return;
    }
    printf("Select vehicle type : ");
    for (int i = 0; i < 3; i++) {
        printf("%d: %s (Capacity: %d kg)", i+1, vehicles[i].name, vehicles[i].capacity);
    }
    if(scanf("%d", &vtype)!= 1) {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (vtype < 1 || vtype > 3) {
        printf("Invalid vehicle type.\n");
        return;
    }
    Vehicle v = vehicles[vtype - 1];
    if(weight > v.capacity) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }
    deliveries[delivery_count].src = src;
    deliveries[delivery_count].dest = dest;
    deliveries[delivery_count].weight = weight;
    deliveries[delivery_count].vehicle_type = vtype -1;
    delivery_count++;

    printf("Delivery request recorded.\n");
}
void CalculateAndDisplayLatestDelivery() {
    if (delivery_count == 0) {
        printf("No deliveries recorded.\n");
        return;
    }
    Delivery *d = &deliveries[delivery_count - 1];
    int dist = distance[d->src][d->dest];
    if(dist == 0) {
        printf("Distance between %s and %s not set.\n", cities[d->src].name, cities[d->dest].name);
        return;
    }
    Vehicle v = vehicles[d->vehicle_type];
    double delivery_cost = dist * v.rate_per_km * (1 + ((double)d->weight)/10000);
    double delivery_time = (double) dist / v.avg_speed;
    double fuel_used = (double) dist / v.fuel_efficiency;
    double fuel_cost = fuel_used * FUEL_PRICE;
    double operational_cost = delivery_cost + fuel_cost;
    double profit = delivery_cost * 0.25;
    double customer_charge = operational_cost + profit;

    d->distance = dist;
    d->delivery_cost = delivery_cost;
    d->fuel_cost = fuel_cost;
    d->operational_cost = operational_cost;
    d->profit = profit;
    d->customer_charge = customer_charge;
    d->delivery_time = delivery_time;

    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("From: %s\n", cities[d->src].name);
    printf("To: %s\n", cities[d->dest].name);
    printf("Distance: %d km\n", dist);
    printf("Vehicle: %s\n", v.name);
    printf("Weight: %d kg\n", d->weight);
    printf("Base Cost: %.2f LKR\n", delivery_cost);
    printf("Fuel Used: %.2f L\n", fuel_used);
    printf("Fuel Cost: %.2f LKR\n", fuel_cost);
    printf("Operational Cost: %.2f LKR\n", operational_cost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customer_charge);
    printf("Estimated Time: %.2f hours\n", delivery_time);
printf("\n======================================================\n");
}
void ShowReports() {
    if (delivery_count == 0) {
        printf("No deliveries completed yet.");
        return;
    }
    int total_deliveries = delivery_count;
    int total_distance = 0;
    double total_delivery_time = 0.0;
    double total_revenue = 0.0;
    double total_profit = 0.0;
    int longest_route = deliveries[0].distance;
    int shortest_route = deliveries[0].distance;

    for (int i=0; i<delivery_count; i++) {
        total_distance += deliveries[i].distance;
        total_delivery_time += deliveries[i].delivery_time;
        total_revenue += deliveries[i].customer_charge;
        total_profit += deliveries[i].profit;
        if (deliveries[i].distance > longest_route)
            longest_route = deliveries[i].distance;
        if (deliveries[i].distance < shortest_route)
            shortest_route = deliveries[i].distance;
    }
    printf("===== Performance Report =====");
    printf("Total Deliveries Completed: %d\n", total_deliveries);
   printf("Total Distance Covered: %d km\n", total_distance);
    printf("Average Delivery Time: %.2f hours\n", total_delivery_time/total_deliveries);
    printf("Total Revenue: %.2f LKR\n", total_revenue);
    printf("Total Profit: %.2f LKR\n", total_profit);
    printf("Longest Route Completed: %d km\n", longest_route);
    printf("Shortest Route Completed: %d km\n", shortest_route);
    printf("===============================\n");
}
