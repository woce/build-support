/* ============================================================
 * Date  : 2009-03-09
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGLRUCACHE_H
#define PGLRUCACHE_H

#include <map>
#include <algorithm>

template <typename Key, typename Value>
class PGLruCache
{
public:

	PGLruCache();
	~PGLruCache();

	void setMaxSize(int maxSize);

	Value* find(const Key& key);
	void add(const Key& key, Value* value);

	void clear();   

private:

	void prune();
	
	class PGLruCacheEntry {
	public:

		PGLruCacheEntry() : next(this), prev(this), value(0) {}
		PGLruCacheEntry(Value* val) : next(this), prev(this), value(val) {}
		~PGLruCacheEntry() { delete value; }
	
		PGLruCacheEntry* next;
		PGLruCacheEntry* prev;
		Value* value;
	};	
	
	std::map<Key, PGLruCacheEntry*> m_cache;
	PGLruCacheEntry* m_list;
	int m_currSize;
	int m_maxSize;
};

template <typename Key, typename Value>
PGLruCache<Key, Value>::PGLruCache()
	: m_list(new PGLruCacheEntry)
	, m_currSize(0)
	, m_maxSize(0)
{	
}

template <typename Key, typename Value>
PGLruCache<Key, Value>::~PGLruCache()
{
	clear();
	delete m_list;
}

template <typename Key, typename Value>
void PGLruCache<Key, Value>::setMaxSize(int maxSize)
{
	m_maxSize = maxSize;
	prune();
}

template <typename Key, typename Value>
Value* PGLruCache<Key, Value>::find(const Key& key)
{
	typename std::map<Key, PGLruCacheEntry*>::iterator it = m_cache.find(key);
	if (it == m_cache.end())
		return 0;

	// Move to beginning of list
	PGLruCacheEntry* entry = (*it).second;
	if (m_list->next == entry)
		return entry->value;

	// Remove from list
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
	entry->next = entry;
	entry->prev = entry;

	// this is the new head
	m_list->next->prev = entry;
	entry->next = m_list->next;
	entry->prev = m_list;
	m_list->next = entry;

	return entry->value;
}

template <typename Key, typename Value>
void PGLruCache<Key, Value>::add(const Key& key, Value* value)
{
	PGLruCacheEntry* entry = new PGLruCacheEntry(value);
	if (!m_list) {
		m_list = entry;
		return;
	}
	
	// This is the new head
	m_list->next->prev = entry;
	entry->next = m_list->next;
	entry->prev = m_list;
	m_list->next = entry;

	m_cache[key] = entry;
	m_currSize += value->size();

	prune();
}

template <typename Key, typename Value>
void PGLruCache<Key, Value>::clear()
{
	// FIXME: implement
}

template <typename Key, typename Value>
void PGLruCache<Key, Value>::prune()
{
	if (m_currSize <= m_maxSize)
		return;

	PGLruCacheEntry* entry = m_list->prev;
	while (entry != m_list && m_currSize > m_maxSize) {

		entry->prev->next = m_list;
		m_list->prev = entry->prev;

		m_currSize -= entry->value->size();
		m_cache.erase(entry->value->key());
		delete entry;
		
		entry = m_list->prev;
	}
}

#endif /* PGLRUCACHE_H */
