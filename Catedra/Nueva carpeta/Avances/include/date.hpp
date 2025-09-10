#pragma once
#include <iostream>

class Date{
    private:
        int year;
        int month;
        int day;

        int toInt() const;
        bool isValid() const;
        
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

        bool operator == (const Date&) const;
        bool operator != (const Date&) const;
        bool operator < (const Date&) const;
        bool operator > (const Date&) const;
        bool operator <= (const Date&) const;
        bool operator >=(const Date&) const;

        int compareTo(const Date&) const;
        static int compare(const Date&, const Date&);


        Date& operator = (const Date&);

}; 