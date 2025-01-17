#pragma once

#include <string>
#include <utility>
#include <pqxx/transaction.hxx>

class SearchLocationQueryBuilder {
    std::string name_;
    std::string country_;
    double lat_;
    double lon_;

public:
    SearchLocationQueryBuilder(std::string name, std::string country, double lat, double lon)
        : name_(std::move(name)), country_(std::move(country)), lat_(lat), lon_(lon) {
    }

    [[nodiscard]] std::string build() const {
        auto result = std::string("select * from search_cities(");

        bool first = true;

        if (!name_.empty()) {
            result += "search_name := '" + name_ + "'";
            first = false;
        }

        if (!country_.empty()) {
            if (!first)
                result += ",";
            result += "search_country := '" + country_ + "'";
            first = false;
        }

        if (lat_ != 0.0) {
            if (!first)
                result += ",";
            result += "search_lat := " + std::to_string(lat_);
            first = false;
        }

        if (lon_ != 0.0) {
            if (!first)
                result += ",";
            result += "search_lon := " + std::to_string(lon_);
            first = false;
        }

        result += ")";

        return result;
    }
};
