
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


int main()
{
    Pipe pipe1;
    pipe1.name = "truba 1";
    pipe1.length = 15.5;
    pipe1.diameter = 520;
    pipe1.inRepair = 1;
    


    showPipe(pipe1);
    std::cout << '\n';

    Pipe pipe2;
    createPipe(pipe2);
    showPipe(pipe2);
    
}
