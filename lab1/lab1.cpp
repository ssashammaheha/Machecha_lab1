
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <limits>
#include <iomanip>
#include <cmath>
#include <utility>
#include <set>

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
    std::getline(std::cin, pipe.name, '\n');



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
bool readInt(const std::string& message, int& value,
    int minValue, int maxValue)
{
    std::cout << message;
    while (!(std::cin >> value)
        || std::cin.peek() != '\n'
        || value < minValue
        || value > maxValue)
    {
        if (std::cin.eof())
            return false;
        std::cout << "Vvedite celoe chislo ot "
            << minValue << " do " << maxValue << ": ";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;
}
std::set<int> findPipes(const std::map<int, Pipe>& pipes)
{
    std::set<int> foundIds;
    int choice;
    if (!readInt("Po nazvaniyu - 1, po remontu - 2: ",
        choice, 1, 2))
        return foundIds;
    if (choice == 1)
    {
        std::string text;
        std::cout << "Vvedite nazvanie ili ego chast: ";
        if (!std::getline(std::cin >> std::ws, text))
            return foundIds;
        for (const auto& item : pipes)
        {
            if (item.second.name.find(text) != std::string::npos)
                foundIds.insert(item.first);
        }
    }
    else
    {
        int repair;
        if (!readInt("V remonte - 1, rabotaet - 0: ",
            repair, 0, 1))
            return foundIds;
        for (const auto& item : pipes)
        {
            if (item.second.inRepair == repair)
                foundIds.insert(item.first);
        }
    }
    return foundIds;
}
std::set<int> findStations(
    const std::map<int, CompressorStation>& stations)
{
    std::set<int> foundIds;
    int choice;
    if (!readInt("Po nazvaniyu - 1, po procentu - 2: ",
        choice, 1, 2))
        return foundIds;
    if (choice == 1)
    {
        std::string text;
        std::cout << "Vvedite nazvanie ili ego chast: ";
        if (!std::getline(std::cin >> std::ws, text))
            return foundIds;
        for (const auto& item : stations)
        {
            if (item.second.name.find(text) != std::string::npos)
                foundIds.insert(item.first);
        }
    }
    else
    {
        double percent;
        std::cout << "Vvedite minimalnyi procent ot 0 do 100: ";
        while (!(std::cin >> percent)
            || std::cin.peek() != '\n'
            || !std::isfinite(percent)
            || percent < 0
            || percent > 100)
        {
            if (std::cin.eof())
                return foundIds;
            std::cout << "Vvedite chislo ot 0 do 100: ";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
        }
        for (const auto& item : stations)
        {
            const CompressorStation& cs = item.second;
            double idlePercent =
                100.0 * (cs.workshopCount - cs.workingWorkshops)
                / cs.workshopCount;
            if (idlePercent >= percent)
                foundIds.insert(item.first);
        }
    }
    return foundIds;
}
void batchEditPipes(std::map<int, Pipe>& pipes,
    std::set<int>& foundIds, std::ofstream& log)
{
    if (foundIds.empty())
    {
        std::cout << "Truby ne naideny\n";
        log << "Pipe management: nothing found" << std::endl;
        return;
    }
    for (int id : foundIds)
    {
        showPipe(pipes.at(id));
        std::cout << '\n';
    }
    int action;
    if (!readInt("1 - izmenit remont, 2 - udalit, 0 - otmena: ",
        action, 0, 2))
        return;
    log << "Pipe action: " << action << " (1 - edit repair, 2 - delete, 0 - cancel)" << std::endl;
    if (action == 0)
        return;
    int scope;
    if (!readInt("1 - vse naidennye, 2 - vybrat po ID: ",
        scope, 1, 2))
        return;
    log << "Pipe selection: " << scope << " (1 - all found, 2 - selected IDs)" << std::endl;
    std::set<int> selectedIds;
    if (scope == 1)
    {
        selectedIds = foundIds;
    }
    else
    {
        int id;
        while (true)
        {
            if (!readInt("Vvedite ID, 0 - zakonchit vybor: ",
                id, 0, std::numeric_limits<int>::max()))
                return;
            if (id == 0)
                break;
            if (foundIds.count(id))
            {
                selectedIds.insert(id);
                log << "Pipe selected. ID: " << id << std::endl;
                std::cout << "Truba vybrana\n";
            }
            else
            {
                std::cout << "Etogo ID net sredi naidennyh\n";
                log << "Pipe selection rejected. ID: " << id << std::endl;
            }
        }
    }

    if (selectedIds.empty())
    {
        std::cout << "Truby ne vybrany\n";
        log << "Pipe management cancelled: no pipes selected" << std::endl;
        return;
    }

    if (action == 1)
    {
        int repair;

        if (!readInt("Novoe sostoyanie: 1 - remont, 0 - rabotaet: ",
            repair, 0, 1))
            return;

        for (int id : selectedIds)
        {
            log << "Pipe edited. ID: " << id << "; repair: "
                << pipes.at(id).inRepair << " -> " << repair << std::endl;
            pipes.at(id).inRepair = repair;
        }

        std::cout << "Izmeneno trub: " << selectedIds.size() << '\n';
    }
    else
    {
        for (int id : selectedIds)
        {
            pipes.erase(id);
            foundIds.erase(id);
            log << "Pipe deleted. ID: " << id << std::endl;
        }

        std::cout << "Udaleno trub: " << selectedIds.size() << '\n';
    }
}
int main()
{
    std::map<int, Pipe> pipes;
    std::map<int, CompressorStation> stations;
    std::set<int> foundPipeIds;
    std::set<int> foundStationIds;
    Pipe pipe = {};
    pipe.est = false;
    CompressorStation cs = {};
    cs.est = false;
    int nextId = 1;

    std::ofstream log("log.txt", std::ios::app);
    if (!log)
    {
        std::cout << "Ne udalos otkryt log.txt\n";
        return 1;
    }
    log << "\n=== Program started ===\n";
    int choice;
    while (true)
    {
        std::cout << "======================================\n";
        std::cout << "1. Dobavit pipe\n";
        std::cout << "2. Dobavit compressor station\n";
        std::cout << "3. Show all objects\n";
        std::cout << "4. Edit or delete pipes\n";
        std::cout << "5. Zapustit station\n";
        std::cout << "6. Save\n";
        std::cout << "7. Zagruzit from file\n";
        std::cout << "8. Find pipes\n";
        std::cout << "9. Find compressor stations\n";
        std::cout << "0. Exit\n";
        std::cout << "======================================\n";
        if (!readInt("Choose action: ", choice, 0, 9))
            return 0;

        log << "Menu choice: " << choice << std::endl;

        switch (choice)
        {
        case 1:
            createPipe(pipe);
            pipe.id = nextId;
            pipes.emplace(pipe.id, pipe);
            nextId++;
            std::cout << "Truba dobavlena. ID: " << pipe.id << '\n';
            std::cout << "Vsego trub: " << pipes.size() << '\n';
            log << "Pipe added. ID: " << pipe.id << "; name: " << pipe.name << std::endl;
            break;

        case 2:
            createCompressorStation(cs);
            cs.id = nextId;
            stations.emplace(cs.id, cs);
            nextId++;
            std::cout << "KS dobavlena. ID: " << cs.id << '\n';
            std::cout << "Vsego KS: " << stations.size() << '\n';
            log << "Station added. ID: " << cs.id << "; name: " << cs.name << std::endl;
            break;

        case 3:
        {
            log << "Show all objects" << std::endl;
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
            foundPipeIds = findPipes(pipes);
            log << "Pipe management. Found: " << foundPipeIds.size() << std::endl;
            batchEditPipes(pipes, foundPipeIds, log);
            break;
        }
        case 5:
        {
            int id;
            if (!readInt("Vvedite ID compressor station: ", id,
                1, std::numeric_limits<int>::max()))
                return 0;
            auto it = stations.find(id);
            if (it != stations.end())
            {
                log << "Workshop start requested. Station ID: " << id
                    << "; working before: " << it->second.workingWorkshops << std::endl;
                startWorkshop(it->second);
                log << "Working after: " << it->second.workingWorkshops << std::endl;
            }
            else
            {
                std::cout << "Station ne naidena\n";
                log << "Station not found. ID: " << id << std::endl;
            }
            break;
        }
        case 6:
        {
            if (pipes.empty() && stations.empty())
            {
                std::cout << "Net obektov dlya sohraneniya\n";
                log << "Save cancelled: no objects" << std::endl;
                break;
            }
            std::string filename;
            std::cout << "Vvedite imya faila, naprimer data.txt: ";
            if (!std::getline(std::cin >> std::ws, filename))
                return 0;
            log << "Save requested. File: " << filename << std::endl;
            std::ofstream file(filename);
            if (!file)
            {
                std::cout << "Ne udalos otkryt fail dlya zapisi\n";
                log << "Save failed: cannot open file" << std::endl;
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
                log << "Save failed: write error" << std::endl;
            }
            else
            {
                std::cout << "Dannye sohraneny v " << filename << '\n';
                std::cout << "Trub: " << pipes.size() << '\n';
                std::cout << "KS: " << stations.size() << '\n';
                log << "Data saved. File: " << filename << std::endl;
            }
            break;
        }
        case 7:
        {
            std::string filename;
            std::cout << "Vvedite imya faila: ";
            if (!std::getline(std::cin >> std::ws, filename))
                return 0;
            log << "Load requested. File: " << filename << std::endl;
            std::ifstream file(filename);
            if (!file)
            {
                std::cout << "Fail ne naiden\n";
                log << "Load failed: cannot open file" << std::endl;
                break;
            }
            pipes.clear();
            stations.clear();
            std::string type;
            bool correct = true;
            while (std::getline(file, type))
            {
                if (type.empty())
                    continue;
                Pipe p = {};
                CompressorStation c = {};
                int id;
                if (type == "PIPE")
                {
                    if (!loadPipe(file, p))
                    {
                        correct = false;
                        break;
                    }
                    id = p.id;
                }
                else if (type == "COMPRESSOR")
                {
                    if (!loadCompressorStation(file, c))
                    {
                        correct = false;
                        break;
                    }
                    id = c.id;
                }
                else
                {
                    correct = false;
                    break;
                }
                if (pipes.count(id) || stations.count(id)
                    || id == std::numeric_limits<int>::max())
                {
                    correct = false;
                    break;
                }
                if (type == "PIPE")
                    pipes.emplace(id, p);
                else
                    stations.emplace(id, c);
                if (id >= nextId)
                    nextId = id + 1;
            }
            if (!correct || file.bad())
            {
                pipes.clear();
                stations.clear();
                std::cout << "Fail povrezhden. Dannye ne zagruzheny\n";
                log << "Load failed: damaged file. Objects cleared" << std::endl;
            }
            else
            {
                std::cout << "Zagruzheno trub: " << pipes.size()
                    << ", KS: " << stations.size() << '\n';
                log << "Data loaded. File: " << filename << std::endl;
            }

            break;
        }
        case 8:
        {
            foundPipeIds = findPipes(pipes);
            log << "Pipe search. Found: " << foundPipeIds.size() << std::endl;
            if (foundPipeIds.empty())
                std::cout << "Truby ne naideny\n";
            for (int id : foundPipeIds)
            {
                showPipe(pipes.at(id));
                std::cout << '\n';
            }
            break;
        }
        case 9:
        {
            foundStationIds = findStations(stations);
            log << "Station search. Found: " << foundStationIds.size() << std::endl;
            if (foundStationIds.empty())
                std::cout << "KS ne naideny\n";
            for (int id : foundStationIds)
            {
                showCompressorStation(stations.at(id));
                std::cout << '\n';
            }
            break;
        }
        case 0:
            log << "=== Program finished ===" << std::endl;
            return 0;


        default:
            std::cout << "viberi drugoe\n";
        }
    }
}