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
	//��������Ϊ�麯��
protected:
	virtual ~Reference() {}
private:
	int _count;
	std::mutex _mutex;
};
//���ü�����һ
int Reference::ref()
{
	_mutex.lock();
	++_count;
	_mutex.unlock();
	return _count;
}
//�����ü�����һ��Ϊ�������
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
