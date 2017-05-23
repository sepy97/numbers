#include "fast_deque.h"
#include <stdlib.h>
#include <memory.h>

#if 0
size_t fast_deque::align_up(size_t size)
{
	return size;
}

fast_deque::fast_deque()
{
}


fast_deque::fast_deque(dul *ptr, size_t size, dul const *data, size_t data_size)
{
	body.resize(size);
	for (size_t i = 0; i < data_size; i++)
	{
		body[i] = data[i];
	}
}


void 
fast_deque::free()
{
}

fast_deque::~fast_deque(void)
{
}

size_t fast_deque::size() const
{
	return body.size();
}

fast_deque::dul & fast_deque::operator[]( size_t ptr )
{
	return body[ptr];
}

fast_deque::dul const & fast_deque::operator[]( size_t ptr ) const
{
	return body[ptr];
}

fast_deque::dul & fast_deque::at( size_t p)
{
	return body[p];
}

fast_deque::dul const & fast_deque::at( size_t p ) const
{
	return body[p];
}

void fast_deque::pop_back()
{
	body.pop_back();
}

void fast_deque::push_back( dul elem )
{
	body.push_back(elem);
}
void fast_deque::resize( size_t newSize )
{
	body.resize(newSize);
}

void fast_deque::pop_front()
{
	body.pop_front();
}

void fast_deque::clear()
{
	body.clear();
}

void fast_deque::clone( fast_deque const &v )
{
	body = v.body;
}

void fast_deque::insertToBegin( dul const *ptr, size_t size )
{
	for ( int i = (int)size; --i >= 0; )
	{
		body.push_front(ptr[i]);
	}
}

std::string fast_deque::toString() const
{
	string ret;
	return ret;
}

void fast_deque::init( dul *room, size_t size, dul const *data, size_t dataSize )
{
	body.resize(size);
	for (size_t i = 0; i < dataSize; i++)
	{
		body[i] = data[i];
	}
}
#else
const int CHUNK_SIZE = 16;
size_t fast_deque::align_up(size_t size)
{
	size += CHUNK_SIZE - 1;
	size &= ~(CHUNK_SIZE - 1);
	return size;
}

fast_deque::fast_deque(void)
{
	memory = NULL;
	end_ptr = 0; 
	start_ptr = 0; 
	memory_available = 0;
	is_memory_allocated = false;
}


fast_deque::fast_deque(dul *ptr, size_t size, dul const *data, size_t data_size)
{
	memory = (dul *)ptr;
	end_ptr = 0; 
	start_ptr = 0; 
	size = align_up(size);
	memory_available = size; 
	is_memory_allocated = false; 
	if (data != NULL)
	{
		if (data_size <= size)
		{
			::memcpy(memory, data, data_size * sizeof(dul));
			end_ptr = data_size;
		}
		else
		{
			throw "No room in fast_deque constructor";
		}
	}
}


void 
	fast_deque::free()
{
	::free(memory);
	memory = NULL;
	memory_available = 0;
	end_ptr = 0;
	start_ptr = 0;
}

fast_deque::~fast_deque(void)
{
	if (is_memory_allocated)
	{
		free();
	}
}

size_t fast_deque::size() const
{
	return end_ptr - start_ptr;
}

fast_deque::dul & fast_deque::operator[]( size_t ptr )
{
	return at(ptr);
}

fast_deque::dul const & fast_deque::operator[]( size_t ptr ) const
{
	return at(ptr);
}

fast_deque::dul & fast_deque::at( size_t p)
{
	if (memory != NULL && start_ptr + p < end_ptr)
	{
		return memory[start_ptr + p];
	}
	throw "Index out of bounds";
}

fast_deque::dul const & fast_deque::at( size_t p ) const
{
	if (memory != NULL && start_ptr + p < end_ptr)
	{
		return memory[start_ptr + p];
	}
	throw "Index out of bounds";
}

void fast_deque::pop_back()
{
	if (start_ptr > 0)
	{
		start_ptr--;
	}
	else
	{
		throw "No room in pop_back";
	}
}

void fast_deque::push_back( dul elem )
{
	if (memory_available == 0)
	{
		init_alloc(CHUNK_SIZE);
	}
	if (end_ptr < memory_available)
	{
		memory[end_ptr] = elem;
		end_ptr++;
	}
	else if (is_memory_allocated)
	{
		if (memory != NULL)
		{
			size_t nsize = align_up(memory_available + CHUNK_SIZE);
			dul *new_allocated_memory = (dul *)malloc(nsize * sizeof(dul));
			::memcpy(new_allocated_memory, memory, memory_available * sizeof (dul));
			::free(memory);
			memory = new_allocated_memory;
			memory_available = nsize;
			memory[end_ptr] = elem;
			end_ptr++;
		}
		else
		{
			throw "invalid usage of puch_back";
		}
	}
	else
	{
		throw "no room in puch_back";
	}
}

