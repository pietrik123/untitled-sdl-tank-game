#include <iostream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

class RapidXmlWrapper
{
public:
    rapidxml::file<> _xmlFile;
    rapidxml::xml_document<> _doc;

    RapidXmlWrapper(const char* fileName)
        :_xmlFile{ fileName }
    {
        _doc.parse<0>(_xmlFile.data());
    }
    void printNodeAttributes(const rapidxml::xml_node<>* node);
    void printNodes();
    void printAttrubutesOfNode(const char* name);
};

void RapidXmlWrapper::printNodeAttributes(const rapidxml::xml_node<>* node)
{
    std::cout << "Printing attributes for \" " << node->name() << "\"\n";
    std::cout << "Node " << node->name() << " has value " << node->value() << "\n";
    for (rapidxml::xml_attribute<>* attr = node->first_attribute();
        attr; attr = attr->next_attribute())
    {
        std::cout << "Attribute = " << attr->name() << " ";
        std::cout << ", value = " << attr->value() << "\n";
    }
}

void RapidXmlWrapper::printNodes()
{
    for (rapidxml::xml_node<>* node = _doc.first_node()->first_node(); node; node = node->next_sibling())
    {
        std::cout << node->name() << std::endl;
    }
}
void RapidXmlWrapper::printAttrubutesOfNode(const char* name)
{
    for (rapidxml::xml_node<>* node = _doc.first_node()->first_node(); node; node = node->next_sibling())
    {
        if (*(node->name()) == *name)
        {
            printNodeAttributes(node);
        }
    }
}



int main()
{
    std::cout << "creating my wrapper..." << std::endl;
    RapidXmlWrapper xmlwrapper("lake_col.svg");
    auto firstNode = xmlwrapper._doc.first_node();
    xmlwrapper.printAttrubutesOfNode("circle");
}


