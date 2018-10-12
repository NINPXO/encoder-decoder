#include <cstdlib>
#include <string>

using namespace std;

class node
{
    unsigned char x;
    unsigned int frequency;
    unsigned char min;
    node * left;
    node * right;
public:
    node()
    {

    }

    node(const node &n)
    {
        x = n.x;
        frequency = n.frequency;
        left = n.left;
        right = n.right;
    }

    node(unsigned char d, unsigned int f): x(d), frequency(f), min(d)
    {

    }

    node(node *, node *);

    void cb(string *, string &);

    bool operator> (const node &);
};

class heap
{
    node **minheap;
    int n;
public:
    heap()
    {
        n = 0;
        minheap = new node*[257];
    }
    void push(node *);
    int size()
    {
        return n;
    }
    void pop();
    node * top()
    {
        return minheap[1];
    }
};

void node:: cb(string * codebook, string &code)
{
    if(!left && !right)
    {
        codebook[x] = code;
        return;
    }
    if(left)
    {
        code += '0';
        left->cb(codebook, code);
        code.erase(code.end()-1);
    }
    if(right)
    {
        code += '1';
        right->cb(codebook, code);
        code.erase(code.end()-1);
    }
}

node:: node(node * rc, node * lc)
{
    frequency = rc->frequency + lc->frequency;
    right = rc;
    left = lc;
    min = (rc->min < lc->min) ? rc->min : lc->min;
}

void heap:: push(node *newnode)
{
    int temp = ++n;
    while (temp != 1 && *minheap[temp / 2] > *newnode)
    {
        minheap[temp] = minheap[temp / 2];
        temp = temp / 2;
    }
    minheap[temp] = newnode;
}

void heap:: pop()
{
    node *p = minheap[n];
    minheap [n--] = minheap[1];
    int temp = 1;
    int child = 2;

    while (child <= n)
    {
        if (child < n && *minheap[child] > *minheap[child + 1])
            child++;

        if (*minheap[child] > *p)
            break;

        minheap[temp] = minheap[child];
        temp = child;
        child *= 2;
    }

    minheap[temp] = p;
}

bool node::operator> (const node &rhs)
{
    if(frequency > rhs.frequency)
        return true;
    if(frequency < rhs.frequency)
        return false;
    if(frequency == rhs.frequency)
        if(min > rhs.min)
            return true;
    return false;
}
