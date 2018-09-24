/* Sample tester
 * We've included vector below to show you how your types should behave.
 * You can use that for debugging.
 * As in the assignment description, if you use the std::vector for your submitted code,
 * you will get a 0.
 */

#include "BigInteger.h"
#include "MyVector.h"

int main()
{
    MyVector<int> v;

    cout << v.size() << endl;
    v.push_back(4000);
    cout << v.at(0) << endl;
    cout << v.capacity() << endl;
    v.reserve(10);
    cout << v.capacity() << endl;
    v.push_back(200);
    v.push_back(100);
    v.insert(v.begin(), 3);
    v.insert(v.end(), 20);

    int j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        cout << v.at(j) << endl;
        j++;
    }

    j = 0;
    for(auto i = 0; i < v.size(); i++)
    {
        cout << v[j] << endl;
        j++;
    }

    /*std::string init_string("2342323492423");

    BigInteger my_big_int(init_string);

    BigInteger another_big_int = my_big_int;
    BigInteger yet_another_big_int(my_big_int);

    my_big_int = another_big_int + yet_another_big_int;

    my_big_int = another_big_int = yet_another_big_int - my_big_int;*/


    return 0;
}

