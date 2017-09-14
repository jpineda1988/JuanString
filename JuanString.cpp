#include "JuanString.h"
#include <cstdlib>

namespace
{
    int cStringLength(const char* s);
    bool isGraphic(char character);
}


JuanString::JuanString(const char* str) : size(cStringLength(str))
{
   string = static_cast<char*>(calloc(size, sizeof(char)));
   for(int index = 0; index < size; index++)
     string[index] = str[index];
}

JuanString::JuanString() : string(nullptr), size(0)
{
    //ctor
}

JuanString::~JuanString()
{
    free(string);
    string = nullptr;
    //dtor
}

JuanString::JuanString(const JuanString& other)
{
    copy(other);
    //copy ctor
}

bool JuanString::isEmpty() const
{
    return string == nullptr;
}

int JuanString::length()
{
   return size;
}

const int NOT_FOUND = -1;

int JuanString::findCharAt(char character)
{
    for(int index = 0; index < size; index++)
        if(string[index] == character)
           return index;
    return NOT_FOUND;
}

int JuanString::findLastInstanceOf(char character)
{
    for(int index = size - 1; index >= 0; index--)
       if(string[index] == character)
          return index;
    return NOT_FOUND;
}

int JuanString::find(const JuanString& str, int index)
{
    if(str.size > size || index < 0 || index >= size)
       return NOT_FOUND;

    int position = index, goal = size - index;
    bool valid = false;

    for(; index <= goal; position = ++index)
    {
       for(int num = 0; num < str.size; num++)
       {
          if(string[position++] == str.string[num])
              valid = true;
          else
          {
              valid = false;
              break;
          }
       }
       if(valid)
         break;
    }
    return valid ? index : NOT_FOUND;
}

int JuanString::find(const char* str, int index)
{
    int length = cStringLength(str);
    if(length > size || index < 0 || index >= size)
       return NOT_FOUND;

    int position = index, goal = size - index;
    bool valid = false;

    for(; index <= goal; position = ++index)
    {
        for(int num = 0; num < length; num++)
        {
            if(string[position++] == str[num])
               valid = true;
            else
            {
               valid = false;
               break;
            }
        }

        if(valid)
          break;
    }

    return (valid) ? index : NOT_FOUND;
}

int JuanString::find(char character, int index)
{
    for(int position = index; position < size; position++)
       if(string[position] == character)
          return position;

    return NOT_FOUND;
}

int JuanString::reverseFind(const JuanString& str, int index)
{
    if(index >= size || index < (str.size - 1) || str.size >= size)
       return NOT_FOUND;

    int position = index, goal = str.size - 1;
    bool valid = false;

    for(; index >= goal; position = --index)
    {
       for(int num = str.size - 1; num >= 0; num--)
       {
           if(string[position--] === str.string[num])
              valid = true;
           else
           {
              valid = false;
              break;
           }
       }

       if(valid)
         break;
    }
    return valid ? index : NOT_FOUND;
}

int JuanString::reverseFind(const char* str, int index)
{
    int length = cStringLength(str);
    if(index >= size || index < (length - 1) || length >= size)
        return NOT_FOUND;

    int position = index, goal = length - 1;
    bool valid = false;

    for(; index >= goal; position = --index)
    {
        for(int num = length - 1; num >= 0; num--)
        {
            if(string[position--] == str[num])
               valid = true;
            else
            {
               valid = false;
               break;
            }
        }
        if(valid)
          break;
    }
    return valid ? index : NOT_FOUND;
}

int JuanString::reverseFind(char character, int index)
{
    if(index >= 0 && index < size)
    {
       for(; index >= 0; index--)
          if(string[index] == character)
            return index;
    }
    return NOT_FOUND;
}

bool JuanString::isEmpty() const
{
   return string == nullptr;
}

bool JuanString::operator <(const JuanString& str)
{
    return compare(str) < 0;
}

bool JuanString::operator <=(const JuanString& str)
{
    return compare(str) <= 0;
}

bool JuanString::operator >(const JuanString& str)
{
    return compare(str) > 0;
}

bool JuanString::operator >=(const JuanString& str)
{
   return compare(str) >= 0;
}

bool JuanString::operator==(const JuanString& str)
{
   return compare(str) == 0;
}

bool JuanString::operator !=(const JuanString& str)
{
    return compare(str) != 0;
}

char& JuanString::operator[](int index)
{
    if(index < 0 || index >= size)
       throw NOT_FOUND;
    return string[index];
}

char JuanString::findAt(int index)
{
    if(index < 0 || index >= size)
       return ' ';
    return string[index];
}

void JuanString::insert(const JuanString& str, int index)
{
    if(index >= 0 && index < size)
    {
        int remainder = size - index, num = index;
        char *buffer = new char[remainder];
        for(int position = 0; position < remainder; position++)
           buffer[position] = string[num++];

        string = static_cast<char*>(realloc(string, (size + str.size)*sizeof(char)));

        num = index;
        for(int position = 0; position < str.size; position++)
           string[num++] = str.string[position];

        for(int position = 0; position < remainder; position++)
          string[num++] = buffer[position];

        size += str.size;
        delete [] buffer;
        buffer = nullptr;
    }
}

void JuanString::insert(const char* str, int index)
{
   if(index >= 0 && index < size)
   {
       int remainder = size - index, num = index, length = cStringLength(str);
       char *buffer = new char[remainder];

       for(int position = 0; position < remainder; position++)
          buffer[position] = string[num++];

       string = static_cast<char*>(realloc(string, (size + length)*sizeof(char)));

       num = index;
       for(int position = 0; position < length; position++)
          string[num++] = str[position];

       for(int position = 0; position < remainder; position++)
          string[num++] = buffer[position];

       size += length;
       delete [] buffer;
       buffer = nullptr;
   }
}

void JuanString::insert(char character, int index)
{
    if(index >= 0 && index < size)
    {
        int remainder = size - index, num = index;
        char* buffer = new char[remainder];

        for(int position = 0; position < remainder; position++)
           buffer[position] = string[num++];

        string = static_cast<char*>(realloc(string, ++size*sizeof(char)));

        string[index] = character;
        num = index + 1;
        for(int position = 0; position < remainder; position++)
           string[num++] = buffer[position];

        delete [] buffer;
        buffer = nullptr;
    }
}

void JuanString::remove(const JuanString& str, int index)
{
    int position = find(str, index);
    if(position == NOT_FOUND)
       return;

    int remainder = size - position - str.size;
    if(remainder == 0)
    {
        string = static_cast<char*>(realloc(string, (size - str.size)*sizeof(char)));
        size -= str.size;
    }
    else
    {
        char* buffer = new char[remainder];
        index = position;
        for(int num = 0; num < remainder; num++)
            buffer[num] = string[index++];

        string = static_cast<char*>(realloc(string, (size - str.size)*sizeof(char)));
        index = position;


    }
}



JuanString& JuanString::operator=(const JuanString& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
