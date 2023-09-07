#include "MainMenu.h"

////::::::::::::::::::::::::::::::Main_menu::Main_menu::Main_menu::Main_menu::Main_menu::Main_menu::Main_menu::Main_menu::::::::::::::::::::::::::::::::
void Main_menu::Show_menu()
{
		system("cls");
		std::cout << "\n\t***\t" << _menu_elements[0] << "\t***\n\n\t\n\nChoose an option: \n";
		//for (int i=1; i< _menu_elements_number; i++)		
		for (int i = 1; i < _menu_elements.size(); i++)
			std::cout << "\n" << i << ". " << _menu_elements[i];
		std::cout << "\n\n 0. Exit\n";
		std::cout << "\nYour choice: ";
}
int Main_menu::User_Choice_Handle()
{
	int choice = 0;
	choice = Get_Int_Positive();
	std::cout << "\n";
	// Обработка выбора пользователя
	if (choice == 0) { std::cout << "\nGood By"; for (int j = 0; j < 50; j++) { Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0; }

	else if (choice == 1) Task_1(_menu_elements[1]);
	//else if (choice == 2) Task_2();
	//else if (choice == 3) Task_3();
	//else if (choice == 4) Task_4();

	else { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
	return 1;
}
int Main_menu::User_Choice_Handle(int key_code)
{
	//-48 переводит коды клавиш-цифр в цифры
		std::cout << key_code-48 << "\n\n";
	switch (key_code)
	{
	case 27: case 48: 
	{ std::cout << "\nGood By"; for (int j = 0; j < 50; j++) { Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0;	}
	case 49: Task_1(_menu_elements[1]); break;
	case 50: Task_2(_menu_elements[2]); break;
	//case 51: Task_3(); break;
	//case 52: Task_4(); break;
	//case 53: Task_5(); break;
	default: { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
	}
	return 1;
}


