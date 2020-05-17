#pragma once

struct SYM
{
    char ch;
    int  prior;
};

template<typename T>
class TPQueue
{
    struct ITEM
    {
        T data;
        ITEM* next;
        ITEM* prev;
    };
public:
    TPQueue() :h(nullptr), t(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
private:
    TPQueue::ITEM* create(const T&);
    ITEM* h;
    ITEM* t;
};

template<typename T>
typename TPQueue<T>::ITEM* TPQueue<T>::create(const T& data)
{
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    return item;
}

template<typename T>
TPQueue<T>::~TPQueue()
{
    while (h)
        pop();
}

template<typename T>
void TPQueue<T>::push(const T& dat)
{
    if (h == nullptr)
    {
        h = create(dat);
        t = h;
    }
    else if (t->data.prior >= dat.prior)
    {
        if (t->data.ch == dat.ch)
            t->data = dat;
        else
        {
            t->next = create(dat);
            t->next->prev = t;
            t = t->next;
        }
    }
    else if (h == t)
    {
        t->prev = create(dat);
        h = t->prev;
        h->next = t;
    }
    else
    {
        ITEM* tmp = t;
        while (tmp != h && tmp->data.prior < dat.prior)
        {
            tmp = tmp->prev;
        }
        if (tmp->data.prior == dat.prior)
        {
            ITEM* cell = new ITEM;
            cell->next = tmp->next;
            cell->prev = tmp;
            cell->data = dat;
            tmp->next->prev = cell;
            tmp->next = cell;
        }
        if (tmp == h && tmp->data.prior < dat.prior)
        {
            h->prev = create(dat);
            h = h->prev;
            h->next = tmp;
        }
    }
}

template<typename T>
T TPQueue<T>::pop()
{
    if (h)
    {
        ITEM* temp = h->next;
        T data = h->data;
        delete h;
        h = temp;
        return data;
    }
    else
    {
        return SYM{ '\0', 0 };
    }
}

template<typename T>
void TPQueue<T>::print() const
{
    ITEM* temp = h;
    while (temp)
    {
        std::cout << temp->data.ch << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

