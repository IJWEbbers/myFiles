#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <array>
#include <functional>
#include <string>
#include <iostream>
#include <map>

class Dataframe
{
public:
    using dataframe = std::array<std::uint8_t, 255>;
    Dataframe();
    ~Dataframe();
    void setData(const dataframe &data, std::uint8_t size);
    void setChecksum();
    void setDataframe(const dataframe &dataframe);
    void show()const;
    void showAll()const;
    bool checksumIsCorrect() const;
    void clear();

private:
    dataframe df_;
};

#endif // DATAFRAME_HPP
