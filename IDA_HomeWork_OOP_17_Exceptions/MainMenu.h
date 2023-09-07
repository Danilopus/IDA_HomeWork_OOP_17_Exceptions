#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Service functions.h"
#include <windows.h>

extern void Task_1(std::string);
extern void Task_2(std::string);


class Main_menu
{
	std::vector<std::string> _menu_elements;
public:
	void AddElement(std::string menu_element){	_menu_elements.push_back(menu_element);	}
	void Show_menu();
	int User_Choice_Handle(); //старая реализация 
	int User_Choice_Handle(int key_code);
};

