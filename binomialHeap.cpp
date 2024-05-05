#include <iostream>
#include<bits/stdc++.h>
#define n1 93
using namespace std;


struct node
{
    vector<int> data;
    int degree;
    string s;
    int freq;
    node * child;
    node * parent;
    node * sibling;
};

node * newnode(int key1,int key2,string str,int fre=2)
{
    node * temp=new node;
    temp->data.push_back(key1);
    temp->data.push_back(key2);
    temp->s=str;
    temp->degree=0;
    temp->freq=fre;
    temp->parent=temp->sibling=temp->child=NULL;
    return temp;
}

node * merge(node * a,node * b)
{
    if(a->data[0]>b->data[0])
    swap(a,b);
    b->parent=a;
    b->sibling=a->child;;
    a->child=b;
    a->degree++;
    return a;
}

list<node *> _union(list<node *>l1,list<node *>l2)
{
    list<node *> _new;
    list<node *>:: iterator it1=l1.begin();
    list<node *>:: iterator it2=l2.begin();
    while( it1!=l1.end() && it2!=l2.end())
    {
        if((*it1)->degree<=(*it2)->degree)
        {
            _new.push_back(*it1);
            it1++;
        }
        else
        {
            _new.push_back(*it2);
            it2++;
        }
    }
    while(it1!=l1.end())
    {
         _new.push_back(*it1);
            it1++;
    }
    while(it2!=l2.end())
    {
         _new.push_back(*it2);
            it2++;
    }
    return _new;
}

list<node *> binomial_heap_rearrange(list<node *> _heap)
{
    if(_heap.size()<=1)
    return _heap;
    list<node*>::iterator it1,it2,it3;
    it1=it2=it3=_heap.begin();
    if(_heap.size()==2)
    {
        it2++;
        it3=_heap.end();
    }
    else
    {
        it2++;
        it3=it2;
        it3++;
    }
    while(it1!=_heap.end())
    {
        if(it2==_heap.end())
        it1++;
        else if((*it1)->degree<(*it2)->degree)
        {
            it1++;
            it2++;
            if(it3!=_heap.end())
            it3++;
        }
        else if(it3!=_heap.end() && (*it1)->degree==(*it2)->degree && (*it3)->degree==(*it2)->degree)
        {
            it1++;
            it2++;
            it3++;
        }
        else if((*it1)->degree==(*it2)->degree)
        {
            *it1=merge(*it1,*it2);
            it2=_heap.erase(it2);
            if(it3!=_heap.end())
            it3++;
        }
    
    }
    return _heap;
}

list<node*> insert_tree_into_heap(list<node*> _heap,node * tree)
{
    list<node*> l;
    l.push_back(tree);
    l=_union(_heap,l);
    return binomial_heap_rearrange(l);
}

list<node *> remove_min_from_tree_return_heap(node* tree)
{
    list<node*>heap;
    node * temp=tree->child;
    node * lo;
    while(temp)
    {
        lo=temp;
        temp=temp->sibling;
        lo->sibling=NULL;
        heap.push_front(lo);
    }
    return heap;
}

list<node *> insert(list<node*>_heap,int key1,int key2,string str)
{
    node * temp=newnode(key1,key2,str);
    return insert_tree_into_heap(_heap,temp);
}

node * get_min(list<node*> _heap)
{
    list<node*>::iterator it;
    it=_heap.begin();
    node * temp=*it;
    temp->degree=0;
    while(it!=_heap.end())
    {
        if((temp)->data[0]>(*it)->data[0])
        {temp=*it;}
        it++;
    }
    return temp;
}

list<node *> extract_min(list<node*> _heap)
{
    list<node*> _new,lo;
    node * temp=get_min(_heap);
    list<node*>::iterator it;
    it=_heap.begin();
    while(it!=_heap.end())
    {
        if(*it!=temp)
        {_new.push_back(*it);}
        it++;
    }
    lo=remove_min_from_tree_return_heap(temp);
    _new=_union(_new,lo);
    _new=binomial_heap_rearrange(_new);
    return _new;
}

void print_tree(node * h)
{
    while(h)
    {
        cout<<h->data[0]<<" "<<h->data[1]<<" "<<h->s<<endl;
        print_tree(h->child);
        h=h->sibling;
    }
}

