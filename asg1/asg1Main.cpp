/*Name: Haneef Shah
  Student ID: S10223481B*/
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
//struct for order
struct OrderFoodItems {
    int itemId;
    string itemName;
    int itemQuantity;
    double itemPrice;
};

FoodItems foodItems[4]; //food items array
int foodItemCount = 0;
double totalPrice = 0;

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
    /*User Account Queue: This queue maintains a list of registered users, 
    allowing them to log in. When a user registers, 
    their account details are enqueued into the userAccountQueue. 
    During login attempts, I check the credentials against this queue by 
    dequeuing temporarily to verify the login information while maintaining the order of user accounts.*/
    
    /*Food Order Queue: For order processing, I implemented a foodOrderQueue. Whenever a user places an order, it's enqueued as an OrderFoodItems instance. 
    This ensures that orders are processed in the order they were made, 
    making it fair and efficient for both the customers and the kitchen staff.*/

    /*User Registration and Login: During user registration, the registerUser function adds 
    the new user to the userAccountQueue. For user login, I use the checkUserLogin function. 
    It dequeues users from the queue to compare login credentials. 
    If there's a match, the user is logged in, maintaining the order of user accounts. */
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
    /*Displaying Food Items: the displayFoodItems function goes through the available 
    foodItems array and displays the menu items with their respective details.*/
    void displayFoodItems() {
        if (foodItemCount == 0) {
            cout << "No food items available." << endl;
        }
        else {
            cout << "Available food items:" << endl;
            for (int i = 0; i < foodItemCount; i++) {
                cout << foodItems[i].itemId << "-" << foodItems[i].itemName << " - $" << foodItems[i].price << endl;
                //foodItemCount++;
            }
        }
    }
    /*Creating a New Order: The CreateNewOrder function enqueues order details into the foodOrderQueue 
    when a user places an order. 
    This ensures orders are handled one by one as they're received.*/
    void CreateNewOrder(int itemId, string itemName, int itemQuantity, double itemPrice) {
        OrderFoodItems newOrderItems;
        newOrderItems.itemId = itemId;
        newOrderItems.itemName = itemName;
        newOrderItems.itemQuantity = itemQuantity;
        newOrderItems.itemPrice = itemPrice;
        foodOrderQueue.push(newOrderItems);
    }
    /*Finding Food Item for Ordering: The isFoodItemListFound function searches the foodItems array for the selected food item 
    based on the item's ID to check for availability. 
    If found, it calculates the total price considering the quantity 
    and enqueues the order details into the foodOrderQueue.*/
    bool isFoodItemListFound(int foodMenuChoice) {
        int foodItemQuantity;
        for (int i = 0; i < foodItemCount; i++) {
            if (foodItems[i].itemId == foodMenuChoice) {
                std::cout << "Enter the quantity" << std::endl;
                std::cin >> foodItemQuantity;
                double quantityPrice = foodItems[i].price * foodItemQuantity;
                totalPrice += quantityPrice;
                CreateNewOrder(foodItems[i].itemId,foodItems[i].itemName,
                                foodItemQuantity, quantityPrice);
                return true;
            }
        }
        return false;
    }
    /*Canceling an Order: To cancel orders, the cancelOrder function clears the foodOrderQueue. 
    If there are pending orders, they're dequeued and discarded, effectively cancelling them.*/
    void cancelOrder() {
        if (isFoodOrderExists()) 
        {
            while (!foodOrderQueue.empty()) {
                foodOrderQueue.pop();
            }
            //reset the total price
            totalPrice = 0;
            std::cout << "Your Order has been cancelled" << std::endl;
        }
        else {
            std::cout << "No Current Order to Cancel" << std::endl;
        }
        
    }
    /*Checking for Existing Orders: The isFoodOrderExists function checks if there are any 
    pending orders in the foodOrderQueue. If there are, 
    it returns true, indicating that orders are in process.*/
    bool isFoodOrderExists() {
        if (foodOrderQueue.empty())
            return false;
        else
            return true;

    }
};
//display menu 
void displayMainMenu() {
    std::cout << "Welcome to NP Food Ordering System!" << std::endl;
    std::cout << "[1] Register" << std::endl;
    std::cout << "[2] Login" << std::endl;
    std::cout << "[3] Exit" << std::endl;
}
//display Food menu options
void displayFoodOrderMenu() {
    std::cout << "[1] Create a new order" << std::endl;
    std::cout << "[2] Cancel Order" << std::endl;
    std::cout << "[3] Exit" << std::endl;
}

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
        displayMainMenu(); // to display main menu 

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) { //check what choice the user entered
        case 1:
            std::cout << "Register option selected." << std::endl;
            std::cout << "Please enter your username: " << std::endl;
            std::cin >> username;
            std::cout << "Please enter a password: " << std::endl;
            std::cin >> password;

            foodOrderSystem.registerUser(username, password); //call to register the users
            break;
        case 2:
            std::cout << "Login option selected." << std::endl;
            std::cout << "Please enter your username: " << std::endl;
            std::cin >> username;
            std::cout << "Please enter a password: " << std::endl;
            std::cin >> password;
            //store it to check later
            isLoginSuccessful = foodOrderSystem.checkUserLogin(username, password);
            //if login is successful
            if (isLoginSuccessful) {
                //add food items to the array
                foodOrderSystem.addFoodItems(1, "Chicken Rice", 19.90);
                foodOrderSystem.addFoodItems(2, "Chicken Adobo", 29.90);
                foodOrderSystem.addFoodItems(3, "Butter Chicken", 39.90);
                foodOrderSystem.addFoodItems(4, "Chicken Parmi", 49.90);
                bool isFoodItemFound = false;
                do {
                    std::cout << "Browse the Menu" << std::endl;
                    displayFoodOrderMenu();
                    std::cout << "Enter your choice: ";
                    std::cin >> OrderMenuChoice;
                    switch (OrderMenuChoice) //check order menu choice
                    {
                    case 1:
                        do {
                            if (foodOrderSystem.isFoodOrderExists()) { //if there's alrdy an order
                                std::cout << "Your Order Exists. Please wait to be served." << std::endl;
                                break;
                            }
                            foodOrderSystem.displayFoodItems();
                            std::cout << "Enter the ID of the dish" << std::endl;
                            std::cin >> foodMenuChoice;
                            //check if food item id exists, if it does add to the order queue
                            isFoodItemFound = foodOrderSystem.isFoodItemListFound(foodMenuChoice); 

                            if (isFoodItemFound == false) {
                                std::cout << "invalid food item ID" << std::endl;
                            }
                            std::cout << "Do you wish to continue ordering?" << std::endl;
                            std::cout << "[1]Yes or [2]No" << std::endl;
                            std::cin >> userChoice;
                        } while (userChoice == 1);
                        std::cout << "Thank You For Your Order" << std::endl;
                        std::cout << "Total Order Price: " << "$" << totalPrice << std::endl;
                        break;
                    case 2:
                        foodOrderSystem.cancelOrder();
                        break;
                    default:
                        std::cout << "Invalid choice. Please select a valid option." << std::endl;
                        break;
                    }
                } while (OrderMenuChoice != 3);
                
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