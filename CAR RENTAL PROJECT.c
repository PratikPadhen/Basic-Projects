#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Car {
    char car_type[20];
    char model[50];
    double rent;
};

struct Node {
    struct Car car;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct History {
    struct Car rentedCars[100];
    int numRentedCars;
};

struct User {
    char username[50];
};

void addCar(struct LinkedList* list, struct Car car) {
    struct Node* newCar = (struct Node*)malloc(sizeof(struct Node));
    newCar->car = car;
    newCar->next = list->head;
    list->head = newCar;
}

void displayCars(struct LinkedList* list) {
    struct Node* current = list->head;
    int count = 1;
    while (current) {
        printf("%d. %s (%s) - INR%.2f/day\n", count, current->car.model, current->car.car_type, current->car.rent);
        current = current->next;
        count++;
    }
}

struct Node* getCarByNumber(struct LinkedList* list, int choice) {
    struct Node* current = list->head;
    for (int i = 1; i < choice && current; ++i) {
        current = current->next;
    }
    return current;
}

void addRentedCar(struct History* history, struct Car car) {
    history->rentedCars[history->numRentedCars] = car;
    history->numRentedCars++;
}

void displayRentedCars(struct History* history) {
    printf("\nRented Cars History:\n");
    for (int i = 0; i < history->numRentedCars; ++i) {
        printf("%s (%s) - INR%.2f/day\n", history->rentedCars[i].model, history->rentedCars[i].car_type, history->rentedCars[i].rent);
    }
}

void displayMenu() {
    printf("\n+-----------------------------+\n");
    printf("|   Welcome to the Car Rental  |\n");
    printf("+-----------------------------+\n");
    printf("1. Popular Cars\n");
    printf("2. Cheap Cars\n");
    printf("3. Mid-Range Cars\n");
    printf("4. Luxury Cars\n");
    printf("5. Rent a Car\n");
    printf("6. View Rented Cars\n");
    printf("7. Exit\n");
    printf("+-----------------------------+\n");
    printf("Choose an option (1-7): ");
}

void showLoadingScreen() {
    printf("+-----------------------------+\n");
    printf("|         Processing...        |\n");
    printf("+-----------------------------+\n");
    printf("        Loading");
    for (int i = 0; i < 3; ++i) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

int main() {
    struct LinkedList popularCars;
    struct LinkedList cheapCars;
    struct LinkedList midCars;
    struct LinkedList luxuryCars;
    struct History rentedCarsHistory;
    struct User currentUser;

    // Initialize popular cars
    addCar(&popularCars, (struct Car){"Sedan", "Toyota Camry", 5000.0});
    addCar(&popularCars, (struct Car){"SUV", "Honda CRV", 6000.0});
    addCar(&popularCars, (struct Car){"Compact", "Ford Focus", 4000.0});
    addCar(&popularCars, (struct Car){"Luxury", "Mercedes Benz", 10000.0});
    addCar(&popularCars, (struct Car){"Convertible", "Chevrolet Camaro", 9000.0});

    // Initialize cheap cars
    addCar(&cheapCars, (struct Car){"Cheap", "Chevrolet Spark", 3000.0});
    addCar(&cheapCars, (struct Car){"Cheap", "Ford Fiesta", 3500.0});
    addCar(&cheapCars, (struct Car){"Cheap", "Nissan Versa", 3200.0});
    addCar(&cheapCars, (struct Car){"Cheap", "Toyota Yaris", 3300.0});
    addCar(&cheapCars, (struct Car){"Cheap", "Hyundai Accent", 3100.0});

    // Initialize mid-range cars
    addCar(&midCars, (struct Car){"Mid", "Honda Civic", 4500.0});
    addCar(&midCars, (struct Car){"Mid", "Toyota Corolla", 4200.0});
    addCar(&midCars, (struct Car){"Mid", "Mazda3", 4000.0});
    addCar(&midCars, (struct Car){"Mid", "Volkswagen Jetta", 4300.0});
    addCar(&midCars, (struct Car){"Mid", "Chevrolet Malibu", 4800.0});

    // Initialize luxury cars
    addCar(&luxuryCars, (struct Car){"Luxury", "BMW 5 Series", 12000.0});
    addCar(&luxuryCars, (struct Car){"Luxury", "Mercedes S-Class", 13000.0});
    addCar(&luxuryCars, (struct Car){"Luxury", "Audi A8", 12500.0});
    addCar(&luxuryCars, (struct Car){"Luxury", "Lexus LS", 11500.0});
    addCar(&luxuryCars, (struct Car){"Luxury", "Jaguar XJ", 11000.0});

    while (1) {
        displayMenu(); // Display main menu

        int option;
        scanf("%d", &option);

        if (option == 7) {
            printf("+-----------------------------+\n");
            printf("|     Exiting the program     |\n");
            printf("+-----------------------------+\n");
            displayRentedCars(&rentedCarsHistory); // Display rented cars history
            break;
        }

        switch (option) {
            case 1:
            case 2:
            case 3:
            case 4: {
                struct LinkedList* selectedCategory = NULL;

                switch (option) {
                    case 1:
                        selectedCategory = &popularCars;
                        break;
                    case 2:
                        selectedCategory = &cheapCars;
                        break;
                    case 3:
                        selectedCategory = &midCars;
                        break;
                    case 4:
                        selectedCategory = &luxuryCars;
                        break;
                }

                printf("+-----------------------------+\n");
                printf("|   Available cars in the     |\n");
                printf("|   selected category         |\n");
                printf("+-----------------------------+\n");
                displayCars(selectedCategory);

                // Let the user choose from the selected category
                int userChoice;
                printf("Enter the number of the car you want to rent (or 0 to go back to the menu): ");
                scanf("%d", &userChoice);

                if (userChoice == 0) {
                    continue; // Go back to the menu
                }

                struct Node* selectedCar = getCarByNumber(selectedCategory, userChoice);

                if (selectedCar) {
                    addRentedCar(&rentedCarsHistory, selectedCar->car); // Add rented car to history

                    // Ask for day, date, and rental duration
                    int rentalDays;
                    char rentalDate[20];
                    printf("Enter rental date (MM/DD/YYYY): ");
                    scanf("%s", rentalDate);
                    printf("Enter rental duration (in days): ");
                    scanf("%d", &rentalDays);

                    // Calculate total rent
                    double totalRent = rentalDays * selectedCar->car.rent;

                    // Confirm booking

                    // Display loading screen
                    showLoadingScreen();

                    // After successful payment
                  
                    // Proceed to payment
                    printf("Select payment method:\n");
                    printf("1. Credit Card\n");
                    printf("2. Debit Card\n");
                    printf("3. PayPal\n");
                    int paymentChoice;
                    scanf("%d", &paymentChoice);
                    printf("+-----------------------------+\n");
                    printf("|      Payment Successful!    |\n");
                    printf("+-----------------------------+\n");
                      printf("+-----------------------------+\n");
                    printf("|      Booking Confirmed!     |\n");
                    printf("+-----------------------------+\n");
                    printf("       _______\n");
                    printf("      |       |\n");
                    printf("      |       |\n");
                    printf("      |_______|\n");


                    char paymentMethod[20];
                    switch (paymentChoice) {
                        case 1:
                            strcpy(paymentMethod, "Credit Card");
                            break;
                        case 2:
                            strcpy(paymentMethod, "Debit Card");
                            break;
                        case 3:
                            strcpy(paymentMethod, "PayPal");
                            break;
                        default:
                            printf("Invalid payment choice. Exiting program.\n");
                            return 1;
                    }

                    // After successful payment
                    printf("+-----------------------------+\n");
                    printf("|  Thank you for using our    |\n");
                    printf("|          platform!          |\n");
                    printf("+-----------------------------+\n");
                    printf("You have rented a %s (%s) for %d days, starting from %s.\n", selectedCar->car.model, selectedCar->car.car_type, rentalDays, rentalDate);
                    printf("Total Rent:INR %.2f\n", totalRent);
                    printf("Booking Confirmation: #%d\n", rand() % 10000 + 1);
                    printf("Payment Method: %s\n", paymentMethod);
                    printf("Have a great day!\n");
                } else {
                    printf("Invalid choice. Please choose a valid car.\n");
                }
                break;
            }
            case 5: {
                // View and filter available cars based on rent range
                double minRent, maxRent;
                printf("Enter minimum rent: ");
                scanf("%lf", &minRent);
                printf("Enter maximum rent: ");
                scanf("%lf", &maxRent);

                printf("+-----------------------------+\n");
                printf("|   Available cars in the     |\n");
                printf("|   specified rent range      |\n");
                printf("+-----------------------------+\n");

                struct Car filteredCars[100];
                int numFilteredCars = 0;

                // Filter popular cars
                struct Node* current = popularCars.head;
                while (current) {
                    if (current->car.rent >= minRent && current->car.rent <= maxRent) {
                        filteredCars[numFilteredCars++] = current->car;
                    }
                    current = current->next;
                }

                // Display filtered cars
                for (int i = 0; i < numFilteredCars; ++i) {
                    printf("%s (%s) - INR%.2f/day\n", filteredCars[i].model, filteredCars[i].car_type, filteredCars[i].rent);
                }
                break;
            }
            case 6: {
                // View rented cars history
                displayRentedCars(&rentedCarsHistory);
                break;
            }
            default:
                printf("Invalid option. Please choose a valid option.\n");
                break;
        }
    }

    return 0;
}

