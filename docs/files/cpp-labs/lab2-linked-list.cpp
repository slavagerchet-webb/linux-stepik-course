#include <iostream>
#include <string>

using namespace std;

struct Tovar
{
    string name {};
    int amount {};
    double price {};
    Tovar* next {};
};

void add_first(Tovar*& list, string name, int amount, double price)
{
    Tovar *temp = new Tovar;
    temp->name = name;
    temp->amount = amount;
    temp->price = price;
    temp->next = list;
    list = temp;
}

void add_last(Tovar*& list, string name, int amount, double price)
{
    Tovar* temp = new Tovar;
    temp->name = name;
    temp->amount = amount;
    temp->price = price;
    temp->next = nullptr;

    if (list == nullptr)
    {
        list = temp;
        return;
    }

    Tovar* p = list;
    while (p->next != nullptr)
    {
        p = p->next;
    }

    p->next = temp;
}

int add_after(Tovar*& list, string name, int amount, double price, string after) 
{
    Tovar* p = list; 

    while (p != nullptr && p->name != after)
    {
        p = p->next;
    }

    if (p == nullptr)
    {
        return 0;
    }

    Tovar* temp = new Tovar;
    temp->name = name;
    temp->amount = amount;
    temp->price = price;
    temp->next = p->next;
    p->next = temp;

    return 1;
}

int add_before(Tovar*& list, string name, int amount, double price, string before)
{
    if (list == nullptr)
    {
        return 0;
    }

    if (list->name == before)
    {
        add_first(list, name, amount, price);
        return 1;
    }

    Tovar* p = list;
    while (p->next != nullptr && p->next->name != before)
    {
        p = p->next;
    }

    if (p->next == nullptr)
    {
        return 0;
    }

    Tovar *temp = new Tovar;
    temp->name = name;
    temp->amount = amount;
    temp->price = price;
    temp->next = p->next;
    p->next = temp;

    return 1;
}

int delnode(Tovar*& list, string delname)
{
    if (list == nullptr)
    {
        return 0;
    }

    if (list->name == delname)
    {
        Tovar* temp = list;
        list = list->next;
        delete temp;
        return 1;
    }

    Tovar *p = list;
    while (p->next != nullptr && p->next->name != delname)
    {
        p = p->next;
    }

    if (p->next == nullptr)
    {
        return 0;
    }

    Tovar* temp = p->next;
    p->next = temp->next;
    delete temp;

    return 1;
}

void printlist(Tovar* list)
{
    if (list == nullptr)
    {
        cout << "Список пуст." << '\n';
        return;
    }

    while (list != nullptr)
    {
        cout << "Название: " << list->name
             << ", Количество: " << list->amount
             << ", Цена: " << list->price << '\n';

        list = list->next;
    }
}

void clearlist(Tovar *&list)
{
    while (list != nullptr)
    {
        Tovar *temp = list;
        list = list->next;
        delete temp;
    }
}

int main()
{
    Tovar* list{};

    add_first(list, "Tea", 720, 48.52);
    add_last(list, "Coffee", 800, 100.0);
    add_last(list, "Milk", 300, 60.0);

    cout << "После начального заполнения списка:" << '\n';
    printlist(list);

    if (add_after(list, "Sugar", 500, 30.0, "Tea"))
        cout << "Элемент добавлен после Tea." << '\n';
    else
        cout << "Элемент Tea не найден." << '\n';

    if (add_before(list, "Water", 1000, 10.0, "Coffee"))
        cout << "Элемент добавлен перед Coffee" << '\n';
    else
        cout << "Элемент Coffee не найден" << '\n';

    cout << '\n'
         << "После вставки элементов:" << '\n';
    printlist(list);

    if (delnode(list, "Milk"))
        cout << "Элемент Milk удален." << '\n';
    else
        cout << "Элемент Milk не найден." << '\n';

    cout << '\n'
         << "После удаления элемента:" << '\n';
    printlist(list);

    clearlist(list);
    return 0;
}
