#ifndef SMART_PTR_H
#define SMART_PTR_H
template<class T>
class smart_ptr
{
public:
	typedef T element_type;
	smart_ptr() :_ptr(0) {}
	smart_ptr(T* ptr) :_ptr(ptr) { if (_ptr) _ptr->ref(); }
	smart_ptr(const smart_ptr& ptr) :_ptr(ptr._ptr) { if (_ptr) _ptr->ref(); }
	template<class Other> smart_ptr(const smart_ptr<Other>& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }
	~smart_ptr() { if (_ptr) _ptr->unref(); _ptr = nullptr; }

	smart_ptr& operator= (const smart_ptr& rp)
	{
		assign(rp);
		return *this
	}
	template<class Other> smart_ptr& operator=(const smart_ptr<Other>& rf)
	{
		assign(rf);
		return *this;
	}
	inline smart_ptr& operator =(T* ptr)
	{
		if (_ptr == ptr)
			return *this;
		T* temp_ptr = _ptr;
		_ptr = ptr;
		if (_ptr)
			_ptr->ref();
		if (temp_ptr)
			temp_ptr->unref();
		return *this;
	}
	T* operator ->() const { return _ptr; }
	T& operator*() const { return *_ptr; }
	T* get() const { return _ptr; }
	bool operator!() const { return _ptr == 0; }
	bool valid() const { return _ptr != 0; }

	bool operator==(smart_ptr& rf) { return _ptr == rf._ptr; }
	bool operator==(T* ptr) { return _ptr == ptr; }
	friend bool operator==(const T* ptr, const smart_ptr& rf) { return ptr == rf._ptr;}
	bool operator!=(smart_ptr& rf) { return _ptr != rf._ptr; }
	bool operator!=(T* ptr) { return _ptr != ptr; }
	friend bool operator!=(const T* ptr, const smart_ptr& rf) { return ptr != rf._ptr; }
	void swap(smart_ptr& rp)
	{
		T* tem_ptr = _ptr;
		_ptr = rp._ptr;
		rp._ptr = tem_ptr;
	}
	bool operator == (const smart_ptr& rp) const { return _ptr == rp._ptr; }
private:
	template<class Other> void assign(const smart_ptr<Other>& rp)
	{
		if (_ptr == rp._ptr)
			return;
		T* tmp_ptr = _ptr;
		_ptr = rp._ptr;
		if (_ptr)
			_ptr->ref();
		if (tmp_ptr)
			tmp_ptr->unref();
	}
private:
	T* _ptr;
};
template<typename T> inline
void swap(smart_ptr<T>& rp1, smart_ptr<T>& rp2) { rp1.swap(rp2); }
template<typename T> inline
T* get_pointer(const smart_ptr<T>& rp) { return rp.get(); }
template<typename T,typename Y> inline
smart_ptr<T> static_pointer_cast(const smart_ptr<Y>& rp) { return static_cast<T*>(rp.get()); }
template<typename T, typename Y> inline
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<Y>& rp) { return dynamic_cast<T*>(rp.get()); }
template<typename T, typename Y> inline
smart_ptr<T> const_pointer_cast(const smart_ptr<Y>& rp) { return const_cast<T*>(rp.get()); }

#endif//SMART_PTR_H
