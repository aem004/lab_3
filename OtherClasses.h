#include <utility>



#ifndef LAB3_OTHERCLASSES_H
#define LAB3_OTHERCLASSES_H

class Student{
private:
    std::string name;
    std::string surname;
    int course;
    std::string faculty;
public:
    Student(string name, string surname, int course, string faculty) : name(std::move(name)),
                                                                       surname(std::move(surname)),
                                                                       course(course),
                                                                       faculty(std::move(faculty)) {}

    const string &getName() const {
        return name;
    }

    const string &getSurname() const {
        return surname;
    }

    int getCourse() const {
        return course;
    }

    const string &getFaculty() const {
        return faculty;
    }
};

#endif //LAB3_OTHERCLASSES_H
