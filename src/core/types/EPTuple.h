#ifndef EP_TUPLE_H_
#define EP_TUPLE_H_

#include "core/ehm/result.h"

// epoch function
// epoch/src/core/types/EPTuple.h

#include <utility>
#include <type_traits>

#include "core/types/EPObj.h"

template <size_t index, typename T>
class tuple_implementation {
public:
	tuple_implementation() :
		m_value()
	{}

	tuple_implementation(T const& lval) :
		m_value(lval)
	{}

	tuple_implementation(T&& lval) {
		m_value = std::move(lval);
	}

	// Defaults
	virtual ~tuple_implementation() = default;
	tuple_implementation& operator= (const tuple_implementation&) = default;
	tuple_implementation& operator= (tuple_implementation&&) = default;

	T& get() {
		return m_value;
	}

	//const T& get() const {
	//	return m_value;
	//}

private:
	T m_value;
};

// Base
template <size_t index, typename... TArgs>
class tuple_recurring_base
{
	// 
};

// Specialization
template <size_t index, typename T, typename... TArgs>
class tuple_recurring_base<index, T, TArgs...> : 
	public tuple_implementation<index, T>,
	public tuple_recurring_base<index + 1, TArgs...>
{
public:
	tuple_recurring_base() 
	{
		//
	}

	template<typename CType, typename... CArgs>
	tuple_recurring_base(CType &&arg, CArgs && ... args) :
		tuple_implementation<index, CType>(static_cast<CType&&>(arg)),
		tuple_recurring_base<index + 1, CArgs...>(static_cast<CArgs&&>(args)...)
	{
		// 
	}

};


template <typename... TArgs>
class EPTuple : public tuple_recurring_base<0, TArgs...>
{
public:
	EPTuple() 
	{
		// 
	}

	template <typename... CArgs>
	EPTuple(CArgs && ... args) :
		tuple_recurring_base<0, TArgs...>(static_cast<TArgs&&>(args)...)
	{
		// 
	}

	template <size_t index, typename GType>
	GType& get() {
		return static_cast<tuple_implementation<index, GType>*>(this)->get();
	}

	//template <size_t index, typename GType>
	//GType& get() const {
	//	return static_cast<tuple_implementation<index, GType>*>(this)->get();
	//}

private:
	
};

#endif // ! EP_TUPLE_H_