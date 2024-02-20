#include "PmergeMe.hpp"

int count = 0;

void showcase(std::vector<std::vector<int> > &arr){
	cout << "vecofvec" << endl;
	std::vector<std::vector<int> >::iterator it = arr.begin();
	for (;it < arr.end();it++){
		cout << "[ " ;
		std::vector<int>::iterator i = it->begin();
		for (;i < it->end();i++){
			cout << *i << " ";
		}
		cout << "]\n";
	}
	cout << "end\n\n" << endl;
}


PmergeMe::PmergeMe(){
	elementsize = 1;
	_elementsize = 1;
}
PmergeMe::PmergeMe(const PmergeMe &a){
	*this = a;
}
PmergeMe &PmergeMe::operator=(const PmergeMe __unused &a){
	return *this;
}

bool isnmb(string &nmb){
	int i = 0;
	if (nmb[i] == '+')
		i++;
	for (;nmb[i];i++){
		if (!std::isdigit(nmb[i]))
			return false;
	}
	return true;
}

PmergeMe::vector PmergeMe::make_pairs(){
	vector arr;
	vec tmp;

	vec::iterator it = con.begin();
	for (;it < con.end();){
		for (size_t i = 0;i < elementsize && it < con.end(); i++){
			tmp.push_back(*it);
			it++;
		}
		arr.push_back(tmp);
		tmp.clear();
	}
	return arr;
}

bool	compare(std::vector<int> const &v1, std::vector<int> const &v2) {
	count++;
	return (v1.back() < v2.back());
}

void PmergeMe::sort_pairs(vector &arr){
	vec tmp;

	vector::iterator second;
	vector::iterator first = arr.begin();
	while (first != arr.end()){
		second = first + 1;
		if (first->size() != elementsize || second->size() != elementsize)
			break;
		if (first->back() > second->back())
		{
			tmp = *first;
			*first = *second;
			*second = tmp;
		}
		count++;
		first += 2;
	}
}

void PmergeMe::copy_arr_to_con(vector &arr){
	con.clear();
	vector::iterator it = arr.begin();
	for (;it < arr.end();it++){
		vec::iterator i = it->begin();
		for (;i < it->end();i++){
			con.push_back(*i);
		}
	}
}
bool PmergeMe::more_than_one_pair(vector &arr){
	int i = 0;
	if (arr[i].size() == elementsize && arr[i + 1].size() == elementsize &&
		arr[i + 2].size() == elementsize && arr[i + 3].size() == elementsize)
		return true;
	return false;
}

void	PmergeMe::main_pend(vector& arr){

	if (arr.back().size() != elementsize)
	{
		struggler = arr.back();
		arr.pop_back();
	}

	mainchain.clear();
	pendchain.clear();

	mainchain.reserve(con.size());
	pendchain.reserve(con.size());

	//push b1 a1
	mainchain.insert(mainchain.end(), arr[0]);
	mainchain.insert(mainchain.end(), arr[1]);

	std::pair<vec, vector::iterator > pair;

	for (size_t i = 2; i < arr.size();){
		pair.first = arr[i];
		pair.second = mainchain.end();
		i++;
		if (i < arr.size())
			pair.second = mainchain.insert(mainchain.end(), arr[i]);
		pendchain.push_back(pair);
		i++;
	}
}

void PmergeMe::update(vector::iterator it){
	pend::iterator i = pendchain.begin();
	for (;i < pendchain.end(); i++){
		if (i->second >= it)
			i->second++;
	}
}

void	PmergeMe::insert_pend_to_main(){
	long int jacobsthal_diff[] = {
        2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
        11453246122, 22906492246, 45812984490
    };
	int j = 0;
	vector::iterator lower;
	vector::iterator pos;
	while(pendchain.size()){

 		pend::iterator it = pendchain.begin();
		for (int i = 0; i < jacobsthal_diff[j] && it != pendchain.end();i++)
			it++;
		if (it == pendchain.end())
			it--;
		for(;;){
			lower = std::lower_bound(mainchain.begin(), it->second, it->first, compare);
			pos = mainchain.insert(lower, it->first);
			pendchain.erase(it);
			update(pos);
			if (it == pendchain.begin())
				break;
			it--;
		}
		j++;
	}
	if (struggler.size())
	{
		mainchain.push_back(struggler);
		struggler.clear();
	}
}

void PmergeMe::insertion()
{
	vector arr;
	arr = make_pairs();
	main_pend(arr);
	insert_pend_to_main();
	copy_arr_to_con(mainchain);
	elementsize /= 2;
}

void PmergeMe::MergeInsertion(){
	vector arr;

	arr = make_pairs();

	sort_pairs(arr);
	copy_arr_to_con(arr);
	if (more_than_one_pair(arr)){
		elementsize *= 2;
		MergeInsertion();
	}
	insertion();
}

void PmergeMe::fillContainer(double *fill, int size){
	for (int i = 0;i < size;i++){
		con.push_back(fill[i]);
		_con.push_back(fill[i]);
	}	
}
void arg(double *fill, int size){
	for (int i = 0;i < size;i++){
		cout << fill[i] << " ";
	}
}


//----------------------
void PmergeMe::sort(char **av, int ac){
	int __unused i = 1, j = 0, element = ac - 1;

	double *fill = new double[ac - 1];
	while (av[i]){
		string tmp = av[i];
		std::stringstream in(tmp);
		string nmb;

		in >> nmb;
		if (!isnmb(nmb))
			throw std::invalid_argument("Error: invalid number");
		fill[j] = std::strtod(av[i], NULL);
		i++;
		j++;
	}
	fillContainer(fill, ac - 1);
	if (con.size() == 1)
		return ;
	cout << "Before: "; arg(fill, ac -1); cout << endl;
	//vec algorithm
	{
		clock_t start = clock(); // Record the start time
		MergeInsertion();
    	clock_t end = clock(); // Record the end time
    	double sec = double(end - start) / CLOCKS_PER_SEC;
		cout << "after: "; solution(con);
		cout << "Time to process a range of "<< element << " elements with std::vector : "<< sec <<" us\n";
	}
	//deque
	{
		// solution(_con);
		clock_t start = clock(); // Record the start time
		MergeInsertion1();
		clock_t end = clock(); // Record the end time
		double sec = double(end - start) / CLOCKS_PER_SEC;
		cout << "Time to process a range of "<< element << " elements with std::list : "<< sec <<" us\n";
	}
}

PmergeMe::~PmergeMe(){

}