#pragma once
#include <iostream>
#include <string>

class Date{
    private:
        int year;
        int month;
        int day;
    public:
        Date();
        Date(const Date&);
        Date(const int&, const int&, const int&);

        int getYear() const;
        int getMonth() const;
        int getDay() const;

        std::string toString() const;

        void setYear(const int&);
        void setMonth(const int&);
        void setDay(const int&);

        Date& operator = (const Date&);

        friend std::ostream& operator << (std::ostream&, const Date&);
        friend std::istream& operator >> (std::istream&, Date&);
}; 