#ifndef PARAM_HXX_INCLUDED
#define PARAM_HXX_INCLUDED

#include "numini/reader.hxx"
#include "numini/error.hxx"

#include <string>
#include <map>
#include <iostream>

typedef std::vector<int> vi;
typedef std::map<std::string,double> s2d;

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

typedef std::vector<Vec3> vVec3;
typedef std::map<std::string,Vec3> s2Vec3;

class Parameters
{
    public:
        Parameters();

        void
        read_config_file(std::string filename);

        std::string position(){return m_position;}
        void set_position(std::string p){m_position = p;}
        
        vi properties(){return m_properties;}
        void set_properties(const vi & p){m_properties = p;}
        
        double width(){return m_width;}
        void set_width(const double w){m_width = w;}

        double height(){return m_height;}
        void set_height(const double h){m_height = h;}
        
        s2d coords(){return m_coords;}
        void set_coords(const s2d & c){m_coords = c;}

        Vec3 start(){return m_start;}
        void set_start(const Vec3 & s){m_start = s;}

        vVec3 vstart(){return m_vstart;}
        void set_vstart(const vVec3 & vs){m_vstart = vs;}

        s2Vec3 mstart(){return m_mstart;}
        void set_mstart(const s2Vec3 & ms){m_mstart = ms;}

    private:

        std::string m_position;
        double m_width;
        double m_height;
        s2d m_coords;
        vi m_properties;
        Vec3 m_start;
        vVec3 m_vstart;
        s2Vec3 m_mstart;
};

#endif
