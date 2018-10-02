#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int KeyType;
typedef int ValueType;

typedef struct HashNode
{
	KeyType key;
	ValueType value;
	struct HashNode* next;
}HashNode;

typedef struct HashBucket
{
	HashNode ** tables;
	size_t len;
	size_t size;
}HTB;

HashNode *BuyHashNode(KeyType k, ValueType v);
void HTBInit(HTB *htb, size_t len);
void HTBDestory(HTB* htb);
int HTBInsert(HTB *htb, KeyType key, ValueType value);
int HTBRemove(HTB *htb, KeyType key);
HashNode* HTBFind(HTB *htb, KeyType key);
int HTBSize(HTB* htb);
int HTBEmpty(HTB* htb);

void Print(HTB* htb);
void Test();