#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <string>
#include <map>
#include <vector>

using std::map;
using std::string;
using std::vector;

class DTO {
    string entity_type;
    int count;

public:
    DTO(const string& entity_type, int count) : entity_type{ entity_type }, count{ count } {};

    DTO(const string& entity_type) : entity_type{ entity_type }, count{ 0 } {};

    DTO() : entity_type{ "" }, count{ 0 } {};

    [[nodiscard]] const string& get_entity_type() const noexcept {
        return entity_type;
    }

    [[nodiscard]] int get_count() const noexcept {
        return count;
    }

};

class Tentant {

private:
    int number;
    string name;
    int surface;
    string type;

public:
    /*
    * the constructor of the tentant
    *
    * A tentant has:
    *	~number
    *	~name
    *	~surface
    *	~type
    */

    Tentant(int number, const string& name, int surface, const string& type);

    /*
    * Default constructor
    */

    Tentant();

    /*
    * Destructor
    */

    ~Tentant();

    /*
    * Constructor copy
    */
    Tentant(const Tentant& tentant);

    // getters
    /*
    * Get the number of tenant's apartment
    */
    [[nodiscard]] int get_number() const noexcept;

    /*
    * Get the name of the tenant
    */
    [[nodiscard]] const string& get_name() const noexcept;

    /*
    * Get the surface of the apartment
    */

    [[nodiscard]] int get_surface() const noexcept;

    /*
    * Get the type
    */

    [[nodiscard]] const string& get_type() const noexcept;

    // setters

    [[maybe_unused]] void set_name(const string& new_name);
    [[maybe_unused]] void set_number(int new_number);
    [[maybe_unused]] void set_surface(int new_surface);
    [[maybe_unused]] void set_type(const string& new_type);


    /*
    * Print function
    */
    string to_string_print() const;

    // Operator used to assign a copy
    Tentant& operator=(const Tentant& copy);

    // Equality operator between two objects
    bool operator==(const Tentant& copy) noexcept;

    bool operator!=(const Tentant& copy) noexcept;

    friend std::istream& operator>>(std::istream& input, Tentant& tentant);


};
// comparatori

// returns TRUE if t1.get_number() < t2.get_number()
bool cmp_number(const Tentant& t1, const Tentant& t2);

// returns TRUE if t1.get_name() < t2.get_name()
bool cmp_name(const Tentant& t1, const Tentant& t2);

// returns TRUE if t1.get_surface() < t2.get_surface()
bool cmp_surface(const Tentant& t1, const Tentant& t2);

// returs TRUE if t1.get_type() < t2.get_type()
bool cmp_type(const Tentant& t1, const Tentant& t2);

bool cmp_type_surface(const Tentant& t1, const Tentant& t2);

std::ostream& operator <<(std::ostream& output, const Tentant& tentant);

vector<string> split(const string& input, char delimiter);


#endif