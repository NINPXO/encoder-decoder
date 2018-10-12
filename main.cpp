#include "huff.h"
#include <iostream>

void compress();
void encode();
void decompress();
node * constructHeap();
unsigned int frequency[256] = {0};
string codebook[256];

int main(int argc, char* argv[])
{
    if(argc == 4)
    {
        decompress();
    }
    else
        compress();
    return 0;
}

void compress()
{
    unsigned char x;
    cin >> noskipws;
    while(cin >> x)
        frequency[x]++;


    node * root = constructheap();
    string code;
    root->cb(codebook,code);

    encode();
}

void encode()
{
    unsigned int i;
    for(i = 0; i < 256; i++)
    {
        cout<<(char) (0x000000ff & frequency[i]);
        cout<<(char) ((0x0000ff00 & frequency[i]) >> 8);
        cout<<(char) ((0x00ff0000 & frequency[i]) >> 16);
        cout<<(char) ((0xff000000 & frequency[i]) >> 24);
    }

    unsigned char x;
    char y = 0;
    int z = 0;

    cin.clear();
    cin.seekg(0);
    cin >> noskipws;
    while(cin >> x){
        for(i = 0; i < codebook[x].size(); i++, z++){
            if(z == 8){
                cout<< y;
                y = 0;
                z = 0;
            }
            if(codebook[x][i] == '1')
                y = y | (0x01 << z);
        }
    }
    if(z)
        cout << y;
}

void decompress()
{
    cin >> noskipws;
    char x;
    for(int i = 0; i < 256; i++){
        cin.read((char *)&frequency[i],4);
    }

    node * root = constructheap();
    string code;
    root->cb(codebook,code);

    while(cin>>x)
    {
        for(int i = 0; i < 8; i++)
        {
            if((x >> i) & 0x01)
                code += '1';
            else
                code += '0';
            for(int i = 0; i < 256; i++)
            {
                if(codebook[i] == code)
                {
                    if(frequency[i])
                    {
                              cout << (unsigned char) i;
                              code.clear();
                              frequency[i]--;
                              break;
                    }
                    else
                        return;
                }
            }
        }
    }


}

node * constructheap()
{
    heap minheap;
    node *temp;
    for(int i = 0; i < 256; i++)
    {
        if (frequency[i])
        {
            temp = new node(i, frequency[i]);
            minheap.push(temp);
        }
    }

    node * x;
    node * y;
    node * z;
    while(minheap.size() > 1)
    {
        x = minheap.top();
        minheap.pop();
        y = minheap.top();
        minheap.pop();
        z = new node(x, y);
        minheap.push(z);
    }

    return minheap.top();
}
