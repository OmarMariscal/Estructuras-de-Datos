#ifndef __DATE_H__
#define __DATE_H__

#include <iostream>
#include <fstream>
#include <chrono>

#include "../lib/nlohmann/json.hpp"

#include "ownexceptions.hpp"

class Date{
    private:
        int year;
        int month;
        int day;

        int toInt() const;
        bool isValid(const int&, const int&, const int&) const;
        
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

        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json&);

        friend std::ostream& operator << (std::ostream&, const Date&);
        friend std::istream& operator >> (std::istream&, Date&);
}; 

#endif // __DATE_H__