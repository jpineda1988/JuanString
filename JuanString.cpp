#include "JuanString.h"
#include <cstdlib>

namespace
{
    int cStringLength(const char* s);
    bool isGraphic(char character);
}


JuanString::JuanString(const char* str) : string(nullptr), size(cStringLength(str))
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

JuanString::JuanString(const JuanString& other) : string(nullptr), size(0)
{
    copy(other);
    //copy ctor
}

bool JuanString::isEmpty() const
{
    return string == nullptr;
}

int JuanString::length() const
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
           if(string[position--] == str.string[num])
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
        index = position + str.size;
        for(int num = 0; num < remainder; num++)
            buffer[num] = string[index++];

        string = static_cast<char*>(realloc(string, (size - str.size)*sizeof(char)));
        index = position;

        for(int num = 0; num < remainder; num++)
           string[index++] = buffer[num];

        size -= str.size;
        delete [] buffer;
        buffer = nullptr;
    }
}

void JuanString::remove(const char* str, int index)
{
    int position = find(str, index), length = cStringLength(str);
    if(position == NOT_FOUND)
       return;

    int remainder = size - position - length;
    if(remainder == 0)
    {
       string = static_cast<char*>(realloc(string, (size - length)*sizeof(char)));
       size -= length;
    }
    else
    {
        char* buffer = new char[remainder];
        index = position + length;
        for(int num = 0; num < remainder; num++)
          buffer[num] = string[index++];

        string = static_cast<char*>(realloc(string, (size - length)*sizeof(char)));
        index = position;

        for(int num = 0; num < remainder; num++)
            string[index++] = buffer[num];

        size -= length;
        delete [] buffer;
        buffer = nullptr;
    }
}

void JuanString::remove(char character, int index)
{
    int position = find(character, index);
    if(position == NOT_FOUND)
      return;

    int remainder = size - position - 1;
    if(remainder == 0)
      string = static_cast<char*>(realloc(string, --size*sizeof(char)));
    else
    {
        char* buffer = new char[remainder];
        index = position + 1;
        for(int num = 0; num < remainder; num++)
            buffer[num] = string[index++];

        string = static_cast<char*>(realloc(string, --size*sizeof(char)));

        index = position;
        for(int num = 0; num < remainder; num++)
            string[index++] = buffer[num];

        delete [] buffer;
        buffer = nullptr;
    }
}

void JuanString::replace(const JuanString& str, int index)
{
    if(index >= 0 && index <= (size - str.size))
    {
        for(int position = 0; position < str.size; position++)
            string[index++] = str.string[position];
    }
}

void JuanString::replace(const char* str, int index)
{
    int length = cStringLength(str);
    if(index >= 0 && index <= (size - length))
    {
        for(int position = 0; position < length; position++)
            string[index++] = str[position];
    }
}

void JuanString::replace(char character, int index)
{
    if(index >= 0 && index < size)
      string[index] = character;
}

void JuanString::resize(int newSize)
{
    string = static_cast<char*>(realloc(string, newSize*sizeof(char)));
    size = newSize;
}

JuanString JuanString::substring(int startIndex)
{
    JuanString part;
    if(startIndex >= 0 && startIndex < size)
    {
        part.size = size - startIndex;
        part.string = static_cast<char*>(calloc(part.size, sizeof(char)));

        for(int index = 0; index < part.size; index++)
            part.string[index] = string[startIndex++];
    }
    return part;
}

JuanString JuanString::substring(int startIndex, int endIndex)
{
    JuanString part;
    if(startIndex >= 0 && startIndex < endIndex && endIndex < size)
    {
        part.size = endIndex - startIndex;
        part.string = static_cast<char*>(calloc(part.size, sizeof(char)));

        for(int index = 0; index < part.size; index++)
            part.string[index] = string[startIndex++];

    }
    return part;
}

JuanString JuanString::operator +(const JuanString& other)
{
    JuanString combine;
    combine.size = size + other.size;
    combine.string = static_cast<char*>(calloc(combine.size, sizeof(char)));
    int position = 0;

    for(int index = 0; index < size; index++)
        combine.string[position++] = string[index];

    for(int index = 0; index < other.size;index++)
        combine.string[position++] = other.string[index];
    return combine;
}

JuanString& JuanString::operator +=(const JuanString& other)
{
    string = static_cast<char*>(realloc(string, (size + other.size)*sizeof(char)));
    int index = size;

    for(int position = 0; position < other.size; position++)
        string[index++] = other.string[position];
    size += other.size;
    return *this;
}

JuanString JuanString::operator -(const JuanString& other)
{
    JuanString part(*this);
    part.remove(other);
    return part;
}

JuanString& JuanString::operator -=(const JuanString& other)
{
    remove(other);
    return *this;
}

JuanString& JuanString::operator=(const JuanString& rhs)
{
    if(this == &rhs)
        return *this;// handle self assignment
    free(string);
    string = nullptr;
    copy(rhs);//assignment operator
    return *this;
}

const int MAX_BUFFER_SIZE = 250;
istream& operator >>(istream& read, JuanString& str)
{
    char buffer[MAX_BUFFER_SIZE] = {0}, letter = '0';
    int index = 0, count = 0;

    do
    {
        for(; index < MAX_BUFFER_SIZE && isGraphic(letter); index++)
        {
            read >> letter;
            buffer[index] = letter;
            count++;
        }
    }while(count == 1);

    free(str.string);
    str.string = nullptr;

    str.size = count - 1;
    str.string = static_cast<char*>(calloc(str.size, sizeof(char)));

    for(index = 0; index < str.size; index++)
        str.string[index] = buffer[index];
    return read;
}

ostream& operator <<(ostream& print, const JuanString& str)
{
    for(int index = 0; index < str.size; index++)
        print << str.string[index];
    return print;
}

void JuanString::copy(const JuanString& str)
{
    string = static_cast<char*>(calloc(str.size, sizeof(char)));
    size = str.size;

    for(int index = 0; index < str.size; index++)
        string[index] = str.string[index];
}

int JuanString::compare(const JuanString& str)
{
    int difference = 0, goal = (size < str.size) ? size : str.size;

    for(int index = 0; index < goal; index++)
    {
       difference += string[index] - str.string[index];
       if(difference != 0)
          break;
    }

    if(difference == 0 && size < str.size)
       difference = -1;
    if(difference == 0 && size > str.size)
       difference = 1;
    return difference;
}

namespace
{
    int cStringLength(const char* s)
    {
        int count = 0, index = 0;
        while(s[index++] != '\0')
           count++;
        return count;
    }

    bool isGraphic(char character)
    {
        return !(character >= 0 && character <= ' ') || character != 127;
    }
}
