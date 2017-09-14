#ifndef JUANSTRING_H
#define JUANSTRING_H

#include <iostream>
using std::istream;
using std::ostream;

class JuanString
{
    public:
        JuanString(const char* str);
        /** Default constructor */
        JuanString();
        /** Default destructor */
        ~JuanString();
        /** Copy constructor
         *  \param other Object to copy from
         */
        JuanString(const JuanString& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
         int length() const;
         int findCharAt(char character);
         int findLastInstanceOf(char character);
         int find(const JuanString& str, int index = 0);
         int find(const char* str, int index = 0);
         int find(char character, int index = 0);
         int reverseFind(const JuanString& str, int index);
         int reverseFind(const char* str, int index);
         int reverseFind(char character, int index);
         bool isEmpty() const;
         bool operator <(const JuanString& str);
         bool operator <=(const JuanString& str);
         bool operator >(const JuanString& str);
         bool operator >=(const JuanString& str);
         bool operator ==(const JuanString& str);
         bool operator !=(const JuanString& str);
         char& operator [](int index);
         char findAt(int index);
         void insert(const JuanString& str, int index = 0);
         void insert(const char* str, int index = 0);
         void insert(char character, int index = 0);
         void remove(const JuanString& str, int index = 0);
         void remove(const char* str, int index = 0);
         void remove(char character, int index = 0);
         void replace(const JuanString& str, int index = 0);
         void replace(const char* str, int index = 0);
         void replace(char character,  int index = 0);
         void resize(int newSize);
         MyString substring(int startIndex);
         MyString substring(int startIndex, int endIndex);
         MyString operator +(const MyString& other);
         MyString& operator +=(const MyString& other);
         MyString operator -(const MyString& other);
         MyString& operator -=(const MyString& other);
         JuanString& operator=(const JuanString& other);
         friend istream& operator >>(istream& read, JuanString& str);
         friend ostream& operator <<(ostream& print, const JuanString& str);
    private:
        char* string;; //!< Member variable "string;"
        int size;; //!< Member variable "size;"
        void copy(const JuanString& str);
        int compare(const JuanString& str);
};

#endif // JUANSTRING_H
