#include <map>

#include "SortedMap.h"
#include "SortedMapIterator.h"

int main() {

    SortedMap<int, std::string> maplol;

    maplol.set(3, "Hello");
    maplol.set(15, "?");
    maplol.set(5, "World");
    maplol.set(8, "!");

    // map.delete(15);

    auto x = maplol.get(15);

    std::cout << x << std::endl;

    SortedMapIterator<int, std::string> iter = SortedMapIterator<int, std::string>(maplol);


    for (; iter.valid(); iter.next())
    {
        std::cout << iter.getCurrent().second << std::endl;
    }


    return 0;
}