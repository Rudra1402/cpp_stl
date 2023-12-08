#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Shop
{
private:
    vector<pair<string, pair<int, int>>> items;

public:
    void initiateShop()
    {
        items.push_back(make_pair("Shoes", make_pair(10, 5)));
        items.push_back(make_pair("T-Shirt", make_pair(15, 3)));
        items.push_back(make_pair("Television", make_pair(25, 2)));
        items.push_back(make_pair("X-Box", make_pair(20, 4)));
        items.push_back(make_pair("iPhone XR", make_pair(18, 5)));
    }

    vector<pair<string, pair<int, int>>> getItems()
    {
        return items;
    }

    void populateShop()
    {
        for (auto &it : items)
        {
            int index = &it - &items[0] + 1;
            cout << "<" << index << ">" << endl;
            cout << "Item: " << it.first << endl;
            cout << "Price: " << it.second.first << endl;
            cout << "Quantity: " << it.second.second << endl;
            cout << endl;
        }
    }

    int updateQuantity(string item, int reqQty)
    {
        auto it = find_if(items.begin(), items.end(), [item](const pair<string, pair<int, int>> &element)
                          { return element.first == item; });

        if (it != items.end() && it->second.second >= reqQty)
        {
            it->second.second -= reqQty;
            return it->second.second;
        }
        else
        {
            cout << "Enough stock is not available!" << endl;
            return -1;
        }
    }
};

class User
{
private:
    string firstName, lastName;
    unordered_map<string, pair<int, int>> cart;
    Shop &shop;

public:
    User(Shop &s) : shop(s) {}

    string getFirstName()
    {
        return firstName;
    }

    string getLastName()
    {
        return lastName;
    }

    void setName(string fn, string ln)
    {
        firstName = fn;
        lastName = ln;
    }

    bool checkItem(string item)
    {
        if (cart.find(item) != cart.end())
            return true;
        else
            return false;
    }

    void initializeItem(string item, int price, int qty)
    {
        cart[item] = make_pair(price, qty);
    }

    void addToCart(string item, int qty)
    {
        auto it = find_if(shop.getItems().begin(), shop.getItems().end(), [item](const pair<string, pair<int, int>> &element)
                          { return element.first == item; });

        if (it != shop.getItems().end())
        {
            int price = it->second.first;
            int availableQty = shop.updateQuantity(item, qty);

            if (availableQty != -1)
            {
                if (cart.find(item) != cart.end())
                {
                    cart[item].second += qty;
                }
                else
                {
                    cart[item] = make_pair(price, qty);
                }

                cout << "Item added to cart successfully!" << endl;
            }
        }
        else
        {
            cout << "Item not found in the shop!" << endl;
        }
    }

    void viewCart()
    {
        if (!cart.empty())
        {
            int totalPrice = 0;
            for (auto &it : cart)
            {
                totalPrice += (it.second.first * it.second.second);
                cout << endl;
                cout << "Item: " << it.first << endl;
                cout << "Price: " << it.second.first << endl;
                cout << "Quantity: " << it.second.second << endl;
            }
            cout << endl
                 << "Total Amount: " << totalPrice << endl;
        }
        else
        {
            cout << "Your cart is empty!" << endl;
        }
    }
};

bool checkUser(vector<User> &users, string &fn, string &ln)
{
    if (!users.empty())
    {
        for (auto &user : users)
        {
            if (user.getFirstName() == fn && user.getLastName() == ln)
            {
                return true;
            }
        }
        return false;
    }
    else
        return false;
}

int findUserIndex(vector<User> &users, string &fn, string &ln)
{
    int index;
    for (auto &user : users)
    {
        if (user.getFirstName() == fn && user.getLastName() == ln)
        {
            index = &user - &users[0];
            break;
        }
    }
    return index;
}

void addUser(string &fn, string &ln, vector<User> &users, Shop &s)
{
    bool doesUserExists = checkUser(users, fn, ln);
    if (doesUserExists)
        cout << "User already exists!" << endl;
    else
    {
        User u(s);
        u.setName(fn, ln);
        users.push_back(u);
        cout << "User added successfully!" << endl;
    }
}

int main()
{
    Shop s;
    vector<User> users;
    s.initiateShop();
    bool flag = true;
    while (flag)
    {
        string firstName, lastName;
        cout << "--------------------" << endl;
        cout << "----Rudra's Shop----" << endl;
        cout << "--------------------" << endl;
        cout << endl;
        cout << "1. View Shop Items" << endl
             << "2. Create Account" << endl
             << "3. View Cart" << endl
             << "4. Add to Cart" << endl
             << "5. Exit" << endl
             << "Enter choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            s.populateShop();
            break;
        case 2:
            cout << endl;
            cout << "First Name: ";
            cin >> firstName;
            cout << "Last Name: ";
            cin >> lastName;
            addUser(firstName, lastName, users, s);
            cout << endl;
            break;
        case 3:
            cout << endl;
            cout << "First Name: ";
            cin >> firstName;
            cout << "Last Name: ";
            cin >> lastName;
            if (checkUser(users, firstName, lastName))
            {
                int userIndex = findUserIndex(users, firstName, lastName);
                users[userIndex].viewCart();
            }
            else
                cout << "User doesn't exists!" << endl;
            cout << endl;
            break;
        case 4:
            cout << endl;
            cout << "First Name: ";
            cin >> firstName;
            cout << "Last Name: ";
            cin >> lastName;
            if (checkUser(users, firstName, lastName))
            {
                int userIndex = findUserIndex(users, firstName, lastName);
                int qty, item;
                char purchase;
                cout << "Do you want to purchase items? (y/n): ";
                cin >> purchase;
                while (purchase == 'y')
                {
                    vector<pair<string, pair<int, int>>> items = s.getItems();
                    cout << "Enter item number: ";
                    cin >> item;
                    cout << "Enter quantity: ";
                    cin >> qty;
                    users[userIndex].addToCart(items[item - 1].first, qty);
                    cout << "Do you want to purchase items? (y/n): ";
                    cin >> purchase;
                }
            }
            else
                cout << "User doesn't exists!" << endl;
            cout << endl;
            break;
        case 5:
            flag = false;
            break;
        default:
            flag = false;
            break;
        }
    }
    cout << endl
         << "SEE YOU SOON! Bye!" << endl;
    return 0;
}