#include <iostream>

#include "dsa/hash_table.hpp"

int main()
{
    dsa::HashTable<std::string> phonebook{{{"John Smith", "521-1234"},
                                           {"Lisa Smith", "521-8976"}}};
    std::cout << "Initialized `phonebook` as {\n"
              << "  \"John Smith\": \"521-1234\",\n"
              << "  \"Lisa Smith\": \"521-8976\"\n"
              << "}\n\n";

    // searching
    std::cout << "phonebook[\"John Smith\"] == \"" << phonebook["John Smith"] << "\"\n";
    std::cout << "phonebook[\"Lisa Smith\"] == \"" << phonebook["Lisa Smith"] << "\"\n";
    std::cout << "phonebook[\"Sandra Dee\"] == \"" << phonebook["Sandra Dee"] << "\"\n\n";

    // inserting (setting)
    phonebook["Sandra Dee"] = "521-9655";
    std::cout << "Set phonebook[\"Sandra Dee\"] = \"521-9655\"\n";
    std::cout << "phonebook[\"Sandra Dee\"] == \"" << phonebook["Sandra Dee"] << "\"\n\n";

    // deleting
    phonebook.remove("Lisa Smith");
    std::cout << "phonebook.remove(\"Lisa Smith\")\n";
    std::cout << "phonebook[\"Lisa Smith\"] == \"" << phonebook["Lisa Smith"] << "\"\n";
}
