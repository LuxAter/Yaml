# Yaml Class #

Defined in header `<yaml/yaml.hpp>`

```cpp
class Yaml;
```

`yaml::Yaml` is a structured class, that mimics yaml file structure. This class
can either be a single type value (`bool`, `float`, `int`, `string`), or it can
be an ordered list of values (`std::vector`), or it can be a sorted list of
associated pairs (`std::map`).

## Member Types ##

| Member type     | Definition                   |
|-----------------|------------------------------|
| hash_type_      | `std::map<std::string,Yaml>` |
| list_type_      | `std::vector<Yaml>`          |
| bool_type_      | `bool`                       |
| float_type_     | `float`                      |
| int_type_       | `int`                        |
| string_type_    | `std::string`                |
| reference       | `Yaml&`                      |
| const_reference | `const Yaml&`                |

## Member functions ##

|                                |                                       |
|--------------------------------|---------------------------------------|
| [(constructor)](#constructors) | constructs the yaml                   |
| [(destructor)](#destructor)    | destructs the yaml                    |
| [operator=](#operator=)        | assigns value to container            |
| [String](#string)              | returns string representation of yaml |

| Element access             |                                             |
|----------------------------|---------------------------------------------|
| [at](#at)                  | access specified element with bounds checks |
| [operator[ ]](#operator[]) | access specified element                    |
| [operator( )](#operator()) | finds specified element with bounds checks  |
| [get_hash](#get_hash)      | returns hash value of yaml                  |
| [get_list](#get_list)      | returns list value of yaml                  |
| [get_bool](#get_bool)      | returns bool value of yaml                  |
| [get_float](#get_float)    | returns float value of yaml                 |
| [get_int](#get_int)        | returns int value of yaml                   |
| [get_string](#get_string)  | returns string value of yaml                |
| [get_type](#get_type)      | returns the type value of the yaml          |

| Checks                  |                            |
|-------------------------|----------------------------|
| [is_valid](#is_valid)   | checks if yaml is valid    |
| [is_hash](#is_hash)     | checks if yaml is a hash   |
| [is_list](#is_list)     | checks if yaml is a list   |
| [is_bool](#is_bool)     | checks if yaml is a bool   |
| [is_float](#is_float)   | checks if yaml is a float  |
| [is_int](#is_int)       | checks if yaml is a int    |
| [is_string](#is_string) | checks if yaml is a string |

| Capacity              |                                            |
|-----------------------|--------------------------------------------|
| [empty](#empty)       | checks whether the container is empty      |
| [size](#size)         | returns number of elements                 |
| [max_size](#max_size) | returns maximum posible number of elements |

| Modifiers               |                                 |
|-------------------------|---------------------------------|
| [clear](#clear)         | clears the contents             |
| [insert](#insert)       | inserts elements or nodes       |
| [push_back](#push_back) | adds element or node to the end |

| Lookup            |                                                               |
|-------------------|---------------------------------------------------------------|
| [access](#access) | finds element with specific key without creating new elements |
| [find](#find)     | finds element with specific key                               |

## Non-member functions ##

|                           |                                                  |
|---------------------------|--------------------------------------------------|
| [operator<<](#operator<<) | outputs string representation of yaml to ostream |
| [SetValue](#setvalue)     | sets yaml from string representation of value    |
| [TrimString](#trimstring) | removes spaces from ends of string               |
| [GetIndent](#getindent)   | gets the number of indentation characters        |
| [TrimIndent](#trimindent) | removes indentation characters                   |
| [LoadVector](#loadvector) | creates yaml from vector of strings              |
| [LoadString](#loadstring) | creates yaml from string representation          |
| [LoadFile](#loadfile)     | creates yaml from yaml file                      |
