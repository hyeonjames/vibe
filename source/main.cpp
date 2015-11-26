#include<stdio.h>
#include "com/vibe_obj.h"
#include "com/vibe_data.h"
namespace vibe{
	class obj : public object
	{
	public:
		void print(){
			printf("hello");
		}
	};
}

int main(){
	/*
	vibe::ostack<vibe::obj> s(5, 100, 5);
	{
		vibe::poolsafe<vibe::obj> obj(new vibe::obj());
		s.push(obj);
		
	}

	s.pop();
	*/
	vibe::pool<vibe::obj> p(50);
	p.use([](vibe::obj& v)  {
		v.print();
	});
	return 0;
}