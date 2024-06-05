#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// represents an employee
class Employee
{
private:
    string name;
    string email;
    string role;
    string groupId;

public:
    // default constructor
    Employee()
    {
        name = "";
        email = "";
        role = "";
        groupId = "";
    }

    // constructor which takes in all arguments
    Employee(string n, string e, string r)
    {
        name = n;
        email = e;
        role = r;
        groupId = "";
    }

    // Getters
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getRole() const { return role; }
    string getGroup() const { return groupId; }

    // Setters
    void setName(const string &n) { name = n; }
    void setEmail(const string &e) { email = e; }
    void setRole(const string &r) { role = r; }
    void setGroup(string g) { groupId = g; }

    // overloading << and >>
    friend ostream &operator<<(ostream &out, const Employee &employee);
    friend istream &operator>>(istream &in, Employee &employee);
};

// represents a group
class Group
{
private:
    string name;
    string area_of_responsibility;
    string ID;
    vector<Employee> employees;

public:
    // default contructor
    Group()
    {
        name = "";
        area_of_responsibility = "";
        ID = "1";
        employees = vector<Employee>();
    };

    // constructor which takes in all the parameters
    Group(string n, string aor, string id, vector<Employee> e)
    {
        name = n;
        area_of_responsibility = aor;
        ID = id;
        employees = e;
    }

    // Getters
    string getName() const { return name; }
    string getAreaOfResponsibility() const { return area_of_responsibility; }
    string getID() const { return ID; }
    vector<Employee> getEmployees() const { return employees; }

    // Setters
    void setName(const string &n) { name = n; }
    void setAreaOfResponsibility(const string &aor) { area_of_responsibility = aor; }
    void setID(const string &id) { ID = id; }
    void setEmployees(const vector<Employee> &e) { employees = e; }

    // add an employee to the group
    friend void add_employee(Group &g, Employee &e);

    // overloading the -, +, <<, and >> operators
    Group operator-(int X);
    Group operator+(Group &other_group);
    friend ostream &operator<<(ostream &out, const Group &group);
    friend istream &operator>>(istream &in, Group &employee);
};

// adds an employee to the group
void add_employee(Group &g, Employee &e)
{
    auto it = find_if(g.employees.begin(), g.employees.end(), [&e](const Employee &emp)
                      { return emp.getEmail() == e.getEmail(); });

    // If the employee is not found, add them to the group
    if (it == g.employees.end() && e.getGroup() == "")
    {
        e.setGroup(g.ID);
        g.employees.push_back(e);
    }
    else
    {
        throw runtime_error("Cannot add an employee with the same email address to multiple groups");
    }
}

// overloading the group's '-' operator
Group Group::operator-(int X)
{
    int employees_to_fire = min(static_cast<int>(employees.size()), X);
    for (int i = 0; i < employees_to_fire; i++)
    {
        // remove the employee from the gorup it is assigned to
        Employee &current_employee = employees.back(); 
        current_employee.setGroup("");
        employees.pop_back(); 
    }
    return *this;
}

// overloading the group's '+' operator
Group Group::operator+(Group &other_group)
{
    Group new_group;
    new_group.name = name + " " + other_group.name;
    new_group.area_of_responsibility = area_of_responsibility + " " + other_group.area_of_responsibility;
    new_group.employees = employees;
    new_group.employees.insert(new_group.employees.end(), other_group.employees.begin(), other_group.employees.end());
    return new_group;
}

// overloading the group's '<<' operator
ostream &operator<<(ostream &out, const Group &group)
{
    out << "Group name: " << group.name << "\nArea of responsibility: " << group.area_of_responsibility << "\nEmployees:\n";
    for (const auto &employee : group.employees)
    {
        out << employee << endl;
    }
    out << "ID:" << group.ID << endl;
    return out;
}

// overloading the group's '>>' operator
istream &operator>>(istream &in, Group &group)
{
    cout << "Print a Groups name, area of respoinsibility, and ID, seperated by spaces" << endl;
    in >> group.name >> group.area_of_responsibility >> group.ID;
    cout << endl;
    return in;
}

// overloading the employees's '<<' operator
ostream &operator<<(ostream &out, const Employee &employee)
{
    out << "Employee name: " << employee.name << ", Email: " << employee.email << ", Role: "
        << employee.role << ", GroupId: " << employee.groupId;
    return out;
}

// overloading the employees's '>>' operator
istream &operator>>(istream &in, Employee &employee)
{
    cout << "Print an employees name, email and role seperated by spaces" << endl;
    in >> employee.name >> employee.email >> employee.role;
    cout << endl;
    return in;
}

int main()
{
    try
    {
        // testing '<<' operator
        cout << "Testing '<<' operator" << endl;
        Group group1("group 1", "sales", "1", vector<Employee>());
        Employee employee1("Aaryan", "aaryanjain1203@gmail.com", "role 1");
        cout << group1 << endl;
        cout << employee1 << endl;
        cout << endl;

        // testing '+' operator
        cout << "Testing '+' operator" << endl;
        Group group2("group 2", "marketing", "2", vector<Employee>());
        Group group3 = group1 + group2;
        cout << group3 << endl;
        cout << endl;

        // testing '-' operator
        cout << "Testing '-' operator" << endl;
        Employee employee2("Laith", "laith@gmail.com", "role 2");
        Employee employee3("User 3", "guest@gmail.com", "role 3");
        add_employee(group1, employee1);
        add_employee(group1, employee2);
        add_employee(group1, employee3);
        cout << "Group before subtraction" << endl;
        cout << group1 << endl;
        cout << endl;
        group1 - 2;
        cout << "Group after subtraction" << endl;
        cout << group1 << endl;
        cout << endl;

        // testing '>>' operator
        cout << "Testing '>>' operator" << endl;
        Group group4;
        Employee employee4;
        cin >> group4;
        cin >> employee4;
        cout << group4 << endl;
        cout << employee4 << endl;

        // this should throw an error when trying to add an employee with a duplicate ID to a group
        add_employee(group1, employee1);
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}