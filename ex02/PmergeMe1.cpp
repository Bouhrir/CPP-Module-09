/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe1.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:31:24 by obouhrir          #+#    #+#             */
/*   Updated: 2024/01/08 17:57:15 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int count1 = 0;

void printlist(std::list<int> &li){
	std::list<int>::iterator it = li.begin();
	for (;it != li.end();++it){
		cout << *it << " ";
	}
	cout << "\n--------------------------" << endl;
}
void showcase(std::list<std::list<int> > &arr){
	cout << "listoflist" << endl;
	std::list<std::list<int> >::iterator it = arr.begin();
	for (;it != arr.end();it++){
		cout << "[ " ;
		std::list<int>::iterator i = it->begin();
		for (;i != it->end();i++){
			cout << *i << " ";
		}
		cout << "]\n";
	}
	cout << "end\n\n" << endl;
}

PmergeMe::list PmergeMe::make_pairs1(){
	list arr;
	li tmp;

	li::iterator it = _con.begin();
	for (;it != _con.end();){
		for (size_t i = 0;i < _elementsize && it != _con.end(); i++){
			tmp.push_back(*it);
			it++;
		}
		arr.push_back(tmp);
		tmp.clear();
	}
	return arr;
}

bool	compare1(std::list<int> const &v1, std::list<int> const &v2) {
	count1++;
	return (v1.back() < v2.back());
}

void PmergeMe::sort_pairs1(list &arr){
	li tmp;

	list::iterator second;
	list::iterator first = arr.begin();
	while (first != arr.end()){
		second = std::next(first);
		if (first->size() != _elementsize || second->size() != _elementsize)
			break;
		if (first->back() > second->back())
		{
			tmp = *first;
			*first = *second;
			*second = tmp;
		}
		count1++;
		first = std::next(second);
	}
}

void PmergeMe::copy_arr_to_con1(list &arr){
	_con.clear();
	list::iterator it = arr.begin();
	for (;it != arr.end();it++){
		li::iterator i = it->begin();
		for (;i != it->end();i++){
			_con.push_back(*i);
		}
	}
}
bool PmergeMe::more_than_one_pair1(list &arr){
	list::iterator it = arr.begin();
	std::advance(it, 2);
   	if (it->size() == _elementsize){
		++it;
		if (it->size() == _elementsize)
			return true;
	}
    return false;
}

void	PmergeMe::main_pend1(list& arr){
	std::pair<li, list::iterator > pair;

	if (arr.back().size() != _elementsize)
	{
		_struggler = arr.back();
		arr.pop_back();
	}
	_mainchain.clear();
	_pendchain.clear();

	//push b1 a1
	list::iterator it = arr.begin();
	
	_mainchain.insert(_mainchain.end(), *it);
	++it;
	_mainchain.insert(_mainchain.end(), *it);
	++it;
	for (; it != arr.end(); ){
		pair.first = *it;
		pair.second = _mainchain.end();
		it++;
		if (it != arr.end())
			pair.second = _mainchain.insert(_mainchain.end(), *it);
		_pendchain.push_back(pair);
		if (it == arr.end())
			break ;
		it++;
	}
}

void	PmergeMe::insert_pend_to_main1(){
	long int jacobsthal_diff[] = {
        2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
        11453246122, 22906492246, 45812984490
    };
	int j = 0;
	list::iterator lower;
	
	while(_pendchain.size()){

 		_pend::iterator it = _pendchain.begin();
 		_pend::iterator start = _pendchain.begin();
		for (int i = 0; i < jacobsthal_diff[j] - 1 && it != _pendchain.end(); i++)
			it++;
		if (it == _pendchain.end())
			it--;
		for(;;){
			lower = std::lower_bound(_mainchain.begin(), it->second, it->first, compare1);
			_mainchain.insert(lower, it->first);
			_pendchain.erase(it);
			if (it == start)
				break;
			it--;
		}
		j++;
	}
	if (_struggler.size())
	{
		_mainchain.push_back(_struggler);
		_struggler.clear();
	}
}

void PmergeMe::insertion1()
{
	list arr;
	
	arr = make_pairs1();
	main_pend1(arr);
	insert_pend_to_main1();
	copy_arr_to_con1(_mainchain);
	_elementsize /= 2; 
}

void PmergeMe::MergeInsertion1(){
	list arr;

	arr = make_pairs1();
	
	sort_pairs1(arr);
	copy_arr_to_con1(arr);
	if (more_than_one_pair1(arr)){
		_elementsize *= 2;
		MergeInsertion1();
	}
	insertion1();

}
