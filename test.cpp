// #include "DataEngine.h"
#include "DecisionTree.h"
using namespace std;
std::string tableAttrib = "create table dataTable (age INTEGER, workclass TEXT, fnlwgt INTEGER,"
" education TEXT, education_num INTEGER, marital_status TEXT,"
" occupation TEXT, relationship TEXT, race TEXT, sex TEXT,"
" capital_gain INTEGER, capital_loss INTEGER,"
" hours_per_week INTEGER, native_country TEXT, result TEXT)";
std::vector<std::string> contAttributes;
// std::string tableAttrib = "create table dataTable (outlook TEXT, temperature TEXT, humidity TEXT, wind TEXT, playtennis TEXT)";

std::string dataPath = "../adult.data";

// std::string dataPath = "../playtennis.csv";


std::vector<std::string> split(const std::string &text, std::string sep)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + sep.length();
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
std::string testDataPath = "../adult.test";

void parseData(DecisionTree &decisionTree)
{
    std::ifstream input(testDataPath);
    std::vector<std::string> result;
    std::string resultString;
    std::string line;

    if (input.is_open()) {
        while (getline(input, line)) {
            if (line.find('?') != std::string::npos) { //ignore missing for now
                continue;
            }
            result = split(line, ", ");

            // cout << line <<endl;
            vector<ItemPair> instanceList;

            instanceList.push_back(make_pair("age", result[0]));
            instanceList.push_back(make_pair("workclass", "'" +result[1]+"'"));
            instanceList.push_back(make_pair("education", "'"+ result[3] + "'"));
            instanceList.push_back(make_pair("marital_status", "'"+result[5]+"'"));
            instanceList.push_back(make_pair("occupation", "'"+result[6]+"'"));
            instanceList.push_back(make_pair("relationship", "'"+result[7]+"'"));
            instanceList.push_back(make_pair("race", "'"+result[8]+"'"));
            instanceList.push_back(make_pair("sex", "'"+result[9]+"'"));
            instanceList.push_back(make_pair("capital_gain", result[10]));
            instanceList.push_back(make_pair("capital_loss", result[11]));
            instanceList.push_back(make_pair("hours_per_week", result[12]));
            instanceList.push_back(make_pair("native_country", "'"+result[13]+"'"));

            cout << decisionTree.evaluateInstance(&decisionTree.myRoot, instanceList)<<endl;
        }
    }
}

typedef std::pair<std::string, std::string> ItemPair;
int main()
{
    std::vector<std::string> v;
    v.push_back("age");
    v.push_back("workclass");
    v.push_back("education");
    v.push_back("marital_status");
    v.push_back("occupation");
    v.push_back("relationship");
    v.push_back("race");
    v.push_back("sex");
    v.push_back("capital_gain");
    v.push_back("capital_loss");
    // v.push_back("fnlwgt");
    v.push_back("hours_per_week");
    v.push_back("native_country");

    contAttributes.push_back("age");
    contAttributes.push_back("fnlwgt");
    contAttributes.push_back("capital_gain");
    contAttributes.push_back("capital_loss");
    contAttributes.push_back("hours_per_week");
    // DecisionTree decisionTree0(v, contAttributes, dataPath, tableAttrib, "result", "<=50K", ">50K");

    DecisionTree decisionTree(v, contAttributes, dataPath, tableAttrib, "result", "<=50K", ">50K", false);
    ifstream input("rule_base");
    queue<ItemPair> ruleQueue;
    string line;
    int i =0;


    for (; getline(input, line);) {
        // std::cout <<line <<std::endl;
        if (line == "RULE: ") {
            // std::cout << i++ << std::endl;
            decisionTree.buildTreeFromRule(&decisionTree.myRoot, ruleQueue);
            while(!ruleQueue.empty()) {
                ruleQueue.pop();
            }
            continue;
        }
        istringstream iss(line);
        string attribute, attributeValue;
        iss >> attribute >> attributeValue;
        ItemPair tempPair;
        tempPair = make_pair(attribute, attributeValue);
        ruleQueue.push(tempPair);
    }
    cout << "Tree built!" <<endl;
    parseData(decisionTree);
    // decisionTree.traverseTree(&decisionTree.myRoot, "");


    // vector<ItemPair> instanceList;

    // instanceList.push_back(make_pair("age", "60"));
    // instanceList.push_back(make_pair("workclass", "Private"));
    // instanceList.push_back(make_pair("education", "'11th'"));
    // instanceList.push_back(make_pair("marital_status", "'Never-married'"));
    // instanceList.push_back(make_pair("occupation", "'Machine-op-inspct'"));
    // instanceList.push_back(make_pair("relationship", "'Own-child'"));
    // instanceList.push_back(make_pair("race", "'Black'"));
    // instanceList.push_back(make_pair("sex", "'Male'"));
    // instanceList.push_back(make_pair("capital_gain", "0"));
    // instanceList.push_back(make_pair("capital_loss", "0"));
    // instanceList.push_back(make_pair("hours_per_week", "40"));
    // instanceList.push_back(make_pair("native_country", "'United-States'"));


    // cout << decisionTree.evaluateInstance(&decisionTree.myRoot, instanceList);
    return 0;
}
