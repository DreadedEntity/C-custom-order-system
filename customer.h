#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

class Customer {
    public:
        Customer() {};
        Customer(std::string, std::string, std::string, std::string, std::string);
        std::string getFirstName();
        std::string getLastName();
        std::string getAddress();
        std::string getItemName();
        std::string getAmountOrdered();

    private:
        std::string firstName = "";
        std::string lastName = "";
        std::string address = "";
        std::string itemName = "";
        std::string amountOrdered = "";
};

Customer::Customer(std::string fn, std::string ln, std::string a, std::string in, std::string num) {
    firstName = fn;
    lastName = ln;
    address = a;
    itemName = in;
    amountOrdered = num;
};

std::string Customer::getFirstName() {
    return firstName;
};
std::string Customer::getLastName() {
    return lastName;
}
std::string Customer::getAddress() {
    return address;
}
std::string Customer::getItemName() {
    return itemName;
}
std::string Customer::getAmountOrdered() {
    return amountOrdered;
}
#endif // CUSTOMER_H_INCLUDED
