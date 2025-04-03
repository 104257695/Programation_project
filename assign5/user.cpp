#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

// Destructor
User::~User() {
  delete[] _friends;
}

// Copy constructor
User::User(const User& other) : 
  _name(other._name),
  _size(other._size),
  _capacity(other._capacity),
  _friends(other._size > 0 ? new std::string[other._capacity] : nullptr) {
  
  for (size_t i = 0; i < _size; ++i) {
      _friends[i] = other._friends[i];
  }
}

// Copy assignment operator
User& User::operator=(const User& other) {
  if (this != &other) {
      // Free existing resources
      delete[] _friends;
      
      // Copy data
      _name = other._name;
      _size = other._size;
      _capacity = other._capacity;
      
      // Allocate new array and copy elements
      _friends = (other._size > 0) ? new std::string[_capacity] : nullptr;
      for (size_t i = 0; i < _size; ++i) {
          _friends[i] = other._friends[i];
      }
  }
  return *this;
}

// += operator to mutually add friends
User& User::operator+=(User& rhs) {
  // Add rhs to this user's friends
  add_friend(rhs._name);
  
  // Add this user to rhs's friends
  rhs.add_friend(_name);
  
  return *this;
}

// < operator for name comparison
bool User::operator<(const User& rhs) const {
  return _name < rhs._name;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "User(name=" << user._name << ", friends=[";
  for (size_t i = 0; i < user._size; ++i) {
      if (i != 0) {
          os << ", ";
      }
      os << user._friends[i];
  }
  os << "])";
  return os;
}
