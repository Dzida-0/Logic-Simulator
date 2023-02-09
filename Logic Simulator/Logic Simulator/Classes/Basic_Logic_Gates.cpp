#include "Basic_Logic_Gates.h"
// ka¿dy konstruktor zawiera scieszkê do tekstury i tablicê wartoœci logicznych in out
OR::OR()
{
    png_name = "Assets/OR.png";
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = false;
}

AND::AND()
{
    png_name = "Assets/AND.png";
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = false;
}

NOR::NOR()
{
    png_name = "Assets/NOR.png";
    output_active = true;
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = true;
    output();
}

NAND::NAND()
{
    png_name = "Assets/NAND.png";
    output_active = true;
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = true;
    output();
}

XOR::XOR()
{
    png_name = "Assets/XOR.png";
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = false;
}

XNOR::XNOR()
{
    png_name = "Assets/XNOR.png";
    output_active = true;
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = true;
    output();

}
