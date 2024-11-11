#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Maximum number of customers in the deque
#define MAX_REQUESTS 5  // Maximum number of requests per customer

// Structure to represent a customer
typedef struct {
    int id;
    char name[50];
    char requests[MAX_REQUESTS][100]; // Array to store each customer's requests
    int requestCount;  // Number of requests the customer has
} Customer;

// Deque structure using a single array
typedef struct {
    Customer data[MAX];
    int front;
    int rear;
} Deque;

// Function to initialize the deque
void initDeque(Deque *deque) {
    deque->front = -1;
    deque->rear = -1;
}

// Check if the deque is empty
int isEmpty(Deque *deque) {
    return deque->front == -1;
}

// Check if the deque is full
int isFull(Deque *deque) {
    return deque->rear == MAX - 1;
}

// Add a customer to the front of the deque
void addFront(Deque *deque, Customer customer) {
    if (isFull(deque)) {
        printf("Deque is full! Cannot add customer.\n");
        return;
    }
    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    } else if (deque->front == 0) {
        if (deque->rear < MAX - 1) {
            for (int i = deque->rear; i >= deque->front; i--) {
                deque->data[i + 1] = deque->data[i];
            }
            deque->rear++;
        }
    } else {
        deque->front--;
    }
    deque->data[deque->front] = customer;
    printf("Customer added to the front of the line.\n");
}

// Add a customer to the rear of the deque
void addRear(Deque *deque, Customer customer) {
    if (isFull(deque)) {
        printf("Deque is full! Cannot add customer.\n");
        return;
    }
    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    } else {
        deque->rear++;
    }
    deque->data[deque->rear] = customer;
    printf("Customer added to the rear of the line.\n");
}

// Remove a customer from the front of the deque
void removeFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("The line is empty! No customer to remove.\n");
        return;
    }
    printf("Customer removed from the front of the line.\n");
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->front++;
    }
}

// Remove a customer from the rear of the deque
void removeRear(Deque *deque) {
    if (isEmpty(deque)) {
        printf("The line is empty! No customer to remove.\n");
        return;
    }
    printf("Customer removed from the rear of the line.\n");
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->rear--;
    }
}

// Process (display and remove) a customer from the front of the deque
void processFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("The line is empty! No customer to process.\n");
        return;
    }
    printf("Processing customer ID: %d, Name: %s\n", deque->data[deque->front].id, deque->data[deque->front].name);
    for (int i = 0; i < deque->data[deque->front].requestCount; i++) {
        printf("Request %d: %s\n", i + 1, deque->data[deque->front].requests[i]);
    }
    removeFront(deque);
}

// Process (display and remove) a customer from the rear of the deque
void processRear(Deque *deque) {
    if (isEmpty(deque)) {
        printf("The line is empty! No customer to process.\n");
        return;
    }
    printf("Processing customer ID: %d, Name: %s\n", deque->data[deque->rear].id, deque->data[deque->rear].name);
    for (int i = 0; i < deque->data[deque->rear].requestCount; i++) {
        printf("Request %d: %s\n", i + 1, deque->data[deque->rear].requests[i]);
    }
    removeRear(deque);
}

// Display all customers in the deque
void displayDeque(Deque *deque) {
    if (isEmpty(deque)) {
        printf("The line is empty!\n");
        return;
    }
    printf("Current customers in line:\n");
    for (int i = deque->front; i <= deque->rear; i++) {
        printf("Customer ID: %d, Name: %s\n", deque->data[i].id, deque->data[i].name);
        for (int j = 0; j < deque->data[i].requestCount; j++) {
            printf("  Request %d: %s\n", j + 1, deque->data[i].requests[j]);
        }
    }
}

// Function to take customer details as input
Customer inputCustomer() {
    Customer customer;
    printf("Enter customer ID: ");
    scanf("%d", &customer.id);
    printf("Enter customer name: ");
    scanf(" %[^\n]", customer.name);
    customer.requestCount = 0;
    
    // Input customer requests
    int reqCount;
    printf("Enter number of requests (up to %d): ", MAX_REQUESTS);
    scanf("%d", &reqCount);
    customer.requestCount = reqCount > MAX_REQUESTS ? MAX_REQUESTS : reqCount;
    
    for (int i = 0; i < customer.requestCount; i++) {
        printf("Enter request %d: ", i + 1);
        scanf(" %[^\n]", customer.requests[i]);
    }
    
    return customer;
}

// Function to display customer details by ID
void displayCustomerDetailsById(Deque *deque, int id) {
    if (isEmpty(deque)) {
        printf("The line is empty! No customer to search for.\n");
        return;
    }
    for (int i = deque->front; i <= deque->rear; i++) {
        if (deque->data[i].id == id) {
            printf("Customer found - ID: %d, Name: %s\n", deque->data[i].id, deque->data[i].name);
            for (int j = 0; j < deque->data[i].requestCount; j++) {
                printf("  Request %d: %s\n", j + 1, deque->data[i].requests[j]);
            }
            return;
        }
    }
    printf("Customer with ID %d not found.\n", id);
}

// Main function to test the deque operations
int main() {
    Deque deque;
    initDeque(&deque);

    int choice, id;
    Customer customer;

    while (1) {
        printf("\n--- Customer Service Desk ---\n");
        printf("1. Add customer to front\n");
        printf("2. Add customer to rear\n");
        printf("3. Remove customer from front\n");
        printf("4. Remove customer from rear\n");
        printf("5. Process customer from front\n");
        printf("6. Process customer from rear\n");
        printf("7. Display all customers\n");
        printf("8. Display customer by ID\n");
        printf("9. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customer = inputCustomer();
                addFront(&deque, customer);
                break;
            case 2:
                customer = inputCustomer();
                addRear(&deque, customer);
                break;
            case 3:
                removeFront(&deque);
                break;
            case 4:
                removeRear(&deque);
                break;
            case 5:
                processFront(&deque);
                break;
            case 6:
                processRear(&deque);
                break;
            case 7:
                displayDeque(&deque);
                break;
            case 8:
                printf("Enter customer ID to search: ");
                scanf("%d", &id);
                displayCustomerDetailsById(&deque, id);
                break;
            case 9:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}