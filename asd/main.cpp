#include <string>
#include <iostream>

#include "Stack.h"
#include "Map.h"
#include "MapIterator.h"
#include "Invoice.cpp"

std::string getHeader(size_t suffix) {
    std::string result = "#\tName";

    for (size_t i = 0; i < suffix; i++)
        result += " ";

    result += "Cost";

    return result;
}

int main() {
    // #    Name                    Cost    Other stuff..
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah
    Map<int, Invoice> map;
    for (size_t i = 0; i < 10; i++)
    {
        auto invoice = Invoice();
        invoice.id = i + 100;
        invoice.name = "Factura " + std::to_string(invoice.id);
        invoice.cost = 20 + i;
        map.add(invoice.id, invoice);
    }

    std::string output;
    size_t maxLength = 0;

    for (auto iter = map.iterator(); iter.valid(); iter.next())
    {
        auto p = iter.getCurrent();
        output += std::to_string(p.second.id);
        output += "\t";
        output += p.second.name;
        output += "\t";
        output += std::to_string(p.second.cost);
        output += "\n";

        if (p.second.name.length() > maxLength)
            maxLength = p.second.name.length();
    }

    std::cout << getHeader(maxLength + 1) << std::endl;
    std::cout << output << std::endl;

    return 0;
}