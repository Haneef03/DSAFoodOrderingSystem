#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct UserAccount {
    string userName;
    string password;
};
//struct for fooditems
struct FoodItems
{
    int itemId;
    string itemName;
    double price;
};
struct OrderFoodItems {
    int itemId;
    string itemName;
    int itemQuantity;
    double itemPrice;
};

FoodItems foodItems[4];
int foodItemCount = 0;

class FoodOrderSystem {
private:
    queue<UserAccount> userAccountQueue;
    /*queue<FoodItems> foodItemQueue;*/
    queue<OrderFoodItems> foodOrderQueue;
public:
    // Array to store food items
     // Number of food items in the array
    void registerUser(string username, string password) {
        UserAccount newUser;
        newUser.userName = username;
        newUser.password = password;
        userAccountQueue.push(newUser);
        cout << "User is registered successfully" << endl;
    }
    
    bool checkUserLogin(string username, string password)
    {
        queue<UserAccount> tempQueue;  // Temporary queue to hold dequeued elements

        while (!userAccountQueue.empty()) {
            UserAccount user = userAccountQueue.front(); 
            userAccountQueue.pop();

            if (user.userName == username && user.password == password) //check if username and password match
            {
                cout << "Login is successful" << endl;

                // Enqueue the elements back from the temporary queue to the main queue
                while (!tempQueue.empty()) {
                    userAccountQueue.push(tempQueue.front());
                    tempQueue.pop();
                }

                return true;
            }
            else {
                tempQueue.push(user);
            }
        }

        // Enqueue the elements back from the temporary queue to the main queue
        while (!tempQueue.empty()) {
            userAccountQueue.push(tempQueue.front());
            tempQueue.pop();
        }

        cout << "Invalid username/password.Please try again" << endl;
        return false;
    }

    //Add food items
    void addFoodItems(int itemId, string itemName, double price) {
        if (foodItemCount < 4) { // Check if there's space in the array
            foodItems[foodItemCount].itemId = itemId;
            foodItems[foodItemCount].itemName = itemName;
            foodItems[foodItemCount].price = price;
            foodItemCount++;
        }
        else {
            cout << "Space filled. Cannot add further on." << endl;
        }
    }
    //to display the food items available 
    void displayFoodItems() {
        if (foodItemCount == 0) {
            cout << "No food items available." << endl;
        }
        else {
            cout << "Available food items:" << endl;
            for (int i = 0; i < foodItemCount; i++) {
                cout << foodItems[i].itemId << foodItems[i].itemName << " - $" << foodItems[i].price << endl;
                //foodItemCount++;
            }
        }
    }
    //create new order
    void CreateNewOrder(int itemId, string itemName, int itemQuantity, double itemPrice) {
        OrderFoodItems newOrderItems;
        newOrderItems.itemId = itemId;
        newOrderItems.itemName = itemName;
        newOrderItems.itemQuantity = itemQuantity;
        newOrderItems.itemPrice = itemPrice;
        foodOrderQueue.push(newOrderItems);
    }
    bool isFoodItemListFound(int foodMenuChoice) {
        int foodItemQuantity;
        for (int i = 0; i < foodItemCount; i++) {
            if (foodItems[i].itemId == foodMenuChoice) {
                std::cout << "Enter the quantity" << std::endl;
                std::cin >> foodItemQuantity;
                double quantityPrice = foodItems[i].price * foodItemQuantity;
                CreateNewOrder(foodItems[i].itemId,foodItems[i].itemName,
                                foodItemQuantity, quantityPrice);
                return true;
            }
        }
        return false;
    }
};
//display menu 
void displayMainMenu() {
    std::cout << "Welcome to NP Food Ordering System!" << std::endl;
    std::cout << "[1] Register" << std::endl;
    std::cout << "[2] Login" << std::endl;
    std::cout << "[3] Exit" << std::endl;
}
//Food menu options
void displayFoodOrderMenu() {
    std::cout << "[1] Create a new order" << std::endl;
    std::cout << "[2] Cancel Order" << std::endl;
    std::cout << "[3] Exit" << std::endl;
}
//Display food items
//void displayFoodItems() {
//    FoodOrderSystem foodListSystem;
//    foodListSystem.addFoodItems(1, "Chicken Rice", 19.90);
//    foodListSystem.addFoodItems(2, "Chicken Adobo", 29.90);
//    foodListSystem.addFoodItems(3, "Butter Chicken", 39.90);
//    foodListSystem.addFoodItems(4, "Chicken Parmi", 49.90);
//
//    //foodListSystem.displayFoodItems();
//}

int main() {
    int choice;
    string username;
    string password;
    int OrderMenuChoice;
    int foodMenuChoice;
    int foodItemQuantity;
    bool isLoginSuccessful=false;
    int userChoice;
    FoodOrderSystem foodOrderSystem;

    do {
        displayMainMenu();

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Register option selected." << std::endl;
            std::cout << "Please enter your username: " << std::endl;
            std::cin >> username;
            std::cout << "Please enter a password: " << std::endl;
            std::cin >> password;

            foodOrderSystem.registerUser(username, password);
            break;
        case 2:
            std::cout << "Login option selected." << std::endl;
            std::cout << "Please enter your username: " << std::endl;
            std::cin >> username;
            std::cout << "Please enter a password: " << std::endl;
            std::cin >> password;
            //store it to check later
            isLoginSuccessful = foodOrderSystem.checkUserLogin(username, password);
            
            if (isLoginSuccessful) {
                foodOrderSystem.addFoodItems(1, "Chicken Rice", 19.90);
                foodOrderSystem.addFoodItems(2, "Chicken Adobo", 29.90);
                foodOrderSystem.addFoodItems(3, "Butter Chicken", 39.90);
                foodOrderSystem.addFoodItems(4, "Chicken Parmi", 49.90);
                bool isFoodItemFound = false;
                std::cout << "Browse the Menu" << std::endl;
                displayFoodOrderMenu();
                std::cout << "Enter your choice: ";
                std::cin >> OrderMenuChoice;
                switch (OrderMenuChoice)
                {
                case 1:
                    do {
                        foodOrderSystem.displayFoodItems();
                        std::cout << "Enter the ID of the dish" << std::endl;
                        std::cin >> foodMenuChoice;

                        isFoodItemFound = foodOrderSystem.isFoodItemListFound(foodMenuChoice);
                        
                        if (isFoodItemFound == false) {
                            std::cout << "invalid food item ID" << std::endl;
                        }
                        std::cout << "Do you wish to continue ordering?" << std::endl;
                        std::cout << "[1]Yes or [2]No" << std::endl;
                        std::cin >> userChoice;
                    } while (userChoice == 1);
                    break;
                default:
                    std::cout << "Invalid choice. Please select a valid option." << std::endl;
                    break;
                }
            }
            else
            {
                break;
            }
            break;
        case 3:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
            break;
        }
    } while (choice != 3);


    return 0;
}