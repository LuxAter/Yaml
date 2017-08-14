#ifndef YAML_BASIC_YAML_HPP
#define YAML_BASIC_YAML_HPP

#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace yaml {

  enum ValueType {
    NONE = 0,
    HASH = 1,
    LIST = 2,
    BOOL = 3,
    FLOAT = 4,
    INT = 5,
    STRING = 6
  };

  class Yaml {
   public:
    typedef std::map<std::string, Yaml> hash_type_;
    typedef std::vector<Yaml> list_type_;
    typedef bool bool_type_;
    typedef double float_type_;
    typedef int int_type_;
    typedef std::string string_type_;

    typedef Yaml& reference;
    typedef const Yaml& const_reference;

    Yaml() {}
    Yaml(const Yaml& copy)
        : hash_(copy.hash_),
          list_(copy.list_),
          bool_(copy.bool_),
          float_(copy.float_),
          int_(copy.int_),
          string_(copy.string_),
          type_(copy.type_) {}

    Yaml(std::map<std::string, Yaml> value) : hash_(value), type_(HASH) {}
    Yaml(std::vector<Yaml> value) : list_(value), type_(LIST) {}
    Yaml(bool value) : bool_(value), type_(BOOL) {}
    Yaml(double value) : float_(value), type_(FLOAT) {}
    Yaml(int value) : int_(value), type_(INT) {}
    Yaml(std::string value) : string_(value), type_(STRING) {}
    Yaml(const char* value) : string_(value), type_(STRING) {}

    bool empty() const {
      if (type_ == NONE) {
        return true;
      } else if (type_ == HASH) {
        return hash_.empty();
      } else if (type_ == LIST) {
        return list_.empty();
      } else if (type_ == STRING) {
        return string_.empty();
      } else {
        return false;
      }
    }

    size_t size() const {
      if (type_ == NONE) {
        return 0;
      } else if (type_ == HASH) {
        return hash_.size();
      } else if (type_ == LIST) {
        return list_.size();
      } else if (type_ == STRING) {
        return string_.size();
      } else {
        return 1;
      }
    }

    size_t max_size() const {
      if (type_ == NONE) {
        return 0;
      } else if (type_ == HASH) {
        return hash_.max_size();
      } else if (type_ == LIST) {
        return list_.max_size();
      } else if (type_ == STRING) {
        return string_.max_size();
      } else {
        return 1;
      }
    }

    void clear() {
      if (type_ == HASH) {
        hash_.clear();
      } else if (type_ == LIST) {
        list_.clear();
      } else if (type_ == BOOL) {
        bool_ = bool();
      } else if (type_ == FLOAT) {
        float_ = float();
      } else if (type_ == INT) {
        int_ = int();
      } else if (type_ == STRING) {
        string_ = std::string();
      }
    }

    void push_back(Yaml value) {
      type_ = LIST;
      list_.push_back(value);
    }

    void push_back(std::string name, Yaml value) {
      type_ = HASH;
      hash_[name] = value;
    }

    void insert(int position, Yaml value) {
      if (type_ == LIST) {
        list_.insert(list_.begin() + position, value);
      }
    }

    void insert(std::string key, Yaml value) {
      if (type_ == HASH) {
        hash_[key] = value;
      }
    }

    reference access(std::string key) {
      type_ = HASH;
      return hash_[key];
    }

    reference access(int position) {
      type_ = LIST;
      if (position >= list_.size()) {
        list_.resize(position + 1);
      }
      return list_[position];
    }

    reference at(std::string key) {
      std::stringstream ss(key);
      std::string level_key;
      int level_index = -1;
      getline(ss, level_key, '.');
      getline(ss, key);
      if (key == level_key) {
        key = std::string();
      }
      bool is_int = true;
      for (int i = 0; i < level_key.size() && is_int == true; i++) {
        if (level_key[i] > 57 || level_key[i] < 48) {
          is_int = false;
        }
      }
      if (is_int == true) {
        level_index = std::stoi(level_key);
      }
      if (key == std::string()) {
        if (is_int == false) {
          return access(level_key);
        } else if (is_int == true) {
          return access(level_index);
        }
      } else {
        if (is_int == false) {
          return access(level_key).at(key);
        } else if (is_int == true) {
          return access(level_index).at(key);
        }
      }
      return *this;
    }

    reference find(std::string key) {
      std::stringstream ss(key);
      std::string level_key;
      int level_index = -1;
      getline(ss, level_key, '.');
      getline(ss, key);
      if (type_ == HASH) {
        for (std::map<std::string, Yaml>::iterator it = hash_.begin();
             it != hash_.end(); ++it) {
          if (it->first == level_key) {
            if (key == std::string()) {
              return it->second;
            } else {
              return it->second.find(key);
            }
          }
        }
      } else if (type_ == LIST) {
        bool is_int = true;
        for (int i = 0; i < level_key.size() && is_int == true; i++) {
          if (level_key[i] > 57 || level_key[i] < 48) {
            is_int = false;
          }
        }
        if (is_int == true) {
          level_index = std::stoi(level_key);
        }
        for (int i = 0; i < list_.size(); i++) {
          if (i == level_index) {
            if (key == std::string()) {
              return list_[i];
            } else {
              return list_[i].find(key);
            }
          }
        }
      }
      return *this;
    }

    std::string String(int level = 0, bool no_step = false) const {
      std::stringstream out;
      std::string indent(level * 2, ' ');
      if (no_step == true) {
        indent = std::string();
      }
      if (type_ == NONE) {
        out << "(null)";
      } else if (type_ == HASH) {
        if (level != 0 && no_step == false) {
          out << "\n";
        }
        for (std::map<std::string, Yaml>::const_iterator it = hash_.begin();
             it != hash_.end(); ++it) {
          out << indent << it->first << ": " << it->second.String(level + 1);
          if (it != --hash_.end()) {
            out << "\n";
          }
        }
      } else if (type_ == LIST) {
        if (level != 0 && no_step == false) {
          out << "\n";
        }
        for (std::vector<Yaml>::const_iterator it = list_.begin();
             it != list_.end(); ++it) {
          out << indent << "- " << it->String(level, true);
          if (it != --list_.end()) {
            out << "\n";
          }
        }
      } else if (type_ == BOOL) {
        if (bool_ == false) {
          out << "false";
        } else if (bool_ == true) {
          out << "true";
        }
      } else if (type_ == FLOAT) {
        out << float_;
      } else if (type_ == INT) {
        out << int_;
      } else if (type_ == STRING) {
        std::string sub;
        for (int i = 0; i < string_.size(); i++) {
          if (string_[i] == '\n') {
            sub += "\n" + std::string(level * 2, ' ');
          } else {
            sub += string_[i];
          }
        }
        out << sub;
      }
      return out.str();
    }

    inline bool is_valid() const { return type_ != NONE; }

    inline bool is_hash() const { return type_ == HASH; }
    inline bool is_list() const { return type_ == LIST; }
    inline bool is_bool() const { return type_ == BOOL; }
    inline bool is_float() const { return type_ == FLOAT; }
    inline bool is_int() const { return type_ == INT; }
    inline bool is_string() const { return type_ == STRING; }

    inline int get_type() const { return type_; }

    inline std::map<std::string, Yaml> get_hash() const { return hash_; }
    inline std::vector<Yaml> get_list() const { return list_; }
    inline bool get_bool() const { return bool_; }
    inline double get_float() const { return float_; }
    inline int get_int() const { return int_; }
    inline std::string get_string() const { return string_; }

    reference operator[](int index) {
      if (index >= list_.size()) {
        list_.resize(index + 1);
      }
      type_ = LIST;
      return list_[index];
    }
    reference operator[](std::string key) {
      type_ = HASH;
      return hash_[key];
    }

    reference operator()(std::string key) { return at(key); }

   private:
    ValueType type_ = NONE;

    std::map<std::string, Yaml> hash_;
    std::vector<Yaml> list_;
    bool bool_ = bool();
    double float_ = double();
    int int_ = int();
    std::string string_ = std::string();
  };

  std::ostream& operator<<(std::ostream& out, Yaml y) {
    out << y.String();
    return out;
  }

  bool operator==(const Yaml& lhs, const Yaml& rhs) {
    if (lhs.get_type() != rhs.get_type()) {
      return false;
    } else {
      if (lhs.is_hash() == true) {
        return lhs.get_hash() == rhs.get_hash();
      } else if (lhs.is_list() == true) {
        return lhs.get_list() == rhs.get_list();
      } else if (lhs.is_bool() == true) {
        return lhs.get_bool() == rhs.get_bool();
      } else if (lhs.is_float() == true) {
        return lhs.get_float() == rhs.get_float();
      } else if (lhs.is_int() == true) {
        return lhs.get_int() == rhs.get_int();
      } else if (lhs.is_string() == true) {
        return lhs.get_string() == rhs.get_string();
      } else {
        return true;
      }
    }
  }

  Yaml SetValue(std::string value) {
    Yaml yaml;
    if (value == "true" || value == "True") {
      yaml = true;
    } else if (value == "false" || value == "False") {
      yaml = false;
    } else if (value.size() > 0) {
      bool is_int = true;
      bool has_dot = false;
      for (int i = 0; i < value.size() && is_int == true; i++) {
        if (i == 0 && value[i] == '-') {
        } else if (value[i] == '.' && has_dot == false) {
          has_dot = true;
        } else if (value[i] == '.' && has_dot == true) {
          is_int = false;
        } else if (int(value[i]) > 57 || int(value[i]) < 48) {
          is_int = false;
        }
      }
      if (is_int == true && has_dot == true) {
        yaml = stod(value);
      } else if (is_int == true && has_dot == false) {
        yaml = stoi(value);
      } else if (is_int == false) {
        yaml = value;
      }
    } else {
      yaml = value;
    }
    return yaml;
  }

  int TrimString(std::string& str, std::string character = " ") {
    size_t str_begin = str.find_first_not_of(character);
    size_t str_end = str.find_last_not_of(character);
    std::string trimed = str.substr(str_begin, str_end - str_begin + 1);
    int diff = str.size() - trimed.size();
    str = trimed;
    return diff;
  }

  int GetIndent(std::string str) {
    std::string::iterator first_non_space = std::find_if(
        str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace)));
    int count = std::distance(str.begin(), first_non_space);
    return count;
  }

  void TrimIndent(std::string& str, int limit = 2,
                  std::string character = " ") {
    size_t str_begin = str.find_first_not_of(character);
    if (limit != -1) {
      if (str_begin > limit) {
        str_begin = limit;
      }
    }
    str = str.substr(str_begin, str.size() - str_begin + 1);
  }

  Yaml LoadVector(std::vector<std::string> lines) {
    Yaml yaml;
    for (int i = 0; i < lines.size(); i++) {
      std::stringstream ss(lines[i]);
      std::string name, value;
      getline(ss, name, ':');
      getline(ss, value);
      if (name.size() > 2 && name[0] == '-' && name[1] == ' ' &&
          value == std::string()) {
        name.erase(name.begin(), name.begin() + 2);
        yaml.push_back(name);
      } else if (value == std::string()) {
        std::vector<std::string> sub_set;
        i++;
        int step = 2;
        if (i < lines.size()) {
          step = GetIndent(lines[i]);
        }
        while (i < lines.size() && GetIndent(lines[i]) >= step) {
          TrimIndent(lines[i], step);
          sub_set.push_back(lines[i]);
          i++;
        }
        i--;
        TrimString(name);
        Yaml chunk = LoadVector(sub_set);
        yaml[name] = chunk;
      } else {
        TrimString(name);
        TrimString(value);
        yaml[name] = SetValue(value);
      }
    }
    return yaml;
  }

  Yaml LoadString(std::string content) {
    Yaml yaml;
    std::stringstream ss(content);
    std::string line;
    std::vector<std::string> lines;
    while (getline(ss, line)) {
      lines.push_back(line);
    }
    return LoadVector(lines);
  }

  Yaml LoadFile(std::string file_path) {
    std::ifstream in(file_path.c_str());
    std::vector<std::string> lines;
    if (in.is_open()) {
      std::string line;
      while (getline(in, line)) {
        lines.push_back(line);
      }
      in.close();
    }
    return LoadVector(lines);
  }

}  // namespace yaml

#endif /* ifndef YAML_BASIC_YAML_HPP */
