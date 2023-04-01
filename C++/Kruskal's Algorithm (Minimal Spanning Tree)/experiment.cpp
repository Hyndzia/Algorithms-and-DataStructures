#include "MST(only for experiment).h"
#include <iostream>

//path to data files
std::string g1 = "C:\\Users\\Suwa\\Desktop\\g1.txt";
std::string g2 = "C:\\Users\\Suwa\\Desktop\\g2.txt";
std::string g3 = "C:\\Users\\Suwa\\Desktop\\g3.txt";
// 

int main() {
    auto graph1 = Graph(g1);
    auto graph2 = Graph(g2);
    auto graph3 = Graph(g3);
    std::cout << "KRUSKAL'S ALGORITHM\n\n";
    std::cout << "\n**************************************************************************************\n\n";
    std::cout << "<GRAPH #1>\n";
    std::cout << graph1.stats() << "\n";
    std::cout << "<MST>\n";
    Graph MST = MST_Kruskal(graph1, false, false);
    std::cout << "\n<union by rank with path compression>\n";

    MST = MST_Kruskal(graph1, true, true);
    std::cout << "\n<union by rank without path compression>\n";

    MST = MST_Kruskal(graph1, true, false);
    std::cout << "\n<standard union with path compression>\n";

    MST = MST_Kruskal(graph1, false, true);
    std::cout << "\n" << MST.stats();
    std::cout << "\n**************************************************************************************\n\n";
    std::cout << "<GRAPH #2>\n";
    std::cout << graph2.stats() << "\n";
    std::cout << "<MST>\n";
    MST = MST_Kruskal(graph2, false, false);
    std::cout << "\n<union by rank with path compression>\n";

    MST = MST_Kruskal(graph2, true, true);
    std::cout << "\n<union by rank without path compression>\n";

    MST = MST_Kruskal(graph2, true, false);
    std::cout << "\n<standard union with path compression>\n";

    MST = MST_Kruskal(graph2, false, true);
    std::cout << "\n" << MST.stats();
    std::cout << "\n**************************************************************************************\n\n";
    std::cout << "<GRAPH #3>\n";
    std::cout << graph3.stats() << "\n";
    std::cout << "<MST>\n";
    MST = MST_Kruskal(graph3, false, false);
    std::cout << "\n<union by rank with path compression>\n";

    MST = MST_Kruskal(graph3, true, true);
    std::cout << "\n<union by rank without path compression>\n";

    MST = MST_Kruskal(graph3, true, false);
    std::cout << "\n<standard union with path compression>\n";

    MST = MST_Kruskal(graph3, false, true);
    std::cout << "\n" << MST.stats();
    std::cout << "\n**************************************************************************************\n\n";

    return 0;
}