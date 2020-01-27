#include <iostream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


int main()
{
    using namespace rapidxml;
    file<> xmlFile("lake_col.svg"); // Default template is char
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    // Printing.
    //std::cout << doc << std::endl;

    std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    xml_node<>* node = doc.first_node("svg");
    std::cout << "Node foobar has value " << node->value() << "\n";
    for (xml_attribute<>* attr = node->first_attribute();
        attr; attr = attr->next_attribute())
    {
        std::cout << "Node foobar has attribute " << attr->name() << " ";
        std::cout << "with value " << attr->value() << "\n";
    }
}


