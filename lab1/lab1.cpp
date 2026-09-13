
#include <iostream>
#include <string>

struct Pipe
{
    std::string name;
    double length;
    int diameter;
    bool inRepair;
};

struct CompressorStation
{
    std::string name;
    int workshopCount;
    int workingWorkshops;
    int stationClass;
};

void showPipe(Pipe pipe)
{
    std::cout << "name: " << pipe.name << std::endl;

    std::cout << "lenght: "
        << pipe.length
        << " km"
        << std::endl;

    std::cout << "diametr: "
        << pipe.diameter
        << " mm"
        << std::endl;

    std::cout << "is repair: ";

    if (pipe.inRepair)
    {
        std::cout << "da";
    }
    else
    {
        std::cout << "net";
    }
}
void showCompressorStation(CompressorStation cs)
{
    std::cout << "name: " << cs.name << std::endl;

    std::cout << "kol-vo nasosov: "
        << cs.workshopCount
        << " pcs."
        << std::endl;

    std::cout << "rabotayut "
        << cs.workingWorkshops
        << " pcs."
        << std::endl;

    std::cout << "klass station "
        << cs.stationClass
        << std::endl;

    
}
void createPipe(Pipe& pipe)
{
    std::cout << "enter name:";
    std::cin >> pipe.name;


    std::cout << "enter length:";
    std::cin >> pipe.length;


    std::cout << "enter diametr:";
    std::cin >> pipe.diameter;


    std::cout << "is repair: 1-da 0-net";
    std::cin >> pipe.inRepair;
}

void createCompressorStation(CompressorStation& cs)
{
    std::cout << "enter name:";
    std::cin >> cs.name;


    std::cout << "kol-vo nasosov:";
    std::cin >> cs.workshopCount;


    std::cout << "seyichas rabotayut:";
    std::cin >> cs.workingWorkshops;

    while (cs.workshopCount < cs.workingWorkshops)
    {
        std::cout << "ne mozhet rabotat stolko stations: ";
        std::cin >> cs.workingWorkshops;
    }


    std::cout << "klass: 1-moshnaya 2-slabee 3-samaya slabaya ";
    std::cin >> cs.stationClass;

    while (cs.stationClass < 1 || cs.stationClass > 3)
    {
        std::cout << "Wrong value. Enter 1, 2 or 3: ";
        std::cin >> cs.stationClass;
    }
}

void changeRepair(Pipe& pipe)
{
    std::cout << "change repair 1 - v remonte 0 - rabotaet :";

    std::cin >> pipe.inRepair;
}

void startWorkshop(CompressorStation& cs)
{
    if (cs.workingWorkshops < cs.workshopCount)
    {
        cs.workingWorkshops++;

        std::cout << "Workshop started\n";
    }
    else
    {
        std::cout << "All workshops are already working\n";
    }
}

int main()
{

    Pipe pipe2;
    createPipe(pipe2);
    showPipe(pipe2);
    std::cout << '\n';

    changeRepair(pipe2);
    showPipe(pipe2);
    std::cout << '\n';

    CompressorStation cs1;
    createCompressorStation(cs1);
    showCompressorStation(cs1);
}
