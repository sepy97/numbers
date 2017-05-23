#pragma once
#include <string>
using namespace std;
#include <deque>
class fast_deque
{
public:
	typedef long long dul;
	fast_deque();
	fast_deque(dul *room, size_t size, dul const *data, size_t dataSize); // allocate ONLY using align_up
	~fast_deque();
	size_t size() const;
	dul & operator[](size_t ptr);
	dul const & operator[](size_t ptr) const;
	dul & at(size_t ptr);
	dul const & at(size_t ptr) const;
	void pop_back();
	void push_back(dul elem);
	void pop_front();
	void resize(size_t newSize);
	void clear();
	void clone(fast_deque const &);
	void insertToBegin(dul const *ptr, size_t size);
	void insertToEnd(dul const *ptr, size_t size);
	string toString() const;
	void free();
	static size_t align_up(size_t size);
	void init(dul *room, size_t size, dul const *data, size_t dataSize); 
private:
//	deque<dul> body;
	void init_alloc(size_t init_size);
	// Два способа добычи памяти: или мы сами заказываем. или пользуемся заказанной.
	dul *memory;   
	size_t end_ptr; // Последняя валидная позиция + 1 (push изменяет её)
	size_t start_ptr; // На какой позиции мы сейчас (важно при front операциях)
	size_t memory_available;  // Сколько нам доступно
	bool is_memory_allocated; // Сами заказали или нам её выдали.
	fast_deque(fast_deque const &);
	fast_deque & operator=(fast_deque const &);
};

