#ifndef VORETERATOR_HPP
#define VORETERATOR_HPP

#include <iterator>
#include <cstring>

template <int consonant_limit=2, int vowel_limit=1>
class voreterator {
public:
  voreterator (char * str, int max_length, int vorefix_length=-1):
    data(str), len(vorefix_length), size(max_length), ended(false)
  {
    if (len < 0) {
      len = strlen(str);
      if (len > size) len = size;
    }
    
    stack = new group_t[max_length];
    group_t* top = stack;
    top->type = type(*data);
    top->count = 1;
    top++;
    
    int ibad = -1;
    for (int i = 1; i < len; i++, top++) {
      top->type = type(data[i]);
      top->count = top->type == (top-1)->type ? (top-1)->count + 1 : 1;
      if (ibad < 0 && top->count > limits(top->type)) ibad = i;
    }
    
    if (ibad >= 0) increment (ibad);
  }
  
  voreterator (const voreterator& rhs):
    data(rhs.data), len(rhs.len), size(rhs.size), ended(rhs.ended)
  {
    if (size) {
      stack = new group_t[size];
      memcpy(stack, rhs.stack, size * sizeof(group_t));
    } else {
      stack = nullptr;
    }
  }
  
  voreterator& operator = (const voreterator& rhs) {
    if (this == &rhs) return *this;
    
    if (size < rhs.size) {
      delete [] stack;
      stack = new group_t[rhs.size];
    }
    
    data = rhs.data;
    len = rhs.len;
    size = rhs.size;
    ended = rhs.ended;
    if (size) memcpy(stack, rhs.stack, size * sizeof(group_t));
  }
  
  bool operator == (const voreterator& rhs) const {
    return data == rhs.data && ended == rhs.ended;
  }
  
  bool operator != (const voreterator& rhs) const {
    return data != rhs.data || ended != rhs.ended;
  }
  
  const char * operator * () const {
    return data;
  }
  
  voreterator& operator ++ () {
    increment(len - 1);
    return *this;
  }
  
  ~voreterator () {
    delete [] stack;
  }
  
  operator bool () const {
    return ended;
  }
  
  voreterator begin() const {
    return *this;
  }
  
  voreterator end() const {
    return voreterator(data);
  }
  
private:
  enum chartype {
    TYPE_C=0, TYPE_V, NTYPES
  };
  
  char * data;
  int len, size;
  bool ended;

  struct group_t {
    chartype type;
    int count;
  } * stack;
  
  explicit voreterator (char * str):
    data(str), len(0), size(0), ended(true), stack(nullptr)
  {}
  
  int basic_increment (int pos) {
    for (int i = pos; i >= 0; i--) {
      data[i] = next(data[i]);
      if (data[i] == first()) {
        if (i == 0) {
          int cursize = len + strlen(data + len);
          if (cursize >= size) return -1;
          memmove(data+1, data, cursize+1);
          *data = first();
          len ++;
          return i;
        }
      } else {
        return i;
      }
    }
    
    return 0;
  }
  
  void increment (int i) {
    while (1) {
      i = basic_increment(i);
      
      if (i <= 0) {
        if (i < 0) {
          ended = true;
          return;
        }
        stack->type = type(*data);
        stack->count = 1;
        i = 1;
      }
      
      for (; i < len; i++) {
        group_t* const top = stack + i;
        top->type = type(data[i]);
        if (top->type == (top-1)->type) {
          top->count = (top-1)->count + 1;
          if (top->count > limits(top->type)) break;
        } else {
          top->count = 1;
        }
      }
      
      if (i == len) return;
    }
  }
  
  static int limits (int type) {
    switch (type) {
      case TYPE_C: return consonant_limit;
      case TYPE_V: return vowel_limit;
      default: return 0;
    }
  }

  static chartype type (char c) {
    switch (c) {
      case 'a': return TYPE_V;
      case 'b': return TYPE_C;
      case 'c': return TYPE_C;
      case 'd': return TYPE_C;
      case 'e': return TYPE_V;
      case 'f': return TYPE_C;
      case 'g': return TYPE_C;
      case 'h': return TYPE_C;
      case 'i': return TYPE_V;
      case 'j': return TYPE_C;
      case 'k': return TYPE_C;
      case 'l': return TYPE_C;
      case 'm': return TYPE_C;
      case 'n': return TYPE_C;
      case 'o': return TYPE_V;
      case 'p': return TYPE_C;
      case 'q': return TYPE_C;
      case 'r': return TYPE_C;
      case 's': return TYPE_C;
      case 't': return TYPE_C;
      case 'u': return TYPE_V;
      case 'v': return TYPE_C;
      case 'w': return TYPE_C;
      case 'x': return TYPE_C;
      case 'y': return TYPE_C;
      case 'z': return TYPE_C;
      default:  return NTYPES;
    }
  }

  static char first () {
    return 'a';
  }
  
  static char next (char c) {
    switch (c) {
      case 'a': return 'b';
      case 'b': return 'c';
      case 'c': return 'd';
      case 'd': return 'e';
      case 'e': return 'f';
      case 'f': return 'g';
      case 'g': return 'h';
      case 'h': return 'i';
      case 'i': return 'j';
      case 'j': return 'k';
      case 'k': return 'l';
      case 'l': return 'm';
      case 'm': return 'n';
      case 'n': return 'o';
      case 'o': return 'p';
      case 'p': return 'q';
      case 'q': return 'r';
      case 'r': return 's';
      case 's': return 't';
      case 't': return 'u';
      case 'u': return 'v';
      case 'v': return 'w';
      case 'w': return 'x';
      case 'x': return 'y';
      case 'y': return 'z';
      case 'z': return 'a';
      default:  return 0;
    }
  }

};

#endif