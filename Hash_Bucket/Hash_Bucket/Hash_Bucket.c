#include "Hash_Bucket.h"

HashNode *BuyHashNode(KeyType k, ValueType v)
{
	HashNode *node = (HashNode*)malloc(sizeof(HashNode));
	node->key = k;
	node->value = v;
	node->next = NULL;
	return node;
}

void HTBInit(HTB* htb, size_t len)
{
	assert(htb);
	htb->len = len;
	htb->size = 0;
	htb->tables = (HashNode **)malloc(sizeof(HashNode)*htb->len);
	memset(htb->tables, 0, sizeof(HashNode*)*htb->len);
}

void HTBDestory(HTB* htb)
{
	assert(htb);
	size_t i = 0;
	for (i = 0; i < htb->len; i++)
	{
		HashNode* cur = htb->tables[i];
		while (cur)
		{
			HashNode* next = cur->next;
			free(cur);
			cur = next;
		}
		htb->tables[i] = NULL;
	}
	htb->tables = NULL;
	htb->len = htb->size = 0;
}

size_t HTBHashFunc(KeyType key, size_t len)
{
	return key % len;
}

void HTBCheckCapacity(HTB* htb)
{
	assert(htb);
	if (htb->size == htb->len)
	{
		size_t i = 0;
		HTB newhtb;
		newhtb.len = 2*htb->len;
		HTBInit(&newhtb, newhtb.len);
		for (i = 0; i < htb->len; i++)
		{
			HashNode* cur = htb->tables[i];
			while (cur)
			{
				HashNode* next = cur->next;
				size_t index = HTBHashFunc(cur->key, newhtb.len);

				cur->next = newhtb.tables[index];
				newhtb.tables[index] = cur;
				cur = next;
			}
			htb->tables[i] = NULL;
		}
		HTBDestory(htb);
		htb->tables = newhtb.tables;
		htb->size = newhtb.size;
		htb->len = newhtb.len;
	}
}

int HTBInsert(HTB *htb, KeyType key,ValueType value)
{
	assert(htb);
	HTBCheckCapacity(htb);
	size_t index = 0;
	HashNode *cur;
	HashNode *newNode;
	index = HTBHashFunc(key, htb->len);
	cur = htb->tables[index];
	while (cur)
	{
		if (cur->key == key)
		{
			cur->value++;
			return -1;
		}
		cur = cur->next;
	}

	newNode = BuyHashNode(key, value);
	newNode->next = htb->tables[index];
	htb->tables[index] = newNode;
	htb->size++;
	return 0;
}

int HTBRemove(HTB *htb, KeyType key)
{
	assert(htb);
	size_t index;
	HashNode* cur = NULL;
	HashNode* prev = NULL;

	index = HTBHashFunc(key, htb->len);
	cur = htb->tables[index];
	while (cur)
	{
		if (cur->key == key)
		{
			if (prev == NULL)
			{
				htb->tables[index] = cur->next;
			}
			else
			{
				prev->next = cur->next;
			}
			free(cur);
			htb->size--;
			return 0;
		}
		prev = cur;
		cur = cur->next;
	}
	return -1;
}

HashNode* HTBFind(HTB *htb, KeyType key)
{
	assert(htb);
	int index = 0;
	HashNode *cur;
	index = HTBHashFunc(key, htb->len);
	cur = htb->tables[index];
	while (cur)
	{
		if (cur->key == key)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}


void Print(HTB* htb)
{
	size_t i = 0;
	assert(htb);
	for (i = 0; i < htb->len; i++)
	{
		HashNode* cur = htb->tables[i];
		printf("table[%d]->", i);
		while (cur)
		{
			printf("[%d:%d]->", cur->key, cur->value);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\n");
}

int HTBSize(HTB* htb)
{
	assert(htb);
	return htb->size;
}

int HTBEmpty(HTB* htb)
{
	assert(htb);
	if (htb->size == 0)
	{
		return 1;
	}
	return 0;
}

void Test()
{
	HTB htb;
	HTBInit(&htb, 50);
	int i = 0;
	/*srand(time(0));
	for (i = 0; i < 10000; ++i)
	{
		HTBInsert(&htb, rand(), 0);
	}*/
	/*HTBInsert(&htb, 10, 0);
	printf("%d\n", HTBFind(&htb, 10)->key);*/
	Print(&htb);
	HTBDestory(&htb);

}