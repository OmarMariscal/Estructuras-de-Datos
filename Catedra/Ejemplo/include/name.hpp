#pragma once

#include <string>
#include <iostream>

class Name{
    private:
        std::string last;
        std::string fist;
    public:
        Name();
        Name(const Name&);
        Name(const std::string&, const std::string&);

        std::string getLast() const;
        std::string getFirst() const;

        std::string toString() const;

        void setLast(const std::string&);
        void setFirst(const std::string&);

        Name& operator = (const Name&);

        friend std::ostream& operator << (std::ostream&, const Name&);
        friend std::istream& operator >> (std::istream&, Name&);

        std::string serialize() const;
        void deserialize(const std::string&);

};

