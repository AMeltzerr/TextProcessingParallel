#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace chrono;

map<string, int> frecventaGlobala;

mutex mtx;

void proceseazaText(vector<string> cuvinte)
{
    map<string, int> frecventaLocala;

    for (string cuvant : cuvinte)
    {
        string curat = "";

        for (char c : cuvant)
        {
            if (isalpha(c))
            {
                curat += tolower(c);
            }
        }

        if (!curat.empty())
        {
            frecventaLocala[curat]++;
        }
    }

    // Blocam accesul simultan
    lock_guard<mutex> lock(mtx);

    for (auto x : frecventaLocala)
    {
        frecventaGlobala[x.first] += x.second;
    }
}

int main()
{
    auto start = high_resolution_clock::now();

    ifstream file("text.txt");

    if (!file)
    {
        cout << "Fisierul nu poate fi deschis!";
        return 1;
    }

    vector<string> toateCuvintele;

    string cuvant;

    while (file >> cuvant)
    {
        toateCuvintele.push_back(cuvant);
    }

    file.close();

    int numarThreaduri = 4;

    vector<thread> threads;

    int dimensiune = toateCuvintele.size() / numarThreaduri;

    for (int i = 0; i < numarThreaduri; i++)
    {
        int startIndex = i * dimensiune;

        int endIndex;

        if (i == numarThreaduri - 1)
        {
            endIndex = toateCuvintele.size();
        }
        else
        {
            endIndex = startIndex + dimensiune;
        }

        vector<string> parte(
            toateCuvintele.begin() + startIndex,
            toateCuvintele.begin() + endIndex
        );

        threads.push_back(thread(proceseazaText, parte));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << "Frecventa cuvintelor:\n\n";

    for (auto x : frecventaGlobala)
    {
        cout << x.first << " -> " << x.second << endl;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nTimp executie paralel: "
        << duration.count()
        << " ms";

    return 0;
}