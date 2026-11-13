
#include<bits/stdc++.h>
using namespace std;
vector<string>keywords={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};

bool iskeyword(string word){
    return find(keywords.begin(),keywords.end(),word)!=keywords.end();
}

int main(){
    ifstream fp;
    string token,filename;
    char ch,next;
    cout<<"Enter the filename: ";
    cin>>filename;
    fp.open(filename);
    if(!fp){
        cout<<"File not found"<<endl;
        return 0;
    }
    while(fp.get(ch)){
        if(isspace(ch))
            continue;

        if(ch=='/'){
            if(fp.get(next)){
                if(next=='/'){
                    while(fp.get(ch) && ch!='\n');
                    continue;
                }
                else if(next=='*'){
                    char prev='\0';
                    while(fp.get(ch)){
                       if(prev=='*' && ch=='/')
                            break;
                        prev=ch;
                    }
                    continue;
                }
                else{
                    fp.unget();
                    cout<<"/ is an operator"<<endl;
                    continue;
                }
            }
        }

        if(ch=='"'||ch=='\''){
            char quote=ch;
            string str="";
            str+=quote;
            while(fp.get(ch)){
                str+=ch;
                if(ch==quote)
                    break;
            }
            if(quote=='"')
                cout<<str<<" is a string literal"<<endl;
            else
                cout<<str<<" is a character literal"<<endl;
            continue;
        }

        if(isalpha(ch)||ch=='_'){
            token="";
            token+=ch;
            while(fp.get(ch) && (isalnum(ch)||ch=='_')){
                token+=ch;
            }
            if(fp)
                fp.unget();
            if(iskeyword(token))
                cout<<token<<" is a keyword"<<endl;
            else
                cout<<token<<" is an identifier"<<endl;
        }

        else if(isdigit(ch)){
            token="";
            token+=ch;
            while(fp.get(ch) && isdigit(ch)){
                token+=ch;
            }
            if(fp)
                fp.unget();
            cout<<token<<" is a number"<<endl;
        }
        
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='='||ch=='<'||ch=='>'||ch=='!'||ch=='&'||ch=='|'||ch=='^'||ch=='~'){
            token="";
            token+=ch;
            if(fp.get(next) && (next=='=' || (ch==next && (ch=='+' || ch=='-' || ch=='&' || ch=='|' || ch=='<')))){
                token+=next;
            }
            else{
                if(fp)
                    fp.unget();
            }
            cout<<token<<" is an operator"<<endl;
        }

        else if(ch==';'||ch==','||ch=='.'||ch==':'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'){
            cout<<ch<<" is a symbol"<<endl;
        }

        else{
            cout<<ch<<" is an unknown character"<<endl;
        }
    }
    fp.close();
}
