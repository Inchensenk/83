#include <string>
#include <iostream>
using namespace std;
class MyClass
{
    int size;
public:
    int* data;

    MyClass(int size)
    {
        this->size = size;
        this->data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = i;
        }
        cout << "Вызволся конструктор " << this << endl;
    }

    MyClass(const MyClass& other)
    {
        this->size = other.size;
        this->data = new int[other.size];

        for (int i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }
    }
    // const MyClass& other это константная ссылка на объект класса
    //ссылка потому что нам не нужна копия объекта а толко нужно посмотреть что там лежит
    //константная она потому что мы там ничего менять не собираемся и для того чтобы себя обезопасить чтобы ничего случайнео не изменить пишем const
    //после перегрузки у обьекта класса появляется функция operator=
    //компилятор позволяет не писать: a.operator=(b) а позволяет просто написать вот так: a = b

    //MyClass& потому что нам не нужно создавать новый объект для того чтобы просто посмотреть его
    MyClass& operator = (const MyClass& other)
    {
        cout << "Вызволся оператора присваивания  = " << this << endl;
        //далее процесс похож на конструктор копирования
        //при копирывании изменяем поле size который отвечает за массив, так как поле size не выделено в динамической памяти, нам в нем ничего чистить не нужно, мы просто можем присвоить
        //присваиваем значение поля size из обьекта донора this->size в объект реципиент other.size
        this->size = other.size;

        //в обьекте в который мы хотим совершить копирование, мы дожны выполнить освобождение памяти
        //на которую указывает наш указатель data
        //для нас это безопасно, потому что конструктор создан таким образом что в любом случае при создании объекта уже выделяются данные под массив
        //по этому в этом случае никогда не будет ситуации что данных в data не было
        //если бы у нас был конструктор где массив бы не инициализировался в динамической памяти то нужно было бы data устанавливать в nullptr
        //и делать проверку на null: if(this->data!=nullptr){ delete[] this->data;}
        //то есть, если бы мы наш массив не инициализировали то мы могли бы выполнять очистку памяти только в том случае когда он не указывает на ноль
        delete[] this->data;
        
        //далее работаем с динамической памятью

        //выделяется новая область памяти согласно размеру и колличесву элементов в том объекте от которого мы копируемся то есть из other в нашем текущем указателе this->data
        this->data = new int[other.size];
        //поэлементно копируем из объекта other(из которого копируем) в объект this(текущий объект)
        for (int i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }
        //возвращаем разименованный указатель на объект
        return *this;
    }

    ~MyClass()
    {
        cout << "Вызволся деструктор " << this << endl;
        delete[]data;
    }
};
int main()
{
    setlocale(LC_ALL, "ru");
    MyClass a(10);
    MyClass b(2);

    //после перегрузки =,  теперь при данной записи a = b; создаются 2 объекта с одинаковыми данными и с разными адресами в памяти у каждого свой массив в динамической памяти
    //по этому когда начнут вызываться деструкторы у каждого объекта вызовиться деструктор именно для своей области памяти и на выходе не будет ошибки
    //казалось бы все хорошо но есть 1 момент при записи вида int q=1; int w; int e; e=w=q; e,q и w будут равны 1
    //если мы захотим сделать тоже самое с обьектами класса то будет ошибка, так как оператор = должен возвращать ссылку на текущий объект (MyClass&)
    a = b;
    //если мы хотим сразу при создании объекта b 
    //присвоить ему значение a , то в таком случае
    //так как обьект b еще не был инициализирован вообще ничем
    //и мы фактически еще должны его создать так как его еще нету
    //то здесь компилятор вызовет конструктор копирования
    //по сути если мы еще объект не создали и хотим присвоить ему значение
    //то запись MyClass b=a; эквивалентна записи  MyClass b(a);
    //как будто мы просто бы вызывали конструктор копирования
    
    /*MyClass b(a);

    //если не делать перегрузку оператора присваивания "=" 
    //то просто будет 2 переменные a и b ссылающиеся на одну и ту же область памяти 
    a = b;*/
}