void fast_deque::resize( size_t newSize )
{
	if (memory_available == 0)
	{
		init_alloc(newSize );
	}
	if (is_memory_allocated)
	{
		if (memory == NULL)
		{
			size_t nsize = align_up(newSize = CHUNK_SIZE);
			memory = (dul *)malloc(nsize * sizeof(dul));
			::memset(memory, 0, (nsize * sizeof(dul)));
			memory_available = nsize;
			start_ptr = 0;
			end_ptr = newSize;
		}
		if (start_ptr + newSize >= memory_available) 
		{
			size_t nsize = align_up(newSize + CHUNK_SIZE);
			dul *new_allocated_memory = (dul *)malloc(nsize * sizeof(dul));
			::memcpy(new_allocated_memory, memory, memory_available * sizeof (dul));
			::free(memory);
			memory = new_allocated_memory;
			memory_available = nsize;
		}
	}
	if (start_ptr + newSize < memory_available)
	{
		while (end_ptr - start_ptr < newSize)
		{
			memory[end_ptr++] = 0;
		}
		if (newSize > end_ptr - start_ptr)
		{
			end_ptr = start_ptr + newSize;
		}
	}
	else if (!is_memory_allocated)
	{
		throw "invalid resize in fast_deque";
	}
}

void fast_deque::pop_front()
{
	if (start_ptr < end_ptr)
	{
		start_ptr++;
	}
	else
	{
		throw "pop_front no room";
	}
}

void fast_deque::clear()
{
	start_ptr = end_ptr = 0;
}

void fast_deque::clone( fast_deque const &v )
{
	if (memory_available == 0 || is_memory_allocated)
	{
		if (memory != NULL)
		{
			::free(memory);
			memory = NULL;
		}
		memory = (dul *)malloc(v.memory_available * sizeof(dul));
		::memcpy(memory, v.memory, v.memory_available * sizeof(dul));
		end_ptr = v.end_ptr; 
		start_ptr = v.start_ptr; 
		memory_available = v.memory_available; 
		is_memory_allocated = true;
	}
	else
	{
		if (v.memory_available > memory_available)
		{
			throw "No room in clone";
		}
		::memcpy(memory, v.memory, v.memory_available * sizeof(dul));
		// is_memory_allocated = v.is_memory_allocated;
		end_ptr = v.end_ptr; 
		start_ptr = v.start_ptr; 
	}
}

void fast_deque::insertToBegin( dul const *ptr, size_t size )
{
	if (size <= start_ptr)
	{
		start_ptr -= size;
		::memcpy(memory+start_ptr, ptr, size * sizeof(dul));
	}
	else if (is_memory_allocated)
	{
		size_t nsize = align_up(memory_available + size);
		dul *new_allocated_memory = (dul *)malloc(nsize * sizeof(dul));
		::memcpy(new_allocated_memory+size, memory, memory_available * sizeof (dul));
		::free(memory);
		memory = new_allocated_memory;
		memory_available = nsize;
		::memcpy(memory, ptr, size * sizeof(dul));
		end_ptr += size;
	} 
	else 
	{
		throw "no room in insertToBegin";
	}
}

std::string fast_deque::toString() const
{
	string ret;
	for (size_t i = start_ptr; i < end_ptr; i++)
	{
		ret.push_back((char)(memory[i] + '0'));
	}
	return ret;
}

void fast_deque::init_alloc(size_t init_size)
{
	init_size = align_up(init_size);
	memory = (dul *)malloc(init_size * sizeof(dul));
	end_ptr = 0; 
	start_ptr = 0; 
	memory_available = init_size; 
	is_memory_allocated = true; // Сами заказали или нам её выдали.
}

void fast_deque::init( dul *room, size_t size, dul const *data, size_t dataSize )
{
	if (is_memory_allocated)
	{
		throw "This uses allocated memory in init";
	}
	memory = (dul *)room;
	end_ptr = 0; 
	start_ptr = 0; 
	memory_available = size; 
	is_memory_allocated = false; 
	if (data != NULL)
	{
		if (dataSize <= size)
		{
			::memcpy(memory, data, dataSize * sizeof(dul));
			end_ptr = dataSize;
		}
		else
		{
			throw "No room in fast_deque::init";
		}
	}
}

#endif
