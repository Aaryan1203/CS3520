# Aaryan Jain

Features
Employee Management: Create and manage employees with attributes like name, email, role, and group ID.
Group Management: Create and manage groups with attributes like name, area of responsibility, ID, and a list of employees.
Employee Assignment: Add employees to groups, ensuring no duplicate assignments.
    Employees can only be added to one group. They can only be unadded to a group if they are removed by using the - operator.
    If you try to assign an employee to a second group before removing them, then it will throw an error
Group Combination: Combine two groups into one.
Employee Removal: Remove a specified number of employees from a group.
Input and Output: Use overloaded << and >> operators to handle input and output for employees and groups.
    When inputting an employee from the terminal, you cannot specify the group it will be a part of. In order to do that, you must call the add_employee method
    Similarly when inputting a group from the terminal, you cannot specify the employees that will be a part of it. In order to do that you must call the add_employee method