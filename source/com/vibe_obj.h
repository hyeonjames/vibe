#ifndef _VIBE_OBJ_H
#define _VIBE_OBJ_H
#define UINTMAX	0xffffffff
#define INTMAX	0x7fffffff
namespace vibe
{

	template <typename T>
	class safe
	{
	protected:
		T* value;
	public:
		safe()
		{
			value = new T;
		}
		safe(safe<T>& v)
		{
			value = v.value;
			if (value != NULL){
				value->_reference();
			}
		}
		safe(T* val){
			value = val;
			if (value != NULL){
				val->_reference();
			}
		}
		
		virtual ~safe(){
			printf("safe delete\n");
			if (value != nullptr && value->_release() == 0) {
				delete value;
			}
		}
		T* operator->(){
			return value;
		}
	};
	
	class object
	{
		
	private:
		unsigned int _refc = 0;
		
	public:
		
		virtual unsigned int _reference();
		virtual unsigned int _release();
		virtual ~object(){

		}
	};

	
};
#endif