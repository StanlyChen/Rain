#pragma once
#include <list>
#include <map>
#include <algorithm>

namespace util
{
	template<class T>
	class OrderList
	{

	public:
		using ORDER_TYPE = std::list<T>;
		using UNIQUE_TYPE = std::map<T, typename ORDER_TYPE::iterator>;
		ORDER_TYPE m_list;
		UNIQUE_TYPE m_uniques;

	public:
		using iterator = typename ORDER_TYPE::iterator;
		using const_iterator = typename ORDER_TYPE::const_iterator;

		iterator begin()
		{
			return m_list.begin();
		}

		iterator end()
		{
			return m_list.end();
		}

		const_iterator begin() const
		{
			return m_list.begin();
		}

		const_iterator end() const
		{
			return m_list.end();
		}

		size_t size()
		{
			return m_uniques.size();
		}

		std::pair<iterator, bool> push_back(const T& obj)
		{
			auto it_uniq = m_uniques.find(obj);
			if (it_uniq == m_uniques.end())
			{
				m_list.push_back(obj);
				//TODO better performance 
				iterator it_list = std::next( m_list.begin(), m_list.size()-1 );
				m_uniques.insert(std::make_pair(obj, it_list));
				return std::make_pair(it_list, true);
			}
			else
			{
				return std::make_pair( it_uniq->second, false);
			}
		}

		std::pair<iterator, bool> push_front(const T& obj)
		{
			auto it_uniq = m_uniques.find(obj);
			if (it_uniq == m_uniques.end())
			{
				m_list.push_front(obj);
				iterator it_list = m_list.begin();
				m_uniques.insert(std::make_pair(obj, it_list));
				return std::make_pair(it_list, true);
			}
			else
			{
				return std::make_pair(it_uniq->second, false);
			}
		}

		iterator find(const T& obj)
		{
			auto it_uniq = m_uniques.find(obj);
			if (it_uniq != m_uniques.end())
			{
				return it_uniq->second;
			}
			return m_list.end();
		}

		const_iterator find(const T& obj) const
		{
			auto it_uniq = m_uniques.find(obj);
			if (it_uniq != m_uniques.end())
			{
				return it_uniq->second;
			}
			return m_list.end();
		}

		bool erase(const T& obj)
		{
			auto it_uniq = m_uniques.find(obj);
			if (it_uniq != m_uniques.end())
			{
				m_list.erase( it_uniq->second );
				m_uniques.erase(it_uniq);
				return true;
			}
			return false;
		}

		bool erase(const iterator& iter)
		{
			if (m_list.erase(iter))
			{
				m_uniques.erase(*iter);
				return true;
			}
			return false;
		}

        void clear()
        {
            m_list.clear();
            m_uniques.clear();
        }

	};
}
