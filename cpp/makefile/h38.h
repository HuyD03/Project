#ifndef H38_H_
#define H38_H_

#include <string>

///// Declare all of your classes here ////////////////
///// In this order: Worker, SalariedWorker, HourlyWorker
class Worker
{
protected:
    std::string name;
    double rate;
public:
    Worker(const std::string &name1, double rate1)
    {
        name = name1;
        rate = rate1;
    }

    void setName(const std::string &name1)
    {
        name = name;
    }

    void setRate(double rate1)
    {
        rate = rate1;
    }

    std::string getName()
    {
        return name;
    }

    double getRate()
    {
        return rate;
    }

    virtual std::string payInfo(int hours) = 0;

    virtual ~Worker() = default;
};

// Hourly worker class
class HourlyWorker : public Worker
{
public:
    HourlyWorker(const std::string &name1, double rate1) : Worker(name1, rate1){};

    std::string payInfo(int hours)
    {
        char buffer[250];
        double salary = 0;
        if (hours > 40)
            salary = (1.5) * (hours - 40) * rate + 40 * rate;
        else
            salary = hours * rate;
        sprintf(buffer, "(Hourly, $ %.2f) worked %d hours. Pay: $ %.2f", rate, hours, salary);
        std::string result(buffer);
        return name + result;
    }
};

// Salaried worker class
class SalariedWorker : public Worker
{
public:
    SalariedWorker(const std::string &name1, double rate1) : Worker(name1, rate1){};

    std::string payInfo(int hours)
    {
        char buffer[250];
        sprintf(buffer, "(Salaried, $ %.2f) worked %d hours. Pay: $ %.2f", rate, hours, (rate * 40));
        std::string result(buffer);
        return name + result;
    }
};
#endif

