#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Name{
    private:
        std::string lastName;
        std::string firstName;
    public:
        Name();
        Name(const Name&);
        /// @brief 
        /// @param FirstName 
        /// @param  LastName
        Name(const std::string&, const std::string&);

        std::string getLastName() const;
        std::string getFirstName() const;

        std::string toString() const;

        void setLastName(const std::string&);
        void setFirstName(const std::string&);

        bool operator == (const Name&) const;
        bool operator != (const Name&) const;
        bool operator < (const Name&) const;
        bool operator > (const Name&) const;
        bool operator <= (const Name&) const;
        bool operator >=(const Name&) const;

        int compareTo(const Name&) const;
        static int compare(const Name&, const Name&);

        Name& operator = (const Name&);

        friend std::ostream& operator << (std::ostream&, const Name&);
        friend std::istream& operator >> (std::istream&, Name&);

        void serialize(const Name&);
        std::string deserialize() const;
};

