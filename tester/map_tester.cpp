#include "tester.hpp"

void testMap(void) {
    ft::map<int, int> mp;
    struct timeval diff, start, end;
    gettimeofday(&start, NULL);

    mp[1] = 1;
    mp[2] = 2;
    mp[3] = 3;
    std::cout << "Tested constructor" << std::endl;
    std::cout << "Tested operator[]" << std::endl;
    if (mp.begin()->first == mp.at(1))
        std::cout << "Tested begin\n" << "Tested at" << std::endl;

    ft::map<int, int> mp2 = mp;
    std::cout << "Tested operator=" << std::endl;
    ft::map<int, int>::iterator it = mp2.begin();
    ft::map<int, int>::iterator ite = mp2.end();
    ite--;

    ft::map<int, int>::reverse_iterator it1 = mp2.rbegin();
    ft::map<int, int>::reverse_iterator it2 = mp2.rend();
    it2--;
    if (it1->first == ite->first && it->first == it2->first) {
        std::cout << "Tested end" << std::endl << "Tested rbegin" << std::endl;
        std::cout << "Tested rend" << std::endl;
    }
    mp.clear();
    if (mp.empty() && !mp.size()) {
        std::cout << "Tested clear" << std::endl << "Tested empty" << std::endl;
        std::cout << "Tested size" << std::endl;
    }

    mp.insert(ft::pair<int, int>(4, 4));
    mp.insert(mp.end(), ft::pair<int, int>(5, 5));
    it = mp.begin();
    ite = mp.end();
    ite--;
    if (it->first == 4 && ite->first == 5)
        std::cout << "Tested insert" << std::endl;

    mp.erase(ite);
    mp.erase(4);
    it = mp2.begin();
    ite = mp2.end();
    mp2.erase(it, ite);
    if (mp.empty() && mp2.empty())
        std::cout << "Tested erase" << std::endl;

    for (int i = 0; i < 3; i++)
        mp[i] = i;
    for (int i = 3; i < 6; i++)
        mp2[i] = i;

    mp.swap(mp2);
    it = mp.begin();
    if (it->first == 3)
        std::cout << "Tested swap" << std::endl;

    if (mp.count(0) == 0 && mp.count(3) == 1)
        std::cout << "Tested count" << std::endl;

    if (mp.find(3) == it)
        std::cout << "Tested find" << std::endl;

    ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ret;
    ret = mp.equal_range(4);
    if (ret.first->first == 4 && ret.second->first == 5) {
        std::cout << "Test lower_bound" << std::endl;
        std::cout << "Tested upper_bound" << std::endl;
        std::cout << "Tested equal_range" << std::endl;
    }

    mp[1] = 1;
    mp[2] = 2;


    ft::map<int, int>::iterator itLow = mp.lower_bound(3);
    ft::map<int, int>::iterator itUp = mp.upper_bound(3);
    std::cout << itLow->first << "   " << itUp->first << std::endl;
    mp.erase(itLow, itUp);

    it = mp.begin();
    for (; it != mp.end(); it++)
        std::cout << it->first;

    it = mp.begin();
    ft::map<int, int>::const_iterator iter = mp.begin();
    if (it == mp.begin())
        std::cout << "LOLILOL\n";

    // int test = 1000000;
    // for (int i = 0; i < test; i++)
    //     mp[i] = i;
    // for (int i = 0; i < test; i++)
    //     mp.erase(i);

    
    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);

    std::cout << BOLD << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "FT::MAP: " << diff.tv_sec << ".";
    std::cout << diff.tv_usec << " seconds" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << END << std::endl;
}