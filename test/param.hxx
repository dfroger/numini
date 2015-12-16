#ifndef PARAM_HXX_INCLUDED
#define PARAM_HXX_INCLUDED

#include "numini/reader.hxx"
#include "numini/error.hxx"

#include <string>
#include <map>
#include <iostream>

class Vec3
{
    public:
        Vec3();

        Vec3(double x, double y, double z);
        
        double get_x() const { return m_x;}
        double get_y() const { return m_y;}
        double get_z() const { return m_z;}

        void set_x(double x) {m_x = x;}
        void set_y(double y) {m_y = y;}
        void set_z(double z) {m_z = z;}

    private:
        double m_x, m_y, m_z;
};

class Parameters
{
    public:

        void
        read_config_file(std::string filename);

        std::string position(){return m_position;}
        void set_position(std::string p){m_position = p;}
        
        std::vector<int> properties(){return m_properties;}
        void set_properties(const std::vector<int> & p){m_properties = p;}
        
        double width(){return m_width;}
        void set_width(const double w){m_width = w;}

        double height(){return m_height;}
        void set_height(const double h){m_height = h;}
        
        std::map<std::string,double> coords(){return m_coords;}

        Vec3 start(){return m_start;}
        void set_start(const Vec3 & s){m_start = s;}

    private:

        std::string m_position;
        double m_width;
        double m_height;
        std::map<std::string,double> m_coords;
        std::vector<int> m_properties;
        Vec3 m_start;
};

#endif
