#pragma once
#ifndef _WORDBOOK_H
#define _WORDBOOK_H
typedef signed long int Long;
typedef struct _word {
	char spelling[64];
	char wordClass[16];
	char mean[16];
	char example[256];
} Word;

typedef struct _wordBook {
	Word(*words);
	Long capacity;
	Long length;
} WordBook;

void Create(WordBook* wordBook, Long capacity);
void Destroy(WordBook* wordBook);


#endif // _WORDBOOK_H