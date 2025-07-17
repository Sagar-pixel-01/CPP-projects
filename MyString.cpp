#include <bits/stdc++.h>

using namespace std;
class MyString{
    private:
        char* data;
    public:
        MyString(const char* s){
            data = new char [strlen(s)+1];
            strcpy(data,s);
        }
        ~MyString(){delete[] data;}
        MyString(const MyString& other){
         
                data = new char[strlen(other.data)+1];
                strcpy(data,other.data);
            
        }
        MyString( MyString&& other){
          
              
                data = other.data;
                other.data = nullptr;
            
        }
        MyString& operator = (const MyString& other){
            if(this != &other){
                delete[] data;
                 data = new char[strlen(other.data)+1];
                 strcpy(data,other.data);
            }
            return *this;

        }
        MyString& operator = ( MyString&& other){
            if(this != &other){
                 delete[] data;
                 data = other.data;
                 other.data = nullptr;
            }
            return *this;

        }
         bool operator == ( MyString&& other){
            return strcmp(data, other.data) ==0;

        }

        MyString operator + ( const MyString& other) const{
            char* new_string = new char[strlen(other.data)+strlen(data)+1];
            strcpy(new_string,data);
            strcat(new_string,other.data);
            MyString result(new_string);
            delete[] new_string;
            return result;

        }

        
        MyString operator + ( MyString&& other) const{
            char* new_string = new char[strlen(other.data)+strlen(data)+1];
            strcpy(new_string,data);
            strcat(new_string,other.data);
            MyString result(new_string);
            delete[] new_string;
            return result;

        }

        void print() const{
            printf("%s\n",data);
        }
        size_t length() const{
            return strlen(data);
        }

        char& operator[] (size_t index){
            if(index>=length())
                 throw out_of_range("Index out of range");
           
           return data[index];

        }
};


int main(){
    MyString s("Sagar");
    MyString s1(s);
    s.print();
    cout<<endl;
    s[0] ='c';
    for(size_t i=0;i<s.length();i++){
        cout<<s[i];
    }
    cout<<endl;
   s= s+s1;
   s.print();

   int * ptr = new int();
   int *ptr2 = ptr;

   delete ptr;
   ptr = nullptr;
   delete ptr2;

   
}