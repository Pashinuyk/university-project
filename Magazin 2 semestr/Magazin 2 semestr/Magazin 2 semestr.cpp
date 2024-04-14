#include <vector>
#include <iostream>
#include <locale.h>
#include <cmath>
#include <iterator>
#include "container.cpp"


class Good {
private:
    std::string name;
    int cost;
    int age;
    int count;
public:
    Good(std::string imy, int money, int amount, int years) {
        name = imy;
        cost = money;
        count = amount;
        age = years;
    }

    Good() {
        name = ' ';
        cost = 0;
        count = 0;
        age = 0;
    }


    std::string GetName() {
        return name;
    }
    int GetCost() {
        return cost;
    }
    int GetCount() {
        return count;
    }

    int GetAge() {
        return age;
    }

    virtual void CostUp() {
        cost = cost * 1;
    }

    void SetCount(int num) {
        count = num;
    }

    bool operator==(Good& other) {

        bool usl;

        if (this->name == other.name) return true;
        else return false;

    }

    bool operator!=(Good& other) {

        bool usl;

        if (this->name != other.name) return true;
        else return false;

    }

    Good operator+(Good& other) {

        this->name = this->name + " и " + other.name;
        this->cost = this->cost + other.cost;
        if (other.age < this->age) this->age = other.age;
        this->count = (this->count + other.count) / 2;

        return *this;
    }

    Good operator+=(Good& other) {

        this->name += " и " + other.name;
        this->cost += other.cost;
        if (other.age < this->age) this->age = other.age;
        this->count = (this->count + other.count) / 2;

        return *this;
    }

    bool operator>(Good& other) {

        return (this->count * this->cost > other.count * other.cost);

    }

    bool operator>=(Good& other) {

        return (this->count * this->cost >= other.count * other.cost);

    }

    bool operator<(Good& other) {

        return (this->count * this->cost < other.count * other.cost);

    }

    bool operator<=(Good& other) {

        return (this->count * this->cost <= other.count * other.cost);

    }

    friend std::ostream& operator<<(std::ostream& stream, const Good& counter)
    {
       // stream << "Value: ";
        stream << counter.name;
        return stream;
    }

};

class VegetablesAndFruits : public Good {
private:
    int age = 0;
    int cost;
    int count;
    std::string name;
public:
    VegetablesAndFruits(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
    }

    void CostUp() override {
        cost = cost * 1;
    }
};

class BreadProducts : public Good {
private:
    int age;
    int cost;
    int count;
    std::string name;
public:
    BreadProducts(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
        age = years;
    }

    void CostUp() override {
        cost = cost * 1;
    }
};

class SeaFood : public Good {
private:
    int age = 0;
    int cost;
    int count;
    std::string name;
public:
    SeaFood(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
    }

    void CostUp() override {
        cost = cost * 3;
    }

};

class Alcohol : public Good {
private:
    int age;
    int cost;
    int count;
    std::string name;
public:
    Alcohol(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
        age = 18;
    }

    void CostUp() override {
        cost = cost * 2;
    }


};

class Absent : public Good {
private:
    int age;
    int cost;
    int count;
    std::string name;
public:
    Absent(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
        age = 18;
    }

    void CostUp() override {
        cost = cost * 2;
    }


};

class TobaccoProducts : public Good {
private:
    int age = 18;
    int cost;
    int count;
    std::string name;
public:
    TobaccoProducts(std::string imy, int money, int amount, int years) : Good(imy, money, amount, years) {
        name = imy;
        cost = money;
        count = amount;
    }

    void CostUp() override {
        cost = cost * 2;
    }
};



class Magazine {
private:
    std::string name;
    std::string address;
    std::vector<Good*> tovar;
    //  Buyer buyer;
public:
    Magazine(std::string imy, std::string whereitis, std::vector<Good*> goods) {
        name = imy;
        address = whereitis;
        tovar = goods;
    }
    void ShowAssort() {
        if (tovar.size() > 0)
        {
            std::cout << "========= Ассортимент магазина " << name << " ===========" << std::endl;
            for (int i = 0; i <= tovar.size() - 1; i++) {
                if (tovar[i]->GetCount() != 0)
                {
                    std::cout << "ТОВАР №" << i + 1 << ": " << tovar[i]->GetName() << "\nКОЛ - ВО: " << tovar[i]->GetCount() << "\nЦЕНА : " << tovar[i]->GetCost() << std::endl;
                    std::cout << "" << std::endl;
                }
            }
        }
        else {
            std::cout << "Магазин " << name << " пуст" << std::endl;
            std::cout << "" << std::endl;
        }

    }

    std::vector<Good*> GetList() {
        return tovar;
    }

    friend class Buyer;

