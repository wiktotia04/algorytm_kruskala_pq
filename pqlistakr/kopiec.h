#include <iostream>
#include <vector>
using namespace std;

struct slistEl
{
    int prio, u, v;
};

class PriorityQueue
{
private:
    vector<slistEl> data;

public:
    PriorityQueue();
    bool empty(void);
    slistEl front(void);
    void push(int u, int v, int prio);
    void pop(void);
    void swap(int index1, int index2);
    void buildHeap();
    void heapify(int i, int n);
};

PriorityQueue::PriorityQueue()
{
    buildHeap();
}

bool PriorityQueue::empty(void)
{
    return data.empty();
}

slistEl PriorityQueue::front(void)
{
    return data[0];
}

void PriorityQueue::push(int u, int v, int prio)
{
    slistEl p;
    p.prio = prio;
    p.v = v;
    p.u = u;

    data.push_back(p);
    int i = data.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (data[i].prio >= data[parent].prio)
            break;
        swap(i, parent);
        i = parent;
    }
}

void PriorityQueue::pop(void)
{
    if (!empty())
    {
        data[0] = data.back();
        data.pop_back();
        heapify(0, data.size());
    }
}

void PriorityQueue::swap(int index1, int index2)
{
    slistEl temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

void PriorityQueue::buildHeap()
{
    int n = data.size();
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(i, n);
}

void PriorityQueue::heapify(int i, int n)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l].prio < data[smallest].prio)
        smallest = l;

    if (r < n && data[r].prio < data[smallest].prio)
        smallest = r;

    if (smallest != i)
    {
        swap(i, smallest);
        heapify(smallest, n);
    }
}
