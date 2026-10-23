
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <limits>
#include <iomanip>
#include <cmath>
#include <utility>

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
void savePipe(std::ofstream& file, const Pipe& pipe)
{
    file << "PIPE" << '\n';
    file << pipe.id << '\n';
    file << pipe.name << '\n';
    file << pipe.length << '\n';
    file << pipe.diameter << '\n';
    file << pipe.inRepair << '\n';
}
bool loadPipe(std::ifstream& file, Pipe& pipe)
{
    if (!(file >> pipe.id))
        return false;

    file.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    if (!std::getline(file, pipe.name))
        return false;

    int repair;

    if (!(file >> pipe.length >> pipe.diameter >> repair))
        return false;

    if (pipe.id <= 0
        || pipe.name.empty()
        || !std::isfinite(pipe.length)
        || pipe.length <= 0
        || pipe.diameter <= 0
        || (repair != 0 && repair != 1))
    {
        return false;
    }

    pipe.inRepair = (repair == 1);
    pipe.est = true;

    file.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}

void saveCompressorStation(
    std::ofstream& file,
    const CompressorStation& cs)
{
    file << "COMPRESSOR" << '\n';
    file << cs.id << '\n';
    file << cs.name << '\n';
    file << cs.workshopCount << '\n';
    file << cs.workingWorkshops << '\n';
    file << cs.stationClass << '\n';
}
bool loadCompressorStation(
    std::ifstream& file,
    CompressorStation& cs)
{
    if (!(file >> cs.id))
        return false;

    file.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    if (!std::getline(file, cs.name))
        return false;

    if (!(file >> cs.workshopCount
        >> cs.workingWorkshops
        >> cs.stationClass))
    {
        return false;
    }

    if (cs.id <= 0
        || cs.name.empty()
        || cs.workshopCount <= 0
        || cs.workingWorkshops < 0
        || cs.workingWorkshops > cs.workshopCount
        || cs.stationClass < 1
        || cs.stationClass > 3)
    {
        return false;
    }

    cs.est = true;

    file.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
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
        {
            if (pipes.empty())
            {
                std::cout << "Net trub\n";
                break;
            }
            int id;
            std::cout << "Vvedite ID truby: ";
            while (!(std::cin >> id)
                || std::cin.peek() != '\n'
                || id <= 0)
            {
                if (std::cin.eof())
                    return 0;
                std::cout << "Vvedite celoe polozhitelnoe chislo: ";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
            }
            auto it = pipes.find(id);
            if (it == pipes.end())
            {
                std::cout << "Truba s takim ID ne naidena\n";
            }
            else
            {
                changeRepair(it->second);
                std::cout << "Sostoyanie truby izmeneno\n";
            }

            break;
        }
        case 5:
        {
            if (stations.empty())
            {
                std::cout << "Net compressor stations\n";
                break;
            }

            int id;

            std::cout << "Vvedite ID compressor station: ";

            while (!(std::cin >> id)
                || std::cin.peek() != '\n'
                || id <= 0)
            {
                if (std::cin.eof())
                    return 0;

                std::cout << "Vvedite celoe polozhitelnoe chislo: ";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
            }

            auto it = stations.find(id);

            if (it == stations.end())
            {
                std::cout << "Station s takim ID ne naidena\n";
            }
            else
            {
                startWorkshop(it->second);
            }

            break;
        }
        case 6:
        {
            if (pipes.empty() && stations.empty())
            {
                std::cout << "Net obektov dlya sohraneniya\n";
                break;
            }

            std::string filename;

            std::cout << "Vvedite imya faila, naprimer data.txt: ";
            if (!std::getline(std::cin >> std::ws, filename))
                return 0;

            std::ofstream file(filename);

            if (!file)
            {
                std::cout << "Ne udalos otkryt fail dlya zapisi\n";
                break;
            }

            file << std::setprecision(
                std::numeric_limits<double>::max_digits10);

            for (const auto& item : pipes)
            {
                savePipe(file, item.second);
            }

            for (const auto& item : stations)
            {
                saveCompressorStation(file, item.second);
            }

            file.close();

            if (!file)
            {
                std::cout << "Oshibka pri sohranenii dannyh\n";
            }
            else
            {
                std::cout << "Dannye sohraneny v " << filename << '\n';
                std::cout << "Trub: " << pipes.size() << '\n';
                std::cout << "KS: " << stations.size() << '\n';
            }

            break;
        }
        case 7:
        {
            std::string filename;

            std::cout << "Vvedite imya faila: ";
            if (!std::getline(std::cin >> std::ws, filename))
                return 0;

            std::ifstream file(filename);

            if (!file)
            {
                std::cout << "Fail ne naiden ili ne otkryvaetsya\n";
                break;
            }

            std::map<int, Pipe> loadedPipes;
            std::map<int, CompressorStation> loadedStations;

            int loadedNextId = nextId;
            bool correct = true;
            std::string type;

            while (std::getline(file, type))
            {
                if (type.empty())
                    continue;

                int id;

                if (type == "PIPE")
                {
                    Pipe loadedPipe = {};

                    if (!loadPipe(file, loadedPipe))
                    {
                        correct = false;
                        break;
                    }

                    id = loadedPipe.id;

                    if (loadedPipes.count(id) != 0
                        || loadedStations.count(id) != 0)
                    {
                        correct = false;
                        break;
                    }

                    loadedPipes.emplace(id, loadedPipe);
                }
                else if (type == "COMPRESSOR")
                {
                    CompressorStation loadedStation = {};

                    if (!loadCompressorStation(file, loadedStation))
                    {
                        correct = false;
                        break;
                    }

                    id = loadedStation.id;

                    if (loadedPipes.count(id) != 0
                        || loadedStations.count(id) != 0)
                    {
                        correct = false;
                        break;
                    }

                    loadedStations.emplace(id, loadedStation);
                }
                else
                {
                    correct = false;
                    break;
                }

                if (id == std::numeric_limits<int>::max())
                {
                    correct = false;
                    break;
                }

                if (id >= loadedNextId)
                    loadedNextId = id + 1;
            }

            if (!correct || file.bad())
            {
                std::cout << "Oshibka dannyh. Zagruzka otmenena\n";
                break;
            }

            pipes = std::move(loadedPipes);
            stations = std::move(loadedStations);
            nextId = loadedNextId;

            std::cout << "Dannye zagruzheny iz " << filename << '\n';
            std::cout << "Trub: " << pipes.size() << '\n';
            std::cout << "KS: " << stations.size() << '\n';

            break;
        }

        case 0:
            return 0;


        default:
            std::cout << "viberi drugoe\n";
        }
    }
}