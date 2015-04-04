#ifndef _PRINT_H
#define _PRINT_H
/*
  "Система обработки транзакций  с использованием 
  распределенных колоночных индексов"
  
  Модуль вывода параметров эксперимента и результата.
  Авторы: Иванова Е.В., Соколинский Л.Б.
  
*/

#include "common.h"

/*	
	Печать параметров программы
*/
int print_header();

/*	
	Печать результата программы
*/
int print_result();

#endif