    Magazine operator+(Magazine& other) {
        int i, j;
        bool exists;
        std::vector<Good*> copy = this->tovar;

        for (i = 0; i < other.tovar.size(); i++) {
            exists = false;
            for (j = 0; j < copy.size(); j++) {
                //  std::cout << other.tovar[i]->GetName() << " " << this->tovar[j]->GetName() << std::endl;
                if (copy[j]->GetName() == other.tovar[i]->GetName()) {
                    this->tovar[j]->SetCount(this->tovar[j]->GetCount() + other.tovar[i]->GetCount());
                    exists = true;

                }
            }
            if (!exists) this->tovar.push_back(other.tovar[i]);
        }
        other.tovar.clear();
        return *this;
    }
};


class Buyer {
private:
    std::vector<Good*> wishlist;
    int money;
    int age;
public:
    Buyer(std::vector<Good*> wish, int dengi, int years) {
        wishlist = wish;
        money = dengi;
        age = years;
    }

    bool CheckForAge(Good* item) {
        if ((age >= 18) and (item->GetAge() >= 18) or (item->GetAge() < 18)) return true;
        else return false;
    }

    void Buy(Magazine& magaz) {
        bool exist;

        std::vector<Good*>& assort = magaz.tovar;

        for (int i = 0; i <= wishlist.size() - 1; i++) {
            exist = false;
            for (int j = 0; j <= assort.size() - 1; j++) {
                if (wishlist[i]->GetName() == assort[j]->GetName()) { //проверка есть ли в магазине товар с нужным именем
                    exist = true;
                    if (wishlist[i]->GetCount() > assort[j]->GetCount()) wishlist[i]->SetCount(assort[j]->GetCount()); //проверка на соответствие числа товаров желаемому

                    if (wishlist[i]->GetCount() > 0) {
                        int payment = wishlist[i]->GetCount() * assort[j]->GetCost();

                        if (money >= payment) {
                            if (!CheckForAge(wishlist[i])) {
                                std::cout << "Товар " << wishlist[i]->GetName() << " в магазине " << magaz.name << " по адресу " << magaz.address << " продается для лиц старше 18 лет" << std::endl;
                            }
                            else
                            {
                                money -= payment;
                                assort[j]->SetCount(assort[j]->GetCount() - wishlist[i]->GetCount());
                                std::cout << "Товар " << wishlist[i]->GetName() << " был куплен в кол-ве " << wishlist[i]->GetCount() << " шт. за " << payment << " руб., в магазине " << magaz.name << " по адресу " << magaz.address << std::endl;
                            }
                        }
                        else std::cout << "Недостаточно денег для покупки товара " << wishlist[i]->GetName() << " в кол-ве " << wishlist[i]->GetCount() << " шт. в магазине " << magaz.name << " по адресу " << magaz.address << ": у покупателя " << money << " руб., а пак стоит " << payment << " руб." << std::endl;
                    }
                }
            }
            if (!exist) std::cout << "Товар " << wishlist[i]->GetName() << " отсутствует в магазине " << magaz.name << " по адресу " << magaz.address << std::endl;
        }
        std::cout << " " << std::endl;
    }
};








int main()
{
    setlocale(LC_ALL, "Russian");

    Alcohol* beer = new Alcohol("Пиво", 250, 10, 18);
    Alcohol* vodyara = new Alcohol("Водка", 500, 5, 18);
    BreadProducts* bread = new BreadProducts("Хлеб", 100, 5, 0);
    TobaccoProducts* siga = new TobaccoProducts("Кубинские сигары", 5000, 10, 18);

    std::vector<Good*> tovar{ vodyara, beer, bread, siga };
    Magazine arka("Арка", "Надибаидзе", tovar);
   // arka.ShowAssort();

    /*VegetablesAndFruits* apple = new VegetablesAndFruits("Яблоко", 100, 4, 0);
    Alcohol* beer2 = new Alcohol("Пиво", 200, 3, 18);
    BreadProducts* suhki = new BreadProducts("Сушки", 80, 1, 0);
    std::vector<Good*> good{ apple,beer2,suhki };
    Magazine samberi("Самбери", "Окатовая", good);
    samberi.ShowAssort();*/

    Alcohol* beer2 = new Alcohol("Пиво", 200, 3, 18);
    BreadProducts* suhki = new BreadProducts("Сушки", 80, 1, 0);
    Alcohol digit1("Пиво", 200, 3, 18);
    Alcohol vodka("Водка", 500, 5, 18);
    TobaccoProducts digit2("Сига", 100, 1, 18);
    Alcohol digit3("Водка", 500, 5, 18);
    Good digit4("Вода", 50, 1, 0);
    BreadProducts digit5("Хлеб", 50, 3, 0);

    Array<Good, 4> kont1 = { digit1,digit2 };
    Array<Good, 4> kont2 = { digit3,digit4,digit5 };

    std::cout << kont1 << std::endl;
    std::cout << kont2 << std::endl;

    Array<Good,4>kont3(kont1);
    std::cout << kont3 << std::endl;

    std::cout << (kont1 <= kont2) << std::endl;

}