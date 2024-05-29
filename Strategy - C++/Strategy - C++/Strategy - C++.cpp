#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum TimeOfDay { Breakfast, Lunch, Dinner };

enum Product { Bread, Mayonnaise, Dumplings, Cheese, Ham, Egg, Tomato };

class Fridge {
private:
    vector<Product> products;
public:
    void AddProduct(Product product) {
        products.push_back(product);
    }

    bool HasProduct(Product product) const {
        for (const auto& p : products) {
            if (p == product) {
                return true;
            }
        }
        return false;
    }
};

class CookingStrategy {
public:
    virtual void cook(const Fridge& fridge) const = 0;
    virtual ~CookingStrategy() = default;
};

class BreakfastStrategy : public CookingStrategy {
public:
    void cook(const Fridge& fridge) const override {
        if (fridge.HasProduct(Product::Bread) && fridge.HasProduct(Product::Cheese) && fridge.HasProduct(Product::Ham)) {
            cout << "Making a ham and cheese sandwich for breakfast.\n";
        }
        else if (fridge.HasProduct(Product::Egg)) {
            cout << "Making scrambled eggs for breakfast.\n";
        }
        else {
            cout << "No ingredients for breakfast.\n";
        }
    }
};

class LunchStrategy : public CookingStrategy {
public:
    void cook(const Fridge& fridge) const override {
        if (fridge.HasProduct(Product::Dumplings)) {
            cout << "Cooking dumplings for lunch.\n";
        }
        else if (fridge.HasProduct(Product::Tomato) && fridge.HasProduct(Product::Cheese)) {
            cout << "Making a tomato and cheese salad for lunch.\n";
        }
        else {
            cout << "No ingredients for lunch.\n";
        }
    }
};

class DinnerStrategy : public CookingStrategy {
public:
    void cook(const Fridge& fridge) const override {
        if (fridge.HasProduct(Product::Bread) && fridge.HasProduct(Product::Mayonnaise) && fridge.HasProduct(Product::Ham)) {
            cout << "Making a ham sandwich for dinner.\n";
        }
        else if (fridge.HasProduct(Product::Dumplings)) {
            cout << "Cooking dumplings for dinner.\n";
        }
        else {
            cout << "No ingredients for dinner.\n";
        }
    }
};

class CookingContext {
private:
    CookingStrategy* strategy = nullptr;
public:
    void setStrategy(CookingStrategy* strategy) {
        this->strategy = strategy;
    }

    void cook(const Fridge& fridge) const {
        if (strategy) {
            strategy->cook(fridge);
        }
        else {
            cout << "No cooking strategy set.\n";
        }
    }
};

int main() {
    Fridge fridge;
    fridge.AddProduct(Product::Bread);
    fridge.AddProduct(Product::Cheese);
    fridge.AddProduct(Product::Ham);

    CookingContext context;
    TimeOfDay timeOfDay = TimeOfDay::Breakfast;
   
   context.setStrategy(new BreakfastStrategy());   
   /*context.setStrategy(new LunchStrategy());      
   context.setStrategy(new DinnerStrategy());*/
   context.cook(fridge);
}
