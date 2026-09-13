
#include <iostream>
#include <string>
#include <fstream>

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
void savePipe(Pipe pipe)
{
    std::ofstream file("pipe.txt");
    file << pipe.name << std::endl;
    file << pipe.length << std::endl;
    file << pipe.diameter << std::endl;
    file << pipe.inRepair << std::endl;
    file.close();
}
void loadPipe(Pipe& pipe)
{
    std::ifstream file("pipe.txt");
    file >> pipe.name;
    file >> pipe.length;
    file >> pipe.diameter;
    file >> pipe.inRepair;
    file.close();
}
void saveCompressorStation(CompressorStation cs)
{
    std::ofstream file("cs.txt");
    file << cs.name << std::endl;
    file << cs.workshopCount << std::endl;
    file << cs.workingWorkshops << std::endl;
    file << cs.stationClass << std::endl;
    file.close();
}
void loadCompressorStation(CompressorStation& cs)
{
    std::ifstream file("cs.txt");
    file >> cs.name;
    file >> cs.workshopCount;
    file >> cs.workingWorkshops;
    file >> cs.stationClass;
    file.close();
}
int main()
{
    Pipe pipe;
    CompressorStation cs;
    int choice;
    while (true)
    {
        std::cout << "======================================\n";
        std::cout << "1. Dobavit pipe\n";
        std::cout << "2. Dobavit compressor station\n";
        std::cout << "3. Show all objects\n";
        std::cout << "4. Edit pipe\n";
        std::cout << "5. Zapustit station\n";
        std::cout << "6. Save\n";
        std::cout << "7. Zagruzit from file\n";
        std::cout << "0. Exit\n";
        std::cout << "======================================\n";
        std::cout << "Choose action: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            createPipe(pipe);
            break;

        case 2:
            createCompressorStation(cs);
            break;

        case 3:
            std::cout << "PIPE\n";
            showPipe(pipe);
            std::cout << "\n";
            std::cout << "COMPRESSOR STATION\n";
            showCompressorStation(cs);
            break;

        case 4:
            changeRepair(pipe);
            break;


        case 5:
            std::cout << "zapustit station\n";
            startWorkshop(cs);
            break;

        case 6:
            savePipe(pipe);
            saveCompressorStation(cs);
            std::cout << "Saved\n";
            break;

        case 7:
            loadPipe(pipe);
            loadCompressorStation(cs);
            std::cout << "Loaded\n";
            break;

        case 0:
            return 0;


        default:
            std::cout << "viberi drugoe\n";
        }
    }
}