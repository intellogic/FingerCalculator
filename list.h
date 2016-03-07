#ifndef LIST_H
#define LIST_H
#include <sstream>
using namespace std;
template <class T>
class Node{
public:
    T value;
    Node *next;
    Node *prev;
    Node(){
        next=0;
    }
    Node(T val):Node(){
        this->value=val;
    }
    ~Node(){
        if(next){
            delete next;
            next=0;
        }
    }
};

template <class T>
class List{
private:
    Node<T>* root;
    unsigned int size;
public:
    Node<T>* end;
    List():size(0){
        root=0;
        end=0;
    }
    List(const List<T> &copy):List(){
        Node<T>* copyNode = copy.root;
            while(copyNode!=0){
            this->add(copyNode->value);
            copyNode = copyNode->next;
        }
    }
    ~List(){
        clear();
    }
    bool insert(T val, unsigned int pos){
        if(size<pos)
            return false;
        Node<T>* node = new Node<T>(val);
        //вставка в начало
        if(pos==0){
            if(root!=0){
                node->next=root;
                }
            root = node;
            root->prev=0;
            if (root==0)
            {end=node;
            end->next=0;}
            size++;
            return true;
        }
        Node<T> * cur = root;
        for(int i=0; i<pos-1; i++){
            cur = cur->next;
        }
        //вставка в конец
        if (cur->next==0){
            cur->next = node;
            node->prev=cur;
            end=node;
            end->next=0;
            size++;
            return true;
        }
        //вставка в середину
        node->next=cur->next;
        cur->next =node;
        node->prev=cur;
        size++;
        return true;

    }
    T& get(unsigned int pos){
        if(pos>=size)
            throw exception();
        Node<T>*cur=root;
        for(int i=0; i<pos; i++){
            cur = cur->next;
        }
        return cur->value;
    }
    bool remove(unsigned pos){
        if(pos>=size)
            return false;
        if(pos==0){
            Node<T>* node = root->next;
            root->next = 0;
            delete root;
            root = node;
        }
        else{
            Node<T>* prev = root;
            for(int i=0; i<pos-1; i++){
                prev=prev->next;
            }
            Node<T>* cur = prev->next;
            prev->next = cur->next;
            cur->next = 0;
            delete cur;
        }
        size--;
        return true;
    }
    int ifExists(T value, int start=0){
        if(size==0)
           return -1;
        Node<T>* node = this->root;
        int i=0;
        while(node!=0){
            if(i>=start&& node->value == value){
                return i;
            }
            i++;
            node = node->next;
        }
        return -1;
    }

    void clear(){
        if(root!=0){
           delete root;
           root=0;
        }
    }
    T& operator[](unsigned int pos){
        return get(pos);
    }
    void add_first(T val){
        this->insert(val,0);
    }
    void add(T val){
        this->insert(val,size);
    }
    int getSize(){
        return size;
    }

    string toString(){
        ostringstream st;
        Node<T>* cur = this ->root;
        st << "[" ;
        while(cur){
            st<<cur->value;
            if(cur->next!=0)
                st <<", ";
            cur = cur->next;
        }
        st <<"]";
        return st.str();
    }
    void Sort(){
        int n=getSize();
        int a=0,b=1;
        int t=this->root->value;
        for (Node<T>*cur=this->root; cur!=0; cur=cur->next)

        for(int i = 0; i < n; i++){
             for (Node<T>*cur=this->root; cur->next!=0; cur=cur->next)
                if(cur->value>cur->next->value){
                    swap(cur->value,cur->next->value);
                    //cur->value=-2;
                }
        }
    }
    void div(List <int> &a1, List <int> &a2){
         for (Node<T>*cur=this->root; cur!=0; cur=cur->next){
         if (cur->value>0) a1.add(cur->value); else a2.add(cur->value);
         }
    }
    int ma (){
         int i=0;
         for (Node<T>*cur=this->root; cur!=0; cur=cur->next){
            if (cur->value>i) i=cur->value;
         }
    return i;
    }
    int mi (){
         int i=100;
         for (Node<T>*cur=this->root; cur!=0; cur=cur->next){
            if (cur->value<i) i=cur->value;
         }
    return i;
    }

    void sortList(){
        int mid=(this->mi()+this->ma())/2,c=0,s;
        s=this->getSize();
        Node<T> *cur=this->root;
        Node<T> *temp=new Node<T>();
        for (int i=0; i<s-c; i++){
            temp=cur->next;
            if (cur->value>=mid){
                if (i==s-1){
                    c++;
                    break;
                }
                if(cur->next)
                    cur->next->prev=cur->prev;
                if (cur->prev)
                    cur->prev->next=cur->next;
                else
                    root=cur->next;
                this->end->next=cur;
                cur->prev = this->end;
                cur->next=0;
                this->end=cur;
                c++;
                i--;
            }
            cur=temp;
        }
        insert(0,s-c);
    }
        int lonSeq(){
        int m=0,a=0,b=0;
        Node<T> * cur1, *cur2;
        cur1=root;
        cur2=end;
        for (int i=0; i<this->getSize(); i++){

            if(cur1->value%2==1)
                a++;
            else{
                if (a>m)
                    m=a;
                a=0;
            }
            if (cur2->value%2==1)
                b++;
            else{
                if (b>m)
                    m=b;
                b=0;
            }
            if (cur1==cur2){
                if (a+b-1>m)
                    m=a+b-1;
                return m;
            }
            cur1=cur1->next;
            cur2=cur2->prev;
        }
    }
};
#endif
