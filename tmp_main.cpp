#include "containers/map.hpp"
#include "containers/vector.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <string>

#include <ctime>
#include <sys/time.h>

void test_vector_no_reserve()
{
    std::cout << "VECTOR -> 1000000000 insertions, 1000000000 deletions" << std::endl;
    
    struct timeval diff, startTV, endTV;

    {
        std::vector<int> vec;
        std::cout << "STD: " << std::flush;
        gettimeofday(&startTV, NULL);
        
        for (int i = 0; i < 1000000000; ++i) {
            vec.push_back(i);
        }
        for (int i = 0; i < 1000000000; ++i) {
            vec.pop_back();
        }
        
        gettimeofday(&endTV, NULL);
        timersub(&endTV, &startTV, &diff);
        std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
    }
    
    
    ft::vector<int> vec2;
    std::cout << "FT: " << std::flush;
    gettimeofday(&startTV, NULL);
    
    for (int i = 0; i < 1000000000; ++i) {
        vec2.push_back(i);
    }
    for (int i = 0; i < 1000000000; ++i) {
        vec2.pop_back();
    }
    
    gettimeofday(&endTV, NULL);
    timersub(&endTV, &startTV, &diff);
    std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void test_vector_reserve()
{
    std::cout << "VECTOR -> 1000000000 insertions, 1000000000 deletions (pre-allocated)" << std::endl;
    
    struct timeval diff, startTV, endTV;
    
    {
        std::vector<int> vec;
        vec.reserve(1000000000);
        std::cout << "STD: " << std::flush;
        gettimeofday(&startTV, NULL);
        
        for (int i = 0; i < 1000000000; ++i) {
            vec.push_back(i);
        }
        for (int i = 0; i < 1000000000; ++i) {
            vec.pop_back();
        }
        
        gettimeofday(&endTV, NULL);
        timersub(&endTV, &startTV, &diff);
        
        std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
    }
    
    ft::vector<int> vec2;
    vec2.reserve(1000000000);
    std::cout << "FT: " << std::flush;
    gettimeofday(&startTV, NULL);
    
    for (int i = 0; i < 1000000000; ++i) {
        vec2.push_back(i);
    }
    for (int i = 0; i < 1000000000; ++i) {
        vec2.pop_back();
    }
    
    gettimeofday(&endTV, NULL);
    timersub(&endTV, &startTV, &diff);
    std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void test_map()
{
    std::cout << "MAP -> 10000000 insertions, 10000000 deletions" << std::endl;
    
    struct timeval diff, startTV, endTV;
    
    // std::map<int, int> map;
    // std::cout << "STD: " << std::flush;
    // gettimeofday(&startTV, NULL);
    
    // for (int i = 0; i < 10000000; ++i) {
    //     map[i] = i;
    // }
    // for (int i = 0; i < 10000000; ++i) {
    //     map.erase(i);
    // }
    
    // gettimeofday(&endTV, NULL);
    // timersub(&endTV, &startTV, &diff);
    
    // std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
    
    ft::map<int, int> map2;
    std::cout << "FT: " << std::flush;
    gettimeofday(&startTV, NULL);
    
    for (int i = 0; i < 10000000; ++i) {
        map2[i] = i;
    }
    for (int i = 0; i < 10000000; ++i) {
        map2.erase(i);
    }
    
    gettimeofday(&endTV, NULL);
    timersub(&endTV, &startTV, &diff);
    std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

void test_map_random()
{
    std::cout << "MAP -> 10000000 insertions, 10000000 deletions (random keys)" << std::endl;
    
    srand(0);
    
    struct timeval diff, startTV, endTV;
    
    {
        std::map<int, int> map;
        std::cout << "STD: " << std::flush;
        gettimeofday(&startTV, NULL);
        
        for (int i = 0; i < 10000000; ++i) {
            map[rand()] = i;
        }
        for (int i = 0; i < 10000000; ++i) {
            map.erase(map.begin());
        }
        
        gettimeofday(&endTV, NULL);
        timersub(&endTV, &startTV, &diff);
        
        std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
    }
    
    srand(0);
    ft::map<int, int> map2;
    std::cout << "FT: " << std::flush;
    gettimeofday(&startTV, NULL);
    
    for (int i = 0; i < 10000000; ++i) {
        map2[rand()] = i;
    }
    for (int i = 0; i < 10000000; ++i) {
        map2.erase(map2.begin());
    }
    
    gettimeofday(&endTV, NULL);
    timersub(&endTV, &startTV, &diff);
    std::cout << diff.tv_sec << "." << diff.tv_usec << " seconds" << std::endl;
}

int main()
{
    // test_vector_no_reserve();
    // test_vector_reserve();
    test_map();
    test_map_random();
    
    return 0;
}
