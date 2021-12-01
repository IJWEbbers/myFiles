#include "dataframe.hpp"


Dataframe::Dataframe()
{
    for(uint8_t i = 0; i < sizeof(df_); i++)
    {
        df_[i] = 0;
    }
}

Dataframe::~Dataframe()
{}

void Dataframe::setData(const Dataframe::dataframe &data, uint8_t size)
{
    df_[0] = 19;
    df_[1] = size;
    for(uint8_t i = 2; i < sizeof(df_); i++)
    {
        df_[i] = data[i - 2];
    }
    setChecksum();
}

void Dataframe::setChecksum()
{
    uint8_t used_size = df_[1];
    uint8_t checksum = 0;
    for(uint8_t i = 0; i < used_size; i++)
    {
        checksum -= df_[i];
    }
    df_[2 + used_size] = checksum;
}

void Dataframe::setDataframe(const Dataframe::dataframe &dataframe)
{
    for(uint8_t i = 0; i < sizeof(df_); i++)
    {
        df_[i] = dataframe[i];
    }
}

void Dataframe::show() const
{
    uint8_t size = df_[1] + 3;
    for(int i = 0; i < size; i++)
    {
        std::cout << "[" << static_cast<int>(df_[i]) << "] ";
    }
    std::cout << std::endl;
}

void Dataframe::showAll() const
{
    for(auto data : df_)
    {
        std::cout << "[" << static_cast<int>(df_[data]) << "] ";
    }
    std::cout << std::endl;
}

bool Dataframe::checksumIsCorrect() const
{
    uint8_t size = df_[1] + 2;
    uint8_t checksum = 0;
    for(int i = 0; i < size; i++)
    {
        checksum += df_[i+1];
    }
    return checksum == 255;
}

void Dataframe::clear()
{
    for(auto e: df_)
    {
        df_[e] = 0;
    }
}
