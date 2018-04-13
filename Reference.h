#ifndef REFERENCR_H
#define REFERENCR_H
#include <mutex>
class Reference
{
public:
	Reference() :_count(0) {}
	

	inline int ref();
	inline int unref();
	int refCount() { return _count; }
	//析构函数为虚函数
protected:
	virtual ~Reference() {}
private:
	int _count;
	std::mutex _mutex;
};
//引用计数加一
int Reference::ref()
{
	_mutex.lock();
	++_count;
	_mutex.unlock();
	return _count;
}
//解引用技术减一，为零就析构
int Reference::unref()
{
	_mutex.lock();
	--_count;
	_mutex.unlock();
	if (_count == 0)
		delete this;
	return _count;
}
#endif //REFERENCR_H
