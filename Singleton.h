#pragma once

namespace util
{
	template<class T>
	class Singletion
	{
	public:
		//TODO var param list
		T& operator()()
		{
			static T singletion;
			return &singletion;
		}
	};
}
