
#include <iostream>
#include <string>
#include <fstream>

struct Pipe
{
    std::string name;
    double length;
    int diameter;
    bool inRepair;
    bool est;
};

struct CompressorStation
{
    std::string name;
    int workshopCount;
    int workingWorkshops;
    int stationClass;
    bool est;
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
    std::cin.ignore();
    std::getline(std::cin, pipe.name,'\n');
    


    std::cout << "enter length:";
    while (!(std::cin >> pipe.length) || (pipe.length <= 0)) 
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
    }

    std::cout << "enter diametr:"; 
    while (!(std::cin >> pipe.diameter) || (pipe.diameter <= 0)) 
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
    }
 
    std::cout << "is repair 1-da 0-net:";
    while (!(std::cin >> pipe.inRepair) || (pipe.inRepair < 0) || (pipe.inRepair > 1))
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
    while (!(std::cin >> cs.workshopCount) || (cs.workshopCount <= 0))
    {
        std::cout << "nelza" << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');

    }


    std::cout << "seyichas rabotayut:";

    while ((cs.workshopCount < cs.workingWorkshops) || !(std::cin >> cs.workingWorkshops) || (cs.workingWorkshops <= 0))
    {
        std::cout << "ne mozhet rabotat stolko compressorov: ";
        std::cin >> cs.workingWorkshops;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }


    std::cout << "klass 1-moshnaya 2-slabee 3-samaya slabaya: ";
    while (!(std::cin >> cs.stationClass) || cs.stationClass < 1 || cs.stationClass > 3)
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
    while (!(std::cin >> pipe.inRepair) || (pipe.inRepair < 0) || (pipe.inRepair > 1))
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
        std::string line;

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
            else if (type == "COMPRESSOR")
            {
                for (int i = 0; i < 4; i++)
                    std::getline(file, line);
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
        std::string line;

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
            else if (type == "PIPE")
            {
                for (int i = 0; i < 4; i++)
                    std::getline(file, line);
            }
        }
        std::cout << "Compressor ne naiden\n";
    }
    else
        std::cout << "kakie-to problems\n";
}
int main()
{
    Pipe pipe = {};
    pipe.est = false;
    CompressorStation cs = {};
    cs.est = false;
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
        while (!(std::cin >> choice) || (choice < 0) || (choice > 7))
        {
            std::cout << "nelza" << '\n';
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

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
            std::ofstream("data.txt").close();
            savePipe(pipe);
            saveCompressorStation(cs);
            std::cout << "Saved\n";
            break;

        case 7:
        {
            int object;
            std::cout << "Chto zagruzit? 1 - truba, 2 - compressor: ";
            while (!(std::cin >> object) || (object < 1) || (object > 2))
            {
                std::cout << "Vvedite 1 ili 2: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            if (object == 1)
                loadPipe(pipe);
            else
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