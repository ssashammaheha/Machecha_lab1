
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <limits>

struct Pipe
{
    int id = 0;
    std::string name;
    double length;
    int diameter;
    bool inRepair;
    bool est;
};

struct CompressorStation
{
    int id = 0;
    std::string name;
    int workshopCount;
    int workingWorkshops;
    int stationClass;
    bool est;
};

void showPipe(Pipe pipe)
{
    std::cout << "ID: " << pipe.id << '\n';
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
    std::cout << "ID: " << cs.id << '\n';
    std::cout << "name: " << cs.name << std::endl;

    std::cout << "kol-vo compreesor: "
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
    std::cin.ignore();
    std::getline(std::cin, pipe.name,'\n');
    


    std::cout << "enter length:";
    while (!(std::cin >> pipe.length) || std::cin.peek() != '\n' || pipe.length <= 0)
    {
        std::cout << "nelza\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::cout << "enter diametr:"; 
    while (!(std::cin >> pipe.diameter) || std::cin.peek() != '\n' || (pipe.diameter <= 0))
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
    }
 
    std::cout << "is repair 1-da 0-net:";
    while (!(std::cin >> pipe.inRepair) || std::cin.peek() != '\n' || (pipe.inRepair < 0) || (pipe.inRepair > 1))
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    pipe.est = true;
}

void createCompressorStation(CompressorStation& cs)
{
    std::cout << "enter name:";
    std::cin.ignore();
    std::getline(std::cin, cs.name);


    std::cout << "kol-vo compressors:";
    while (!(std::cin >> cs.workshopCount) || std::cin.peek() != '\n' || (cs.workshopCount <= 0))
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');

    }


    std::cout << "seyichas rabotayut:";
    while (!(std::cin >> cs.workingWorkshops) || std::cin.peek() != '\n' || (cs.workingWorkshops < 0) || (cs.workingWorkshops > cs.workshopCount))
    {
        std::cout << "Vvedite chislo ot 0 do " << cs.workshopCount << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }


    std::cout << "klass 1-moshnaya 2-slabee 3-samaya slabaya: ";
    while (!(std::cin >> cs.stationClass) || std::cin.peek() != '\n' || cs.stationClass < 1 || cs.stationClass > 3)
    {
        std::cout << "Wrong value. Enter 1, 2 or 3: " << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    cs.est = true;
}

void changeRepair(Pipe& pipe)
{
    std::cout << "change repair 1 - v remonte 0 - rabotaet :";
    while (!(std::cin >> pipe.inRepair) || std::cin.peek() != '\n' || (pipe.inRepair < 0) || (pipe.inRepair > 1))
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
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
    std::ofstream file("data.txt", std::ios::app);
    if (file)
    {
        file << "PIPE" << std::endl;
        file << pipe.name << std::endl;
        file << pipe.length << std::endl;
        file << pipe.diameter << std::endl;
        file << pipe.inRepair << std::endl;
        file.close();
    }
    else
        std::cout << "kakie-to problems\n";
}

void loadPipe(Pipe& pipe)
{
    std::ifstream file("data.txt");
    if (file)
    {
        std::string type;
        while (std::getline(file, type))
        {
            if (type == "PIPE")
            {
                std::getline(file, pipe.name);
                if (file >> pipe.length >> pipe.diameter >> pipe.inRepair)
                {
                    pipe.est = true;
                    std::cout << "Pipe loaded\n";
                }
                else
                    std::cout << "Oshibka dannih\n";

                return;
            }
        }
        std::cout << "Truba ne naidena\n";
    }
    else
        std::cout << "kakie-to problems\n";
}

void saveCompressorStation(CompressorStation cs)
{
    std::ofstream file("data.txt", std::ios::app);
    if (file)
    {
        file << "COMPRESSOR" << std::endl;
        file << cs.name << std::endl;
        file << cs.workshopCount << std::endl;
        file << cs.workingWorkshops << std::endl;
        file << cs.stationClass << std::endl;
        file.close();
    }
    else
        std::cout << "kakie-to problems\n";
}

void loadCompressorStation(CompressorStation& cs)
{
    std::ifstream file("data.txt");
    if (file)
    {
        std::string type;

        while (std::getline(file, type))
        {
            if (type == "COMPRESSOR")
            {
                std::getline(file, cs.name);
                if (file >> cs.workshopCount >> cs.workingWorkshops >> cs.stationClass)
                {
                    cs.est = true;
                    std::cout << "Compressor loaded\n";
                }
                else
                    std::cout << "Oshibka dannih\n";
                return;
            }
        }
        std::cout << "Compressor ne naiden\n";
    }
    else
        std::cout << "kakie-to problems\n";
}
int main()
{
    std::map<int, Pipe> pipes;
    std::map<int, CompressorStation> stations;
    Pipe pipe = {};
    pipe.est = false;
    CompressorStation cs = {};
    cs.est = false;
    int nextId = 1;
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
        while (!(std::cin >> choice) || std::cin.peek() != '\n' || (choice < 0) || (choice > 7))
        {
            std::cout << "nelza" << '\n';
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        switch (choice)
        {
        case 1:
            createPipe(pipe);
            pipe.id = nextId;
            pipes.emplace(pipe.id, pipe);
            nextId++;
            std::cout << "Truba dobavlena. ID: " << pipe.id << '\n';
            std::cout << "Vsego trub: " << pipes.size() << '\n';
            break;

        case 2:
            createCompressorStation(cs);
            cs.id = nextId;
            stations.emplace(cs.id, cs);
            nextId++;
            std::cout << "KS dobavlena. ID: " << cs.id << '\n';
            std::cout << "Vsego KS: " << stations.size() << '\n';
            break;

        case 3:
        {
            if (pipes.empty() && stations.empty())
            {
                std::cout << "Truba i stanciya ne sozdany\n";
                break;
            }

            for (const auto& item : pipes)
            {
                std::cout << "\nPIPE\n";
                showPipe(item.second);
                std::cout << "\n";
            }

            for (const auto& item : stations)
            {
                std::cout << "\nCOMPRESSOR STATION\n";
                showCompressorStation(item.second);
                std::cout << "\n";
            }

            break;
        }
        case 4:
            if (pipe.est == false)
                std::cout << "net trubi\n";
            else
                changeRepair(pipe);
            break;


        case 5:
            if (cs.est == false)
                std::cout << "net compressor\n";
            else
            {
                std::cout << "zapustit station\n";
                startWorkshop(cs);
            }

            break;

        case 6:
        {
            if (pipe.est || cs.est)
            {
                std::ofstream("data.txt").close();
                if (pipe.est)
                {
                    savePipe(pipe);
                    std::cout << "Truba sohranena\n";
                }
                if (cs.est)
                {
                    saveCompressorStation(cs);
                    std::cout << "Compressor sohranen\n";
                }
            }
            else
                std::cout << "Net obektov dlya sohraneniya\n";

            break;
        }
        case 7:
        {
            std::ifstream file("data.txt");
            if (!file)
            {
                std::cout << "Fail ne naiden ili ne otkryvaetsya\n";
                break;
            }
            file.close();

            loadPipe(pipe);
            loadCompressorStation(cs);

            break;
        }

        case 0:
            return 0;


        default:
            std::cout << "viberi drugoe\n";
        }
    }
}