/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:19:12 by obouhrir          #+#    #+#             */
/*   Updated: 2024/01/08 18:01:53 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <deque>
#include <list>

using std::string;
using std::cout;
using std::endl;


class PmergeMe{
	private:
		//vector
		typedef std::vector<std::vector<int> > vector;
		typedef std::vector<int> vec;
		typedef std::vector<std::pair<vec, vector::iterator> > pend;

		vector mainchain;
		pend pendchain;
		vec con;
		vec struggler;
		//deque
		typedef std::list<std::list<int> > list;
		typedef std::list<int> li;
		typedef std::list<std::pair<li, list::iterator> > _pend;
		
		list _mainchain;
		_pend _pendchain;
		li _con;
		li _struggler;
		
		size_t	elementsize;
		size_t	_elementsize;
		
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe  &);
		void sort(char **, int);
		
		//vec
		void	main_pend(vector&);
		void	insert_pend_to_main();
		void MergeInsertion();
		void insertion();
		void fillContainer(double *, int);
		vector make_pairs();
		bool more_than_one_pair(vector &);
		void sort_pairs(vector &);
		void copy_arr_to_con(vector &);
		void update(vector::iterator);

		//deque
		void	main_pend1(list&);
		void	insert_pend_to_main1();
		void MergeInsertion1();
		void insertion1();
		list make_pairs1();
		bool more_than_one_pair1(list &);
		void sort_pairs1(list &);
		void copy_arr_to_con1(list &);
		void update1(list::iterator);
		~PmergeMe();
};


template <typename T>
void solution(T &con){

	typename T::iterator it = con.begin();
	for (;it != con.end();it++){
		cout << *it << " ";
	}
	cout << endl;
}