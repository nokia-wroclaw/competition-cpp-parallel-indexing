#pragma once

#include <vector>
#include <string>
#include <algorithm>


class Word
{
public:
    using const_iterator = std::vector<std::string>::const_iterator;

    template<class InputIt>
    Word(InputIt begin, InputIt end);

    std::string const& word() const;
    const_iterator begin() const;
    const_iterator end() const;

private:
    std::vector<std::string> data_;
};


template<class InputIt>
Word::Word(InputIt begin, InputIt end) :
    data_(begin, end)
{
    std::sort(data_.begin()+1, data_.end());
}
