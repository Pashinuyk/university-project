#include <vector>
#include <iostream>
#include <locale.h>
#include <cmath>
#include <iterator>


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
    //std::vector<Good*> tovar;
    List tovar;
    //  Buyer buyer;
public:
    Magazine(std::string imy, std::string whereitis, List goods) {
        name = imy;
        address = whereitis;
        tovar = goods;
    }
    void ShowAssort() {
        if (tovar.Size() > 0)
        {
            std::cout << "========= Ассортимент магазина " << name << " ===========" << std::endl;
            for (int i = 0; i <= tovar.Size() - 1; i++) {
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

    List GetList() {
        return tovar;
    }

    friend class Buyer;

    Magazine operator+(Magazine& other) {
        int i, j;
        bool exists;
        List copy = this->tovar;

        for (i = 0; i < other.tovar.Size(); i++) {
            exists = false;
            for (j = 0; j < copy.Size(); j++) {
                //  std::cout << other.tovar[i]->GetName() << " " << this->tovar[j]->GetName() << std::endl;
                if (copy[j]->GetName() == other.tovar[i]->GetName()) {
                    this->tovar[j]->SetCount(this->tovar[j]->GetCount() + other.tovar[i]->GetCount());
                    exists = true;

                }
            }
            if (!exists) this->tovar.AddHead(other.tovar[i]);
        }
        other.tovar.Clean();
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

        List& assort = magaz.tovar;

        for (int i = 0; i <= wishlist.size() - 1; i++) {
            exist = false;
            for (int j = 0; j <= assort.Size() - 1; j++) {
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









struct Arrow {
    Good data;
    Arrow* next;

    /*Arrow(Good data) {
        data = data;
        next = nullptr;
    }*/

    Arrow(Good data) : data(data), next(nullptr) {}
};



struct Iterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Arrow;
    using pointer = Arrow*;
    using reference = Arrow&;

    Iterator(pointer iter) : ptr(iter) {
        iter++;
    }

    reference operator*() const { return *ptr; }
    pointer operator->() { return ptr; }
    Iterator& operator++()
    {
        Arrow* iter = ptr;
        if (ptr->next != nullptr)
        {
            double number = std::sqrt(ptr->data.GetCount());
            ptr->next->data.SetCount(ptr->next->data.GetCount() + number); //+= number;
        }

        ptr = ptr->next;
        return *this;
    }

    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
    friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

private:
    pointer ptr;
};



struct List {
private:
    Arrow* head;
    Arrow* tail;
    int max_size;
public:
    List(Arrow* digit, int size) : head(digit), max_size(size) {}
    List() : head(nullptr), max_size(1) {}

    List(List& List) {
        head = List.head;
        max_size = List.max_size;
    }

    /*List(Good tovar, Arrow* dalee, int size) {
        head->data = tovar;
        head->next = dalee;
        max_size = size;
    };

    List() {
        head->data = *new Good();
        head->next = nullptr;
        max_size = 1;
    };*/

    ~List()
    {
        while (head != nullptr)
        {
            Arrow* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Iterator begin() { 
        return Iterator(head);
    };
    Iterator end() { 
        return Iterator(tail); 
    };


    int ElCount() {
        int count = 0;
        if (head == nullptr) return 0;

        if (head->next != nullptr) {
            Arrow* curr = head;
            while (curr->next != nullptr) {
                count = count + 1;
                curr = curr->next;
            }
            return count+1;
        }
        else return count + 1;
    }

    bool Empty() {
        return this->begin() == this->end();
    }

    int Size() {
        return std::distance(this->begin(), this->end())+1;
    }

    int Max_Size(int a) {
        return max_size = a;
    }

    void AddHead(Good digit) {
        Arrow* y = new Arrow(digit);

        if (ElCount() < max_size) {

            if (head == nullptr) {
                head = y;
            }
            else {
                Arrow* curr = head;
                while (curr->next != nullptr) curr = curr->next;
                curr->next = y;

            }
            tail = y;


        }
        else std::cout << "Размер контейнера превышен" << std::endl;

    }

    void Vyvod() {
        Arrow* curr = head;

        if (curr != nullptr) {
            while (curr->next != nullptr) {
                std::cout << curr->data << ", ";
                curr = curr->next;
            }
            std::cout << curr->data << std::endl;
        }
    }

    bool Search(Good digit) {
        Arrow* curr = head;

        while (curr->next != nullptr) {
            if (curr->data == digit) return true;
            curr = curr->next;
        }
        if (curr->data == digit) return true;
        else return false;
    }

    void Del(Good digit) {
        Arrow* u = head;
        Arrow* x; Arrow* dx; Arrow* curr;
        x = u;
        if (x != nullptr) {
            if (x->next == nullptr) {
                if (x->data == digit) x = nullptr;
            }
            else {
                while ((x->data == digit) && (x->next != nullptr)) {    //УДАЛЯЕМ 1-Й ЭЛЕМЕНТ
                    dx = x;
                    dx = dx->next;
                    x = nullptr;
                    x = dx;
                    if ((x->next != nullptr) && (x->data == digit)) x = x->next;
                    head = x;
                }
                if (x->data == digit) {
                    x = nullptr;
                    head = x;
                }
                if (x != nullptr) {
                    dx = x;
                    curr = x;

                    while (curr->next != nullptr) {     //УДАЛЯЕМ СЕРЕДИННЫЕ
                        if (curr->data == digit) {
                            dx->next = curr->next;
                            curr = nullptr;
                            curr = dx->next;
                        }
                        else {
                            dx = curr;
                            if (curr->next != nullptr) curr = curr->next;
                        }

                    }
                    if (curr->data == digit) {             //УДАЛЕМ ПОСЛЕДНИЕ
                        dx->next = nullptr;
                        curr = nullptr;
                        tail = dx;
                    }
                }
            }
        }
        u = x;
        
    }

    /*void Swap(Good digit1, Good digit2) {
        List* t = this;
        List* x;

        if ((t->SearchSpis(digit1) == true) && (t->SearchSpis(digit2) == true)) {
            x = t;
            if (x != nullptr) {
                while (x->next != nullptr)
                {
                    if (x->data == digit1) x->data = digit2;
                    else if (x->data == digit2) x->data = digit1;
                    x = x->next;
                    std::cout << "ЗНАЕНИЕ: " << x->data.GetName() << std::endl;
                }
                if (x->next == nullptr) {
                    if (x->data == digit1) x->data = digit2;
                    else if (x->data == digit2) x->data = digit1;
                    std::cout << "ЗНАЕНИЕ: " << x->data.GetName() << std::endl;
                }
            }
        }
        else if ((t->SearchSpis(digit1) == false) && (t->SearchSpis(digit2) == true)) std::cout << "Элемент " << digit1 << " не найден в списке" << std::endl;
        else if ((t->SearchSpis(digit1) == true) && (t->SearchSpis(digit2) == false)) std::cout << "Элемент " << digit2 << " не найден в списке" << std::endl;
        else std::cout << "Оба элемента не найдены в списке" << std::endl;
    }*/

    void Swap(List& other) {
        List t = *this;
        List x;

        x = t;
        t = other;
        other = x;
        head = t.head;
        this->max_size = t.max_size;

    }

    void FullInfo() {
        if (this != nullptr) {
            std::cout << "All elements: ";
            this->Vyvod();

            std::cout << "Count: " << Size() << std::endl;

            std::cout << "Cont. max size: " << max_size << std::endl;
        }
        else std::cout << "This container doesn't exist" << std::endl;
    }

    void Clean() {

        /*if (this->head != nullptr) {
            Arrow* curr = this->head;
            while (curr->next != nullptr) {
                this->head = curr;
                this->head = this->head->next;
                this->head = nullptr;
            }
            curr = nullptr;
        }*/

        Arrow* curr = head;
        while (curr != nullptr) {
            Arrow* cont;
            cont = curr->next;
            delete curr;
            curr = cont;
        }
    }

    void Copy(List& a) {
        this->Clean();
        *this = a;
    }

    bool operator ==(List& other) {
        Arrow* curr = this->head;
        Arrow* curr2 = other.head;
        std::cout << "PUTIN: " << curr->data << std::endl;
        std::cout << "PUTIN2: " << curr2->data << std::endl;
        if (this->Size() != other.Size()) return false;
        while ((curr != nullptr) or (curr2 != nullptr)) {
            if (curr->data != curr2->data) return false;
            curr = curr->next;
            curr2 = curr2->next;
        }
        return true;
    }

    void operator=(List& other) {
        while (head != nullptr)
        {
            Arrow* temp = head;
            head = head->next;
            delete temp;
        }

        Arrow* current = other.head;
        while (current != nullptr)
        {
            AddHead(current->data);
            current = current->next;
        }
    }


};



void Swap(List& thisone, List& other) {
    List t = thisone;
    List x;

    x = t;
    t = other;
    /*other = x;
    thisone.head = t.head;
    thisone.max_size = t.max_size;*/
    thisone = other;

}










int main()
{
    setlocale(LC_ALL, "Russian");


    //Alcohol vodka = new Alcohol("Водка", 500, 5, 18);
    Alcohol* beer = new Alcohol("Пиво", 250, 10, 18);
    Alcohol* vodyara = new Alcohol("Водка", 500, 5, 18);
    BreadProducts* bread = new BreadProducts("Хлеб", 100, 5, 0);
    TobaccoProducts* siga = new TobaccoProducts("Кубинские сигары", 5000, 10, 18);

  //  List();


    std::vector<Good*> tovar{ vodyara, beer, bread, siga };
    Magazine arka("Арка", "Надибаидзе", tovar);
    arka.ShowAssort();



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

   // List kont1;
   // kont1.max_size = 10;
   // List kont2;
   // kont2.max_size = 5;

   //// kont1->Vyvod();
   // kont1.AddHead(digit1);
   // kont1.AddHead(digit2);
   // kont1.AddHead(digit3);
   // kont1.AddHead(digit4);
   // kont1.AddHead(digit5);

   // kont2.AddHead(digit2);
   // kont2.AddHead(digit5);

  //  kont1.FullInfo();
    std::cout << "" << std::endl;
  //  kont2.FullInfo();
    std::cout << "" << std::endl;
  //  std::cout << "Число элементов в списке: " << kont1.SpisElCount() << std::endl;
  //  std::cout << "Наличие элемента: " << kont1.SearchSpis(digit1) << std::endl;

  //  Swap(kont1, kont2);

  //  kont1.FullInfo();
    //std::cout << "" << std::endl;
    //kont1.FullInfo();
    //kont2.FullInfo();

    //std::cout << "-------------------------------------" << std::endl;
    //kont1 = kont2;
    //kont1.FullInfo();
    //std::cout << " " << std::endl;
    //kont2.FullInfo();

    List kont1;
    List kont2;
    kont1.Max_Size(5);
    kont2.Max_Size(7);
    kont1.AddHead(digit1);
    kont1.AddHead(digit2);
    kont2.AddHead(vodka);
    kont2.AddHead(digit4);

    kont1.FullInfo();
    kont2.FullInfo();
   // kont1 = kont2;
    if (kont1 == kont2) std::cout << "YEAH" << std::endl;
    else std::cout << "NOPE" << std::endl;
    std::cout << "--------------" << std::endl;
    kont1 = kont2;
    kont1.FullInfo();
    kont2.FullInfo();
    if (kont1 == kont2) std::cout << "YEAH" << std::endl;
    else std::cout << "NOPE" << std::endl;


  //  std::cout << kont2.head->data << std::endl;







}