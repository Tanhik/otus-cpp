#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

struct ip_filter
{
   int a;
   int b;
   int c;
   int d;
};

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
template <typename Predicate>
void print_ips(const std::vector<ip_filter>& ips, Predicate matches)
{
    for (const auto& ip : ips)
    {
        if (matches(ip))
        {
            std::cout << ip.a << '.' << ip.b << '.'
                      << ip.c << '.' << ip.d << '\n';
        }
    }
}
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


