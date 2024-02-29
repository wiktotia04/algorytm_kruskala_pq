
#include <vector>
#include <algorithm>

const int MAXINT = -2147483647;



struct slistEl
{
    slistEl* next;
    int prio, u, v;
};


class PriorityQueue
{
private:
    slistEl* head;
    slistEl* tail;

public:
    PriorityQueue();
    ~PriorityQueue();
    bool empty(void);
    int front_u(void);
    int front_v(void);
    int frontprio(void);
    void push(int u, int v, int prio);
    void pop(void);
};


// tworzy pust¹ listê
PriorityQueue::PriorityQueue()
{
    head = tail = NULL;
}

//  usuwa listê z pamiêci
PriorityQueue::~PriorityQueue()
{
    while (head)
        pop();
}

// Sprawdza, czy kolejka jest pusta
bool PriorityQueue::empty(void)
{
    return !head;
}

// Zwraca pocz¹tek kolejki.
int PriorityQueue::front_u(void)
{
    if (head)
        return head->u;
    else
        return -MAXINT;
}
int PriorityQueue::front_v(void)
{
    if (head)
        return head->v;
    else
        return -MAXINT;
}


// Zwraca priorytet pierwszego elementu
int PriorityQueue::frontprio(void)
{
    if (!head)
        return -MAXINT;
    else
        return head->prio;
}

// Zapisuje do kolejki
void PriorityQueue::push(int u, int v, int prio)
{
    slistEl* p, * r;
    p = new slistEl;
    p->next = NULL;
    p->prio = prio;
    p->v = v;
    p->u = u;

    if (!head) {
        head = tail = p;
    }
    else if (head->prio > prio) {
        p->next = head;
        head = p;
    }
    else {
        r = head;
        while (r->next && r->next->prio <= prio) {
            r = r->next;
        }
        p->next = r->next;
        r->next = p;
        if (!p->next) {
            tail = p;
        }
    }
}

// Usuwa z kolejki
void PriorityQueue::pop(void)
{
    if (head)
    {
        slistEl* p = head;
        head = head->next;
        if (!head)
            tail = NULL;
        delete p;
    }
}