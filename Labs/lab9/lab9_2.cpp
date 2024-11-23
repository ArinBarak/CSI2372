//Lab 9
//Exercice 2

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

class Average {
public:
    double operator()(const std::vector<double>& prices) const {
        double sum = 0;
        for (double price : prices) {
            sum += price;
        }
        return (prices.empty()) ? 0.0 : sum / prices.size();
    }
};

class StandardDeviation {
public:
    double operator()(const std::vector<double>& prices) const {
        if (prices.empty()) return 0.0;

        double avg = Average()(prices);
        double sum_squared_diff = 0.0;
        for (double price : prices) {
            sum_squared_diff += std::pow(price - avg, 2);
        }
        return std::sqrt(sum_squared_diff / prices.size());
    }
};

class DataAnalysis {
private:
    std::vector<double> prices;

public:
    DataAnalysis(const std::vector<double>& data) : prices(data) {}

    std::vector<double> filterPrices(double threshold) const {
        std::vector<double> filteredPrices;
        std::copy_if(prices.begin(), prices.end(), std::back_inserter(filteredPrices),
                [threshold](double price) { return price > threshold; });
        return filteredPrices;
    }

    double getAverage() const {
        Average avg;
        return avg(prices);
    }

    double getStandardDeviation() const {
        StandardDeviation stddev;
        return stddev(prices);
    }

    void printPrices() const {
        for (double price : prices) {
            std::cout << price << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<double> stockPrices = {100.5, 102.3, 98.7, 105.2, 103.5, 110.1, 97.8, 99.5, 104.3};
    DataAnalysis data(stockPrices);

    std::cout << "Original Stock Prices: ";
    data.printPrices();

    double threshold = 100.0;
    std::vector<double> filteredPrices = data.filterPrices(threshold);

    std::cout << "Filtered Stock Prices (above " << threshold << "): ";
    for (double price : filteredPrices) {
        std::cout << price << " ";
    }
    std::cout << std::endl;

    double average = data.getAverage();
    std::cout << "Average Stock Price: " << average << std::endl;

    double stddev = data.getStandardDeviation();
    std::cout << "Standard Deviation of Stock Prices: " << stddev << std::endl;

    return 0;
}
