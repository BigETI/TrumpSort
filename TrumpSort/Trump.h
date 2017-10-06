#ifndef __TRUMP_H__
#	define __TRUMP_H__
#	include <vector>

// Make sorting algorithms great again
// https://medium.com/@gantlaborde/trump-sort-a-new-sorting-algorithm-b37b1133356a
namespace Trump
{
	// Sort with the power of walls
	template <class _T> std::vector<typename _T> trumpify(std::vector<typename _T> items, std::vector<typename _T> *minorities = nullptr)
	{
		std::vector<typename _T> ret;
		typename _T *wall = nullptr;
		if (minorities)
			minorities->clear();
		for (std::vector<typename _T>::iterator it(items.begin()), end(items.end()); it != end; ++it)
		{
			if (wall)
			{
				if ((*it) > (*wall))
				{
					ret.push_back(*it);
					wall = &(*it);
				}
				else if (minorities)
					minorities->push_back(*it);
			}
			else
			{
				ret.push_back(*it);
				wall = &(*it);
			}
		}
		return ret;
	}

	// Merge pre-sorted lists
	template <class _T> std::vector<typename _T> merge_presorted(std::vector<typename _T> & left, std::vector<typename _T> & right)
	{
		std::vector<typename _T> ret;
		size_t l(0U), r(0U), l_sz(left.size()), r_sz(right.size());
		while ((l < l_sz) && (r < r_sz))
		{
			if (left[l] < right[r])
				ret.push_back(left[l++]);
			else
				ret.push_back(right[r++]);
		}
		for (; l < l_sz; l++)
			ret.push_back(left[l]);
		for (; r < r_sz; r++)
			ret.push_back(right[r]);
		return ret;
	}

	// Sort combined with minorities
	template <class _T> std::vector<typename _T> sort(std::vector<typename _T> & items)
	{
		std::vector<typename _T> ret, majorities(items), t;
		do
		{
			t = trumpify(majorities, &majorities);
			ret = merge_presorted(ret, t);
		} while (!(majorities.empty()));
		return ret;
	}
}
#endif