void print_heap(list<node *> _heap)
{
    list<node *>::iterator it;
    it=_heap.begin();
    while(it!=_heap.end())
    {
        print_tree(*it);
        it++;
    }
}


int main() 
{
    int key;
    list<node *> _heap;
    list<node *> _heap2;
    list<node *> _heap3;
    int h=0;
    while(h<n1)
    {
       string str;
       int a;
       int b;
       cin>>str;
       cin>>a;
       cin>>b;
       _heap=insert(_heap,a,b,str);
       h++;
    }
    
    cout<<endl;
    print_heap(_heap);

    node * newnod;
    node * head1;
    node * head2;
    while(_heap.size()!=0)
    {
    head1=get_min(_heap);
    _heap=extract_min(_heap);
    if(_heap.size()==0)break;
    head2=get_min(_heap);
    _heap=extract_min(_heap);
    int curr_loc1=head1->data[0];
    int curr_loc2=head2->data[0];
    head1->degree=0;
    head1->parent=head1->child=head1->sibling=NULL;
    head2->degree=0;
    head2->parent=head2->child=head2->sibling=NULL;
    if((curr_loc1+1)==curr_loc2)
    {  
        newnod=newnode(0,0,head1->s+" "+head2->s,0);
        newnod->data.pop_back();
        newnod->data.pop_back();
        newnod->degree=0;
    }
    
    while(curr_loc1<curr_loc2)
    {
    if(curr_loc2==curr_loc1+1)
    {
        head1->freq--;
        head2->freq--;
        newnod->freq++;
        newnod->data.push_back(curr_loc2);
        curr_loc1=head1->data[1];
        curr_loc2=head2->data[1];
        if(head1->freq==0 && head2->freq==0)
        {
            curr_loc1=0;
            curr_loc2=0;
        }
    }
    else 
    {
      break;
    }
    }
    if(head1->freq==1 && head2->freq==1 )
    {
        free(newnod);
        head2->freq=2;
        _heap=insert_tree_into_heap(_heap,head2);
    }
    else if(head1->freq==2 && head2->freq==2)
    {
        head2->freq=2;
        _heap=insert_tree_into_heap(_heap,head2);
    }
    else if(head1->freq==0 && head2->freq==0)
    {
        _heap2=insert_tree_into_heap(_heap2,newnod);
        
    }
    }
    cout<<endl<<"Strings of length 2"<<endl;
    print_heap(_heap2);
    
    
   while(_heap2.size()!=0)
    {
    head1=get_min(_heap2);
    _heap2=extract_min(_heap2);
    if(_heap2.size()==0)break;
    head2=get_min(_heap2);
    _heap2=extract_min(_heap2);
    int curr_loc1=head1->data[0];
    int curr_loc2=head2->data[0];
    head1->degree=0;
    head1->parent=head1->child=head1->sibling=NULL;
    head2->degree=0;
    head2->parent=head2->child=head2->sibling=NULL;
    if((curr_loc1+2)==curr_loc2)
    {
        newnod=newnode(0,0,head1->s+" "+head2->s,0);
        newnod->data.pop_back();
        newnod->data.pop_back();
    }
    
    while(curr_loc1<curr_loc2)
    {
    if(curr_loc2==curr_loc1+2)
    {
        int n=head1->freq;
        int m=head2->freq;
        head1->freq--;
        head2->freq--;
        newnod->freq++;
        newnod->data.push_back(curr_loc2);
        curr_loc1=head1->data[1];
        curr_loc2=head2->data[1];
        if(head1->freq==0 && head2->freq==0)
        {
            curr_loc1=0;
            curr_loc2=0;
        }
    }
    else 
    {
        break;
    }
    }
    
    if(head1->freq!=0 && head2->freq!=0  && head1->freq==head2->freq)
    {
        
        head2->freq=2;
        _heap2=insert_tree_into_heap(_heap2,head2);
    }
    else if(head1->freq==0 && head2->freq==0)
    {
        _heap3=insert_tree_into_heap(_heap3,newnod);
    }
    }
    cout<<endl<<"Strings of length 4"<<endl;
    print_heap(_heap3);

    return 0;
}
