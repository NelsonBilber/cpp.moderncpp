//from : "the c++ programming language"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Randon
{
public:
    Randon(int low, int high): dist{ low, high}{}
    int operator()(){return dist(re);}
private:
    default_random_engine re;
    uniform_int_distribution<> dist;
};

int main()
{
    Randon ran {0,4};
    vector<int> histograms(5);
    for (int i = 0; i!= 200; ++i) {
        ++histograms[ran()];
    }
    
    for(int i = 0; i < histograms.size(); i++){
        std::cout << "value = " << histograms[i] << std::endl;
    }
    
    return 0;
}

