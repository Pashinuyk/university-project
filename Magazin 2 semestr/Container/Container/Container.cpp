#include <vector>
#include <iostream>
#include <locale.h>
#include <cmath>
#include <iterator>


struct Arrow {
    float data;
    Arrow* next;

    /*Arrow(Good data) {
        data = data;
        next = nullptr;
    }*/

    Arrow(float data) : data(data), next(nullptr) {}
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
        //    double number = std::sqrt(ptr->data.GetCount());                 //ВРЕМЕННЫЙ ТИП
        //    ptr->next->data.SetCount(ptr->next->data.GetCount() + number); //+= number;
            double number = std::sqrt(ptr->data);
            ptr->next->data = (ptr->next->data + number); //+= number;
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




class List {
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
            return count + 1;
        }
        else return count + 1;
    }

    bool Empty() {
        return this->begin() == this->end();
    }

    int Size() {
        return std::distance(this->begin(), this->end()) + 1;
    }

    int Max_Size(int a) {
        return max_size = a;
    }

    void AddHead(float digit) {
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

    bool Search(float digit) {
        Arrow* curr = head;

        while (curr->next != nullptr) {
            if (curr->data == digit) return true;
            curr = curr->next;
        }
        if (curr->data == digit) return true;
        else return false;
    }

    void Del(float digit) {
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

void ListSwap(List& thisone, List& other) {
    List t = thisone;
    List x;

    x = t;
    t = other;
    thisone = other;

}












template<class data,std::size_t N> 
class Array {
private:
    data mas[N];
    std::size_t max_size = 0;
public:
    Array() {}   //конструктор по умолчанию

    Array(std::initializer_list<data> l)
    {
        for (const data& val : l)
        {
            mas[max_size++] = val;
            if (max_size >= N) break;
        }
    }

    Array(data massive) {   //конструктор, 1-й  элемент
        mas[0] = massive;
        max_size = N;
    }

    ~Array() {};      //деструктор

    std::size_t MaxSize() {
        return max_size;
    }



    template<bool Const> struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::conditional_t<Const, const data, data>;
        using pointer = std::conditional_t<Const, const data*, data*>;
        using reference = std::conditional_t<Const, const data&, data&>;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        reference operator[](difference_type n) const { return *(m_ptr + n); }

        Iterator operator+(difference_type n) const { return Iterator(m_ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(m_ptr - n); }

        Iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

        difference_type operator-(const Iterator& other) const { return m_ptr - other.m_ptr; }

        bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }

    private:
        pointer m_ptr;
    };

    Iterator<false> begin() { return Iterator<false>(&mas[0]); }
    Iterator<false> end() { return Iterator<false>(&mas[max_size-1]); }

    std::size_t Size() {
      return std::distance(this->begin(), this->end())+1;
    }

    bool Empty() {
        return this->begin() == this->end();
    }



    data& operator[](std::size_t iter)
    {
        return mas[iter];
    }

    data& Front() {
        return *this->begin();
    }

    data& Back() {
        return *this->end();
    }

    data& At(std::size_t iter) {
        if ((iter > (this->max_size - 1)) or (iter < 0)) abort;
        else return mas[iter];
    }

    data* Data() {
        return &mas[0];
    }

    
    bool operator==(Array& other) {
        for (std::size_t i=0; i < this->MaxSize(); i++) {
            if (this->mas[i] != other.mas[i]) return 0;
        }
        return 1;
    }

    bool operator!=(Array& other) {
        if (this->mas == other.mas) return 0;
        else return 1;
    }

    bool operator>(Array& other) {
        data merge1 = 0;
        data merge2 = 0;
        for (std::size_t i = 0; i < this->Size(); i++) {
            merge1 += mas[i];
        }

        for (std::size_t i = 0; i < other.Size(); i++) {
            merge2 += mas[i];
        }
        if (merge1 > merge2) return true;
        else return false;
    }

    bool operator<(Array& other) {
        data merge1 = 0;
        data merge2 = 0;
        for (std::size_t i = 0; i < this->Size(); i++) {
            merge1 += mas[i];
        }

        for (std::size_t i = 0; i < other.Size(); i++) {
            merge2 += mas[i];
        }
        if (merge1 < merge2) return true;
        else return false;
    }

    bool operator>=(Array& other) {
        data merge1 = 0;
        data merge2 = 0;
        for (std::size_t i = 0; i < this->Size(); i++) {
            merge1 += mas[i];
        }

        for (std::size_t i = 0; i < other.Size(); i++) {
            merge2 += mas[i];
        }
        if (merge1 >= merge2) return true;
        else return false;
    }

    bool operator<=(Array& other) {
        data merge1 = 0;
        data merge2 = 0;
        for (std::size_t i = 0; i < this->Size(); i++) {
            merge1 += mas[i];
        }

        for (std::size_t i = 0; i < other.Size(); i++) {
            merge2 += mas[i];
        }
        if (merge1 <= merge2) return true;
        else return false;
    }

    friend std::ostream& operator<<(std::ostream& stream, Array& one)
    {
        for (std::size_t i = 0; i < one.Size(); i++) {
            if (i < one.Size()-1) stream << one.mas[i] << ", ";
            else stream << one.mas[i];
        }
        return stream;
    }

    void Swap(Array& other) {
        Array t = *this;
        Array x;

        x = t;
        t = other;
        other = x;
        *this = t;
        this->max_size = t.max_size;
    }

    Array& Fill(data thisone) {
        for (std::size_t i=0; i < N; i++) {
            mas[i] = thisone;
        }
        return *this;
    }


};

template<class data, std::size_t N>
void Swap(Array<data,N>& thisone, Array<data,N>& other) {
    Array<data,N> t = thisone;
    Array<data,N> x;

    x = t;
    t = other;
    thisone = other;
    other = x;
}








int main()
{
    setlocale(LC_ALL, "Russian");

    //Array<int, 3> a(5);
    //int aa = b[1];
    ////  std::cout << a.Size();
    ///*std::cout << "BEFORE: " << std::endl;
    //for (int i = 0; i < a.MaxSize(); i++) std::cout << a[i] << " ";
    //std::cout << "" << std::endl;
    //for (int i = 0; i < b.MaxSize(); i++) std::cout << b[i] << " ";
    //
    //Swap(a, b);

    //std::cout << "" << std::endl;;
    //std::cout << "AFTER: " << std::endl;
    //for (int i = 0; i < a.MaxSize(); i++) std::cout << a[i] << " ";
    //std::cout << "" << std::endl;
    //for (int i = 0; i < b.MaxSize(); i++) std::cout << b[i] << " ";*/



    //a.Fill(5);
    //Swap(a, b);

    //for (int i = 0; i < a.Back(); i++) std::cout << a[i] << " ";
    //std::cout << "" << std::endl;

    //std::cout << "" << std::endl;
    //for (int i = 0; i < b.Back(); i++) std::cout << b[i] << " ";
    //std::cout << "" << std::endl;
    //
    //std::cout << (a) << std::endl;




}