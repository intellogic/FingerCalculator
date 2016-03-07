#ifndef POLSKA
#define POLSKA
#include <QDebug>
int pr(char c){
    switch (c){
        case '(': return 0;
        case '+': return 1;
        case '-': return 1;
        case '/': return 2;
        case '*': return 2;
    }
    return -1;
}

struct elem {
    double count;
    char op;
    elem(double count, char c){
    if (pr(c)>=0)
        this->op=c;
    else {
        this->count = count;
        this->op='c';
    }
    }
};

vector <elem> ToPolska(string s){
    string curr;
    vector <elem> res;
    Stack <char> op;
    for (int i=0; i<s.size(); i++){
        if (isdigit(s[i])) curr+=s[i]; else
        {   if (curr.size()!=0) res.push_back(elem(atof(curr.data()),'c'));
            if (s[i]!=')'){
                if (s[i]!='('){
                    int p = pr(s[i]);
                    while (!op.empty() && p<=pr(op.get())){
                        res.push_back(elem(0,op.get()));
                        op.pop();
                    }
                }
                op.push(s[i]);
            } else
            {
                while (!op.empty() && op.get()!='('){
                    res.push_back(elem(0, op.get()));
                    op.pop();
                }
                op.pop();
            }
            curr="";
        }
        if (i==s.size()-1 && curr.size()>0) res.push_back(elem(atof(curr.data()),'c'));
    }
    while (!op.empty()){
            res.push_back(elem(0, op.get()));
            op.pop();
    }
    return res;
}
double Count (string s){
    vector <elem> pol = ToPolska(s);
       int i=-1;
       while (pol.size()>1){
                i++;
                char c = pol[i].op;
                if (c!='c'){
                    if (c=='+') pol[i]=elem(pol[i-2].count+pol[i-1].count, 'c');
                    if (c=='-') pol[i]=elem(pol[i-2].count-pol[i-1].count, 'c');
                    if (c=='*') pol[i]=elem(pol[i-2].count*pol[i-1].count, 'c');
                    if (c=='/') pol[i]=elem((double)pol[i-2].count/pol[i-1].count, 'c');

                pol.erase(pol.begin()+i-1);
                pol.erase(pol.begin()+i-2);
                i-=2;
                }
        }
       return pol[0].count;

}

#endif // POLSKA

