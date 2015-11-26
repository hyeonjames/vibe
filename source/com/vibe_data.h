#ifndef _VIBE_DATA_H
#define _VIBE_DATA_H
#include<functional>
namespace vibe
{
	// vibe 프레임 워크 데이터 부분

	// base 스택 , 기본적인 스택 기능만함
	template <typename T>
	class stack
	{
	private:
		T** _array;
		int _top;
		int _size;
		int _fullsize;
		int _step;
		void expand()
		{
			//delete[] _array;
			unsigned int __size = _size + _step;
			if (__size > _fullsize) {
				__size = _fullsize;
			}
			if (__size <= _size) {
				throw "stack expand overflow";
			}
			int i = 0 ;
			T** _temp = new T*[__size];
			while (i < _size){
				_temp[i] = _array[i];
				i++;
			}
			_size += _step;
			delete[] _array;
			_array = _temp;
		}
	public:
		stack(int min,int max,unsigned int expand)
		{
			_top = -1;
			_size = min;
			_fullsize = max;
			_step = expand;
			_array = new T*[min];
		}
		stack(int min,int max = INTMAX) : stack<T>(min, max, min)
		{

		}
		virtual ~stack()
		{
			delete[] _array;
		}
		int full(){
			return _fullsize;
		}
		int size(){
			return _top;
		}
		T& top()
		{
			if (_top < 0) {
				return nullptr;
			}
			return *(_array[_top]);
		}
		virtual T& pop()
		{
			if (_top < 0) {
				throw "stack overflow";
			}
			return *_array[_top--];
		}
		bool empty()
		{
			return _top < 0;
		}
		/* push T return top*/
		virtual int push(T& v)
		{
			if (_top >= _size) {
				expand();
			}
			_array[++_top] = &v;
			return _top;
		}
	};

	
	template<typename T>
	class ostack : public stack<safe<T>>
	{
	public:
		ostack(int min, int max, int expand) 
			:stack<safe<T>>(min,max,expand)
		{

		}
		ostack(int min,int max=UINTMAX)
			:stack<safe<T>>(min, max, min)
		{

		}
		virtual ~ostack()
		{

		}
		safe<T>& pop()
		{
			safe<T>& r = stack<safe<T>>::pop();
			r->_release();
			return r;
		}
		unsigned int push(safe<T>& v) {
			v->_reference();
			return stack<safe<T>>::push(v);
		}
	};


	template <typename T>
	class pool : stack<T>
	{
	private:
		T& get()
		{
			printf("GET!\n");
			if (stack<T>::empty()) {
				stack<T>::push(*new T);
			}
			return stack<T>::pop();
		}
		void ret(T& v) // 반환
		{
			printf("RET!\n");
			stack<T>::push(v);
		}
	public:
		pool(int min, int max) : stack<T>(min,max,min) {

		}
		pool(int min) : pool<T>(min, UINT_MAX)
		{

		}
		pool() : pool<T>(0)
		{

		}
		virtual ~pool()
		{

		}
		virtual void use(std::function<void(T&)> func)
		{
			T& t=get();
			func(t);
			ret(t);
		}
	};
}
#endif