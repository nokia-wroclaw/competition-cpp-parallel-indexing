#include "Word.hpp"


std::string const& Word::word() const
{
    return data_[0];
}

Word::const_iterator Word::begin() const
{
    return data_.begin()+1;
}

Word::const_iterator Word::end() const
{
    return data_.end();
}
