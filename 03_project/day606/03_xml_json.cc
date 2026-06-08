#include <iostream>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;
using namespace nlohmann;
using json = nlohmann::json;

const char* xmlstring = R"(
    <library>
        <book id="B001">
            <title>三体</title>
            <author>刘慈欣</author>
            <year>2008</year>
            <price currency="CNY">68.00</price>
        </book>
        <book id="B002">
            <title>百年孤独</title>
            <author>加西亚·马尔克斯</author>
            <year>2011</year>
            <price currency="CNY">55.00</price>
        </book>
    </library>
)";

int main(int argc,char *argv[])
{
    // 解析xml字符串
    XMLDocument doc;
    if(doc.Parse(xmlstring) != XML_SUCCESS)
    {
        cerr << "Failed to parse XML string " << endl;
        return -1;
    }

    // 获取library根元素
    XMLElement *library = doc.FirstChildElement();
    if(!library)
    {
        cerr << "No library element found" << endl;
        return -1;
    }

    // 解析所有book元素，添加到result数组
    json result = json::array();
    XMLElement *book = library->FirstChildElement("book");
    while(book)
    {
        json bookjson;
        // 获取属性id
        const char *id = book->Attribute("id");
        if(id)
        {
            bookjson["@id"] = id;
        }
        // 获取子元素 title
        XMLElement *title = book->FirstChildElement("title");
        if(title)
        {
            bookjson["title"] = title->GetText();
        }
        // 获取子元素author
        XMLElement *author = book->FirstChildElement("author");
        if(author)
        {
            bookjson["author"] = author->GetText();
        }
        // 获取子元素 year
        XMLElement *year = book->FirstChildElement("year");
        if(year)
        {
            bookjson["year"] = year->GetText();
        }
        // 获取子元素price 及其属性
        XMLElement *price = book->FirstChildElement("price");
        if(price)
        {
            json priceJson;
            // 获取currency属性
            const char *currency = price->Attribute("currency");
            if(currency)
            {
                priceJson["@currency"] = currency;
            }
            // 获取price的文本内容
            const char *text = price->GetText();
            if(text)
            {
                priceJson["value"] = stod(text);
            }
            bookjson["price"] = priceJson;
        }
        // 将bookjson追加到result数组
        result.push_back(bookjson);
        // 获取下一个book元素
        book = book->NextSiblingElement("book");
    }
    cout << result.dump(2) << endl;

    return 0;
}
