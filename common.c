/*
  "Система обработки транзакций  с использованием 
  распределенных колоночных индексов"
  
  Файл с общими параметрами
  Авторы: Иванова Е.В., Соколинский Л.Б.

*/
#include "common.h"

int NREPEAT = 100;			// Количество повторений эксперимента
int NUM_FRAGMENTS = 1;		// Количество фрагментов
int FRAGMENT_NUM = 0;		// Номер текущего фрагмента
int NUM_THREADS = 60;		// Количество нитей для запуска на сопроцессоре
int NUM_SEGMENTS = 600;		// Количество сегментов во фрагменте

int NUM_ROWS_R = 600000;		// Количество строк в таблице с первичным ключом R в текущем фраменте
int NUM_ROWS_S = 60000000;		// Количество строк в таблице с внешним ключом S в текущем фраменте
int NUM_ROWS_Res;			// Количество строк в таблице с результатом в текущем фраменте

int COMPRESS_LEVEL = 4;		// Степень сжатия алгоритмом Deflate

int NVALUES = 100;			// Количество различных значений R.B в сегменте (в %)

float SEGMENT_TETA = 0.0;	// Вид распределения значений в таблице S по cегментам.
							// Коэффициент перекоса, изменяется от 0 до 1. Коэффициент 0.5 соответствует правилу "45-20".
							// Коэффициент 0.68 соответствует правилу "70-30". Коэффициент 0.2 соответствует правилу "25-15".
							// Коэффициент 0.86 соответствует правилу "80-20". Коэффициент 0 - равномерное распределение.

							
int *segment_domain; 		// Таблица сегментации домена в текущем фрагменте,
							// содержит значениями из домена, обозначающими границы 
							// сегментов в текущем фрагменте.
							// Пример: таблица segment_domain = {1,5,8} обозначает, что в текущем фрагменте два сегмента, 
							// границы первого сегмента от 1 до 4, второго - от 5 до 7 (включительно).


int MIN_VAL_DOMAIN;			// Нижняя граница домена в текущем фраменте
int MAX_VAL_DOMAIN;			// Верхняя граница домена в текущем фраменте

const int MEMORY_SIZE_PHI = 1890000000;// Объем оперативной памяти сопроцессора (в целых числах),
								// доступной для размещения данных, определено экспериментально

int ALIGN = 64;				// Значение, по которому будет производиться выравнивание данных

double GENERATION_TIME;		// Время загрузки данных при инициализации
double EXEC_TIME;		// Время выполнения запроса
double CALC_TIME = 0.0;		// Время вычислений реляционной операции
double UNCOMPRESS_TIME = 0.0;	// Время распаковки данных для выполнения реляционной операции

segment_t *segmentR;		// Таблицы сегментации для	R
segment_t *segmentS;		// Таблицы сегментации для	S
segment_t *segmentRes;		// Таблицы сегментации для	результата операции

char DIR[5] = "db/";

int MAX_SEGMENT_R_SIZE;
int MAX_SEGMENT_S_SIZE;

FILE *R_DB;					// Указатель на фрагмент файла с базой данных R
FILE *S_DB;					// Указатель на фрагмент файла с базой данных S

long long int FLOPS = 0;	// Количество операций
