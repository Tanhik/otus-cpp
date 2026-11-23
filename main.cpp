#include "ip_filter.cpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include "lib.h"
#include <tuple>
#include <fstream>
int main(int, char **)
{
    // std::cout << "Version: " << version() << std::endl;
    // std::cout << "Hello, world!" << std::endl;
    std::fstream input("ip_filter.tsv");
    // while (std::getline(std::cin, str_file))
    if (!input)
    {
        std::cerr << "не удалось открыть файл ip_filter.tsv" << std::endl;
        return 1;
    }
    std::string str_file;
    std::vector<std::string> str_ip; // строка с ip
    std::vector<ip_filter> ip_pool;
    // while (std::getline(input, str_file))
    while (std::getline(std::cin, str_file))
    {
        std::vector<std::string> str;
        str = split(str_file, '\t'); // 76.221.68.186      2       0end
        str_ip = split(str[0], '.');
        if (str_ip.size() != 4)
        {
            std::cerr << "неверный формат ip адреса" << std::endl;
            return 1;
        }
        ip_filter ip{std::stoi(str_ip[0]), std::stoi(str_ip[1]), std::stoi(str_ip[2]), std::stoi(str_ip[3])};
        ip_pool.push_back(ip);
    }

    std::sort(ip_pool.begin(), ip_pool.end(),
              [](const ip_filter &left, const ip_filter &right)
              {
                  return std::tie(left.a, left.b, left.c, left.d) >
                         std::tie(right.a, right.b, right.c, right.d);
              });
    print_ips(ip_pool, [](const ip_filter &)
              { return true; }); // все
    print_ips(ip_pool, [](const ip_filter &ip)
              { return ip.a == 1; });
    print_ips(ip_pool, [](const ip_filter &ip)
              { return ip.a == 46 && ip.b == 70; });

    print_ips(ip_pool, [](const ip_filter &ip)
              { return ip.a == 46 || ip.b == 46 ||
                       ip.c == 46 || ip.d == 46; });
    return 0;
}
